Descripter:
连接数据库，调用深度学习模型（caffe、SSD）对存储的图像数据进行检测识别并返回到数据库中

./mysql_database.h PostgreSql数据库表头文件，相应字段的定义及初始化
./pg_database.h  Mysql数据库头文件，相应字段的定义及初始化
./db_connect.h 数据库连接头文件，对数据库进行连接
./dt_data.h 定义的图像数据结构头文件
./img_process.h  图像处理头文件，对二进制图像进行本地化存储及做图像处理
./caffe_model.h 定义的检测识别模型的相应配置文件路径的头文件
./caffe_classifier.h 调用检测模型对图像进行检测识别并输出Boundingbox坐标及类别value值
./main 调用boost线程，对数据库进行检测不断地读取图像数据；对图像数据进行检测识别并返回数据库


CMakeList.txt
用camke进行多文件编译连接并输出，配置相应的头文件信息和lib库信息
1) 调用model
本demo是基于caffe框架进行model的训练以及应用。所以在调用model进行识别检测之前， 计算机cafee环境的配置ok，主要涉及：boost/opencv/camke....
2) 数据库调用库文件
a. PostgreSql
本地连接pg，需要编译安装libpq。我的安装版本是4.0.1
在编译安装的过程中可能会遇到pg_config/libpgfe.h找不到的问题，安装libpq-dev即可解决
sudo apt-get install libpq-dev
b. Mysql
本地连接mysql，本地装有mysqlclieng/mysqlserver，则可以直接包含相关的头文件，连接相关的库文件进行数据库的操作


后续补充.....
