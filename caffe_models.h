#ifndef CAFFE_MODELS_H
#define CAFFE_MODELS_H

#include <string>

using namespace std;


// models file base class
class models
{
public:
    models(){}
    virtual ~models(){}

public:
    inline string get_model_file()
    {
        return model_file;
    }
    inline string get_trained_model()
    {
        return trained_model;
    }
    inline string get_mean_file()
    {
        return mean_file;
    }
    inline string get_label_file()
    {
        return label_file;
    }

public:
    string model_file;
    string trained_model;
    string mean_file;
    string label_file;
};


// config caffe model file and path
class caffe_models : public models
{
public:
    caffe_models();
    ~caffe_models();

};


// config vgg-ssd caffe model file and path
class ssd_models : public models
{
public:
    ssd_models();
    ~ssd_models();

};


// config faster rcnn model file and weights
class faster_rcnn_models : public models
{
public:
    faster_rcnn_models();
    ~faster_rcnn_models();

};

#endif // CAFFE_MODELS_H
