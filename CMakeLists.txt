cmake_minimum_required(VERSION 2.8)

project(DetailServer)

add_executable(DetailServer 
	       main.cpp
	       db_connect.cpp
		   mysql_database.cpp
	       pg_database.cpp
	       img_process.cpp
	       caffe_models.cpp
           #caffe_classifier.cpp
		   )

include_directories(/usr/local/include/pqxx
			/usr/local/include
        	/home/john/OPenCV/opencv/include/opencv
        	/home/john/OpenCV/opencv/include/opencv2
            #/home/john/caffe/distribute/include
		    /usr/local/cuda/include)

target_link_libraries(DetailServer
              /usr/local/lib/libpqxx.a
              /usr/lib/libpq.so
		      /usr/lib/x86_64-linux-gnu/libmysqlclient.so
			  /home/john/OpenCV/opencv/build/lib/libopencv_highgui.so
			  /home/john/OpenCV/opencv/build/lib/libopencv_core.so
			  /home/john/OpenCV/opencv/build/lib/libopencv_imgproc.so
			  /home/john/OpenCV/opencv/build/lib/libopencv_imgcodecs.so
              #/home/john/caffe/distribute/lib/libcaffe.so
              #/home/john/caffe/distribute/lib/libcaffe.so.1.0.0
		      /usr/lib/x86_64-linux-gnu/libglog.so
		      /usr/lib/x86_64-linux-gnu/libboost_system.so
		      /usr/lib/x86_64-linux-gnu/libboost_thread.so) 
