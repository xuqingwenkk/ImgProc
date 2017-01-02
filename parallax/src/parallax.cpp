#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{
  Mat imgl = imread("../data/image1.jpg", IMREAD_GRAYSCALE);
  Mat imgr = imread("../data/image2.jpg", IMREAD_GRAYSCALE);
  
  Mat imgDisparity16S = Mat(imgl.rows, imgl.cols, CV_16S);
  Mat imgDisparity8U = Mat(imgl.rows, imgl.cols, CV_8UC1);
  
  if(imgl.empty() || imgr.empty())
  {
    cout << "Error when reading images! " << endl;
    return -1;
  }
  
  int ndisparities = 16 * 5;
  int SADWindowSize = 21;
  
  //Ptr<StereoBM> sbm = StereoBM::create(ndisparities, SADWindowSize);
  StereoBM sbm(CV_STEREO_BM_BASIC, ndisparities, SADWindowSize);
  
  sbm.operator()(imgl, imgr, imgDisparity16S, CV_16S);
  
  double minVal, maxVal;
  
  minMaxLoc(imgDisparity16S, &minVal, &maxVal);
  cout << "Min disp is " << minVal << " Max disp is " << maxVal << endl;
  imgDisparity16S.convertTo(imgDisparity8U, CV_8UC1, 255/(maxVal - minVal));
  
  
  namedWindow("display disparity image", WINDOW_NORMAL);
  imshow("display disparity image", imgDisparity8U);
  
  imwrite("../data/disparity.jpg", imgDisparity8U);
  
  waitKey(0);
  return 0;
  
}