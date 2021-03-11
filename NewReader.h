#ifndef __NewReader__
#define __NewReader__

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <sstream>

#include "TGraph.h"
#include "TAxis.h"
#include "TH1F.h"

using namespace std;

class NewReader{
public:
  //Contructor
  NewReader(string);
  //Destructor
  virtual ~NewReader();



protected:
  int Nlines;
  int ColNum;
  string FileName;
  ifstream DataFile;
  vector<double> DataVector;  //{time,number of spots}
};

#endif