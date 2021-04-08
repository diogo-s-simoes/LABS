#include <cmath>
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPad.h"
#include "TF1.h"
#include "NewReader.h"
#include "LETintegral.h"
#include "Spline3Interpolator.h"

int main()  {
    double** V=new double* [10];
    for(int i=0;i<10;++i){
        V[i]=new double[2];
    }
    V[0][0]=2.25387502;
    V[0][1]=2.25519443;
    V[1][0]=3.59122896;
    V[1][1]=3.59171091;
    V[2][0]=4.95498657;
    V[2][1]=4.95529747;
    V[3][0]=6.29391813;
    V[3][1]=6.29403925;
    V[4][0]=7.63268518;
    V[4][1]=7.63272333;
    V[5][0]=8.99838734;
    V[5][1]=8.9921054; //???????????
    V[6][0]=10.33342743;
    V[6][1]=10.33333492;
    V[7][0]=11.65925407;
    V[7][1]=11.65880505;
    V[8][0]=11.80367279;
    V[8][1]=11.80365944;
    V[9][0]=11.80375767;
    V[9][1]=11.80386925;
    double** D=new double* [10];
    for(int i=0;i<10;++i){
        D[i]=new double[2];
    }
    D[0][0]=0.672535;
    D[0][1]=0.678192;
    D[1][0]=1.978749;
    D[1][1]=1.988007;
    D[2][0]=3.870714;
    D[2][1]=3.888194;
    D[3][0]=6.196059;
    D[3][1]=6.206712;
    D[4][0]=8.872160;
    D[4][1]=8.871765;
    D[5][0]=11.926949;
    D[5][1]=11.930707;
    D[6][0]=15.207083;
    D[6][1]=15.206801;
    D[7][0]=18.664036;
    D[7][1]=18.685778;
    D[8][0]=19.075247;
    D[8][1]=19.063478;
    D[9][0]=19.041847;
    D[9][1]=19.041391;
    double** I=new double* [10];
    for(int i=0;i<10;++i){
        I[i]=new double[2];
    }
    I[0][0]=0.71829;
    I[0][1]=0.71835;
    I[1][0]=0.89514;
    I[1][1]=0.89511;
    I[2][0]=1.05456;
    I[2][1]=1.05442;
    I[3][0]=1.19534;
    I[3][1]=1.19531;
    I[4][0]=1.32446;
    I[4][1]=1.32448;
    I[5][0]=1.44684;
    I[5][1]=1.44653;
    I[6][0]=1.55833;
    I[6][1]=1.55824;
    I[7][0]=1.66378;
    I[7][1]=1.66362;
    I[8][0]=1.67478;
    I[8][1]=1.67477;
    I[9][0]=1.67464;
    I[9][1]=1.67464;

    double aux;
    for(int i=0; i<10;++i){
        aux=fabs(V[i][0]-V[i][1])/2.;
        V[i][0]=(V[i][0]+V[i][1])/2.;
        V[i][1]=aux;
        aux=fabs(D[i][0]-D[i][1])/2.;
        D[i][0]=(D[i][0]+D[i][1])/2.;
        D[i][1]=aux;
        aux=fabs(I[i][0]-I[i][1])/2.;
        I[i][0]=(I[i][0]+I[i][1])/2.;
        I[i][1]=aux;
    }

    double R=0.11797;

    for(int i=0; i<10;++i){
        V[i][0]=V[i][0]-R*I[i][0];
    }

    ////////////////////////
    
    NewReader Rdata("data/Rtable.txt");
    NewReader Tdata("data/Ttable.txt");

    int Nlines = Rdata.GetNrInstantes();
    
    double* Rv=new double[Nlines];
    double* Tv=new double[Nlines];

    for(int i=0; i<Nlines; i++){
        Rv[i]=Rdata.GetTempo(i)*0.4911;
        Tv[i]=Tdata.GetTempo(i);
    }

    Spline3Interpolator sp3(Nlines,Rv,Tv);

    ////////////////////////

    TGraph FT;

    for(int i=0; i<10;++i){
        FT.SetPoint(i,sp3.Interpolate(V[i][0]/I[i][0]),D[i][0]);
    }

    TCanvas* c1 = new TCanvas();
    FT.SetMarkerSize(1);
    FT.SetMarkerStyle(16);
    FT.SetMarkerColor(kBlue);
    FT.SetLineWidth(2);
    FT.SetLineColor(kRed);
    TAxis *ax = FT.GetXaxis();
    TAxis *ay = FT.GetYaxis();
    ax->SetTitle("T (K)");
    ay->SetTitle("Vd (mV)");
    FT.Draw("APL");
    c1->SaveAs("F(T).png");

    return 0;
}
