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

    TAxis *ax1 = G1.GetXaxis();
    TAxis *ay1 = G1.GetYaxis();
    ax1->SetTitle("#omega (rad/s)");
    ay1->SetTitle("V2_{max} (V)");
    TAxis *ax2 = G2.GetXaxis();
    TAxis *ay2 = G2.GetYaxis();
    ax2->SetTitle("#omega (rad/s)");
    ay2->SetTitle("V2_{max} (V)");
    TAxis *ax3 = G3.GetXaxis();
    TAxis *ay3 = G3.GetYaxis();
    ax3->SetTitle("#omega (rad/s)");
    ay3->SetTitle("V2_{max} (V)");

    double R=30.;

    for(int i=0;i<Txt1.GetLines();++i){
        G1.SetPoint(i,2*M_PI*data1[i][0],data1[i][1]/2000.);
    }
    for(int i=0;i<Txt2.GetLines();++i){
        G2.SetPoint(i,2*M_PI*data2[i][0],data2[i][1]/(1000.*data2[i][2]/R));
    }
    for(int i=0;i<Txt3.GetLines();++i){
        G3.SetPoint(i,2*M_PI*data3[i][0],data3[i][1]/(1000.*data3[i][2]/R));
    }

    //bobines de Helmholtz
    double R1=0.068; //m
    double N1=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m

    //bobine movel
    double R2=0.0207/2.; //m
    double N2=500;

    double I1=0.795;

    double L=8/(sqrt(5)*5)*m0*N1/R1*N2*M_PI*R2*R2;

    auto v1 = [&](double *x,double *p=nullptr){
        return p[0]*I1*x[0];
    };
    TF1 *V1m= new TF1("F", v1, 0,100000,1);


    auto v2 = [&](double *x,double *p=nullptr){
        return p[0]*x[0];
    };
    TF1 *V2m= new TF1("F", v2, 0,100000,1);    

    TCanvas* c1 = new TCanvas("","",1200,800);
    c1->SetLogx();
    gStyle->SetOptFit(111);
    gStyle -> SetStatBorderSize(5);
    gStyle -> SetStatFontSize(1);
    gStyle -> SetStatFont(62);
    gStyle -> SetStatTextColor(1);
    gStyle -> SetStatColor(3);
    gStyle -> SetStatStyle(0);
    gStyle -> SetStatX(0.55);
    gStyle -> SetStatY(0.85);
    gStyle -> SetStatW(0.2165);
    gPad->SetGrid(1, 1); gPad->Update();
    G1.Fit(V1m);
    G1.Draw("AP");
    c1->SaveAs("F1.png");
    c1->Clear();
    G2.Fit(V2m);
    G2.Draw("AP");
    c1->SaveAs("F2.png");
    c1->Clear();
    G3.Fit(V2m);
    G3.Draw("AP");
    c1->SaveAs("F3.png");
    c1->Clear();

    cout<<L<<endl;

    return 0;
}