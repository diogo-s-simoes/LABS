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

    TH1D* Hstats = new TH1D("","Distribuição de contagens",25,8000,9000);
    Hstats->SetLineWidth(2);
    Hstats->SetLineColor(kBlue-1);
    Hstats->GetXaxis()->SetTitle("Energia [keV]");
    Hstats->GetYaxis()->SetTitle("Channel N");
 
    for (int i = 0; i<Nlines_stats; ++i){
        Hstats->Fill(atof(&(stats_data.GetData()[i][0][0])));
    }

    auto l_res = [](double *x,double *p=nullptr){
      return p[0]/sqrt(x[0]);
      //p[0]=a
    };
    TF1* f_res= new TF1("CAL", l_res, -1e9,1e9,1);

    TCanvas* c1 = new TCanvas("","",1920,1080);

    gStyle->SetOptStat(0);
    gStyle->SetLegendBorderSize(0);

    Hstats->Draw("");
    c1->SaveAs("Stats.png");
    c1->Clear();
   
    return 0;
}
