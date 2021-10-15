#include <cmath>

#include "NewReader.h"

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
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


  Area=138./(Smax-Smin)*1e-6;



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



  TGraph TS,TS2;
  TGraph* PV = new TGraph();
  for(int i=0;i<VPTS.size();i++){
    PV->SetPoint(i,VPTS[i][0],VPTS[i][1]);
    TS.SetPoint(i,VPTS[i][3],VPTS[i][2]);
    TS2.SetPoint(i,VPTS[i][2],VPTS[i][4]);
  }

  TCanvas *c1=new TCanvas();
  
  
////////////////////////////////////////////////////////////////////   PV GRAPH //////////////////////////////



    auto lTlow = [=](double *x,double *p=nullptr){
      return n*R*Tmin/x[0];
    };
    TF1* CompressaoIsotermica = new TF1("L", lTlow, Vmin,Vmax,0);
    CompressaoIsotermica->SetLineColor(4);
                
    auto lThigh = [=](double *x,double *p=nullptr){
      return n*R*Tmax/x[0];
    };
    TF1* ExpansaoIsotermica= new TF1("L", lThigh, Vmin,Vmax,0);
    ExpansaoIsotermica->SetLineColor(4);

    double Wideal=ExpansaoIsotermica->Integral(Vmin,Vmax)-CompressaoIsotermica->Integral(Vmin,Vmax);
    cout<<"trabalho ideal= "<<Wideal<<endl;


    TGraph* AquecimentoIsocorico = new TGraph();
    AquecimentoIsocorico->SetPoint(0,Vmin,n*R*Tmax/Vmin);
    AquecimentoIsocorico->SetPoint(1,Vmin,n*R*Tmin/Vmin);

    TGraph ArrefecimentoIsocorico;
    ArrefecimentoIsocorico.SetPoint(0,Vmax,n*R*Tmax/Vmax);
    ArrefecimentoIsocorico.SetPoint(1,Vmax,n*R*Tmin/Vmax);

    TAxis *ax1 = PV->GetXaxis();
    TAxis *ay1 = PV->GetYaxis();
    ax1->SetLimits(.12e-3,.3e-3);
    ay1->SetRangeUser(50e3,400e3);
    ax1->SetTitle("V(m^3)");
    ay1->SetTitle("P(Pa)");

   PV->SetFillColor(kMagenta-10);
   PV->Draw("ALF"); 

   cout<<"trabalho= "<<PV->Integral()<<endl;
 
 
 /*  TPaveText *t = new TPaveText(.55,0.55,.59,.59, "brNDC");
   t->AddText("1");
   t->Draw("same");*/
   
  AquecimentoIsocorico->SetLineColor(4);

  AquecimentoIsocorico->SetLineWidth(2);
  AquecimentoIsocorico->Draw("same L");
  
  
  ArrefecimentoIsocorico.SetLineColor(4);
  ArrefecimentoIsocorico.SetLineWidth(2);
  ArrefecimentoIsocorico.Draw("same L");
  
  
  ExpansaoIsotermica->Draw("same L");
  CompressaoIsotermica->Draw("same L");

   auto legend1 = new TLegend(0.6,0.75,0.9,0.9);
  // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
   legend1->AddEntry(AquecimentoIsocorico,"Ciclo Ideal de Sterling","l");
      legend1->AddEntry(PV,"Ciclo Real de Sterling","f");
   legend1->Draw("same");
   
  c1->SaveAs("bin/PVgraph.png");

/////////////////////////////////////////    TS GRAPH //////////////////////////////////



    auto lSTlow = [=](double *x,double *p=nullptr){
      return Tmin;
    };

    TF1* STlow= new TF1("L", lSTlow, 0.341,0.384,0);
    STlow->SetLineColor(kTeal+4);

    auto lSThigh = [=](double *x,double *p=nullptr){
      return Tmax;
    };

    TF1* SThigh= new TF1("L", lSThigh, .5,.542,0);
    SThigh->SetLineColor(kTeal+4);
    
    auto lSlow = [=](double *x,double *p=nullptr){
      return exp((x[0]+.5555)/(n*5./2.*R));
    };
    TF1* Slow= new TF1("L", lSlow, 0.341,.501,0);
    Slow->SetLineColor(kTeal+4);

    auto lShigh = [=](double *x,double *p=nullptr){
      return exp((x[0]+.513)/(n*5./2.*R));
    };
    TF1* Shigh= new TF1("L", lShigh, 0.384,.5435,0);
    Shigh->SetLineColor(kTeal+4);

    double Qideal=SThigh->Integral(0.5,0.542)-STlow->Integral(0.341,0.384)+Shigh->Integral(0.384,.5435)-Slow->Integral(0.341,.501);
    cout<<"Calor ideal= "<<Qideal<<endl;

  c1->Clear();


    TAxis *ax_t1 = TS.GetXaxis();
    TAxis *ay_t1 = TS.GetYaxis();

    ax_t1->SetLimits(0.3,.6);
    ay_t1->SetRangeUser(300,875);

    ax_t1->SetTitle("T(K)");
    ay_t1->SetTitle("S(J/K)");
    
  TS.SetFillColor(kMagenta-10);
  TS.Draw("AFL");

  Shigh->Draw("same");
  Slow->Draw("same");
  SThigh->Draw("same");
  STlow->Draw("same");

  cout<<"calor= "<<TS.Integral()<<endl;

  //TS2.Draw("AL");
  c1->SaveAs("bin/TSgraph.png");


///////////////////////////////////////////////////////////////////////////////////////////
{

    double W=0,Q=0,E=0;

    TGraph* Wgraph= new TGraph();
    TGraph* Qgraph= new TGraph();
        TGraph* Egraph= new TGraph();

    Wgraph->SetPoint(0,0,0);
    Qgraph->SetPoint(0,0,0);
    Egraph->SetPoint(0,0,0);

    for(int i=0;i<VPTS.size()-1;i++){
      W-=VPTS[i][1]*(VPTS[i+1][0]-VPTS[i][0]);
      Q+=VPTS[i][2]*(VPTS[i+1][3]-VPTS[i][3]);
      E+=n*5./2*R*(VPTS[i+1][2]-VPTS[i][2]);

    Wgraph->SetPoint(i+1,(i*1.)/((double) VPTS.size()),W);
    Qgraph->SetPoint(i+1,(i*1.)/((double) VPTS.size()),Q);
    Egraph->SetPoint(i+1,(i*1.)/((double) VPTS.size()),E);
    }



    TAxis *ay_t2 = Wgraph->GetYaxis();

    ay_t2->SetRangeUser(-25,25);
    
  
    
    
    
    
    
    
    
    
    Wgraph->SetLineColor(4);
        Wgraph->SetLineWidth(2);
    Wgraph->Draw("AL");
    
    
    
    
    
     Qgraph->SetLineColor(2); 
         Qgraph->SetLineWidth(2); 
    Qgraph->Draw("same");
        Egraph->SetLineWidth(2);
    Egraph->SetLineColor(3);
    Egraph->Draw("same");
    
    
    
          auto legend = new TLegend(0.6,0.75,0.9,0.9);
  // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
   legend->AddEntry(Wgraph,"-W(J)- Trabalho","l");
   legend->AddEntry(Qgraph,"Q(J)- Calor","l");
   legend->AddEntry(Egraph,"E(J)- Energia","l");
   legend->Draw("same");
   
   //c1->BuildLegend();
  

    c1->SaveAs("bin/Energy.png");
  }














}




//Smin 0.8708e-04 m          Pmax 0.9835e+05 Pa


//Smax 0.4937e-01 m          Pmin 0.8752e+03 Pa
//message.txt
//7 KB