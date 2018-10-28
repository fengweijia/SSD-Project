#include "db_connect.h"


db_connect::db_connect() : img_num_str(""),result_num_str(""),event_id("")
{
    //ctor
    // default setting
    query_img.detect_type_id = 1;
    //query_img.detect_flag = "Y";
}

db_connect::~db_connect()
{
    //dtor
}


// PostgreSql Database
pg_connect::pg_connect()
{
    //ctor
    db_database_name = "BlanglungDetectDB";
    db_user_name = "jjkj2017";
    db_password = "jjkj2017**";
    db_host = "rm-8vbu143u42cfsws2zro.pgsql.zhangbei.rds.aliyuncs.com";
    db_port = "3432";

    db_opition = "N";
}

pg_connect::~pg_connect()
{
    //dtor
}

bool pg_connect::ConnectDatabase()
{
    char sql[256];
    sprintf(conn_info,"dbname=%s user=%s password=%s host=%s port=%s",    \
            db_database_name,db_user_name,db_password,db_host,db_port);

    try{
          connection conn(conn_info);
	      if (conn.is_open())
	      {
            cout << "Opened PostgreSql Database Successfully: " << conn.dbname() << endl;

            // create SQL statement
            sprintf(sql,"SELECT * FROM %s WHERE %s = '%s'",pg_db.get_img_table_name(),pg_db.get_detect_flag(),db_opition);
            // create a non-transactional object
            nontransaction nont(conn);
            // execute SQL query 
			result resu(nont.exec(sql)); 
            // list down all the records
            for(result::const_iterator iter = resu.begin(); iter != resu.end(); ++iter)
            {
				// database add dx_cr field
                event_id = iter[0].as<string>();
                query_img.event_id = iter[0].as<string>();

				query_img.img_type = iter[2].as<string>();
                query_img.img_length = iter[3].as<int>();
				//string tmp_img_data = iter[3].as<string>();
                query_img.img_data_str = const_cast<char*>(iter[4].as<string>().c_str());
				//query_img.img_data_str = nont.esc_raw(tmp_img_data);
                query_img.img_width = iter[8].as<int>();
                query_img.img_height = iter[9].as<int>();

                img_data_container.push_back(query_img);

            }
            cout << "-->Select * operation successfully" << endl;

            connect_flag = true;
	      } else
	      {
            cout << "Can't open database" << endl;
            connect_flag = false;
	      }

	      conn.disconnect();

	   }catch (const std::exception &e)
	   {
	      cerr << e.what() << std::endl;
	      connect_flag = false;
	   }

	   return connect_flag;
}

void pg_connect::CountData()
{
    char img_sql[256];
    char detect_sql[256];


    sprintf(conn_info,"dbname=%s user=%s password=%s host=%s port=%s",    \
            db_database_name,db_user_name,db_password,db_host,db_port);

    try{
          connection conn(conn_info);
	      if (conn.is_open())
	      {
            cout << "Opened database successfully: " << conn.dbname() << endl;

            // create SQL statement
            sprintf(img_sql,"SELECT COUNT(*) FROM %s",pg_db.get_img_table_name());
            sprintf(detect_sql,"SELECT COUNT(*) FROM %s",pg_db.get_detect_table_name());
            // create a non-transactional object
            nontransaction nont(conn);
            // execute SQL query
            result img_resu(nont.exec(img_sql));
            result detect_resu(nont.exec(detect_sql));
            // return the number of all the records
            img_num_str = img_resu.at(0)[0].c_str();
            result_num_str = detect_resu.at(0)[0].c_str();

            cout << "-->Select count(*) operation successfully" << endl;
	      } else
	      {
            cout << "Can't open database" << endl;
            return;
	      }

	      conn.disconnect();

	   }catch (const std::exception &e)
	   {
	      cerr << e.what() << std::endl;
	      return;
	   }
}

// insert DetectResult table
// default: detectinfo:blacklung and detecttypeid 1
// default: detecttypeid:1 and detecttypeconfigid 1(positive) 2(negative)
void pg_connect::InsertTableData(const char* event_id,img_data& table_data)
{
    char insert_sql[256];

    sprintf(conn_info,"dbname=%s user=%s password=%s host=%s port=%s",    \
            db_database_name,db_user_name,db_password,db_host,db_port);

    try
    {
        connection conn(conn_info);
        if(conn.is_open())
        {
            cout << "Opened database successfully: " << conn.dbname() << endl;

            // create SQL statement
            sprintf(insert_sql,"INSERT INTO %s(%s,%s,%s,%s) VALUES(\'%s\',\'%d\',\'%d\',\'%f\')",pg_db.get_detect_table_name(),    \
                    pg_db.get_event_id(),pg_db.get_detect_type_id(),pg_db.get_detect_conf_id(),pg_db.get_detect_value(),    \
                    event_id,table_data.detect_type_id,table_data.detect_conf_id,table_data.detect_conf_value);
            // create a transactional object
            work insert_work(conn);
            insert_work.exec(insert_sql);
            insert_work.commit();

            cout << "-->Insert table operation successfully" << endl;
        }else
        {
            cout << "Can't open database" << endl;
            return;
        }

        conn.disconnect();
    }catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
        return;
    }

}

// update imaage table detected flag
void pg_connect::UpdateTableData(const char* event_id,img_data& table_data)
{
    char update_sql[256];

    sprintf(conn_info,"dbname=%s user=%s password=%s host=%s port=%s",    \
            db_database_name,db_user_name,db_password,db_host,db_port);

    try
    {
        connection conn(conn_info);
        if(conn.is_open())
        {
            cout << "Open database successfully: " << conn.dbname() << endl;

            // create SQL statement
            sprintf(update_sql,"UPDATE %s SET %s = '%s' WHERE %s = '%s'",pg_db.get_img_table_name(),pg_db.get_detect_flag(),    \
                    table_data.detect_flag,pg_db.get_event_id(),event_id);
            // create a transactional object
            work update_work(conn);
            update_work.exec(update_sql);
            update_work.commit();

            cout << "Update records operation successfully" << endl;
        }else
        {
            cout << "Can't open database" << endl;
            return;
        }

        conn.disconnect();
    }catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
        return;
    }

}

// select detect id for special event
int pg_connect::SelectTableData(const char* detect_type_conf,int detect_type_id)
{
    int conf_id;
    char select_sql[256];

    sprintf(conn_info,"dbname=%s user=%s password=%s host=%s port=%s",    \
            db_database_name,db_user_name,db_password,db_host,db_port);

    try{
          connection conn(conn_info);
	      if (conn.is_open())
	      {
            cout << "Opened database successfully: " << conn.dbname() << endl;

            // create SQL statement
            sprintf(select_sql,"SELECT %s FROM %s WHERE %s = '%s' and %s = %d",pg_db.get_detect_conf_id(),pg_db.get_detect_type_conf(),    \
                    pg_db.get_detect_type_conf(),detect_type_conf,pg_db.get_detect_type_id(),detect_type_id);
            // create a non-transactional object
            nontransaction nont(conn);
            // execute SQL query
            result resu(nont.exec(select_sql));

            // list down all the records
            for(result::const_iterator iter = resu.begin(); iter != resu.end(); ++iter)
            {
                conf_id = iter[0].as<int>();

            }
            cout << "-->Select 'DetectConfId' operation successfully" << endl;

	      } else
	      {
            cout << "Can't open database" << endl;
	      }

	      conn.disconnect();

	   }catch (const std::exception &e)
	   {
	      cerr << e.what() << std::endl;
	   }

	   return conf_id;

}


// MySql Database
mysql_connect::mysql_connect()
{
    //ctor
    db_database_name = "smartall";
    db_user_name = "john_feng";
    db_password = "SmartAll1";
    db_host = "rm-2ze845t4xp15d2umrao.mysql.rds.aliyuncs.com";
    db_port = "3306";

    db_opition = "N";
}

mysql_connect::~mysql_connect()
{
    //dtor
}

bool mysql_connect::ConnectDatabase()
{
    char sql[256];
	int res;
	MYSQL_RES *res_ptr; /*指向查询结果的指针*/
    MYSQL_ROW result_row;        
	int rows,cols;

    conn = mysql_init(NULL);
    // connect to database
    if(mysql_real_connect(conn,db_host,db_user_name,db_password,db_database_name,0,NULL,0))
    {
        cout << "Opened database successfully!" << endl;
		// create SQL statement
        sprintf(sql,"SELECT %s,%s,%s,octet_length(%s),%s FROM %s WHERE %s = '%s'",mysql_db.get_event_id(),mysql_db.get_img_height(),mysql_db.get_img_width(),mysql_db.get_img_data(),mysql_db.get_img_data(),mysql_db.get_img_table_name(),mysql_db.get_detect_flag(),db_opition);
		// execute SQL query
		res = mysql_query(conn,sql);
		if(res)
		{
			printf("Mysql Query Failed!\n");
			cerr << mysql_error(conn) << endl;
		}
		else
		{
			res_ptr = mysql_store_result(conn);
			if(res_ptr)
			{
				rows = mysql_num_rows(res_ptr) + 1;
				cols = mysql_num_fields(res_ptr);

				for(int i = 1; i < rows; i++)
				{
					result_row = mysql_fetch_row(res_ptr);
					for(int j = 0; j < cols; j++)
					{
						if(j == 1)
						{
							int tmp_height = static_cast<int>(strtol(result_row[j],NULL,10));
							query_img.img_height = tmp_height;
						}else if(j == 2)
						{
							int tmp_width = static_cast<int>(strtol(result_row[j],NULL,10));
							query_img.img_width = tmp_width;
						}else if(j == 3)
						{
							query_img.img_length = static_cast<int>(strtol(result_row[j],NULL,10));
						}
						else if(j == 4)
						{
							query_img.img_data_str =result_row[j];
						}
					}
					img_data_container.push_back(query_img);
				}
				mysql_free_result(res_ptr);
                cout << "-->Select * operation successfully" << endl;
                connect_flag = true;
			}
		}
    }
    mysql_close(conn);
    return connect_flag;
}

void mysql_connect::CountData()
{
    char img_sql[256];
    char detect_sql[256];

    int res,cous;
	MYSQL_RES *res_ptr,*cous_ptr; /*指向查询结果的指针*/
	MYSQL_ROW rows,cous_rows;

    conn = mysql_init(NULL);
	if(NULL == mysql_init(conn))
	{
		cerr << "Init conn failed!" << endl;
	}
    // connect to database
    if(mysql_real_connect(conn,db_host,db_user_name,db_password,db_database_name,0,NULL,0))
    {
        cout << "Opened database successfully!" << endl;
        // create SQL statement
        sprintf(img_sql,"SELECT COUNT(*) FROM %s",mysql_db.get_img_table_name());
        sprintf(detect_sql,"SELECT COUNT(*) FROM %s",mysql_db.get_detect_table_name());
		res = mysql_query(conn,img_sql);
		if(res)
		{
			printf("Mysql Query Failed!!!\n");
			cerr << mysql_error(conn) << endl;
		}  
		else
		{
            cout << "-->Select count(*) operation successfully" << endl;
			res_ptr = mysql_store_result(conn);
			rows = mysql_fetch_row(res_ptr);
		    cous = mysql_query(conn,detect_sql);
			if(!cous)
			{
				cous_ptr = mysql_store_result(conn);
				cous_rows = mysql_fetch_row(cous_ptr);
				img_num_str = rows[0];
				result_num_str = cous_rows[0];
			}
		}
	}
	else
	{
		cerr << "Opened database failed! " << mysql_errno(conn) << mysql_error(conn) << endl;
	}

	mysql_close(conn);
}

// insert DetectResult table
void mysql_connect::InsertTableData(const char* event_id,img_data& table_data)
{
    char insert_sql[256];
	int res;

    conn = mysql_init(NULL);
    // connect to database
    if(!mysql_real_connect(conn,db_host,db_user_name,db_password,db_database_name,0,NULL,0))
    {

        cout << "Opened database successfully " << endl;
        // create SQL statement
        sprintf(insert_sql,"INSERT INTO %s(%s,%s,%s,%s) VALUES(\'%s\',\'%d\',\'%d\',\'%f\')",mysql_db.get_detect_table_name(),    \
                    mysql_db.get_event_id(),mysql_db.get_detect_type_id(),mysql_db.get_detect_conf_id(),mysql_db.get_detect_value(),    \
                    event_id,table_data.detect_type_id,table_data.detect_conf_id,table_data.detect_conf_value);
        // create a transactional object
		res = mysql_query(conn,insert_sql);
		if(res == 0)
		{
			cout << "-->Insert table operation failed!" << endl;
		}
		else
		{
			cout << "-->Insert table operation successfully" << endl;
		}
            
	}
	mysql_close(conn);

}

// update image table detected flag
void mysql_connect::UpdateTableData(const char* event_id,img_data& table_data)
{
    char update_sql[256];
	int res;

    conn = mysql_init(NULL);
    // connect to database
    if(!mysql_real_connect(conn,db_host,db_user_name,db_password,db_database_name,0,NULL,0))
    {

        cout << "Opened database successfully!" << endl;
        // create SQL statement
		sprintf(update_sql,"UPDATE %s SET %s = '%s' WHERE %s = '%s'",mysql_db.get_img_table_name(),mysql_db.get_detect_flag(),    \
                    table_data.detect_flag,mysql_db.get_event_id(),event_id);
        // create a transactional object
		res = mysql_query(conn,update_sql);
		if(res == 0)
		{
            cout << "Update records operation failed!" << endl;
		}
		else
		{
            cout << "Update records operation successfully" << endl;

		}

	} 

	mysql_close(conn);
}

// select retail lable for detail product
int mysql_connect::SelectTableData(const char* detect_type_conf,int detect_type_id)
{
    int lable_id;
    char select_sql[256];
	int res;
	MYSQL_RES *res_ptr; /*指向查询结果的指针*/
	int rows,cols;
	MYSQL_ROW result_row;

    conn = mysql_init(NULL);
    // connect to database
    if(!mysql_real_connect(conn,db_host,db_user_name,db_password,db_database_name,0,NULL,0))
    {
        cout << "Opened database successfully!" << endl;
        // create SQL statement
        sprintf(select_sql,"SELECT %s FROM %s WHERE %s = '%s' and %s = %d",mysql_db.get_detect_conf_id(),mysql_db.get_detect_type_conf(),    \
                    mysql_db.get_detect_type_conf(),detect_type_conf,mysql_db.get_detect_type_id(),detect_type_id);
		// execute SQL query
		res = mysql_query(conn,select_sql);
		if(res)
		{
			printf("Mysql Query Failed!!!");
		}
		else
		{
            cout << "-->Select * operation successfully" << endl;
			res_ptr = mysql_store_result(conn);
			if(res_ptr)
			{

				rows = mysql_num_rows(res_ptr) + 1;
				cols = mysql_num_fields(res_ptr);

				result_row = mysql_fetch_row(res_ptr);
			    int tmp_id = static_cast<int>(strtol(result_row[0],NULL,10));
				lable_id = tmp_id;
			}
		}
	}

	mysql_close(conn);

	return lable_id;
}


