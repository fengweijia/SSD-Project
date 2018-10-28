#ifndef CAFFE_CLASSIFIER_H
#define CAFFE_CLASSIFIER_H

#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace caffe;  // NOLINT(build/namespaces)
using std::string;

/* Pair (label, confidence) representing a prediction. */
typedef std::pair<string, float> Prediction;


// cooy the same file with /home/john/caffe/examples/cpp_classification/classification.cpp
class caffe_classifier
{
public:
    caffe_classifier(const string& model_file,
                     const string& trained_file,
                     const string& mean_file,
                     const string& label_file);

    virtual ~caffe_classifier();

public:
    std::vector<Prediction> Classify(const cv::Mat& img, int N = 5);
    std::vector<Prediction> BlacklungClassify(cv::Mat& img);

protected:

private:
    void SetMean(const string& mean_file);
    std::vector<float> Predict(const cv::Mat& img);
    void WrapInputLayer(std::vector<cv::Mat>* input_channels);
    void Preprocess(const cv::Mat& img,
                    std::vector<cv::Mat>* input_channels);

private:
    shared_ptr<Net<float> > net_;
    cv::Size input_geometry_;
    int num_channels_;
    cv::Mat mean_;
    std::vector<string> labels_;

};

#endif // CAFFE_CLASSIFIER_H
