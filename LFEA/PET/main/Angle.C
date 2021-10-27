#include <cmath>
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPad.h"
#include "TF1.h"
#include "TH1D.h"
#include "NewReader.h"
#include "LETintegral.h"
#include "Spline3Interpolator.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "DataReader.h"

int main(){

    DataReader data("data/angulos.txt");
    double Nlines=data.GetLines();

    TGraph* Graphy = new TGraph();

    for (int i = 0; i<Nlines; ++i){
        Graphy->SetPoint(i,atof(&(data.GetData()[i][0][0])),atof(&(data.GetData()[i][3][0])));
    }

    double r0 = 15.6;
    double R = 5;
    auto l_integrand = [&](double *x,double *p=nullptr){
      return r0/pow(r0*r0+x[0]*x[0],3./2.)*2*sqrt(R*R-x[0]*x[0]);
    };
    TF1* f_integrand= new TF1("integrand", l_integrand, -1e9,1e9,0);


    auto l_Sangle = [&](double *x,double *p=nullptr){
      return p[0]*f_integrand->Integral(-R,r0*sqrt(1/(pow(cos(acos(r0/sqrt(r0*r0+R*R))-fabs(x[0])),2))-1));
    };
    TF1* f_Sangle= new TF1("Solid_Angle", l_Sangle, -acos(r0/sqrt(r0*r0+R*R)),acos(r0/sqrt(r0*r0+R*R)),1);
    f_Sangle->SetParameter(0,1);

    Graphy->Fit(f_Sangle);

    TCanvas* c1 = new TCanvas("","",1920,1080);
    Graphy->Draw("AP");
    c1->SaveAs("angle.png");

    return 0;
}
