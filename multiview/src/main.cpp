#include "multiview.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
using namespace std;
using namespace cv;


int main(int argc,char **argv)
{
  SETTING settings;
  // Rotation transformations
  vector<TRANSFORM> trans;
  ParamReader pr;
  
  // Create the perspective image 
  IMAGE persp;
  persp.width = atoi(pr.getData("perspwidth").c_str()); 
  persp.height = atoi(pr.getData("perspheight").c_str());
  persp.theta = atof(pr.getData("persptheta").c_str());
  persp.rgb = Mat(persp.height,persp.width,CV_8UC3,Scalar(0,0,0));
  
  // Attempt to open the fisheye image 
  FISHIMAGE fishimage;
  fishimage.rgb = imread(pr.getData("image"));
  fishimage.width = fishimage.rgb.cols;
  fishimage.height = fishimage.rgb.rows;
  fishimage.theta = atof(pr.getData("fishtheta").c_str());
  fishimage.theta *= DTOR;
  
  TRANSFORM temp;
  float x_value = atof(pr.getData("x_value").c_str());
  temp.axis = XTILT;
  temp.value = DTOR*x_value;
  trans.push_back(temp);
  float y_value = atof(pr.getData("y_value").c_str());
  temp.axis = ZPAN;
  temp.value = DTOR*y_value;
  trans.push_back(temp);
  float z_value = atof(pr.getData("z_value").c_str());
  temp.axis = YROLL;
  temp.value = DTOR*z_value;
  trans.push_back(temp);
  // Precompute transform sin and cosine
  for (int j=0;j<trans.size();j++) {
    trans[j].cvalue = cos(trans[j].value);
    trans[j].svalue = sin(trans[j].value);
  }
  settings.trans = trans;
  
  int antialias = atoi(pr.getData("antialias").c_str());
  if(antialias < 1) antialias = 1;
  settings.antialias = antialias;
  
  fishimage.cx = atoi(pr.getData("fishcenterx").c_str());
  if (fishimage.cx < 0)
    fishimage.cx = fishimage.width / 2;
  fishimage.cy = atoi(pr.getData("fishcentery").c_str());
  if (fishimage.cy < 0)
    fishimage.cy = fishimage.height / 2;
  fishimage.radius = atoi(pr.getData("fishradius").c_str());
  if (fishimage.radius < 0)
    fishimage.radius = fishimage.height / 2;
  

  pixel_map(persp,fishimage,settings);
  // Display output image
  namedWindow("perspective image", WINDOW_NORMAL);
  imshow("perspective image", persp.rgb);
  waitKey(0);
  return 0;
}