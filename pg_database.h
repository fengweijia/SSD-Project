#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "dt_data.h"

using namespace std;


class pg_database
{
public:
    pg_database();
    virtual ~pg_database();

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

    // primary key
    const char* event_id;

protected:
};

#endif // DATABASE_H
