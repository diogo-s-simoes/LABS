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
    DataReader Helmholtzzz("data/helmholtz-zz.txt");
    DataReader Helmholtzzx("data/helmholtz-zx.txt");
    DataReader Helmholtzxx("data/helmholtz-xx.txt");
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

    TGraph Gcalib; Gcalib.SetTitle(""); Gcalib.SetLineColor(kMagenta); Gcalib.SetLineWidth(3); Gcalib.SetMarkerStyle(45); Gcalib.SetMarkerColor(kAzure+3); Gcalib.SetMarkerSize(2);
    TGraph Gbzz;   Gbzz.SetTitle("");   Gbzz.SetLineColor(kMagenta);   Gbzz.SetLineWidth(3);   Gbzz.SetMarkerStyle(45);   Gbzz.SetMarkerColor(kAzure+3);   Gbzz.SetMarkerSize(2);
    TGraph Gbzx;   Gbzx.SetTitle("");   Gbzx.SetLineColor(kMagenta);   Gbzx.SetLineWidth(3);   Gbzx.SetMarkerStyle(45);   Gbzx.SetMarkerColor(kAzure+3);   Gbzx.SetMarkerSize(2);
    TGraph Gbxx;   Gbxx.SetTitle("");   Gbxx.SetLineColor(kMagenta);   Gbxx.SetLineWidth(3);   Gbxx.SetMarkerStyle(45);   Gbxx.SetMarkerColor(kAzure+3);   Gbxx.SetMarkerSize(2);
    TGraph Ghzz;   Ghzz.SetTitle("");   Ghzz.SetLineColor(kMagenta);   Ghzz.SetLineWidth(3);   Ghzz.SetMarkerStyle(45);   Ghzz.SetMarkerColor(kAzure+3);   Ghzz.SetMarkerSize(2);
    TGraph Ghzx;   Ghzx.SetTitle("");   Ghzx.SetLineColor(kMagenta);   Ghzx.SetLineWidth(3);   Ghzx.SetMarkerStyle(45);   Ghzx.SetMarkerColor(kAzure+3);   Ghzx.SetMarkerSize(2);
    TGraph Ghxx;   Ghxx.SetTitle("");   Ghxx.SetLineColor(kMagenta);   Ghxx.SetLineWidth(3);   Ghxx.SetMarkerStyle(45);   Ghxx.SetMarkerColor(kAzure+3);   Ghxx.SetMarkerSize(2);
    TGraph Gar;    Gar.SetTitle("");    Gar.SetLineColor(kMagenta);    Gar.SetLineWidth(3);    Gar.SetMarkerStyle(45);    Gar.SetMarkerColor(kAzure+3);    Gar.SetMarkerSize(2);
    TGraph Gfe;    Gar.SetTitle("");    Gfe.SetLineColor(kMagenta);    Gfe.SetLineWidth(3);    Gfe.SetMarkerStyle(45);    Gfe.SetMarkerColor(kAzure+3);    Gfe.SetMarkerSize(2);
    TGraph Gxb;    Gxb.SetTitle("");    Gxb.SetLineColor(kMagenta);    Gxb.SetLineWidth(3);    Gxb.SetMarkerStyle(45);    Gxb.SetMarkerColor(kAzure+3);    Gxb.SetMarkerSize(2);
    TGraph Gxh;    Gxh.SetTitle("");    Gxh.SetLineColor(kMagenta);    Gxh.SetLineWidth(3);    Gxh.SetMarkerStyle(45);    Gxh.SetMarkerColor(kAzure+3);    Gxh.SetMarkerSize(2);
    TGraph Gtot;    Gtot.SetTitle("");    Gtot.SetLineColor(kMagenta);    Gtot.SetLineWidth(3);    Gtot.SetMarkerStyle(45);    Gtot.SetMarkerColor(kAzure+3);    Gtot.SetMarkerSize(2);

    for(int i=0;i<Calib.GetLines();++i){
        Gcalib.SetPoint(i,datac[i][0],datac[i][1]/1000);
    }

    double Rb=0.068; //m
    double Nb=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m
    double offset=0.000715773;

    auto lfit = [&](double *x,double *p=nullptr){
        return p[0]*x[0]+p[1];
    };
    TF1 *Ffit = new TF1("FIT", lfit, -10000,10000,2);
    
    Gcalib.Fit(Ffit);

    auto calib = [&](double *x,double *p=nullptr){
        return m0*Nb*(x[0]-offset)/(2*Rb*0.00610303);
    };
    TF1 *Fcalib = new TF1("FIT", calib, -10000,10000,0);

    offset=0.00070;
    for(int i=0;i<Bobinezz.GetLines();++i){
        Gbzz.SetPoint(i,databzz[i][0]/100,Fcalib->Eval(databzz[i][1]/1000));
    }
    offset=0.00071;
    for(int i=0;i<Bobinezx.GetLines();++i){
        Gbzx.SetPoint(i,databzx[i][0]/100,Fcalib->Eval(databzx[i][1]/1000));
    }
    Gxb.SetPoint(0,4./100,Fcalib->Eval(-0.41/1000));
    Gxb.SetPoint(1,10./100,Fcalib->Eval(0.42/1000));
    offset=0.00078;
    for(int i=0;i<Bobinexx.GetLines();++i){
        Gbxx.SetPoint(i,databxx[i][0]/100,Fcalib->Eval(databxx[i][1]/1000));
    }
    offset=0.00080;
    for(int i=0;i<Helmholtzzz.GetLines();++i){
        Ghzz.SetPoint(i,datahzz[i][0]/100,Fcalib->Eval(datahzz[i][1]/1000));
    }
    offset=0.00074;
    for(int i=0;i<Helmholtzzx.GetLines();++i){
        Ghzx.SetPoint(i,datahzx[i][0]/100,Fcalib->Eval(datahzx[i][1]/1000));
    }
    Gxh.SetPoint(0,0.,Fcalib->Eval(0.19/1000));
    Gxh.SetPoint(1,5.5/100,Fcalib->Eval(-0.92/1000));
    Gxh.SetPoint(2,10.5/100,Fcalib->Eval(0.04/1000));
    offset=0.00076;
    for(int i=0;i<Helmholtzxx.GetLines();++i){
        Ghxx.SetPoint(i,datahxx[i][0]/100,Fcalib->Eval(datahxx[i][1]/1000));
    }
    offset=0.00054;
    for(int i=0;i<ar.GetLines();++i){
        Gar.SetPoint(i,dataa[i][0]/100,Fcalib->Eval(dataa[i][1]/1000));
    }
    offset=0.00054;
    double Lf=0.15;
    for(int i=0;i<ferro.GetLines();++i){
        Gfe.SetPoint(i,dataf[i][0]/100+Lf/2.,Fcalib->Eval(dataf[i][1]/1000));
    }
    
    double I=1;
    //Bobine circular
    //x=0 y=0
    auto ex = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]), 3./2.);
    };
    TF1 *fex= new TF1("F", ex, -0.15,0.15,1);
    auto Bx = [&](double *x,double *p=nullptr){
        fex->SetParameter(0, x[0]);
        double Bvalue=fex->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex= new TF1("F", Bx, -0.15,0.15,0);

    auto ez = [&](double *x,double *p=nullptr){
        return Rb/pow((Rb*Rb+p[0]*p[0]), 3./2.);
    };
    TF1 *fez= new TF1("F", ez, -0.15,0.15,1);
    
    auto Bz = [&](double *x,double *p=nullptr){
        fez->SetParameter(0, x[0]);
        double Bvalue=fez->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez= new TF1("F", Bz, -0.15,0.15,0);

    //x=0.025 y=0
    double xx=0.025; //m
    auto ex2 = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]+xx*xx-2*Rb*xx*sin(x[0])), 3./2.);
    };
    TF1 *fex2= new TF1("F", ex2, -0.15,0.15,1);
    
    auto Bx2 = [&](double *x,double *p=nullptr){
        fex2->SetParameter(0, x[0]);
        double Bvalue=fex2->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex2= new TF1("F", Bx2, -0.15,0.15,0);

    auto ez2 = [&](double *x,double *p=nullptr){
        return (Rb-xx*sin(x[0]))/pow((Rb*Rb+p[0]*p[0]+xx*xx-2*Rb*xx*sin(x[0])), 3./2.);
    };
    TF1 *fez2= new TF1("F", ez2, -0.15,0.15,1);


    auto Bz2 = [&](double *x,double *p=nullptr){
        fez2->SetParameter(0, x[0]);
        double Bvalue=fez2->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez2= new TF1("F", Bz2, -0.15,0.15,0);

    //y=0 z=0
    double L;
    auto exx =[&](double *x,double *p=nullptr){
        return ((L/2)*sin(x[0]))/pow(Rb*Rb+p[0]*p[0]+(L/2)*(L/2)-2*p[0]*Rb*sin(x[0]), 3./2.);
    };
    TF1 *fexx= new TF1("F", exx, -0.15,0.15,1);
    auto Bxx = [&](double *x,double *p=nullptr){
        fexx->SetParameter(0, x[0]);
        double Bvalue=fexx->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bexx= new TF1("F", Bxx, -0.15,0.15,0);

    auto ezx =[&](double *x,double *p=nullptr){
        return (Rb-p[0]*sin(x[0]))/pow(Rb*Rb+p[0]*p[0]+(L/2)*(L/2)-2*p[0]*Rb*sin(x[0]),3./2.);
    };
    TF1 *fezx= new TF1("F", ezx, -0.15,0.15,1);
    auto Bzx = [&](double *x,double *p=nullptr){
        fezx->SetParameter(0, x[0]);
        double Bvalue=fezx->Integral(0,2*M_PI);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bezx= new TF1("F", Bzx, -0.15,0.15,0);

    //Bobines de Helmholtz
    //x=0 y=0
    auto Bh1x=[&](double *x,double *p=nullptr){
        return Bex->Eval(x[0]-L/2)+Bex->Eval(x[0]+L/2);
    };
    TF1 *Bh1ex= new TF1("F", Bh1x, -0.15,0.15,0);
    auto Bh1z=[&](double *x,double *p=nullptr){
        return Bez->Eval(x[0]-L/2)+Bez->Eval(x[0]+L/2);
    };
    TF1 *Bh1ez= new TF1("F", Bh1z, -0.15,0.15,0);

    //x=2.5 y=0
    auto Bh2x=[&](double *x,double *p=nullptr){
        return Bex2->Eval(x[0]-L/2)+Bex2->Eval(x[0]+L/2);
    };
    TF1 *Bh2ex= new TF1("F", Bh2x, -0.15,0.15,0);
    auto Bh2z=[&](double *x,double *p=nullptr){
        return Bez2->Eval(x[0]-L/2)+Bez2->Eval(x[0]+L/2);
    };
    TF1 *Bh2ez= new TF1("F", Bh2z, -0.15,0.15,0);
    
    //z=0 y=0
    auto Bh3x=[&](double *x,double *p=nullptr){
        return -Bexx->Eval(x[0])+Bexx->Eval(x[0]);
    };
    TF1 *Bh3ex= new TF1("F", Bh3x, -0.15,0.15,0);
    auto Bh3z=[&](double *x,double *p=nullptr){
        return 2*Bezx->Eval(x[0]);
    };
    TF1 *Bh3ez= new TF1("F", Bh3z, -0.15,0.15,0);

    //solenoides
    double Rar=0.02;
    double Lar=0.186;
    double Rf=0.028;
    double nar=39./0.03;
    double nf=45./0.03;

    auto Bzar = [&](double *x,double *p=nullptr){
        return m0*nar*I/2*((Lar/2-x[0])/sqrt((Lar/2-x[0])*(Lar/2-x[0])+Rar*Rar)+(Lar/2+x[0])/sqrt((Lar/2+x[0])*(Lar/2+x[0])+Rar*Rar));
    };
    TF1 *Bar= new TF1("F", Bzar, -0.15,0.15,0);

    auto Bzf = [&](double *x,double *p=nullptr){
        return m0*(nf*I+p[0])/2*((Lf/2-x[0])/sqrt((Lf/2-x[0])*(Lf/2-x[0])+Rf*Rf)+(Lf/2+x[0])/sqrt((Lf/2+x[0])*(Lf/2+x[0])+Rf*Rf));
    };
    TF1 *Bf= new TF1("F", Bzf, -0.15,0.15,1);

    //Draw
    TCanvas* c1 = new TCanvas();
    Gcalib.Draw("AP");
    c1->SaveAs("calib.png");
    c1->Clear();
    //Bobine
    L=0;
    I=1.001;
    Gbzz.Draw("AP");
    Bez->Draw("SAME");
    c1->SaveAs("bzz.png");
    c1->Clear();
    I=0.998;
    Gbzx.Draw("AP");
    Bez2->Draw("SAME");
    c1->SaveAs("bzx.png");
    c1->Clear();
    Gxb.Draw("AP");
    Bex2->Draw("SAME");
    c1->SaveAs("bex.png");
    c1->Clear();
    I=0.997;
    Gbxx.Draw("AP");
    Bezx->Draw("SAME");
    c1->SaveAs("bxx.png");
    c1->Clear();
    //Helmholtz
    I=0.995;
    L=dbH;
    Ghzz.Draw("AP");
    Bh1ez->Draw("SAME");
    c1->SaveAs("hzz.png");
    c1->Clear();
    I=0.993;
    Ghzx.Draw("AP");
    Bh2ez->Draw("SAME");
    c1->SaveAs("hzx.png");
    c1->Clear();
    Gxh.Draw("AP");
    Bh2ex->Draw("SAME");
    c1->SaveAs("hex.png");
    c1->Clear();
    I=0.993;
    Ghxx.Draw("AP");
    Bh3ez->Draw("SAME");
    c1->SaveAs("hxx.png");
    c1->Clear();
    //Solenoides
    I=0.995;
    Gar.Draw("AP");
    Bar->Draw("SAME");
    c1->SaveAs("ar.png");
    c1->Clear();
    I=0.993;
    Gfe.Fit(Bf);
    Gfe.Draw("AP");
    c1->SaveAs("fe.png");
    c1->Clear();

    return 0;
}