#ifndef DB_CONNECT_H
#define DB_CONNECT_H

#include <iostream>
#include <stdio.h>
#include <pqxx/pqxx>
#include <mysql/mysql.h>
#include "dt_data.h"
#include "pg_database.h"
#include "mysql_database.h"
#include "opencv.hpp"

using namespace std;
using namespace pqxx;


class db_connect
{
public:
    db_connect();
    virtual ~db_connect();

public:
    bool connect_flag;

public:
    // connect remote aliyun database and selct * from table
    virtual bool ConnectDatabase(){}

    // select count(*) data and result table
    virtual void CountData(){}

    // insert result to result table
    virtual void InsertTableData(const char* event_id,img_data& table_data){}

    // update table data
    virtual void UpdateTableData(const char* event_id,img_data& table_data){}

    // select id form table
    virtual int SelectTableData(const char* detect_type_conf,int detect_type_id){}

    // insert special information to special table
    virtual void InsertXdrInfo(){}

    // get query image data
    inline std::vector<img_data> get_query_img()
    {
        return img_data_container;
    }

protected:
    string event_id;
    string img_num_str;
    string result_num_str;
	// add by feng with adapted with mysql database 18.10.26
	int img_num;
	int result_num;

    img_data query_img;
    std::vector<img_data> img_data_container;

protected:
    // Database connect parameters
    const char* db_host;
    const char* db_port;
    const char* db_user_name;
    const char* db_password;
    const char* db_database_name;

    const char* db_opition;
    char conn_info[256];

};


class pg_connect: public db_connect
{
public:
    pg_connect();
    ~pg_connect();

private:
    pg_database pg_db;
    
public:
    // connect remote aliyun database and selct * from table
    bool ConnectDatabase();

    // select count(*) data and result table
    void CountData();

    // insert result to result table
    void InsertTableData(const char* event_id,img_data& table_data);

    // update table data
    void UpdateTableData(const char* event_id,img_data& table_data);

    // select id form table
    int SelectTableData(const char* detect_type_conf,int detect_type_id);

    // insert special information to special table
    //void InsertXdrInfo();

    // get the number of insert images of remote database
    inline string get_img_num_str()
    {
        cout << "The total image container number is " << img_num_str << endl;
        return img_num_str;
    }

    // get the number of detect result of aliyun databse table
    inline string get_result_num_str()
    {
        cout << "The total be detected number is " << result_num_str << endl;
        return result_num_str;
    }


};


// Mysql database
class mysql_connect: public db_connect
{
public:
    mysql_connect();
    ~mysql_connect();

private:
    mysql_database mysql_db;
    MYSQL *conn;

public:
    // connect remote aliyun database and selct * from table
    bool ConnectDatabase();

    // select count(*) data and result table
    void CountData();

    // insert result to result table
    void InsertTableData(const char* event_id,img_data& table_data);

    // update table data
    void UpdateTableData(const char* event_id,img_data& table_data);

    // select id form table
    int SelectTableData(const char* detect_type_conf,int detect_type_id);

    // insert special information to special table
    //void InsertXdrInfo();

    // get the number of insert images of remote database
    inline char* get_img_num_str()
    {
        cout << "The total image container number is " << img_num_str << endl;
        return const_cast<char*>(img_num_str.c_str());
    }

    // get the number of detect result of aliyun databse table
    inline char* get_result_num_str()
    {
        cout << "The total be detected number is " << result_num_str << endl;
        return const_cast<char*>(result_num_str.c_str());
    }

};


#endif // DB_CONNECT_H
