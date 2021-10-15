#ifndef __DataReader__
#define __DataReader__
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "TMultiGraph.h"
using namespace std;

class DataReader{
    public:

    DataReader(string filename);
    DataReader();
    ~DataReader();

    TMultiGraph* DisplayData(
        string KIND, //deaths, cases
        vector<string> COUNTRIES, 
        string OPTION 
    );

    double GetCols();
    double GetLines();
    vector<vector<string> > GetData();

    void Print();

    protected:
    string FileN;
    double mcols;
    double mlines;
    //vector<pair<string,vector<string>>> result;
    vector<vector<string>> matrix;
    vector<string> vec;
};

#endif