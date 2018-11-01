cmake_minimum_required(VERSION 2.8)

project(DetailServer)

add_executable(DetailServer 
	       main.cpp
	       db_connect.cpp
		   mysql_database.cpp
	       pg_database.cpp
	       img_process.cpp
	       caffe_models.cpp
            caffe_classifier.cpp
            ssd_classifier.cpp
		   )

include_directories(/usr/local/include/pqxx
			/usr/local/include
# the directory of opencv and caffe
        	/home/john/Project/OPenCV/opencv-3.2.0/include/opencv
        	/home/john/Project/OpenCV/opencv-3.2.0/include/opencv2
               /home/john/Project/caffe/distribute/include
		    /usr/local/cuda/include)

target_link_libraries(DetailServer
              /usr/local/lib/libpqxx.a
              /usr/lib/x86_64-linux-gnu/libpq.so
		      /usr/lib/x86_64-linux-gnu/libmysqlclient.so
# the directory of locale opencv and ceffe
			  /home/john/Project/OpenCV/opencv-3.2.0/build/lib/libopencv_highgui.so
			  /home/john/Project/OpenCV/opencv-3.2.0/build/lib/libopencv_core.so
			  /home/john/Project/OpenCV/opencv-3.2.0/build/lib/libopencv_imgproc.so
			  /home/john/Project/OpenCV/opencv-3.2.0/build/lib/libopencv_imgcodecs.so
              /home/john/Project/caffe/distribute/lib/libcaffe.so
              /home/john/Project/caffe/distribute/lib/libcaffe.so.1.0.0-rc3
                      /usr/lib/x86_64-linux-gnu/libgflags.so
		      /usr/lib/x86_64-linux-gnu/libglog.so
		      /usr/lib/x86_64-linux-gnu/libboost_system.so
		      /usr/lib/x86_64-linux-gnu/libboost_thread.so) 
