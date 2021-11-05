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

    DataReader data1("data/delay.txt");
    double Nlines1=data1.GetLines();

    DataReader data2("data/tab2.txt");
    double Nlines2=data2.GetLines();

    TGraphErrors* G1 = new TGraphErrors();
    G1->SetMarkerSize(2);
    G1->SetMarkerColor(kGreen+2);
    G1->SetMarkerStyle(kFullSquare);
    G1->SetLineWidth(3);
    G1->SetLineColor(kBlue-1);
    G1->SetFillColor(1);
    G1->SetFillStyle(3004);
    G1->GetXaxis()->SetTitle("Janela de Aquisicao [ns]");
    G1->GetYaxis()->SetTitle("Contagens");
    G1->SetTitle("Janela Minima");

    TGraphErrors* G2 = new TGraphErrors();
    G2->SetMarkerSize(2);
    G2->SetMarkerColor(kGreen+2);
    G2->SetMarkerStyle(kFullSquare);
    G2->SetLineWidth(3);
    G2->SetLineColor(kBlue-1);
    G2->SetFillColor(1);
    G2->SetFillStyle(3004);
    G2->GetXaxis()->SetTitle("Janela de Aquisicao [s]");
    G2->GetYaxis()->SetTitle("Coincidências [s^{-1}]");
    G2->SetTitle("Coincidencias Fortuitas");


    double R1=0;
    double R2=0;
    double dR1=0;
    double dR2=0;


    for (int i = 0; i<Nlines1; ++i){
        G1->SetPoint(i,48-atof(&(data1.GetData()[i][0][0])),atof(&(data1.GetData()[i][3][0])));
        G1->SetPointError(i,8,sqrt(atof(&(data1.GetData()[i][3][0]))));
    }
    for (int i = 0; i<Nlines2-1; ++i){
        G2->SetPoint(i,(1e-9)*atof(&(data2.GetData()[i][0][0])),atof(&(data2.GetData()[i][3][0]))/atof(&(data2.GetData()[i][4][0])));
        G2->SetPointError(i,(1e-9)*atof(&(data2.GetData()[i][5][0])),sqrt(atof(&(data2.GetData()[i][3][0])))/atof(&(data2.GetData()[i][4][0])));
        R1+=atof(&(data2.GetData()[i][1][0]))/atof(&(data2.GetData()[i][4][0]));
        R2+=atof(&(data2.GetData()[i][2][0]))/atof(&(data2.GetData()[i][4][0]));
    }
    R1/=(Nlines2-1);
    R2/=(Nlines2-1);
    for (int i = 0; i<Nlines2-1; ++i){
        dR1=pow(atof(&(data2.GetData()[i][1][0]))/atof(&(data2.GetData()[i][4][0]))-R1,2);
        dR2=pow(atof(&(data2.GetData()[i][2][0]))/atof(&(data2.GetData()[i][4][0]))-R2,2);
    }
    dR1=sqrt(dR1/(Nlines2-1));
    dR2=sqrt(dR2/(Nlines2-1));
    double dRt=4*(dR1/R1+dR2/R2);

    cout<<"R1= "<<R1<<"+-"<<dR1<<endl;
    cout<<"R2= "<<R2<<"+-"<<dR2<<endl;
    cout<<"Rt= "<<2*R1*R2<<"+-"<<dRt<<endl;


    auto l_step = [&](double *x,double *p=nullptr){
      return p[0]*erf(p[1]*(x[0]-p[2]))+p[3];
    };
    TF1* f_step= new TF1("STEP", l_step, -1e9,1e9,4);


    auto l_linear = [&](double *x,double *p=nullptr){
      return p[0]*x[0]+p[1];
    };
    TF1* f_linear= new TF1("LINEAR", l_linear, -1e9,1e9,2);

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

    f_step->SetParameter(0,1);
    f_step->SetParameter(1,0.1);
    f_step->SetParameter(2,1);
    f_step->SetParameter(3,1);

    G1->Fit(f_step);
    G2->Fit(f_linear);

    G1->Draw("AP");
    c1->SaveAs("delay.png");
    c1->Clear();

    G2->Draw("AP");
    c1->SaveAs("janela.png");
    c1->Clear();

    double E0=15e4*3.7;
    double Em=E0*exp(-log(2)/2.6*15.);

    double cts=3796;
    double temp=30;
    double eff = cts/(temp*Em*0.213/(4*M_PI));
    cout<<"efficiency= "<<eff<<endl;

    return 0;
}
