#ifndef SSD_CAFFE_MODEL
#define SSD_CAFFE_MODEL

#include <caffe/caffe.hpp>
//#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#endif  // USE_OPENCV
#include <algorithm>
#include <iomanip>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

//#ifdef USE_OPENCV
using namespace caffe;  // NOLINT(build/namespaces)

class Detector {
 public:
  Detector(const string& model_file,
           const string& weights_file,
           const string& mean_file,
           const string& mean_value);

  std::vector<vector<float> > Detect(const cv::Mat& img);

  inline string get_labels_from(int i)
  {
      return labels_[i];
  }

  inline void set_labels_in(std::string tmp_label)
  {
      labels_.push_back(tmp_label);
  }

 private:
  void SetMean(const string& mean_file, const string& mean_value);

  void WrapInputLayer(std::vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img,
                  std::vector<cv::Mat>* input_channels);

 private:
  shared_ptr<Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
  // Detect labels 
  std::vector<string> labels_;
};

//#endif // USE_OPENCV

#endif // SSD_CAFFE_MODEL
