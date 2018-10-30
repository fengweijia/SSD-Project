#include "caffe_models.h"


caffe_models::caffe_models()
{
    //ctor
    model_file = "/home/****/caffe/models/bvlc_googlenet/google_deploy.prototxt";
    trained_model = "/home/****/caffe/models/bvlc_googlenet/bvlc_googlenet_9ed_iter_100000.caffemodel";
    mean_file = "/home/****/caffe/data/jieblack/cnnimgs/mean_Enhance2.binaryproto";
    label_file = "/home/****/caffe/data/jieblack/cnnimgs/synset_words.txt";

}

caffe_models::~caffe_models()
{
    //dtor
}


ssd_models::ssd_models()
{
    //ctor
    model_file = "/home/john/Project/caffe/models/VGGNet/VOCmydb/SSD_mydb300x300/deploy.prototxt";
    trained_model = "/home/john/Project/caffe/models/VGGNet/VOCmydb/SSD_mydb300x300/VGG_VOCmydb_SSD_mydb300x300_iter_12000.caffemodel";
    label_file = "/home/john/Project/caffe/models/VGGNet/VOCmydb/SSD_mydb300x300/label_words.txt";

}

ssd_models::~ssd_models()
{
    //dtor
}


faster_rcnn_models::faster_rcnn_models()
{
    //ctor
    model_file = "/home/****/py-faster-rcnn/models/pascal_voc/VGG16/faster_rcnn_alt_opt/faster_rcnn_test.pt";
    trained_model = "/home/****/py-faster-rcnn/data/faster_rcnn_models/VGG16_faster_rcnn_final.caffemodel";

}

faster_rcnn_models::~faster_rcnn_models()
{
	//ctor
}
