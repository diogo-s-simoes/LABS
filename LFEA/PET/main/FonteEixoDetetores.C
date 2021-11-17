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
    double d_quad=7.5/6.;

    DataReader data("data/FonteEixoD1.txt");
    DataReader data2("data/FonteEixoD2.txt");
    DataReader data3("data/FonteEixoD3.txt");
    DataReader data4("data/FonteEixoD4.txt");

    double Nlines =data.GetLines();
    double Nlines2 = data2.GetLines();
    double Nlines3 = data3.GetLines();
    double Nlines4 = data4.GetLines();

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

     TGraphErrors* Graph3 = new TGraphErrors();
    Graph3->SetMarkerSize(2);
    Graph3->SetMarkerColor(kMagenta+2);
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

    TGraphErrors* GraphR1 = new TGraphErrors();
    GraphR1->SetMarkerSize(2);
    GraphR1->SetMarkerColor(kBlue+2);
    GraphR1->SetMarkerStyle(kFullSquare);
    GraphR1->SetLineWidth(3);
    GraphR1->SetLineColor(kBlue-1);
    GraphR1->SetFillColor(1);
    GraphR1->SetFillStyle(3004);
    GraphR1->GetXaxis()->SetTitle("d (cm)");
    GraphR1->GetYaxis()->SetTitle("#mu (rad)");
    GraphR1->SetTitle("Pico de coincidencias em funcao da posicao");

    TGraphErrors* GraphR2 = new TGraphErrors();
    GraphR2->SetMarkerSize(2);
    GraphR2->SetMarkerColor(kRed+2);
    GraphR2->SetMarkerStyle(kFullSquare);
    GraphR2->SetLineWidth(3);
    GraphR2->SetLineColor(kBlue-1);
    GraphR2->SetFillColor(1);
    GraphR2->SetFillStyle(3004);
    GraphR2->GetXaxis()->SetTitle("d (cm)");
    GraphR2->GetYaxis()->SetTitle("Coincidências");
    GraphR2->SetTitle("Pico de coincidencias em funcao da posicao");

    {
        GraphR1->SetPoint(0,-1,atof(&(data.GetData()[0][1][0])));
        GraphR1->SetPoint(1,-2,atof(&(data2.GetData()[0][1][0])));
        GraphR1->SetPoint(2,1,atof(&(data3.GetData()[0][1][0])));
        GraphR1->SetPoint(3,2,atof(&(data4.GetData()[0][1][0])));
    }
 
    for (int i = 0; i<Nlines; ++i){
        double d = 1;
        Graph1->SetPoint(i,M_PI/180.*atof(&(data.GetData()[i][0][0])),atof(&(data.GetData()[i][3][0]))/atof(&(data.GetData()[i][4][0]))-52./200.);
        Graph1->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data.GetData()[i][3][0])))/atof(&(data.GetData()[i][4][0])));
        GraphR2->SetPoint(i,sqrt(d*d+15.5*15.5-2*d*15.5*cos(M_PI/180.*atof(&(data.GetData()[i][0][0])))),atof(&(data.GetData()[i][2][0]))/atof(&(data.GetData()[i][4][0])));
    }

    for (int i = 0; i<Nlines2; ++i){
        double d = 2;
        Graph2->SetPoint(i,M_PI/180.*atof(&(data2.GetData()[i][0][0])),atof(&(data2.GetData()[i][3][0]))/atof(&(data2.GetData()[i][4][0]))-52./200.);
        Graph2->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data2.GetData()[i][3][0])))/atof(&(data2.GetData()[i][4][0])));
        GraphR2->SetPoint(i+Nlines,sqrt(d*d+15.5*15.5-2*d*15.5*cos(M_PI/180.*atof(&(data2.GetData()[i][0][0])))),atof(&(data2.GetData()[i][2][0]))/atof(&(data2.GetData()[i][4][0])));
    }
    
    for (int i = 0; i<Nlines3; ++i){
        double d = -1;
        Graph3->SetPoint(i,M_PI/180.*atof(&(data3.GetData()[i][0][0])),atof(&(data3.GetData()[i][3][0]))/atof(&(data3.GetData()[i][4][0]))-52./200.);
        Graph3->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data3.GetData()[i][3][0])))/atof(&(data3.GetData()[i][4][0])));
        GraphR2->SetPoint(i+Nlines+Nlines2,sqrt(d*d+15.5*15.5-2*d*15.5*cos(M_PI/180.*atof(&(data3.GetData()[i][0][0])))),atof(&(data3.GetData()[i][2][0]))/atof(&(data3.GetData()[i][4][0])));
    }

    for (int i = 0; i<Nlines4; ++i){
        double d = -2;
        Graph4->SetPoint(i,M_PI/180.*atof(&(data4.GetData()[i][0][0])),atof(&(data4.GetData()[i][3][0]))/atof(&(data4.GetData()[i][4][0]))-52./200.);
        Graph4->SetPointError(i,0.1*M_PI/180,sqrt(atof(&(data4.GetData()[i][3][0])))/atof(&(data4.GetData()[i][4][0])));
        GraphR2->SetPoint(i+Nlines+Nlines2+Nlines3,sqrt(d*d+15.5*15.5-2*d*15.5*cos(M_PI/180.*atof(&(data4.GetData()[i][0][0])))),atof(&(data4.GetData()[i][2][0]))/atof(&(data4.GetData()[i][4][0])));
    }

    auto l_gaussian = [&](double *x,double *p=nullptr){
      return p[0]*exp(-0.5*((x[0]-p[1])/p[2])*((x[0]-p[1])/p[2]));
    };
    TF1* f_gaussian= new TF1("gaussian", l_gaussian, -1e9,1e9,3);

    f_gaussian->SetParameter(0,1);
    f_gaussian->SetParameter(1,0);
    f_gaussian->SetParameter(2,-1);

    Graph1->Fit(f_gaussian);
    double peak1 = f_gaussian->GetParameter(0);
    double miu1 = f_gaussian->GetParameter(1);
    double sigma1=f_gaussian->GetParameter(2);
    Graph2->Fit(f_gaussian);
    double peak2 = f_gaussian->GetParameter(0);
    double miu2 = f_gaussian->GetParameter(1);
    double sigma2=f_gaussian->GetParameter(2);
    Graph3->Fit(f_gaussian);
    double peak3 = f_gaussian->GetParameter(0);
    double miu3 = f_gaussian->GetParameter(1);
    double sigma3=f_gaussian->GetParameter(2);
    f_gaussian->SetParameter(1,0);
    Graph4->Fit(f_gaussian);
    double peak4 = f_gaussian->GetParameter(0);
    double miu4 = f_gaussian->GetParameter(1);
    double sigma4=f_gaussian->GetParameter(2);

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
    c1->SaveAs("FonteEixoD1.png");
    c1->Clear();

    Graph2->Draw("AP");
    c1->SaveAs("FonteEixoD2.png");
    c1->Clear();

    Graph3->Draw("AP");
    c1->SaveAs("FonteEixoD3.png");
    c1->Clear();

    Graph4->Draw("AP");
    c1->SaveAs("FonteEixoD4.png");
    c1->Clear();

    TMultiGraph* Mlt_G = new TMultiGraph("mg","mg");
    Mlt_G->Add(Graph1);
    Mlt_G->Add(Graph2);
    Mlt_G->Add(Graph3);
    Mlt_G->Add(Graph4);

    Mlt_G->Draw("AP");
    c1->SaveAs("FonteEixoAll.png");
    c1->Clear();

    TGraphErrors* GraphMiu = new TGraphErrors();
    GraphMiu->SetMarkerSize(2);
    GraphMiu->SetMarkerColor(kBlue+2);
    GraphMiu->SetMarkerStyle(kFullSquare);
    GraphMiu->SetLineWidth(3);
    GraphMiu->SetLineColor(kBlue-1);
    GraphMiu->SetFillColor(1);
    GraphMiu->SetFillStyle(3004);
    GraphMiu->GetXaxis()->SetTitle("d (cm)");
    GraphMiu->GetYaxis()->SetTitle("#mu (rad)");
    GraphMiu->SetTitle("Pico de coincidencias em funcao da posicao");

    GraphMiu->SetPoint(0,-2*d_quad,peak2);
    GraphMiu->SetPoint(2,-1*d_quad,peak1);
    GraphMiu->SetPoint(3,1*d_quad,peak3);
    GraphMiu->SetPoint(1,2*d_quad,peak4);

    auto l_solidA = [&](double *x,double *p=nullptr){
      return p[0]*0.5*(1-cos(atan(p[1]/(x[0]))));
    };
    TF1* f_solidA= new TF1("solidA", l_solidA, -1e9,1e9,2);

    f_solidA->SetParameter(0,100);
    f_solidA->SetParameter(1,2);
    GraphMiu->Fit(f_solidA);

    GraphMiu->Draw("AP");
    c1->SaveAs("Peak_Long.png");
    c1->Clear();

    GraphR2->Fit(f_solidA);

    GraphR2->Draw("AP");
    c1->SaveAs("R2_Long.png");
    c1->Clear();
    return 0;
}
