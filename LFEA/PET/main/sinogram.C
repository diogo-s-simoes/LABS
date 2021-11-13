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
#include "TH2D.h"

int main(){

    //Os histogramas hMirror e hMirror_c ainda não estão feitos

    DataReader dataA("data/sin_0_180.txt");
    DataReader dataB("data/sin_195_345.txt");

    double NlinesA = dataA.GetLines();
    double NlinesB = dataB.GetLines();

    TH2D* hFull = new TH2D("Full","Sinograma1",13,-32.5,32.5,24,-7.5,345+7.5);
    hFull->SetMarkerSize(2);
    hFull->SetMarkerColor(kBlue+2);
    hFull->SetMarkerStyle(kFullSquare);
    hFull->SetLineWidth(2);
    hFull->SetLineColor(kBlue-1);
    hFull->SetFillColor(1);
    hFull->SetFillStyle(3004);
    hFull->GetXaxis()->SetTitle("#theta (rad)");
    hFull->GetYaxis()->SetTitle("#phi (rad)");
    hFull->SetTitle("Bruh");


    TH2D* hMirror = new TH2D("Mirror","Sinograma2",13,-32.5,32.5,13,-7.5,345+7.5);
    hMirror->SetMarkerSize(2);
    hMirror->SetMarkerColor(kBlue+2);
    hMirror->SetMarkerStyle(kFullSquare);
    hMirror->SetLineWidth(2);
    hMirror->SetLineColor(kBlue-1);
    hMirror->SetFillColor(1);
    hMirror->SetFillStyle(3004);
    hMirror->GetXaxis()->SetTitle("#theta (rad)");
    hMirror->GetYaxis()->SetTitle("#phi (rad)");
    hMirror->SetTitle("Bruh");

    TH2D* hFull_c = new TH2D("Full_Corrected","Sinograma3",24,-180-7.5,165+7.5,70,-180-2.5,165+2.5);
    hFull_c->SetMarkerSize(2);
    hFull_c->SetMarkerColor(kBlue+2);
    hFull_c->SetMarkerStyle(kFullSquare);
    hFull_c->SetLineWidth(2);
    hFull_c->SetLineColor(kBlue-1);
    hFull_c->SetFillColor(1);
    hFull_c->SetFillStyle(3004);
    hFull_c->GetXaxis()->SetTitle("#theta_{1} (rad)");
    hFull_c->GetYaxis()->SetTitle("#theta_{2} (rad)");
    hFull_c->SetTitle("Bruh");


    TH2D* hMirror_c = new TH2D("Mirror_Corrected","Sinograma4",13,-32.5,32.5,13,-7.5,345+7.5);
    hMirror_c->SetMarkerSize(2);
    hMirror_c->SetMarkerColor(kBlue+2);
    hMirror_c->SetMarkerStyle(kFullSquare);
    hMirror_c->SetLineWidth(2);
    hMirror_c->SetLineColor(kBlue-1);
    hMirror_c->SetFillColor(1);
    hMirror_c->SetFillStyle(3004);
    hMirror_c->GetXaxis()->SetTitle("#theta_{1} (rad)");
    hMirror_c->GetYaxis()->SetTitle("#theta_{2} (rad)");
    hMirror_c->SetTitle("Bruh");

    for (int i = 0; i<NlinesA; ++i){
            hFull->Fill(atof(&(dataA.GetData()[i][1][0])),atof(&(dataA.GetData()[i][0][0])),atof(&(dataA.GetData()[i][4][0]))/30.);

            hFull_c->Fill(-atof(&(dataA.GetData()[i][0][0]))+180,-atof(&(dataA.GetData()[i][0][0]))-atof(&(dataA.GetData()[i][1][0]))+180,atof(&(dataA.GetData()[i][4][0]))/30.);
    }
    for (int i = 0; i<NlinesB; ++i){
            hFull->Fill(atof(&(dataB.GetData()[i][1][0])),atof(&(dataB.GetData()[i][0][0])),atof(&(dataB.GetData()[i][4][0]))/10.);

            hFull_c->Fill(-atof(&(dataB.GetData()[i][0][0]))+180,-atof(&(dataB.GetData()[i][0][0]))-atof(&(dataB.GetData()[i][1][0]))+180,atof(&(dataB.GetData()[i][4][0]))/10.);
    }

    TCanvas* c1 = new TCanvas("","",1920,1080);
    gStyle->SetOptStat(0);
    //gPad->SetGrid(1, 1);
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
    gStyle->SetPalette(kRainBow);



    hFull->Draw("COL");
    c1->SaveAs("Sin_Full.png");
    c1->Clear();

    hFull_c->Draw("COL");
    c1->SaveAs("Sin_Full_C.png");
    c1->Clear();

    return 0;
}
