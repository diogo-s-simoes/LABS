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
    Graph1->SetTitle("Variacao posicao fonte no plano equidistante aos detetores para x=1 quad");



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
    Graph2->SetTitle("Variacao posicao fonte no plano equidistante aos detetores para x=2 quad");

     TGraphErrors* Graph3 = new TGraphErrors();
    Graph3->SetMarkerSize(2);
    Graph3->SetMarkerColor(kGreen);
    Graph3->SetMarkerStyle(kFullSquare);
    Graph3->SetLineWidth(3);
    Graph3->SetLineColor(kBlue-1);
    Graph3->SetFillColor(1);
    Graph3->SetFillStyle(3004);
    Graph3->GetXaxis()->SetTitle("Angle (rad)");
    Graph3->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph3->SetTitle("Variacao posicao fonte no plano equidistante aos detetores para x=3 quad");

         TGraphErrors* Graph4 = new TGraphErrors();
    Graph4->SetMarkerSize(2);
    Graph4->SetMarkerColor(kOrange);
    Graph4->SetMarkerStyle(kFullSquare);
    Graph4->SetLineWidth(3);
    Graph4->SetLineColor(kBlue-1);
    Graph4->SetFillColor(1);
    Graph4->SetFillStyle(3004);
    Graph4->GetXaxis()->SetTitle("Angle (rad)");
    Graph4->GetYaxis()->SetTitle("Coincidences [s^{-1}]");
    Graph4->SetTitle("Variacao posicao fonte no plano equidistante aos detetores para x=0 quad");
 
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

    auto l_gaussian = [&](double *x,double *p=nullptr){
      return p[0]*exp(-0.5*((x[0]-p[1])/p[2])*((x[0]-p[1])/p[2]));
    };
    TF1* f_gaussian= new TF1("gaussian", l_gaussian, -1e9,1e9,3);

    f_gaussian->SetParameter(0,1);
    f_gaussian->SetParameter(1,0);
    f_gaussian->SetParameter(2,-1);

    Graph1->Fit(f_gaussian);
    double miu1 = f_gaussian->GetParameter(1);
    double sigma1=f_gaussian->GetParameter(2);
    Graph2->Fit(f_gaussian);
    double miu2 = f_gaussian->GetParameter(1);
    double sigma2=f_gaussian->GetParameter(2);
    Graph3->Fit(f_gaussian);
    double miu3 = f_gaussian->GetParameter(1);
    double sigma3=f_gaussian->GetParameter(2);
    f_gaussian->SetParameter(1,0);
    Graph4->Fit(f_gaussian);
    double miu4 = f_gaussian->GetParameter(1);
    double sigma4=f_gaussian->GetParameter(2);

    
    TCanvas* c1 = new TCanvas("","",1920,1080);
    gPad->SetGrid(1, 1);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetOptFit(111);
    gStyle -> SetStatBorderSize(5);
    gStyle -> SetStatFontSize(0.2);
    gStyle -> SetStatFont(62);
    gStyle -> SetStatTextColor(1);
    gStyle -> SetStatColor(6);
    gStyle -> SetStatStyle(1);
    gStyle -> SetStatX(2000);
    gStyle -> SetStatY(2000);
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

    TMultiGraph* Mlt_G = new TMultiGraph("Correlacao angular para x=0, 1.25, 2.5 ,3.75 cm","Correlacao angular para x=0, 1.25, 2.5 ,3.75 cm");
    Mlt_G->Add(Graph3);
    Mlt_G->Add(Graph2);
    Mlt_G->Add(Graph1);
    Mlt_G->Add(Graph4);
    Mlt_G->GetXaxis()->SetTitle("Angle (rad)");
    Mlt_G->GetYaxis()->SetTitle("Coincidences [s^{-1}]");

    auto legend1 = new TLegend(0.75,0.7,1,0.8);
    legend1->SetFillStyle(0);
    legend1->SetTextFont(62);
    legend1->SetTextSize(0.03);
    legend1->AddEntry(Graph4,"x = 0 cm","P");
    legend1->AddEntry(Graph1,"x = 1.25 cm","P");
    legend1->AddEntry(Graph2,"x = 2.5 cm","P");
    legend1->AddEntry(Graph3,"x = 3.75 cm","P");
    
    Mlt_G->Draw("AP");
    legend1->Draw("SAME");
    c1->SaveAs("FontePAll.png");
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

    GraphMiu->SetPoint(0,0*d_quad,miu4);
    GraphMiu->SetPoint(1,1*d_quad,miu1);
    GraphMiu->SetPoint(2,2*d_quad,miu2);
    GraphMiu->SetPoint(3,3*d_quad,miu3);

    GraphMiu->Fit("pol1");

    GraphMiu->Draw("AP");
    c1->SaveAs("Miu.png");
    c1->Clear();

    cout<<"Miu1 = "<<miu1<<endl;
    cout<<"Miu2 = "<<miu2<<endl;
    cout<<"Miu3 = "<<miu3<<endl;
    cout<<"Miu4 = "<<miu4<<endl;

    cout<<"Sigma1 = "<<sigma1<<endl;
    cout<<"Sigma2 = "<<sigma2<<endl;
    cout<<"Sigma3 = "<<sigma3<<endl;
    cout<<"Sigma4 = "<<sigma4<<endl;

    cout<<"FWHM1 = "<<2*sqrt(2*log(2))*sigma1<<endl;
    cout<<"FWHM2 = "<<2*sqrt(2*log(2))*sigma2<<endl;
    cout<<"FWHM3 = "<<2*sqrt(2*log(2))*sigma3<<endl;
    cout<<"FWHM4 = "<<2*sqrt(2*log(2))*sigma4<<endl;

    return 0;
}
