FIND_PACKAGE(OpenCV 3.1 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_library(MultiView multiview.cpp)
target_link_libraries(MultiView ${OpenCV_LIBS})

add_executable(PersuUndistort main.cpp)
target_link_libraries(PersuUndistort MultiView ${OpenCV_LIBS})