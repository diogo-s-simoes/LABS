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

    DataReader calib_data("data/Calib.txt");
    DataReader abs_data("data/Abs.txt");
    DataReader unk_data("data/Desc.txt");
    DataReader res_data("data/Res.txt");

    int Nlines_calib = calib_data.GetLines();
    int Nlines_abs = abs_data.GetLines();
    int Nlines_unk = unk_data.GetLines();
    int Nlines_res = res_data.GetLines();
    
    TGraphErrors* Gcalib = new TGraphErrors();
    Gcalib->SetMarkerStyle(kFullSquare);
    Gcalib->SetMarkerSize(4);
    Gcalib->SetMarkerColor(kGreen+2);
    Gcalib->SetLineWidth(4);
    Gcalib->SetLineColor(kBlue-1);
    Gcalib->SetFillColor(2);
    Gcalib->SetFillStyle(3001);
    Gcalib->GetXaxis()->SetTitle("Energia [keV]");
    Gcalib->GetYaxis()->SetTitle("Channel N");

    TGraphErrors* Gabs = new TGraphErrors();
    Gabs->SetMarkerStyle(kFullSquare);
    Gabs->SetMarkerSize(4);
    Gabs->SetMarkerColor(kGreen+2);
    Gabs->SetLineWidth(4);
    Gabs->SetLineColor(kBlue-1);
    Gabs->SetFillColor(2);
    Gabs->SetFillStyle(3001);
    Gabs->GetXaxis()->SetTitle("Densidade  Massica [mg/cm^{2}]");
    Gabs->GetYaxis()->SetTitle("N_{t}");

    TGraphErrors* Gres = new TGraphErrors();
    Gres->SetMarkerStyle(kFullSquare);
    Gres->SetMarkerSize(1);
    Gres->SetMarkerColor(kGreen+2);
    Gres->SetLineWidth(2);
    Gres->SetLineColor(kBlue-1);
    Gres->SetFillColor(2);
    Gres->SetFillStyle(3001);
    Gres->GetXaxis()->SetTitle("Energia [keV]");
    Gres->GetYaxis()->SetTitle("Resolucao (%)");

    //atof(&(ficheiro1.GetData()[i][j][0]))

    for (int i = 0; i<Nlines_calib; ++i){
        Gcalib->SetPoint(i,atof(&(calib_data.GetData()[i][0][0])),atof(&(calib_data.GetData()[i][1][0])));
        Gcalib->SetPointError(i,3,atof(&(calib_data.GetData()[i][2][0]))/sqrt(atof(&(calib_data.GetData()[i][3][0]))));
    }

    for (int i = 0; i<Nlines_abs; ++i){
        Gabs->SetPoint(i,atof(&(abs_data.GetData()[i][0][0])),atof(&(abs_data.GetData()[i][1][0])));
        Gabs->SetPointError(i,1,atof(&(abs_data.GetData()[i][2][0])));
    }
    
    for (int i = 0; i<Nlines_res; ++i){
        Gres->SetPoint(i,atof(&(res_data.GetData()[i][1][0])),100*atof(&(res_data.GetData()[i][2][0])));
        Gres->SetPointError(i,atof(&(res_data.GetData()[i][0][0])),100*atof(&(res_data.GetData()[i][3][0])));
    }

    auto l_abs = [](double *x,double *p=nullptr){
      return p[0]*exp(-x[0]*p[1]);
      //p[0]=I0
      //p[1]=miu
      //x[0]=x
    };
    TF1* f_abs= new TF1("ABS", l_abs, -1e9,1e9,2);

    auto l_calib = [](double *x,double *p=nullptr){
      return (x[0]-p[1])/p[0];
      //p[0]=a
      //p[1]=b
      //x[0]=chn
    };
    TF1* f_calib= new TF1("CAL", l_calib, -1e9,1e9,2);

    auto l_res = [](double *x,double *p=nullptr){
      return p[0]/sqrt(x[0]);
      //p[0]=a
    };
    TF1* f_res= new TF1("CAL", l_res, -1e9,1e9,1);

    f_calib->SetParameter(0,1.);
    f_calib->SetParameter(1,0.);
    f_abs->SetParameter(0,40000.);
    f_abs->SetParameter(1,0.0001);
    f_res->SetParameter(0,1);

    Gcalib->Fit(f_calib);
    Gabs->Fit(f_abs);
    Gres->Fit(f_res);

    double a = f_calib->GetParameter(0);
    double b = f_calib->GetParameter(1);

    TCanvas* c1 = new TCanvas("","",1920,1080);

    Gcalib->Draw("A5");
    c1->SaveAs("Calib.png");
    c1->Clear();
    
    Gabs->Draw("A5");
    c1->SaveAs("Abs.png");
    c1->Clear();

    Gres->Draw("AP");
    c1->SaveAs("Res.png");
    c1->Clear();

    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    TH1D* hUnk = new TH1D("","Fonte Desconhecida",300,0.5+b,a*300.5+b);
    for (int i = 0; i<Nlines_unk; ++i){
        hUnk->Fill(a*atof(&(unk_data.GetData()[i][0][0]))+b,atof(&(unk_data.GetData()[i][1][0])));
    }
    hUnk->GetXaxis()->SetTitle("Energia [keV]");
    hUnk->GetYaxis()->SetTitle("N_{contagens}");
    hUnk->SetLineWidth(2);
    hUnk->Draw("HIST");
    c1->SaveAs("Unk.png");
    c1->Clear();

    return 0;
}
