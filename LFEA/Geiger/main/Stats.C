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

    DataReader stats_data("data/stats.txt");
    
    int Nlines_stats = stats_data.GetLines();

    TH1D* Hstats = new TH1D("","Distribuicao de contagens",15,8100,8800);
    Hstats->SetLineWidth(2);
    Hstats->SetLineColor(kBlue-1);
    Hstats->GetXaxis()->SetTitle("Contagens");
    Hstats->GetYaxis()->SetTitle("Frequencia");
 
    double background=96./300.;

    for (int i = 0; i<Nlines_stats; ++i){
        Hstats->Fill(atof(&(stats_data.GetData()[i][0][0]))-background*30);
    }

    TCanvas* c1 = new TCanvas("","",1920,1080);

    Hstats->Fit("gaus");

    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetOptFit(111);

    Hstats->Draw("");
    c1->SaveAs("2-Stats.png");
    c1->Clear();

    TF1 *gaus_h = (TF1*)Hstats->GetListOfFunctions()->FindObject("gaus");
    double erro_absoluto = gaus_h->GetParameter(2);
    double media = gaus_h->GetParameter(1);
    double erro_relativo = erro_absoluto/media;
    cout<<"Erro relativo: "<<erro_relativo<<endl;

    double variance = 0;
    double average = 0;
    for (int i = 0; i<Nlines_stats; ++i){
        average+=atof(&(stats_data.GetData()[i][0][0]))-background*30;
        variance+=pow(atof(&(stats_data.GetData()[i][0][0]))-background*30-media,2);
    }
    average/=50;
    variance/=50;
    double sigma=sqrt(variance);

    cout<<"average= "<<average<<endl;
    cout<<"sigma= "<<sigma<<endl;
    cout<<"Erro relativo: "<<sigma/media<<endl;
   
    return 0;
}
