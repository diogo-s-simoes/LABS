#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TApplication.h"
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

    double Uf1=0.0445;
    double Uf2=0.0965;
    double Uf3=0.1252;

    double F1=fCal->Eval(Uf1);
    double F2=fCal->Eval(Uf2);
    double F3=fCal->Eval(Uf3);

    cout<<F1<<endl<<F2<<endl<<F3<<endl;

    TCanvas* c1 = new TCanvas();

    fCal->Draw("");

    c1->SaveAs("calib.png");

    return 0;
}
