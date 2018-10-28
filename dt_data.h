#ifndef DETECT_DATA_H
#define DETECT_DATA_H

using namespace std;

// image which be detected attributes and detect results attributes
typedef struct database_img_data
{
	string event_id;
	string img_type;

	int img_length;
	//string img_data_str;
	char* img_data_str;
	int img_width;
	int img_height;
	const char* detect_flag;
	string img_path;

	int detect_type_id;
	int detect_conf_id;
	float detect_conf_value;

	public:
	database_img_data():img_path("./imagedata//"),detect_flag("Y")
	{

	}
	~database_img_data()
	{

	}
}img_data;


#endif
