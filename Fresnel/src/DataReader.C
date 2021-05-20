#include "DataReader.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;
DataReader:: DataReader(){
    mcols=0;
    mlines=0;
}

DataReader:: DataReader(string filename){
    FileN=filename;

    fstream file;
    file.open(filename);

    if (!file) {
    cout << "Error opening the file" << endl;
    exit(1);
    }

    int count=0;
    string line,colname;
    
    string val;
    
    /*if(file.good()){
        getline(file, line);
        stringstream ss(line);
        while(getline(ss, colname, ',')){
            vec.push_back(colname);
            //result.push_back({colname, vector<string> {}});
            //cout<<"ahhhhh"<<colname<< "  "<<endl; //this works
            ++count;
        }
    }
    matrix.push_back(vec);*/
    vec.clear();
    
    int d=0;
    while(getline(file, line)){
        stringstream ss(line);
        //int colIdx = 0;

        /*while(ss>>val){
            vec.push_back(val);
            //result.at(colIdx).second.push_back(val);
            //cout<<val<<endl; // this works mas o val é uma linha toda?
            if(ss.peek() == ',') ss.ignore();
            colIdx++;
        }*/
        while(ss>>val){
            vec.push_back(val);
        }
        while(getline(ss, val, ',')){
            vec.push_back(val);
             //cout<<" "<<val<< "  "<<endl; 
        }
        matrix.push_back(vec);
        //d=colIdx;
        vec.clear();
    }
    mcols=count;
    mlines=matrix.size();
    cout<<mcols<<" "<<mlines<<" "<<endl;
    
    file.close();
}

DataReader::~DataReader(){
    vec.clear();
    matrix.clear();
}

double DataReader:: GetCols(){
    return mcols;
}
double DataReader:: GetLines(){
    return mlines;
}

vector<vector<string>> DataReader:: GetData(){
    return matrix;
}
