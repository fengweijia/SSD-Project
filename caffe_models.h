#ifndef CAFFE_MODELS_H
#define CAFFE_MODELS_H

#include <string>

using namespace std;

// config caffe model file and path;
class caffe_models
{
public:
    caffe_models();
    virtual ~caffe_models();

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

protected:

private:
    string model_file;
    string trained_model;
    string mean_file;
    string label_file;

};


// config faster rcnn model file and weights
class faster_rcnn_models
{
public:
	faster_rcnn_models();
	~faster_rcnn_models();

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
	inline string get_lable_file()
	{
		return lable_file;
	}

protected:

private:
	string model_file;
	string trained_model;
	string mean_file;
	string lable_file;

};

#endif // CAFFE_MODELS_H
