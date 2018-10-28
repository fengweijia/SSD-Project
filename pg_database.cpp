#include "pg_database.h"


pg_database::pg_database()
{
    //ctor
    img_table_name = "\"XdrInfo\"";
    img_length = "\"XdrLength\"";
    img_data = "\"XdrData\"";
    img_width = "\"XdrWidth\"";
    img_height = "\"XdrHeight\"";
    detect_flag = "\"DetectFlag\"";

    detect_table_name = "\"DetectResult\"";
    detect_type_id ="\"DetectTypeId\"";
    detect_conf_id = "\"DetectConfId\"";
    // the same name between table name and column
    detect_type_conf = "\"DetectTypeConf\"";
    detect_value = "\"DetectValue\"";

    event_id = "\"EventId\"";
}

pg_database::~pg_database()
{
    //dtor
}
