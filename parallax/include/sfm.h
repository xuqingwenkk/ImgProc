#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/core/core.hpp"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//camera intrinsic parameter
struct CAMERA_INTRINSIC_PARAM
{
  double cx,cy,fx,fy,scale,k1,k2,k3,k4;
};

struct FRAME
{
  int frameID;
  cv::Mat rgb;
  cv::Mat desp;
  vector<cv::KeyPoint> kp;
};

struct TRANSFORM
{
  cv::Mat rvec, tvec;
  int inliers;
  vector<cv::Point2f> p1;
  vector<cv::Point2f> p2;
  cv::Mat mask;
};

class ParamReader
{
public:
  map<string, string> data;
public:
  ParamReader(string filename="../param/parameters.txt")
  {
    ifstream fin(filename.c_str());
    if(!fin)
    {
      cerr << "param file does not exist! " << endl;
      return;
    }
    while(!fin.eof())
    {
      string str;
      getline(fin,str);
      if(str[0]=='#')
	continue;
      int pos=str.find("=");
      if(pos == -1)
	continue;
      string key = str.substr(0, pos);
      string value = str.substr(pos+1, str.length());
      data[key] = value;
      if(!fin.good())
	break;
    }
  }
  string getData(string key)
  {
    map<string, string>::iterator iter = data.find(key);
    if(iter == data.end())
    {
      cerr << key << "is not found !" << endl;
      return string("NOT FOUND! ");
    }
    return iter->second;
  }
};
