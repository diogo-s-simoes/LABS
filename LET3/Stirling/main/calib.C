#include <cmath>
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPad.h"

#include "TF1.h"
#include "NewReader.h"
#include "LETintegral.h"

int main()  {

    TGraph G;

    G.SetPoint(1,2.459088741e1,1.202473495e1*1.2/73.53);
    G.SetPoint(2,4.442585803e1,2.085033417e1*1.2/73.53);
    G.SetPoint(3,6.386340515e1,2.967428775e1*1.2/73.53);
    G.SetPoint(4,8.250939657e1,3.770010304e1*1.2/73.53);
    G.SetPoint(5,1.031342772e2,4.772126404e1*1.2/73.53);
    G.SetPoint(6,1.237624492e2,5.694757805e1*1.2/73.53);
    G.SetPoint(7,1.431983507e2,6.616895513e1*1.2/73.53);
    G.SetPoint(8,1.634307448e2,7.499620000e1*1.2/73.53);

    auto lCal = [](double *x,double *p=nullptr){
      return p[0]*x[0]+p[1];
    };

    TF1* fCal= new TF1("L", lCal, 1.,500.,2);

    fCal->SetParameter(0,0.1);
    fCal->SetParameter(1,0);

    G.Fit(fCal);

    double Uf1=0.0445*1000;
    double Uf2=0.0965*1000;
    double Uf3=0.1252*1000;

    double F1=fCal->Eval(Uf1);
    double F2=fCal->Eval(Uf2);
    double F3=fCal->Eval(Uf3);

    cout<<F1<<endl<<F2<<endl<<F3<<endl;

    TCanvas* c1 = new TCanvas("cc", "cc", 900,450);
    G.SetMarkerStyle(8);
    
    TAxis *ax_t = G.GetXaxis();
    TAxis *ay_t = G.GetYaxis();

    ax_t->SetTitle("U(V)");
    ay_t->SetTitle("F(N)");
    
   /* auto l = new TLegend(0.65,0.7,0.89,0.89);
   l->AddEntry(fCal,"Fit result", "L");
   l->Draw("same");*/
   
  gStyle->SetOptFit(111);
  gStyle -> SetStatBorderSize(5);
  gStyle -> SetStatFontSize(1);
  gStyle -> SetStatFont(62);
  gStyle -> SetStatTextColor(1);
  gStyle -> SetStatColor(3);
  gStyle -> SetStatStyle(0);
  gStyle -> SetStatX(0.55);
  gStyle -> SetStatY(0.85);
  gStyle -> SetStatW(0.2165);
  
  gPad->SetGrid(1, 1); gPad->Update();

    G.Draw("AP");
    fCal->Draw("same");

    c1->SaveAs("calib.png");

    return 0;
}
