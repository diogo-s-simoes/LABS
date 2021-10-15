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
    Gplat->SetMarkerSize(2);
    Gplat->SetMarkerColor(kRed);
    Gplat->SetLineWidth(2);
    Gplat->SetLineColor(kBlue-1);
    Gplat->GetXaxis()->SetTitle("Voltagem (V)");
    Gplat->GetYaxis()->SetTitle("Contagens");
 
    double background=96./300.;

    for (int i = 0; i<Nlines_plat; ++i){
        Gplat->Fill(1000*atof(&(plat_data.GetData()[i][0][0]))-background*30);
    }

    TCanvas* c1 = new TCanvas("","",1920,1080);

    Hstats->Fit("gaus");

    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    Hstats->Draw("");
    c1->SaveAs("Stats.png");
    c1->Clear();

    TF1 *gaus_h = (TF1*)Hstats->GetListOfFunctions()->FindObject("gaus");
    double erro_absoluto = gaus_h->GetParameter(2);
    double media = gaus_h->GetParameter(1);
    double erro_relativo = erro_absoluto/media;
    cout<<"Erro relativo: "<<erro_relativo<<endl;
   
    return 0;
}
