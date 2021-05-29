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
    vector<vector<double>> datahzz;
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

    TGraph Gcalib;
    TGraph Gbzz;
    TGraph Gbzx;
    TGraph Gbxx;
    TGraph Ghzz;
    TGraph Ghzx;
    TGraph Ghxx;
    TGraph Gar;
    TGraph Gfe;

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
        Gar.SetPoint(i,datac[0][i],datac[1][i]);
    }
    for(int i=0;i<ferro.GetLines();++i){
        Gfe.SetPoint(i,datac[0][i],datac[1][i]);
    }