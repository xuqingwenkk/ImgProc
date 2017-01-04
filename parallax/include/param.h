#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class ParamReader
{
public:
  map<string, string> data;
public:
  ParamReader(string filename="../param/parameter.txt")
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
