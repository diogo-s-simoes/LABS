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



double coth(double x){
  return (exp(2*x)+1)/(exp(2*x)-1);
}


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
      cout<<stod(ficheiro1.GetData()[i][j])<<"   "<<flush;
    }
    cout<<endl;
    DADOS.push_back(temp1);
    temp1.clear();
    cout<<endl;
    
  }




  DataReader ficheiro2("data/histerese1.txt");

  vector<vector<double>> DADOS2;

  vector<double> temp2;

  N=ficheiro2.GetLines();
  cout<<N<<endl;

  for(int i=0;i<N;++i){
    for(int j = 0;j<17;++j){
      temp2.push_back(stod(ficheiro2.GetData()[i][j]));
      cout<<stod(ficheiro2.GetData()[i][j])<<"   "<<flush;
    }
    cout<<endl;
    DADOS2.push_back(temp2);
    temp2.clear();
    cout<<endl;
    
  }




cout << "a"<<endl;

  TGraphErrors *Hysteresisis = new TGraphErrors[DADOS.size()];
  TGraph HCoerc,Bsat,Brem;
  HCoerc.SetMarkerStyle(33);
  Bsat.SetMarkerStyle(33);
  Brem.SetMarkerStyle(33);
  HCoerc.SetMarkerColor(kAzure-3);
  Bsat.SetMarkerColor(kAzure-3);
  Brem.SetMarkerColor(kAzure-3);
  HCoerc.SetMarkerSize(2.5);
  Bsat.SetMarkerSize(2.5);
  Brem.SetMarkerSize(2.5);
  TAxis *ax1 = HCoerc.GetXaxis();
  TAxis *ay1 = HCoerc.GetYaxis();
  ay1->SetTitle("H_{c} (A/m)");
  ax1->SetTitle("H_{max} (A/m)");
  TAxis *ax2 = Bsat.GetXaxis();
  TAxis *ay2 = Bsat.GetYaxis();
  ay2->SetTitle("B_{max} (T)");
  ax2->SetTitle("H_{max} (A/m)");
  TAxis *ax3 = Brem.GetXaxis();
  TAxis *ay3 = Brem.GetYaxis();
  ay3->SetTitle("B_{rem} (T)");
  ax3->SetTitle("H_{max} (A/m)");


  for(int i=0;i<DADOS.size();i++){
    double Hm,HM,Bm,BM,B0m,B0M,H0m,H0M;

    double eHm,eHM,eBm,eBM,eB0m,eB0M,eH0m,eH0M;

    double scale=0;

    if(DADOS[i][16]==1)
      scale = .4;
    else if(DADOS[i][16]==2)
      scale = 1.;
    else if(DADOS[i][16]==3)
      scale = 4.;

    double ConvB=100/49/.154;
    double ConvH=505/0.48;

    Hm=(DADOS[i][0]+DADOS[i][1])/2*scale*ConvH/1000;
    HM=(DADOS[i][2]+DADOS[i][3])/2*scale*ConvH/1000;
    Bm=(DADOS[i][4]+DADOS[i][5])/2*ConvB/1000;
    BM=(DADOS[i][6]+DADOS[i][7])/2*ConvB/1000;
    B0m=(DADOS[i][8]+DADOS[i][9])/2*ConvB/1000;
    B0M=(DADOS[i][10]+DADOS[i][11])/2*ConvB/1000;
    H0m=(DADOS[i][12]+DADOS[i][13])/2*scale*ConvH/1000;
    H0M=(DADOS[i][14]+DADOS[i][15])/2*scale*ConvH/1000;


    eHm=(DADOS[i][0]-DADOS[i][1])/2*scale*ConvH/1000;
    eHM=(DADOS[i][2]-DADOS[i][3])/2*scale*ConvH/1000;
    eBm=(DADOS[i][4]-DADOS[i][5])/2*ConvB/1000;
    eBM=(DADOS[i][6]-DADOS[i][7])/2*ConvB/1000;
    eB0m=(DADOS[i][8]-DADOS[i][9])/2*ConvB/1000;
    eB0M=(DADOS[i][10]-DADOS[i][11])/2*ConvB/1000;
    eH0m=(DADOS[i][12]-DADOS[i][13])/2*scale*ConvH/1000;
    eH0M=(DADOS[i][14]-DADOS[i][15])/2*scale*ConvH/1000;



    Hysteresisis[i].SetPoint(0,Hm,Bm);
    Hysteresisis[i].SetPointError(0,eHm,eBm);
    Hysteresisis[i].SetPoint(1,HM,BM);
    Hysteresisis[i].SetPointError(1,eHM,eBM);
    Hysteresisis[i].SetPoint(2,H0m,0.);
    Hysteresisis[i].SetPointError(2,eH0m,0.);
    Hysteresisis[i].SetPoint(3,H0M,0.);
    Hysteresisis[i].SetPointError(3,eH0M,0.);
    Hysteresisis[i].SetPoint(4,0,B0m);
    Hysteresisis[i].SetPointError(4,0.,eB0m);
    Hysteresisis[i].SetPoint(5,0,B0M);
    Hysteresisis[i].SetPointError(5,0.,eB0M);


    Bsat.SetPoint(i,(HM-Hm)/2,(BM-Bm)/2-1.25663*1e-6*(HM-Hm)/2);
    cout<<HM<<"   "<<1.25663*1e-6*(HM-Hm)/2<<endl;
    Brem.SetPoint(i,(HM-Hm)/2,(B0M-B0m)/2-1.25663*1e-6*(HM-Hm)/2);
    HCoerc.SetPoint(i,(HM-Hm)/2,(H0M-H0m)/2);
  }



  for(int i=0;i<DADOS2.size();i++){
    double Hm,HM,Bm,BM,B0m,B0M,H0m,H0M;

    double eHm,eHM,eBm,eBM,eB0m,eB0M,eH0m,eH0M;

    double scale=0;

    if(DADOS2[i][16]==1)
      scale = .4;
    else if(DADOS2[i][16]==2)
      scale = 1.;
    else if(DADOS2[i][16]==3)
      scale = 4.;

    double ConvB=100/49/.154;
    double ConvH=505/0.48;

    Hm=(DADOS2[i][0]+DADOS2[i][1])/2*scale*ConvH/1000;
    HM=(DADOS2[i][2]+DADOS2[i][3])/2*scale*ConvH/1000;
    Bm=(DADOS2[i][4]+DADOS2[i][5])/2*ConvB/1000;
    BM=(DADOS2[i][6]+DADOS2[i][7])/2*ConvB/1000;
    B0m=(DADOS2[i][8]+DADOS2[i][9])/2*ConvB/1000;
    B0M=(DADOS2[i][10]+DADOS2[i][11])/2*ConvB/1000;
    H0m=(DADOS2[i][12]+DADOS2[i][13])/2*scale*ConvH/1000;
    H0M=(DADOS2[i][14]+DADOS2[i][15])/2*scale*ConvH/1000;


    Bsat.SetPoint(i+DADOS.size(),(HM-Hm)/2,(BM-Bm)/2);
    cout<<HM<<"   "<<1.25663*1e-6*(HM-Hm)/2<<endl;
    Brem.SetPoint(i+DADOS.size(),(HM-Hm)/2,(B0M-B0m)/2);
    HCoerc.SetPoint(i+DADOS.size(),(HM-Hm)/2,(H0M-H0m)/2);
  }

  TCanvas* c1 = new TCanvas("","",1200,800);
    c1->SetLeftMargin(0.2);
    Bsat.Draw("AP");
    c1->SaveAs("Saturado.png");
    c1->Clear();
    HCoerc.Draw("AP");
    c1->SaveAs("Coerc.png");
    c1->Clear();
    Brem.Draw("AP");
    c1->SaveAs("Reman.png");
    c1->Clear();



  auto li2 = [&](double *x,double *p=nullptr){
    double Ms= p[0];
    double c=p[1];
    double a=p[2];
    double alpha=p[3];
    double k=p[4];
    double delta =1;
//    return (p[1]*Ms/p[2]*(1-coth((x[1]+p[3]*x[0])/p[2])*coth((x[1]+p[3]*x[0])/p[2])+(p[2]/(x[1]+p[3]*x[0]))*(p[2]/(x[1]+p[3]*x[0])))+(1-p[1])*(Ms*(coth((x[1]+p[3]*x[0])/p[2])-p[2]/(x[1]+p[3]*x[0]))-x[0])/(p[4]*delta*(1-p[1])-p[3]*((Ms*(coth((x[1]+p[3]*x[0])/p[2])-p[2]/(x[1]+p[3]*x[0])))-x[0])))/(1-p[3]*p[1]);
  
    double B=0;
    double dH=.0001;
    double dMirr,He,Man,Mirr=0;
      
    double M=0;
    for(double H = 1e-12;H<x[0];H+=dH){
      He=H+alpha*M;
      Man=Ms*(1/(tanh(He/a))-a/He);

 //     if(down==1) delta=-1;
 //     else delta=1;

      dMirr=(Man-Mirr)/(k*delta-alpha*(Man-Mirr))*dH;
      Mirr+=dMirr;
      M=c*Man+(1-c)*Mirr;
      B=(H*1.256637e-6+alpha*M);
    }
     //if(x[0]<5000) cout<<x[0]<<endl;

      return B;
  };

  TF1 *Fn= new TF1("F", li2, -1,100,5);









    //Fn->SetParLimits(0,10000.,3./1.256637e-6);
    Fn->SetParameter(0,14103.9);

    //Fn->SetParLimits(1,0.,1.);
    Fn->SetParameter(1,0.062309);
    
    //Fn->SetParLimits(2,0.,1000000.);
    Fn->SetParameter(2,0.440371);
    
    //Fn->SetParLimits(3,0.,100000.);
    Fn->SetParameter(3,9.40263e-05);
    
    //Fn->SetParLimits(4,0.,100000.);
    Fn->SetParameter(4,11.9355);
    

    //Bsat.Fit(Fn);



    Bsat.Draw("AP");
    Fn->Draw("same");
    cout<<Fn->Derivative(0.1)<<endl;

    c1->SaveAs("Hysteresisis.png");
    c1->Clear();


    TGraph gCurva;
    int choice=2;


    double Ms= 14103.9;
    double c=0.062309;
    double a=0.440371;
    double alpha=9.40263e-05;
    double k=11.9355;
    double Hmax=Hysteresisis[choice].GetPointX(1);
    double delta =1;

    int down=1;
    double B=0;
    double dH=.00001;
    double dMirr,He,Man,Mirr=0;
      
    double M=0,H=1e-12;

    for(int i=0;i<1e8;i++){
      He=H+alpha*M;
      Man=Ms*(1/(tanh(He/a))-a/He);

      if(down==-1) delta=-1;
      else delta=1;

      dMirr=(Man-Mirr)/(k*delta-alpha*(Man-Mirr))*dH*down;
      Mirr+=dMirr;
      M=c*Man+(1-c)*Mirr;
      B=(1.256637e-6*H +alpha*M);


      gCurva.SetPoint(i,H,B);

      //cout<<H<<"    "<<dMirr<<endl;
      if(H>Hmax) down=-1;
      else if(H<-Hmax) down=1;
      H+=dH*down;

    }



  Hysteresisis[choice].SetMarkerStyle(33);
  Hysteresisis[choice].SetMarkerColor(kAzure-3);
  Hysteresisis[choice].SetMarkerSize(2.5);


  TAxis *ax5 = Hysteresisis[choice].GetXaxis();
  TAxis *ay5 = Hysteresisis[choice].GetYaxis();
  ay5->SetTitle("B (T)");
  ax5->SetTitle("H (A/m)");

  gCurva.SetMarkerStyle(1);
  gCurva.SetMarkerColor(kAzure-6);
  gCurva.SetMarkerSize(.5);

    gCurva.Draw("AP");
    Hysteresisis[choice].Draw("same P");

    c1->SaveAs("HysteresisisCurve.png");

/*  double Ms= 14103.9;
    double c=0.062309;
    double a=0.440371;
    double alpha=9.40263e-05;
    double k=11.9355;
    double Hmax=100;
    double delta =1;

    int down=1;
    double B=0;
    double dH=.001;
    double dMirr,He,Man,Mirr=0;
      
    double M=0,H=1e-12;

    for(int i=0;i<5e5;i++){
      He=H+alpha*M;
      Man=Ms*(1/(tanh(He/a))-a/He);

      if(down==-1) delta=-1;
      else delta=1;

      dMirr=(Man-Mirr)/(k*delta-alpha*(Man-Mirr))*dH*down;
      Mirr+=dMirr;
      M=c*Man+(1-c)*Mirr;
      B=(1.256637e-6*H +alpha*M);


      gCurva.SetPoint(i,H,B);

      //cout<<H<<"    "<<dMirr<<endl;
      if(H>Hmax) down=-1;
      else if(H<-Hmax) down=1;
      H+=dH*down;

    }
  
    Hysteresisis[0].SetMarkerStyle(33);
    Hysteresisis[0].SetMarkerColor(kAzure-3);
    Hysteresisis[0].SetMarkerSize(2.5);




  
    Hysteresisis[0].Draw("AP");
    gCurva.Draw("same P");
    gCurva.Clear();



    for(int i=1;i<6;i++){

     Ms= 14103.9;
     c=0.062309;
     a=0.440371;
     alpha=9.40263e-05;
     k=11.9355;
     delta =1;

     down=1;
     B=0;
     dH=.001;
     dMirr,He,Man,Mirr=0;
      
     M=0,H=1e-12;


     Hmax=Hysteresisis[i].GetPointX(0);


    for(int i=0;i<5e5;i++){
      He=H+alpha*M;
      Man=Ms*(1/(tanh(He/a))-a/He);

      if(down==-1) delta=-1;
      else delta=1;

      dMirr=(Man-Mirr)/(k*delta-alpha*(Man-Mirr))*dH*down;
      Mirr+=dMirr;
      M=c*Man+(1-c)*Mirr;
      B=(1.256637e-6*H +alpha*M);


      gCurva.SetPoint(i,H,B);

      //cout<<H<<"    "<<dMirr<<endl;
      if(H>Hmax) down=-1;
      else if(H<-Hmax) down=1;
      H+=dH*down;

    }
  
    Hysteresisis[i].SetMarkerStyle(33);
    Hysteresisis[i].SetMarkerColor(kAzure-3);
    Hysteresisis[i].SetMarkerSize(2.5);




    gCurva.Draw("same P");
    Hysteresisis[i].Draw("same P");
  }*/

    cout<<"Coerc:"<<TMath::MaxElement(HCoerc.GetN(),HCoerc.GetY())<<endl;
    cout<<"Sat:"<<TMath::MaxElement(Bsat.GetN(),Bsat.GetY())<<endl;
    cout<<"Rem:"<<TMath::MaxElement(Brem.GetN(),Brem.GetY())<<endl;


  return 0;
}