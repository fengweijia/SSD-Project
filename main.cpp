#include "db_connect.h"
#include "pg_database.h"
#include "mysql_database.h"
#include "img_process.h"
#include "caffe_models.h"
#include "caffe_classifier.h"
#include "ssd_classifier.h"
#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/bind.hpp"
//#include "./lib/faster_rcnn.hpp"

using namespace caffe;

DEFINE_string(mean_file, "",
"The mean file used to subtract from the input image.");
DEFINE_string(mean_value, "104,117,123",
"If specified,can be one value or can be same as image channels"
"- would subtract from the corresponding channel. Separated by ','."
"Either mean_file or mean_value should be provided, not both.");
DEFINE_string(file_type, "iamge",
"The file type in the list_file. Currently support image and video.");
DEFINE_string(out_file, "",
"If provided,store the detection results in the out_file.");
DEFINE_double(confidence_threshold, 0.01,
"Only store detections with score highter than the threshold.");

boost::mutex container_mutex;


void PushContainer(std::vector<img_data>* img_container)
{
    mysql_connect mysql_conn;
    img_process img_processer;

    char* result_num_str;
    char* insert_num_str;

    // 根据数据库中DetectResult table中的数目是否与Image table中的数目一致，来获取新添加的待检测图像
    mysql_conn.CountData();
    result_num_str = mysql_conn.get_result_num_str();
    insert_num_str = mysql_conn.get_img_num_str();
	//char* insert_image;
	//char* result_detect;
	int insert_num = static_cast<int>(strtol(insert_num_str,NULL,10));
	int result_num = static_cast<int>(strtol(result_num_str,NULL,10));
    if(result_num < insert_num)
    {
        mysql_conn.ConnectDatabase();
    }

    //boost::mutex::scoped_lock lock(container_mutex);
    *img_container = mysql_conn.get_query_img();
    if(img_container->size() > 0)
    {
        int i =0;
        for(; i < img_container->size(); i++)
        {
            img_processer.WriteBlobImg(img_container->at(i));
        }
    }

}


// Detect and classify images(video) with SSD caffe models
void DClassifyContainer(std::vector<img_data>* img_container)
{
    mysql_connect mysql_conn;
    img_data predict_data;
    ssd_models model_file;

    const string& mean_file = FLAGS_mean_file;
    const string& mean_value = FLAGS_mean_value;
    const string& file_type = FLAGS_file_type;
    const string& out_file = FLAGS_out_file;
    const float confidence_threshold = FLAGS_confidence_threshold;

    predict_data.event_id = "115";
    Detector detect_classifier(model_file.get_model_file(),model_file.get_trained_model(),mean_file,mean_value);
    
    // Set the output mode
    std::streambuf* buf = std::cout.rdbuf();
    std::ofstream outfile;
    if(!out_file.empty()){
        outfile.open(out_file.c_str());
        if(outfile.good()){
            buf = outfile.rdbuf();
        }
    }
    std::ostream out(buf);

    // Load lables file
    const string& label_file = model_file.get_label_file();
    std::ifstream labels(label_file.c_str());
    CHECK(labels) << "Unable to open labels file" << label_file;
    string line;
    while(std::getline(labels,line)){
        detect_classifier.set_labels_in(line);
    }

    // Process image one by one
    std::ifstream infile("testimg.txt");
    std::string file;
    std::string img_name;

    int count = 0;
    while(infile >> file)
    {
        std::cout << file << " " << count++ << std::endl;
        int pos = file.find_last_of('/');
        img_name = file.substr(pos + 1,file.size() - pos);

        cv::Mat img = cv::imread(file,-1);
        CHECK(!img.empty()) << "Unable to decode image" << file;
        std::vector<vector<float> > detections = detect_classifier.Detect(img);

        // Print the detection result
        for(int i = 0; i < detections.size(); i++){
            const vector<float>& img_dection = detections[i];
            // Detection format: [image_id, label, score, xmin, ymin, xmax, ymax]
            CHECK_EQ(img_dection.size(), 7);
            const float score = img_dection[2];
            string score_str = to_string(score).substr(0,5);
            if(score >= confidence_threshold){
                out << file << " ";
                out << static_cast<int>(img_dection[1]) << " ";
                predict_data.detect_conf_value = score;
                predict_data.detect_type_id = static_cast<int>(img_dection[1]);
                out << score << " ";
                out << static_cast<int>(img_dection[3] * img.cols) << " ";
                out << static_cast<int>(img_dection[4] * img.rows) << " ";
                out << static_cast<int>(img_dection[5] * img.cols) << " ";
                out << static_cast<int>(img_dection[6] * img.rows) << " ";
                predict_data.bb_x = static_cast<int>(img_dection[3] * img.cols);
                predict_data.bb_y = static_cast<int>(img_dection[4] * img.rows);
                predict_data.bb_width = static_cast<int>(img_dection[5] * img.cols);
                predict_data.bb_height = static_cast<int>(img_dection[6] * img.rows);
                out << endl;

                mysql_conn.InsertTableData(predict_data.event_id.c_str(),predict_data);

//                cv::rectangle(img,cv::Point(static_cast<int>(img_dection[3] * img.cols),static_cast<int>(img_dection[4] * img.rows)),cv::Point(static_cast<int>(img_dection[5] * img.cols),static_cast<int>(img_dection[6] * img.rows)),cv::Scalar(255,0,0),1,1,0);
//                cv::putText(img,detect_classifier.get_labels_from(static_cast<int>(img_dection[1])) + score_str,cv::Point(static_cast<int>(img_dection[3] * img.cols),static_cast<int>(img_dection[4] * img.rows + 10)),FONT_HERSHEY_PLAIN,1,cv::Scalar(0,255,0));
//                cv::imwrite("test.jpg",img);
            }
        }
    }
   
}


// Detect images with GoogleNet caffe models
void PredictContainer(std::vector<img_data>* img_container)
{
    db_connect pg_conn;
    caffe_models model_file;
	//faster_rcnn_models faster_model_file;

	//int gpu_id = 0;
	//Caffe::SetDevice(gpu_id);
	//Caffe::set_mode(Caffe::GPU);
	//Detector faster_det = Detector(faster_model_file.get_model_file(),faster_model_file.get_trained_model());

    caffe_classifier blacklung_classifier(model_file.get_model_file(),    \
                                          model_file.get_trained_model(),    \
                                          model_file.get_mean_file(),    \
                                          model_file.get_label_file());

    // caffemodel detect
    img_data predict_data;
    // default blacklung detect
    predict_data.detect_type_id = 1;
    //predict_data.detect_flag = "Y";

    //boost::mutex::scoped_lock lock(container_mutex);
    if(img_container->size() > 0)
    {
        int i = 0;
        std::vector<Prediction> classify_predict;
        for(; i < img_container->size(); i++)
        {
            string detect_img_name = img_container->at(i).event_id + ".jpg";
			detect_img_name = predict_data.img_path + detect_img_name; 

			/*cv::Rect chest_roi = faster_det.Detect(detect_img_name);
			if(chest_roi.width != 0 && chest_roi.height != 0)
			{
				std::cout << "Chest: " << chest_roi.x << "," << chest_roi.y << "," << chest_roi.width << "," << chest_roi.height << std::endl;
			}*/
            cv::Mat src_img = cv::imread(detect_img_name);

            classify_predict = blacklung_classifier.BlacklungClassify(src_img);
            string tmp_str = classify_predict[0].first;

            predict_data.detect_conf_id = pg_conn.SelectTableData(tmp_str.c_str(),predict_data.detect_type_id);
            predict_data.detect_conf_value = classify_predict[0].second;

            tmp_str = img_container->at(i).event_id;
            pg_conn.InsertTableData(tmp_str.c_str(),predict_data);
            pg_conn.UpdateTableData(tmp_str.c_str(),predict_data);
            img_container->pop_back();
        }
    }
}


int main(int, char *argv[])
{
    //::google::InitGoogleLogging(argv[0]);

    std::vector<img_data> tmp_img_container;

	// for mysql test
	//PushContainer(&tmp_img_container);
    DClassifyContainer(&tmp_img_container);

//    while(true)
//    {
//        boost::thread img_thread(boost::bind(&PushContainer,&tmp_img_container));
//        img_thread.join();
//        boost::thread predict_thread(boost::bind(&PredictContainer,&tmp_img_container));
//        predict_thread.join();
//
//        sleep(10);
//    }

    return 0;
}
