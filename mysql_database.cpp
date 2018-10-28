#include "mysql_database.h"


mysql_database::mysql_database()
{
    //ctor
    img_table_name = "businessdetail";
    img_length = "businessDetail_image_length";
    img_data = "businessDetail_image_data";
    img_width = "businessDetail_image_width";
    img_height = "businessDetail_image_height";
    detect_flag = "businessDetail_flag";

    detect_table_name = "detectresult";
    detect_type_id ="detectResult_lable";
    detect_conf_id = "";
    // the same name between table name and column
    detect_type_conf = "";
    detect_value = "detectResult_value";

    detect_bb_x = "detectResult_bb_x";
    detect_bb_y = "detectResult_bb_y";
    detect_bb_width = "detectResult_bb_width";
    detect_bb_height = "detectResult_bb_height";

    event_id = "user_id";
}

mysql_database::~mysql_database()
{
    //dtor
}
