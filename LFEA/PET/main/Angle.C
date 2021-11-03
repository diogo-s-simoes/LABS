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

    TGraphErrors* Graphy = new TGraphErrors();
    Graphy->SetMarkerSize(2);
    Graphy->SetMarkerColor(kGreen+2);
    Graphy->SetMarkerStyle(kFullSquare);
    Graphy->SetLineWidth(3);
    Graphy->SetLineColor(kBlue-1);
    Graphy->SetFillColor(1);
    Graphy->SetFillStyle(3004);
    Graphy->GetXaxis()->SetTitle("Angle (rad)");
    Graphy->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graphy->SetTitle("Correlac#tilde{a}o #hat{A}ngular");

    for (int i = 0; i<Nlines; ++i){
        Graphy->SetPoint(i,M_PI/180.*atof(&(data.GetData()[i][0][0])),atof(&(data.GetData()[i][3][0]))/atof(&(data.GetData()[i][4][0]))-52./200.);
        Graphy->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data.GetData()[i][3][0])))/atof(&(data.GetData()[i][4][0])));
    }

    double r0 = 15.3;
    double R = 5.67/2;

    auto l_integrand = [&](double *x,double *p=nullptr){
      return r0/pow(r0*r0+x[0]*x[0],3./2.)*2*sqrt(R*R-x[0]*x[0]);
    };
    TF1* f_integrand= new TF1("integrand", l_integrand, -1e9,1e9,0);


    auto l_Sangle = [&](double *x,double *p=nullptr){
        if(fabs(x[0])<=acos(r0/sqrt(r0*r0+R*R))) 
            return p[0]*f_integrand->Integral(-R,r0*sqrt(1/(pow(cos(acos(r0/sqrt(r0*r0+R*R))-fabs(x[0])),2))-1));
        if(fabs(x[0])<=2*acos(r0/sqrt(r0*r0+R*R)))
            return p[0]*(f_integrand->Integral(-R,R)-f_integrand->Integral(-R,r0*sqrt(1/(pow(cos(acos(r0/sqrt(r0*r0+R*R))-fabs(x[0])),2))-1)));
        else return 0.;
    };
    TF1* f_Sangle= new TF1("Solid_Angle", l_Sangle, -2*acos(r0/sqrt(r0*r0+R*R)),2*acos(r0/sqrt(r0*r0+R*R)),1);
    f_Sangle->SetParameter(0,1);

    cout<<2*acos(r0/sqrt(r0*r0+R*R))*180/M_PI<<endl;

    Graphy->Fit(f_Sangle);

    TCanvas* c1 = new TCanvas("","",1920,1080);
    gStyle->SetOptStat(0);
    gPad->SetGrid(1, 1);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetOptFit(111);
    gStyle -> SetStatBorderSize(5);
    gStyle -> SetStatFontSize(0.2);
    gStyle -> SetStatFont(62);
    gStyle -> SetStatTextColor(1);
    gStyle -> SetStatColor(6);
    gStyle -> SetStatStyle(1);
    gStyle -> SetStatX(0.85);
    gStyle -> SetStatY(0.85);
    gStyle -> SetStatW(0.1365);

    Graphy->Draw("AP");
    //f_Sangle->Draw();
    c1->SaveAs("angle.png");

    f_Sangle->SetParameter(0,1);
    cout<<f_Sangle->Eval(0.)<<endl;

    return 0;
}
