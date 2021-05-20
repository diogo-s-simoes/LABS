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
  NewReader(string infile);
  NewReader(vector<double>, vector<double>){};
  NewReader(const NewReader& A);

  double GetDataVector(int i){return DataVector[i];};
  double GetTempo(int i){return Tempo[i];};
  int GetNrInstantes(){return nlines;};
  //Destructor
  virtual ~NewReader()=default;
  const NewReader operator=(const NewReader& A);


protected:
  string FILENAME;
  ifstream DataFile;
  int nlines;
  vector<double> Tempo;
  vector<double> DataVector;
};

#endif