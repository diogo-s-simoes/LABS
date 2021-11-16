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

    DataReader data("data/phi.txt");

    double Nlines =data.GetLines();

    TGraphErrors* Graph1 = new TGraphErrors();
    Graph1->SetMarkerSize(2);
    Graph1->SetMarkerColor(kBlue+2);
    Graph1->SetMarkerStyle(kFullSquare);
    Graph1->SetLineWidth(3);
    Graph1->SetLineColor(kBlue-1);
    Graph1->SetFillColor(1);
    Graph1->SetFillStyle(3004);
    Graph1->GetXaxis()->SetTitle("Angle (rad)");
    Graph1->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph1->SetTitle("Variacao posicao fonte no eixo dos detetores para x= 1 quad");


   TGraphErrors* Graph2 = new TGraphErrors();
    Graph2->SetMarkerSize(2);
    Graph2->SetMarkerColor(kRed+2);
    Graph2->SetMarkerStyle(kFullSquare);
    Graph2->SetLineWidth(3);
    Graph2->SetLineColor(kBlue-1);
    Graph2->SetFillColor(1);
    Graph2->SetFillStyle(3004);
    Graph2->GetXaxis()->SetTitle("Angle (rad)");
    Graph2->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph2->SetTitle("Variacao posicao fonte no eixo dos detetores para x= 2 quad");

    double bol=0;
    double i2=0;
    for (int i = 0; i<Nlines; ++i){
        if(atof(&(data.GetData()[i][5][0]))==0){
            Graph1->SetPoint(i,M_PI/180.*atof(&(data.GetData()[i][0][0])),atof(&(data.GetData()[i][3][0]))/atof(&(data.GetData()[i][4][0]))-52./200.);
            Graph1->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data.GetData()[i][3][0])))/atof(&(data.GetData()[i][4][0])));
        }
        if(atof(&(data.GetData()[i][5][0]))==5){
            if(bol==0){bol=1;i2=i;}
            Graph2->SetPoint(i-i2,M_PI/180.*atof(&(data.GetData()[i][0][0])),atof(&(data.GetData()[i][3][0]))/atof(&(data.GetData()[i][4][0]))-52./200.);
            Graph2->SetPointError(i-i2,0.1*M_PI/180,sqrt(atof(&(data.GetData()[i][3][0])))/atof(&(data.GetData()[i][4][0])));
        }
    }

    /*double r0 = 15.3;
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

    Graph1->Fit(f_Sangle);*/

    auto l_gaussian = [&](double *x,double *p=nullptr){
      return p[0]*exp(-0.5*((x[0]-p[1])/p[2])*((x[0]-p[1])/p[2]))+p[0]*exp(-0.5*((x[0]-p[3])/p[2])*((x[0]-p[3])/p[2]));
    };
    TF1* f_gaussian= new TF1("gaussian", l_gaussian, -1e9,1e9,4);

    f_gaussian->SetParameter(0,100);
    f_gaussian->SetParameter(1,0.3);
    f_gaussian->SetParameter(2,1);
    f_gaussian->SetParameter(3,2.7);

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


    Graph1->Draw("AP");
    c1->SaveAs("FontePhi0.png");
    c1->Clear();

    Graph2->Fit(f_gaussian);

    Graph2->Draw("AP");
    c1->SaveAs("FontePhi5.png");
    c1->Clear();

    return 0;
}
