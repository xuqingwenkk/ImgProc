#include "param.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{
  Mat imgl = imread("../data/imgl.jpg", IMREAD_GRAYSCALE);
  Mat imgr = imread("../data/imgr.jpg", IMREAD_GRAYSCALE);
  
  Mat imgDisparity16S = Mat(imgl.rows, imgl.cols, CV_16S);
  Mat imgDisparity8U = Mat(imgl.rows, imgl.cols, CV_8UC1);
  
  if(imgl.empty() || imgr.empty())
  {
    cout << "Error when reading images! " << endl;
    return -1;
  }
  
  
  //undistortion and rectify
  Matx33d intrinsic_matrix(472.4,0,987.5,0,470.4,532.1,0,0,1);
  Vec4d distortion_coeffs(-0.156,0.396,-0.665,0.401);
  Mat R1 = cv::Mat::eye(3,3,CV_32F);
  Size image_size = imgl.size();
  Mat mapx = cv::Mat(image_size,CV_32FC1);
  Mat mapy = cv::Mat(image_size,CV_32FC1);
  fisheye::initUndistortRectifyMap(intrinsic_matrix,distortion_coeffs,R1,intrinsic_matrix,image_size,CV_32FC1,mapx,mapy);
  Mat t1 = imgl.clone();
  remap(imgl,t1,mapx, mapy, cv::INTER_LINEAR);
  Mat t2 = imgr.clone();
  remap(imgr,t2,mapx, mapy, cv::INTER_LINEAR);
  
  namedWindow("undistortion_t1", WINDOW_NORMAL);
  imshow("undistortion_t1", t1);
  namedWindow("undistortion_t2", WINDOW_NORMAL);
  imshow("undistortion_t2", t2);
  
  
  ParamReader pr;
  int ndisparities = atoi(pr.getData("ndisparities").c_str());
  int SADWindowSize = atoi(pr.getData("SADWindowSize").c_str());
  cout << ndisparities << endl << SADWindowSize << endl;
  
  StereoBM sbm(CV_STEREO_BM_FISH_EYE, ndisparities, SADWindowSize);
  //sbm.operator()(imgl, imgr, imgDisparity16S, CV_16S);
  sbm.operator()(t1, t2, imgDisparity16S, CV_16S);
  
  double minVal, maxVal;
  
  minMaxLoc(imgDisparity16S, &minVal, &maxVal);
  //cout << "Min disp is " << minVal << " Max disp is " << maxVal << endl;
  imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));
  
  
  namedWindow("display disparity image", WINDOW_NORMAL);
  imshow("display disparity image", imgDisparity8U);
  
  imwrite("../data/disparity.png", imgDisparity8U);
  
  waitKey(0);
  waitKey(0);
  waitKey(0);
  return 0;
  
}

