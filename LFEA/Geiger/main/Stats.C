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

   
    
    for (int i = 0; i<Nlines_res; ++i){
        Gres->SetPoint(i,atof(&(res_data.GetData()[i][1][0])),100*atof(&(res_data.GetData()[i][2][0])));
        Gres->SetPointError(i,atof(&(res_data.GetData()[i][0][0])),100*atof(&(res_data.GetData()[i][3][0])));
    }

    TF1* f_calib= new TF1("CAL", l_calib, -1e9,1e9,2);

    auto l_res = [](double *x,double *p=nullptr){
      return p[0]/sqrt(x[0]);
      //p[0]=a
    };
    TF1* f_res= new TF1("CAL", l_res, -1e9,1e9,1);

    

    TCanvas* c1 = new TCanvas("","",1920,1080);

    Gres->Draw("AP");
    c1->SaveAs("Res.png");
    c1->Clear();

    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

   
    return 0;
}
