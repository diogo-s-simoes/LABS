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

    DataReader plat_data("data/patamar.txt");
    
    int Nlines_plat = plat_data.GetLines();

    TGraphErrors* Gplat = new TGraphErrors();
    Gplat->SetMarkerStyle(kFullSquare);
    Gplat->SetMarkerSize(0.5);
    Gplat->SetMarkerColor(kRed);
    Gplat->SetLineWidth(2);
    Gplat->SetLineColor(kBlue-1);
    Gplat->GetXaxis()->SetTitle("Voltagem (V)");
    Gplat->GetYaxis()->SetTitle("Contagens");
    Gplat->SetTitle("Resposta do detetor a tensao");
 
    double background=96./300.;

    for (int i = 0; i<Nlines_plat; ++i){
        Gplat->SetPoint(i,1000*atof(&(plat_data.GetData()[i][0][0])),1000*atof(&(plat_data.GetData()[i][1][0]))-background*30);
        Gplat->SetPointError(i,2,0.0133374*1000*(atof(&(plat_data.GetData()[i][1][0]))-background*30));
    }

    Gplat->Fit("x++1","","",550,1100);

    TCanvas* c1 = new TCanvas("","",1920,1080);

    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    Gplat->Draw("AP");
    c1->SaveAs("2-Plat.png");
    c1->Clear();
   
    return 0;
}
