#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H

#include <fstream>
#include <iostream>
#include "opencv.hpp"
#include "dt_data.h"


using namespace cv;
using namespace std;


class img_process
{
public:
    img_process();
    virtual ~img_process();

public:
    // test codeblocks with opencv3.3
    void ImgTest(void);

    // save img in local path(for postgresql)
    int WriteImg(img_data& src_img);
    // 将数据库存储的二进制数据转换成RGB图像数据
    void BinadataToRGB(unsigned char* out_rgb,char* in_rgb,int width,int height,int width_step);
	// 数据库二进制文件直接保存成jpg图像
	void GenerateJpg(string jpg_path,char* data_buf,int length);
	// 十六进制数转换成十进制数
	int Hex2Dec(char hex_char);

	// save img to local path(for mysql)
	void WriteBlobImg(img_data& src_img);

public:
	cv::Mat UnsharpMask(std::string file_path,cv::Mat& src_img,int un_radius,int un_amount);

protected:

private:
    int img_num;
	img_data saved_img;
	int count;

};

#endif // IMG_PROCESS_H
