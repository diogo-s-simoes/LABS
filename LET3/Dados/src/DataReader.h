#ifndef __DataReader__
#define __DataReader__

#include<fstream>
#include<vector>
#include<string>
#include"TMultiGraph.h"

using namespace std;

class DataReader{
public:
  //contructor
  DataReader(string);

  //destructor
  virtual ~DataReader();

  //Read data of a column
  vector<double> GetColumn(int n); //number from 1 to NumCol


  void virtual Print();

  int GetNLines();
  vector<string*> GetRawData();

  TMultiGraph* DisplayData(string KIND,   // KIND: "cases", "deaths"
                            vector<string> COUNTRIES, // COUNTRIES: "ALL" or {"PT", "FR", ...}
                            std::string OPTION="daily"   // OPTION: "daily", "cumulative"
                            );

protected:
  int Nlines;
  string FileName;
  int ColNum;
  ifstream DataFile;
  vector<string*> RawData;
};

#endif