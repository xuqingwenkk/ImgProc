FIND_PACKAGE(OpenCV 2.4 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

add_executable(Parallax parallax.cpp)
target_link_libraries(Parallax ${OpenCV_LIBS})

add_executable(ParallaxFisheye parallax_fisheye.cpp)
target_link_libraries(ParallaxFisheye ${OpenCV_LIBS})
