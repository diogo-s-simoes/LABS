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

    DataReader data("data/FonteP1.txt");
    DataReader data2("data/FonteP2.txt");
    DataReader data3("data/FonteP3.txt");
    DataReader data4("data/angulos.txt");

    double Nlines = data.GetLines();
    double Nlines2 =data2.GetLines();
    double Nlines3 =data3.GetLines();
    double Nlines4 =data4.GetLines();

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
    Graph1->SetTitle("Variacao posicao fonte no eixo perpendicular aos detetores quando estao na posicao central para x= 1 quad");



   TGraphErrors* Graph2 = new TGraphErrors();
    Graph2->SetMarkerSize(2);
    Graph2->SetMarkerColor(kRed);
    Graph2->SetMarkerStyle(kFullSquare);
    Graph2->SetLineWidth(3);
    Graph2->SetLineColor(kBlue-1);
    Graph2->SetFillColor(1);
    Graph2->SetFillStyle(3004);
    Graph2->GetXaxis()->SetTitle("Angle (rad)");
    Graph2->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph2->SetTitle("Variacao posicao fonte no eixo dos detetores para x= 2 quad");

     TGraphErrors* Graph3 = new TGraphErrors();
    Graph3->SetMarkerSize(2);
    Graph3->SetMarkerColor(kGreen-2);
    Graph3->SetMarkerStyle(kFullSquare);
    Graph3->SetLineWidth(3);
    Graph3->SetLineColor(kBlue-1);
    Graph3->SetFillColor(1);
    Graph3->SetFillStyle(3004);
    Graph3->GetXaxis()->SetTitle("Angle (rad)");
    Graph3->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph3->SetTitle("Variacao posicao fonte no eixo dos detetores para x= 3 quad");

         TGraphErrors* Graph4 = new TGraphErrors();
    Graph4->SetMarkerSize(2);
    Graph4->SetMarkerColor(kBlue+6);
    Graph4->SetMarkerStyle(kFullSquare);
    Graph4->SetLineWidth(3);
    Graph4->SetLineColor(kBlue-1);
    Graph4->SetFillColor(1);
    Graph4->SetFillStyle(3004);
    Graph4->GetXaxis()->SetTitle("Angle (rad)");
    Graph4->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph4->SetTitle("Variacao posicao fonte no eixo dos detetores para x= 4 quad");
 
    for (int i = 0; i<Nlines; ++i){
        Graph1->SetPoint(i,M_PI/180.*atof(&(data.GetData()[i][0][0])),atof(&(data.GetData()[i][3][0]))/atof(&(data.GetData()[i][4][0]))-52./200.);
        Graph1->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data.GetData()[i][3][0])))/atof(&(data.GetData()[i][4][0])));
    }

    for (int i = 0; i<Nlines2; ++i){
        Graph2->SetPoint(i,M_PI/180.*atof(&(data2.GetData()[i][0][0])),atof(&(data2.GetData()[i][3][0]))/atof(&(data2.GetData()[i][4][0]))-52./200.);
        Graph2->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data2.GetData()[i][3][0])))/atof(&(data2.GetData()[i][4][0])));
    }
    
    for (int i = 0; i<Nlines3; ++i){
        Graph3->SetPoint(i,M_PI/180.*atof(&(data3.GetData()[i][0][0])),atof(&(data3.GetData()[i][3][0]))/atof(&(data3.GetData()[i][4][0]))-52./200.);
        Graph3->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data3.GetData()[i][3][0])))/atof(&(data3.GetData()[i][4][0])));
    }

    for (int i = 0; i<Nlines4; ++i){
        Graph4->SetPoint(i,M_PI/180.*atof(&(data4.GetData()[i][0][0])),atof(&(data4.GetData()[i][3][0]))/atof(&(data4.GetData()[i][4][0]))-52./200.);
        Graph4->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data4.GetData()[i][3][0])))/atof(&(data4.GetData()[i][4][0])));
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
    c1->SaveAs("FonteP1.png");
    c1->Clear();

    Graph2->Draw("AP");
    c1->SaveAs("FonteP2.png");
    c1->Clear();

    Graph3->Draw("AP");
    c1->SaveAs("FonteP3.png");
    c1->Clear();

    Graph4->Draw("AP");
    c1->SaveAs("FonteP4.png");
    c1->Clear();

    TMultiGraph* Mlt_G = new TMultiGraph("mg","mg");
    Mlt_G->Add(Graph1);
    Mlt_G->Add(Graph2);
    Mlt_G->Add(Graph3);
    Mlt_G->Add(Graph4);

    Mlt_G->Draw("AP");
    c1->SaveAs("FontePAll.png");
    c1->Clear();


   // f_Sangle->SetParameter(0,1);
    //cout<<f_Sangle->Eval(0.)<<endl;

    return 0;
}
