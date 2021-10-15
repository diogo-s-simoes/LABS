#include <cmath>

#include "NewReader.h"

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"


int main(){

  NewReader tS("data/S(t)_corrected.txt");
  NewReader tP("data/P(t)_corrected.txt");

  vector<double> instante;

  vector <vector<double>> data;
  int Nlines = tS.GetNrInstantes();

  TGraph G;

  for(int i=0; i<Nlines; i++){
    instante.push_back(tS.GetTempo(i));
    instante.push_back(tS.GetDataVector(i));
    instante.push_back(tP.GetDataVector(i)*100+1);

    data.push_back(instante);
    G.SetPoint(i,instante[0],instante[2]);
    instante.clear();
  }


  double R = 8.3145;
  double Area = M_PI*36.*1e-4;
  double Smin = 0.8708e-04;
  double Smax = 0.4937e-01;
  double Pmin = 0.8752e+03;
  double Pmax = 0.9835e+05;
  double Patm = 101425.;
  double Tmax = 845.15;
  double Tmin = 308.4;


  Area=138./(Smax-Smin)*1e-4;



  //  double Vmax =  (Smax-Smin)*Area*(Patm+Pmax)/((Patm+Pmax)-(Patm+Pmin)*Tmax/Tmin);

  double Vmax = 278.*1e-6;
  double Vmin = 140.*1e-6;


  double n1 = Vmax*(Patm+Pmin)/(Tmin*R);
  double n2 = Vmin*(Patm+Pmax)/(Tmax*R);

  cout<<Vmax<<"   "<<(n1+n2)/2.<<" \\pm "<<(n1-n2)/2.<<endl;


  double n = (n1+n2)/2.;

//  cout<<(Smax-Smin)*Area<<endl;

  vector<vector<double>> VPTS;

  for(int i=0; i<data.size(); i++){
    vector<double> temp;

    temp.push_back(Vmax - (Smax-data[i][1]*.01)*Area);
    temp.push_back(Patm+data[i][2]);
    temp.push_back(temp[0]*temp[1]/(n*R));
    temp.push_back(n*5./2.*R*log(temp[2])+n*R*log(temp[0]));
    temp.push_back(n*7./2.*R*log(temp[1]*pow(temp[0],7./5.)));
    temp.push_back(n*7./2.*R*log(temp[2])+n*R*log(temp[1]));
    //cout<<temp[1]<<endl;
    VPTS.push_back(temp);

  }



  TGraph PV,TS,TS2;

  for(int i=0;i<VPTS.size();i++){
    PV.SetPoint(i,VPTS[i][0],VPTS[i][1]);
    TS.SetPoint(i,VPTS[i][2],VPTS[i][3]);
    TS2.SetPoint(i,VPTS[i][2],VPTS[i][4]);
  }

  TCanvas *c1=new TCanvas();

  PV.Draw("AL");

  c1->SaveAs("bin/PVgraph.png");

  c1->Clear();

  TS.Draw("AL");
  //TS2.Draw("AL");
  c1->SaveAs("bin/TSgraph.png");



}




//Smin 0.8708e-04 m          Pmax 0.9835e+05 Pa


//Smax 0.4937e-01 m          Pmin 0.8752e+03 Pa