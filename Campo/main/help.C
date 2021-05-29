#include "Integrator.h"
#include "Func1D.h"
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

    double Rb=0.068; //m
    double Nb=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m

    auto calib = [&](double *x,double *p=nullptr){
        return m0*Nb*x[0]/(2*Rb);
    };
    TF1 *Fit1 = new TF1("FIT", calib, -10000,10000,0);

    
    double I=1;
    double err=0;
    auto ex = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]), 3/2);
    };
    TF1 *fex= new TF1("F", ex, -10000,10000,1);
    //Bobine circular
    auto Bx = [&](double *x,double *p=nullptr){
        fex->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fex);
        double Bvalue;
        B.Simpson(1000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex= new TF1("F", Bx, -10000,10000,0);



    auto ez = [&](double *x,double *p=nullptr){
        return Rb/pow((Rb*Rb+p[0]*p[0]), 3/2);
    };
    TF1 *fez= new TF1("F", ez, -10000,10000,1);
    //Bobine circular
    auto Bz = [&](double *x,double *p=nullptr){
        fez->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fez);
        double Bvalue;
        B.Simpson(1000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez= new TF1("F", Bz, -10000,10000,0);





    double xx=0.025; //m
    auto ex2 = [&](double *x,double *p=nullptr){
        return p[0]*sin(x[0])/pow((Rb*Rb+p[0]*p[0]+xx*xx-2*Rb*xx*sin(x[0])), 3/2);
    };
    TF1 *fex2= new TF1("F", ex2, -10000,10000,1);
    //Bobine circular
    auto Bx2 = [&](double *x,double *p=nullptr){
        fex2->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fex2);
        double Bvalue;
        B.Simpson(1000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bex2= new TF1("F", Bx2, -10000,10000,0);

    auto ez2 = [&](double *x,double *p=nullptr){
        return (Rb-xx*sin(x[0]))/pow((Rb*Rb+p[0]*p[0]+xx*xx-2*Rb*xx*sin(x[0])), 3/2);
    };
    TF1 *fez2= new TF1("F", ez2, -10000,10000,1);
    //Bobine circular
    auto Bz2 = [&](double *x,double *p=nullptr){
        fez2->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fez2);
        double Bvalue;
        B.Simpson(1000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bez2= new TF1("F", Bz2, -10000,10000,0);

    auto ezx =[&](double *x,double *p=nullptr){
        return (Rb-p[0]*sin(x[0]))/(Rb*Rb+p[0]*p[0]-2*p[0]*Rb*sin(x[0]));
    };
    TF1 *fezx= new TF1("F", ezx, -10000,10000,1);
    auto Bzx = [&](double *x,double *p=nullptr){
        fezx->SetParameter(0, x[0]);
        Integrator B(0, 2*M_PI, *fezx);
        double Bvalue;
        B.Simpson(1000, Bvalue, err);
        return m0*Nb*Rb*I/(4*M_PI)*Bvalue;
    };
    TF1 *Bezx= new TF1("F", Bzx, -10000,10000,0);


    return 0;
}

