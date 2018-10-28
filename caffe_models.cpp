#include "caffe_models.h"

caffe_models::caffe_models() : model_file("/home/john/caffe/models/bvlc_googlenet/google_deploy.prototxt"),    \
                           trained_model("/home/john/caffe/models/bvlc_googlenet/bvlc_googlenet_9ed_iter_100000.caffemodel"),    \
                           mean_file("/home/john/caffe/data/jieblack/cnnimgs/mean_Enhance2.binaryproto"),    \
                           label_file("/home/john/caffe/data/jieblack/cnnimgs/synset_words.txt")
{
    //ctor
}

caffe_models::~caffe_models()
{
    //dtor
}


faster_rcnn_models::faster_rcnn_models() : model_file("/home/john/py-faster-rcnn/models/pascal_voc/VGG16/faster_rcnn_alt_opt/faster_rcnn_test.pt"),    \
										   trained_model("/home/john/py-faster-rcnn/data/faster_rcnn_models/VGG16_faster_rcnn_final.caffemodel")
{
	//ctor
}

faster_rcnn_models::~faster_rcnn_models()
{
	//ctor
}
