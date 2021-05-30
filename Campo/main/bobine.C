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

    TGraph Gcalib; Gcalib.SetTitle(""); Gcalib.SetLineColor(kMagenta); Gcalib.SetLineWidth(2); Gcalib.SetMarkerStyle(16); Gcalib.SetMarkerColor(kAzure+3);
    TGraph Gbzz;   Gbzz.SetTitle(""); Gbzz.SetLineColor(kMagenta); Gbzz.SetLineWidth(2); Gbzz.SetMarkerStyle(16); Gbzz.SetMarkerColor(kAzure+3);
    TGraph Gbzx;   Gbzx.SetTitle(""); Gbzx.SetLineColor(kMagenta); Gbzx.SetLineWidth(2); Gbzx.SetMarkerStyle(16); Gbzx.SetMarkerColor(kAzure+3);
    TGraph Gbxx;   Gbxx.SetTitle(""); Gbxx.SetLineColor(kMagenta); Gbxx.SetLineWidth(2); Gbxx.SetMarkerStyle(16); Gbxx.SetMarkerColor(kAzure+3);
    TGraph Ghzz;   Ghzz.SetTitle(""); Ghzz.SetLineColor(kMagenta); Ghzz.SetLineWidth(2); Ghzz.SetMarkerStyle(16); Ghzz.SetMarkerColor(kAzure+3);
    TGraph Ghzx;   Ghzx.SetTitle(""); Ghzx.SetLineColor(kMagenta); Ghzx.SetLineWidth(2); Ghzx.SetMarkerStyle(16); Ghzx.SetMarkerColor(kAzure+3);
    TGraph Ghxx;   Ghxx.SetTitle(""); Ghxx.SetLineColor(kMagenta); Ghxx.SetLineWidth(2); Ghxx.SetMarkerStyle(16); Ghxx.SetMarkerColor(kAzure+3);
    TGraph Gar;    Gar.SetTitle(""); Gar.SetLineColor(kMagenta); Gar.SetLineWidth(2); Gar.SetMarkerStyle(16); Gar.SetMarkerColor(kAzure+3);
    TGraph Gfe;    Gar.SetTitle(""); Gfe.SetLineColor(kMagenta); Gfe.SetLineWidth(2); Gfe.SetMarkerStyle(16); Gfe.SetMarkerColor(kAzure+3);

    for(int i=0;i<Calib.GetLines();++i){
        Gcalib.SetPoint(i,datac[i][0],datac[i][1]/1000);
    }

    double Rb=0.068; //m
    double Nb=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m

    auto lfit = [&](double *x,double *p=nullptr){
        return p[0]*x[0]+p[1];
    };
    TF1 *Ffit = new TF1("FIT", lfit, -10000,10000,2);
    
    Gcalib.Fit(Ffit);

    auto calib = [&](double *x,double *p=nullptr){
        return m0*Nb*(x[0]-0.000715773)/(2*Rb*0.00610303);
    };
    TF1 *Fcalib = new TF1("FIT", calib, -10000,10000,0);

    for(int i=0;i<Bobinezz.GetLines();++i){
        Gbzz.SetPoint(i,databzz[i][0],Fcalib->Eval(databzz[i][1]/1000));
    }
    for(int i=0;i<Bobinezx.GetLines();++i){
        Gbzx.SetPoint(i,databzx[i][0],Fcalib->Eval(databzx[i][1]/1000));
    }
    for(int i=0;i<Bobinexx.GetLines();++i){
        Gbxx.SetPoint(i,databxx[i][0],Fcalib->Eval(databxx[i][1]/1000));
    }
    for(int i=0;i<Helmholtzzz.GetLines();++i){
        Ghzz.SetPoint(i,datahzz[i][0],Fcalib->Eval(datahzz[i][1]/1000));
    }
    for(int i=0;i<Helmholtzzx.GetLines();++i){
        Ghzx.SetPoint(i,datahzx[i][0],Fcalib->Eval(datahzx[i][1]/1000));
    }
    for(int i=0;i<Helmholtzxx.GetLines();++i){
        Ghxx.SetPoint(i,datahxx[i][0],Fcalib->Eval(datahxx[i][1]/1000));
    }
    for(int i=0;i<ar.GetLines();++i){
        Gar.SetPoint(i,dataa[i][0],Fcalib->Eval(dataa[i][1]/1000));
    }
    for(int i=0;i<ferro.GetLines();++i){
        Gfe.SetPoint(i,dataf[i][0],Fcalib->Eval(dataf[i][1]/1000));
    }
    
    double I=1;
    auto ex = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]), 3/2);
    };
    TF1 *fex= new TF1("F", ex, -10000,10000,1);
    //Bobine circular
    auto Bx = [&](double *x,double *p=nullptr){
        fex->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fex);
        double Bvalue=0;
        double err=0;
        B.Simpson(10000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex= new TF1("F", Bx, -10000,10000,0);

    auto ez = [&](double *x,double *p=nullptr){
        return Rb/pow((Rb*Rb+p[0]*p[0]), 3/2);
    };
    TF1 *fez= new TF1("F", ez, -10000,10000,1);
    
    auto Bz = [&](double *x,double *p=nullptr){
        fez->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fez);
        double Bvalue=0;
        double err=0;
        B.Simpson(10000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez= new TF1("F", Bz, -10000,10000,0);

    TCanvas* c1 = new TCanvas();
    Gcalib.Draw("AP");
    c1->SaveAs("calib.png");
    c1->Clear();
    Gbzz.Draw("AP");
    Bez->Draw("SAME");
    c1->SaveAs("bzz.png");
    c1->Clear();
    Gbzx.Draw("AP");
    c1->SaveAs("bzx.png");
    c1->Clear();
    Gbxx.Draw("AP");
    c1->SaveAs("bxx.png");
    c1->Clear();
    Ghzz.Draw("AP");
    c1->SaveAs("hzz.png");
    c1->Clear();
    Ghzx.Draw("AP");
    c1->SaveAs("hzx.png");
    c1->Clear();
    Ghxx.Draw("AP");
    c1->SaveAs("hxx.png");
    c1->Clear();
    Gar.Draw("AP");
    c1->SaveAs("ar.png");
    c1->Clear();
    Gfe.Draw("AP");
    c1->SaveAs("fe.png");
    c1->Clear();

    return 0;
}