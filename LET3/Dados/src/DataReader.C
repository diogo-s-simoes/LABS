#include"DataReader.h"
#include<stdexcept>
#include<iostream>
#include"TGraph.h"

DataReader::DataReader(string infile):FileName(infile){
  DataFile.open(infile);
  string *LineData;
  ColNum=1;

  string tempstr;

  getline(DataFile,tempstr);
  for(int i=0;i<tempstr.size();i++){
    if(tempstr[i]==',' || tempstr[i]==';')
      ColNum++;
  }

  while(getline(DataFile,tempstr)){
    LineData = new string[ColNum];
    int j=0;

    
    for(int i=0;i<ColNum;i++){
      int comma=0;
      LineData[i]="";

      while((j<tempstr.size()-1)&&(comma==0)){
        if(tempstr.at(j)!=',' && tempstr[j]!=';'){

          LineData[i].push_back(tempstr.at(j));
        }
        else{

          comma=1;
        }
        j++;
        
      }
    }
    RawData.push_back(LineData);
  }
  Nlines= RawData.size();

}


DataReader::~DataReader(){
  DataFile.close();
  for(int i=0;i<Nlines;i++)
    delete[] RawData.at(i);
}


vector<double> DataReader::GetColumn(int n){
//  if(n<1||n>ColNum)
//  throw std::invalid_argument;//(Form("[%s] Column out of range\n", __PRETTY_FUNCTION__));
  
  vector<double> ColVec;

  for(int i=0;i<Nlines;i++){
    //std::cout<<n<<"    "<<RawData.at(i)[0]<<std::endl;
    ColVec.push_back(stod(RawData.at(i)[n-1]));
  }

  return ColVec;
}

int DataReader::GetNLines(){

  return RawData.size();
}

vector<string*> DataReader::GetRawData(){

  return RawData;
}

void DataReader::Print(){
  cout<<ColNum<<"Colunas por "<<Nlines<<" Linhas"<<endl;
  cout<<FileName<<endl;

}


TMultiGraph* DataReader::DisplayData(string KIND="cases",   // KIND: "cases", "deaths"
  vector<string> COUNTRIES={"PT"}, // COUNTRIES: "ALL" or {"PT", "FR", ...}
  string OPTION   // OPTION: "daily", "cumulative"
  ){

  int ReadCol;  //chooses Death or Case Statistics column
  if(KIND=="cases")
    ReadCol=4;
  else
    ReadCol=5;
    



  if(COUNTRIES[0]=="ALL"){   //Creates array with every country, to plot them all at once
    COUNTRIES={};
    COUNTRIES.push_back(RawData.at(0)[7]);
    for(int line=1;line<Nlines;line++){
      if(RawData.at(line)[7]!=RawData.at(line-1)[7])
        COUNTRIES.push_back(RawData.at(line)[7]);
    }
  }

  TGraph **glist = new TGraph*[COUNTRIES.size()];  //array of TGraph object-pointers, one for every country
  

  for(int country=0;country<COUNTRIES.size();country++){       //Run once for every country

    vector<int> countrydata,date;  //Arrays to store the data
    int dates=365;  

    for(int line=0;line<Nlines;line++){           //Search every line
      if(RawData.at(line)[7]==COUNTRIES[country]){       //Store valuse if they're from the apropriate country
        countrydata.push_back(stoi(RawData.at(line)[ReadCol]));
        date.push_back(dates--);
      }
    }


    if(OPTION=="cumulative"){         //calculate cumulative values
      for(int i=countrydata.size()-2;i>=0;i--)   //Starting, from the end of the array, aka the earliest time
        countrydata[i]+=countrydata[i+1]; 
    }

    double arrDate[1000];
    std::copy(date.begin(), date.end(), arrDate);  //copy vector to array
    double arrCountry[1000];
    std::copy(countrydata.begin(), countrydata.end(), arrCountry);   //copy vector to array



    glist[country] = new TGraph(date.size(),arrDate,arrCountry);  //give values to the TGraph

    TString helpstr=COUNTRIES[country];

    glist[country]->SetName(helpstr);       //Graph settings
    helpstr= "Graph "+COUNTRIES[country];
    glist[country]->SetTitle(helpstr);
    glist[country]->SetMarkerStyle(1);
    glist[country]->SetLineColor(4);
    glist[country]->SetLineWidth(2);
    glist[country]->SetFillStyle(0);
  

  }

  TMultiGraph *mtg= new TMultiGraph;

  for(int country=0;country<COUNTRIES.size();country++){
    mtg->Add(glist[country]);  //Fill multiGraph
  }
  return mtg;


}