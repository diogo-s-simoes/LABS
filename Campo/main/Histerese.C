#include <cmath>
#include "DataReader.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "ODEsolver.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"


int main(){

  //read file
  DataReader ficheiro1("data/histerese2.txt");

  vector<vector<double>> DADOS;

  vector<double> temp1;

  int N=ficheiro1.GetLines();
  cout<<N<<endl;

  for(int i=0;i<N;++i){
    for(int j = 0;j<17;++j){
      temp1.push_back(stod(ficheiro1.GetData()[i][j]));
      cout<<"i: "<<i<<" j: "<<j<<" v: "<<stod(ficheiro1.GetData()[i][j])<<endl;
    }
    cout<<endl;
    DADOS.push_back(temp1);
    temp1.clear();
    cout<<"asdjsdni"<<endl;
    
  }

cout << "a"<<endl;

  TGraphErrors *Hysteresisis = new TGraphErrors[10];

  for(int i=0;i<DADOS.size();i++){
    double Hm,HM,Bm,BM,B0m,B0M,H0m,H0M;

    double eHm,eHM,eBm,eBM,eB0m,eB0M,eH0m,eH0M;

    double scale;

    if(DADOS[i][16]==1)
      scale = .4;
    else if(DADOS[i][16]==1)
      scale = 1.;
    else if(DADOS[i][16]==1)
      scale = 4.;


    Hm=(DADOS[i][0]+DADOS[i][1])/2*scale;
    HM=(DADOS[i][2]+DADOS[i][3])/2*scale;
    Bm=(DADOS[i][4]+DADOS[i][5])/2;
    BM=(DADOS[i][6]+DADOS[i][7])/2;
    B0m=(DADOS[i][8]+DADOS[i][9])/2;
    B0M=(DADOS[i][10]+DADOS[i][11])/2;
    H0m=(DADOS[i][12]+DADOS[i][13])/2*scale;
    H0M=(DADOS[i][14]+DADOS[i][15])/2*scale;    


    eHm=(DADOS[i][0]-DADOS[i][1])/2*scale;
    eHM=(DADOS[i][2]-DADOS[i][3])/2*scale;
    eBm=(DADOS[i][4]-DADOS[i][5])/2;
    eBM=(DADOS[i][6]-DADOS[i][7])/2;
    eB0m=(DADOS[i][8]-DADOS[i][9])/2;
    eB0M=(DADOS[i][10]-DADOS[i][11])/2;
    eH0m=(DADOS[i][12]-DADOS[i][13])/2*scale;
    eH0M=(DADOS[i][14]-DADOS[i][15])/2*scale;



    Hysteresisis[i].SetPoint(0,Hm,Bm);
    Hysteresisis[i].SetPointError(0,eHm,eBm);
    Hysteresisis[i].SetPoint(1,HM,BM);
    Hysteresisis[i].SetPoint(1,eHM,eBM);
    Hysteresisis[i].SetPoint(2,H0m,0.);
    Hysteresisis[i].SetPoint(2,eH0m,0.);
    Hysteresisis[i].SetPoint(3,H0m,0.);
    Hysteresisis[i].SetPoint(3,eH0m,0.);
    Hysteresisis[i].SetPoint(4,0,B0m);
    Hysteresisis[i].SetPoint(4,0.,eB0m);
    Hysteresisis[i].SetPoint(5,0,B0m);
    Hysteresisis[i].SetPoint(5,0.,eB0m);
  }


  /*auto lHist = [](double *x,double *p=nullptr){


    auto DifEq = [](){
      return 
    }

    return 
  };
*/





  return 0;
}