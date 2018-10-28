#include "db_connect.h"
#include "pg_database.h"
#include "mysql_database.h"
#include "img_process.h"
//#include "caffe_models.h"
//#include "caffe_classifier.h"
#include "boost/thread.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/bind.hpp"
//#include "./lib/faster_rcnn.hpp"


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


int main(int, char *argv[])
{
    //::google::InitGoogleLogging(argv[0]);

    std::vector<img_data> tmp_img_container;

	// for mysql test
	PushContainer(&tmp_img_container);

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
