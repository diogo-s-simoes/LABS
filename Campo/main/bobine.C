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

int main(){
    DataReader Calib("data/calib.txt");
    DataReader Bobinezz("data/bobine-zz.txt");
    DataReader Bobinezx("data/bobine-zx.txt");
    DataReader Bobinexx("data/bobine-xx.txt");
    DataReader Helmholtzzz("data/bobine-zz.txt");
    DataReader Helmholtzzx("data/bobine-zx.txt");
    DataReader Helmholtzxx("data/bobine-xx.txt");
    DataReader ar("data/ar.txt");
    DataReader ferro("data/ferro.txt");

    vector<vector<double>> datac;
    vector<vector<double>> databzz;
    vector<vector<double>> databzx;
    vector<vector<double>> databxx;
    vector<vector<double>> datahzz;
    vector<vector<double>> datahzx;
    vector<vector<double>> datahxx;
    vector<vector<double>> dataa;
    vector<vector<double>> dataf;

    vector<double> temp;

    for(int i=0;i<Calib.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Calib.GetData()[i][j][0])));
        }
        datac.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Bobinezz.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Bobinezz.GetData()[i][j][0])));
        }
        databzz.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Bobinezx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Bobinezx.GetData()[i][j][0])));
        }
        databzx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Bobinexx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Bobinexx.GetData()[i][j][0])));
        }
        databxx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Helmholtzzz.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Helmholtzzz.GetData()[i][j][0])));
        }
        datahzz.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Helmholtzzx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Helmholtzzx.GetData()[i][j][0])));
        }
        datahzx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<Helmholtzxx.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(Helmholtzxx.GetData()[i][j][0])));
        }
        datahxx.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<ar.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(ar.GetData()[i][j][0])));
        }
        dataa.push_back(temp);
        temp.clear();
    }
    for(int i=0;i<ferro.GetLines();++i){
        for(int j =0;j<2;++j){
            temp.push_back(atof(&(ferro.GetData()[i][j][0])));
        }
        dataf.push_back(temp);
        temp.clear();
    }

    TGraph Gcalib; Gcalib.SetTitle(""); Gcalib.SetLineColor(kMagenta); Gcalib.SetLineWidth(2); Gcalib.SetMarkerStyle(16); Gcalib.SetMarkerColor(kOrange);
    TGraph Gbzz;   Gbzz.SetTitle(""); Gbzz.SetLineColor(kMagenta); Gbzz.SetLineWidth(2); Gbzz.SetMarkerStyle(16); Gbzz.SetMarkerColor(kOrange);
    TGraph Gbzx;   Gbzx.SetTitle(""); Gbzx.SetLineColor(kMagenta); Gbzx.SetLineWidth(2); Gbzx.SetMarkerStyle(16); Gbzx.SetMarkerColor(kOrange);
    TGraph Gbxx;   Gbxx.SetTitle(""); Gbxx.SetLineColor(kMagenta); Gbxx.SetLineWidth(2); Gbxx.SetMarkerStyle(16); Gbxx.SetMarkerColor(kOrange);
    TGraph Ghzz;   Ghzz.SetTitle(""); Ghzz.SetLineColor(kMagenta); Ghzz.SetLineWidth(2); Ghzz.SetMarkerStyle(16); Ghzz.SetMarkerColor(kOrange);
    TGraph Ghzx;   Ghzx.SetTitle(""); Ghzx.SetLineColor(kMagenta); Ghzx.SetLineWidth(2); Ghzx.SetMarkerStyle(16); Ghzx.SetMarkerColor(kOrange);
    TGraph Ghxx;   Ghxx.SetTitle(""); Ghxx.SetLineColor(kMagenta); Ghxx.SetLineWidth(2); Ghxx.SetMarkerStyle(16); Ghxx.SetMarkerColor(kOrange);
    TGraph Gar;    Gar.SetTitle(""); Gar.SetLineColor(kMagenta); Gar.SetLineWidth(2); Gar.SetMarkerStyle(16); Gar.SetMarkerColor(kOrange);
    TGraph Gfe;    Gar.SetTitle(""); Gfe.SetLineColor(kMagenta); Gfe.SetLineWidth(2); Gfe.SetMarkerStyle(16); Gfe.SetMarkerColor(kOrange);

    for(int i=0;i<Calib.GetLines();++i){
        Gcalib.SetPoint(i,datac[0][i],datac[1][i]);
    }
    for(int i=0;i<Bobinezz.GetLines();++i){
        Gbzz.SetPoint(i,databzz[0][i],databzz[1][i]);
    }
    for(int i=0;i<Bobinezx.GetLines();++i){
        Gbzx.SetPoint(i,databzx[0][i],databzx[1][i]);
    }
    for(int i=0;i<Bobinexx.GetLines();++i){
        Gbxx.SetPoint(i,databxx[0][i],databxx[1][i]);
    }
    for(int i=0;i<Helmholtzzz.GetLines();++i){
        Ghzz.SetPoint(i,datahzz[0][i],datahzz[1][i]);
    }
    for(int i=0;i<Helmholtzzx.GetLines();++i){
        Ghzx.SetPoint(i,datahzx[0][i],datahzx[1][i]);
    }
    for(int i=0;i<Helmholtzxx.GetLines();++i){
        Ghxx.SetPoint(i,datahxx[0][i],datahxx[1][i]);
    }
    for(int i=0;i<ar.GetLines();++i){
        Gar.SetPoint(i,dataa[0][i],dataa[1][i]);
    }
    for(int i=0;i<ferro.GetLines();++i){
        Gfe.SetPoint(i,dataf[0][i],dataf[1][i]);
    }

    TCanvas* c1 = new TCanvas();
    Gcalib.Draw("APL");
    c1->SaveAs("calib.png");
    c1->Clear();
    Gbzz.Draw("APL");
    c1->SaveAs("bzz.png");
    c1->Clear();
    Gbzx.Draw("APL");
    c1->SaveAs("bzx.png");
    c1->Clear();
    Gbxx.Draw("APL");
    c1->SaveAs("bxx.png");
    c1->Clear();
    Ghzz.Draw("APL");
    c1->SaveAs("hzz.png");
    c1->Clear();
    Ghzx.Draw("APL");
    c1->SaveAs("hzx.png");
    c1->Clear();
    Ghxx.Draw("APL");
    c1->SaveAs("hxx.png");
    c1->Clear();
    Gar.Draw("APL");
    c1->SaveAs("ar.png");
    c1->Clear();
    Gfe.Draw("APL");
    c1->SaveAs("fe.png");
    c1->Clear();

    return 0;
}