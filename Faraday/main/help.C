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
    //bobines de Helmholtz
    double R1=0.068; //m
    double N1=320;
    double dbH=0.068; //m
    double m0=1.256637e-6; //H/m

    //bobine móvel
    double R2=0.0207; //m
    double N2=500;

    I1=0.795; //correct this

    auto v1 = [&](double *x,double *p=nullptr){
        return 8/(sqrt(5)*5)*m0*N1*I1/R1*N2*S2*x[0];
    };
    TF1 *V2m= new TF1("F", v1, -3,30,0);


    auto v2 = [&](double *x,double *p=nullptr){
        return 8/(sqrt(5)*5)*m0*N1*N2*R2*x[0]; 
    };
    TF1 *V2m1= new TF1("F", Bx, -3,50,0);    

    return 0;
}

