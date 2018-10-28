#include "img_process.h"

img_process::img_process() : count(0)
{
    //ctor
}

img_process::~img_process()
{
    //dtor
}


void img_process::ImgTest(void)
{
    cv::Mat img = cv::imread("test.jpg");
    cv::imshow("Test",img);
    cv::waitKey(1000);
}


int img_process::WriteImg(img_data& src_img)
{
    cv::Mat jpg_img(src_img.img_height,src_img.img_width,CV_8UC3);
    //char* tmp_data = new char[src_img.img_data_str.size() + 1];
    char* tmp_data = new char[src_img.img_length + 1];

    //std::copy(src_img.img_data_str.begin(),src_img.img_data_str.end(),tmp_data);
	memcpy(tmp_data,src_img.img_data_str,src_img.img_length + 1);
    tmp_data[src_img.img_length] = '\0';

    BinadataToRGB(jpg_img.data,tmp_data,src_img.img_width,src_img.img_height,jpg_img.step);

    string jpg_img_name = src_img.event_id + ".jpg";
    jpg_img_name = saved_img.img_path + jpg_img_name;

	cv::Mat un_jpg_img;
	int dx_cr_result = std::strcmp(src_img.img_type.c_str(),"DX");
	if(dx_cr_result == 0)
	{
		un_jpg_img = UnsharpMask(jpg_img_name,jpg_img,201,50);
	}
	else
	{
		un_jpg_img = UnsharpMask(jpg_img_name,jpg_img,201,150);

	}

    cv::imwrite(jpg_img_name,un_jpg_img);

    delete tmp_data;
    tmp_data = NULL;
}


void img_process::BinadataToRGB(unsigned char* out_rgb,char* in_rgb,int width,int height,int width_step)
{
		int col,row;
		unsigned char r,g,b;
		int idx;
		int a_pixel_value;
		int b_pixel_value;

		for (row = 0; row < height; row++)
		{
			idx = row * width_step;
            int count = 0;
			// \xab52,bytea二进制图像数据以十六进制输出，一个像素8位，2个十六进制数
			for (col = 2; col < width * 2;)
			{
				a_pixel_value = Hex2Dec(in_rgb[width * row * 2 + col]);
				b_pixel_value = Hex2Dec(in_rgb[width * row * 2 + col + 1]);
				a_pixel_value = 16 * a_pixel_value + b_pixel_value;

				//r = (unsigned char)in_rgb[width * row + col];			
				//g = (unsigned char)in_rgb[width * row + col];
				//b = (unsigned char)in_rgb[width * row + col];

				out_rgb[idx + count * 3] = a_pixel_value;
				out_rgb[idx + count * 3 + 1] = a_pixel_value;
				out_rgb[idx + count * 3 + 2] = a_pixel_value;

				col += 2;
				count++;
			}
		}
}


int img_process::Hex2Dec(char hex_char)
{
	int dec_value;

	if(hex_char >= 'a' && hex_char <= 'f')
	{
		dec_value = hex_char - 'a' + 10;
	}else if(hex_char >= 'A' && hex_char <= 'F')
	{
		dec_value = hex_char - 'A' + 10;
	}else if(hex_char >= '0' && hex_char <= '9')
	{
		dec_value = hex_char - '0';
	}

	return dec_value;
}


void img_process::WriteBlobImg(img_data& src_img)
{
	if(src_img.img_length > 0)
	{
		char* tmp_buff = (char*)malloc(src_img.img_length * sizeof(char) + 1);
		if(NULL == tmp_buff)
		{
			cerr << "Malloc image error!" << endl;
		}else
		{
			char* tmp_data = src_img.img_data_str;
			memset(tmp_buff,0,src_img.img_length * sizeof(char) + 1);
			memcpy(tmp_buff,tmp_data,src_img.img_length * sizeof(char));
			tmp_buff[src_img.img_length * sizeof(char) + 1] = '\0';
//
//			stringstream pic_name;
//			pic_name << count << ".jpg";
//
//			ofstream outfile;
//			string file_path = saved_img.img_path + pic_name.str();
//			outfile.open(file_path.c_str(),ios::binary);
//			if(outfile.is_open())
//			{
//				outfile.write(tmp_buff,src_img.img_length + 1);
//			}
		}
		count++;
		free(tmp_buff);
	}
	else
	{
		cerr << "Invalid Image record!" << endl;
	}
}


void img_process::GenerateJpg(string jpg_path,char* data_buf,int binary_length)
{
	fstream binary_file("test.jpg",ios::out | ios::app);

	std::string tmp_str(data_buf,(data_buf + binary_length));
	if(binary_file.is_open())
	{
		binary_file.write(data_buf,binary_length);
		binary_file << endl;
	}

	binary_file.close();
}


cv::Mat img_process::UnsharpMask(std::string file_path,cv::Mat& src_img,int un_radius,int un_amount)
{
	cv::Mat src_copy_img;
	cv::Mat dst_img;

	int radius = un_radius;
	int amount = un_amount;
	int threshold = 0;

	src_img.copyTo(src_copy_img);
	src_img.copyTo(dst_img);
	cv::GaussianBlur(src_img,src_copy_img,cv::Size(radius,radius),0,0);
	cv::cvtColor(src_copy_img,src_copy_img,CV_BGR2YCrCb);
	cv::cvtColor(dst_img,dst_img,CV_BGR2YCrCb);

	for(int i = 0;i < src_img.rows;i++)
	{
		uchar* dst_ptr = dst_img.ptr(i);
		uchar* tmp_ptr = src_copy_img.ptr(i);

		for(int j = 0;j < src_img.cols;j++)
		{
			int tmp_threshold = dst_ptr[j * 3] - tmp_ptr[j * 3];
			if(abs(tmp_threshold) > threshold)
			{
				int value = dst_ptr[j * 3] + amount * tmp_threshold / 100;
				dst_ptr[j * 3] = (unsigned char)((((ushort)value | ((short)(255 - value) >> 15)) & ~value >> 15));
			}

    	}
	}

	cv::cvtColor(dst_img,dst_img,CV_YCrCb2BGR);
	//cv::imwrite(file_path,dst_img);
	return dst_img;
}

