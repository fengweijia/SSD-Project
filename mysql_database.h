#ifndef MYSQL_DATABASE_H
#define MYSQL_DATABASE_H

#include <iostream>
#include "dt_data.h"

using namespace std;


class mysql_database
{
public:
    mysql_database();
    virtual ~mysql_database();

public:
    inline const char* get_img_table_name()
    {
        return img_table_name;
    }
    inline const char* get_img_lenth()
    {
        return img_length;
    }
    inline const char* get_img_data()
    {
        return img_data;
    }
    inline const char* get_img_width()
    {
        return img_width;
    }
    inline const char* get_img_height()
    {
        return img_height;
    }
    inline const char* get_detect_flag()
    {
        return detect_flag;
    }

    inline const char* get_detect_table_name()
    {
        return detect_table_name;
    }
    inline const char* get_detect_type_id()
    {
        return detect_type_id;
    }
    inline const char* get_detect_conf_id()
    {
        return detect_conf_id;
    }
    inline const char* get_detect_value()
    {
        return detect_value;
    }
    inline const char* get_detect_type_conf()
    {
        return detect_type_conf;
    }

    inline const char* get_event_id()
    {
        return event_id;
    }

    inline const char* get_bb_x()
    {
        return detect_bb_x;
    }
    inline const char* get_bb_y()
    {
        return detect_bb_y;
    }
    inline const char* get_bb_width()
    {
        return detect_bb_width;
    }
    inline const char* get_bb_height()
    {
        return detect_bb_height;
    }
private:
    // XdrInfo table of BlanglungDetectDB
    const char* img_table_name;
    const char* img_length;
    const char* img_data;
    const char* img_width;
    const char* img_height;
    const char* detect_flag;

    // DetectResult table of BlanglungDetectDB
    const char* detect_table_name;
    const char* detect_type_id;
    const char* detect_conf_id;
    const char* detect_type_conf;
    const char* detect_value;

    const char* detect_bb_x;
    const char* detect_bb_y;
    const char* detect_bb_width;
    const char* detect_bb_height;

    // primary key
    const char* event_id;

protected:
};

#endif // MYSQL_DATABASE_H
