#include <cmath>
#include "DataReader.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "Integrator.h"
#include "TGraph2D.h"
#include "TF2.h"

int main(){
    DataReader Txt1("data/faraday1.txt");
    DataReader Txt2("data/faraday2.txt");
    DataReader Txt3("data/faraday3.txt");

    vector<vector<double>> data1;
    vector<vector<double>> data2;
    vector<vector<double>> data3;
    vector<double> temp;

    for(int i=0;i<Txt1.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Txt1.GetData()[i][j][0])));
        }
        data1.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Txt2.GetLines();++i){
        for(int j =0;j<3;++j){
            temp.push_back(atof(&(Txt2.GetData()[i][j][0])));
        }
        data2.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Txt3.GetLines();++i){
        for(int j =0;j<3;++j){
            temp.push_back(atof(&(Txt3.GetData()[i][j][0])));
        }
        data3.push_back(temp);
        temp.clear();
    }

    TGraph G1;   G1.SetTitle("");   G1.SetLineColor(kMagenta);   G1.SetLineWidth(3);   G1.SetMarkerStyle(16);   G1.SetMarkerColor(kViolet+2);   G1.SetMarkerSize(2);
    TGraph G2;   G2.SetTitle("");   G2.SetLineColor(kMagenta);   G2.SetLineWidth(3);   G2.SetMarkerStyle(16);   G2.SetMarkerColor(kViolet+2);   G2.SetMarkerSize(2);
    TGraph G3;   G3.SetTitle("");   G3.SetLineColor(kMagenta);   G3.SetLineWidth(3);   G3.SetMarkerStyle(16);   G3.SetMarkerColor(kViolet+2);   G3.SetMarkerSize(2);

    double R=30.;

    for(int i=0;i<Txt1.GetLines();++i){
        G1.SetPoint(i,data1[i][0],data1[i][1]/2000.);
    }
    for(int i=0;i<Txt2.GetLines();++i){
        G2.SetPoint(i,data2[i][0],data2[i][1]/(1000.*data2[i][2]/R));
    }
    for(int i=0;i<Txt3.GetLines();++i){
        G3.SetPoint(i,data3[i][0],data3[i][1]/(1000.*data3[i][2]/R));
    }

    TCanvas* c1 = new TCanvas("","",1200,800);
    c1->SetLeftMargin(0.2);
    G1.Draw("AP");
    c1->SaveAs("F1.png");
    c1->Clear();
    G2.Draw("AP");
    c1->SaveAs("F2.png");
    c1->Clear();
    G3.Draw("AP");
    c1->SaveAs("F3.png");
    c1->Clear();

    return 0;
}