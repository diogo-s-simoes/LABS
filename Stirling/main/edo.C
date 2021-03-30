#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TApplication.h"
#include "ODEsolver.h"

int main(){

    double g=1.4;
    double w = 2*M_PI/0.313;
    double A = 0.002827;
    double ac = 0.5*0.000138;
    double ae = 0.5*0.000138;
    double R=8.3145;
    double h=0.001;
    double Tck=(23.2+40.)/2+273.15;
    double The=542+273.15;

    //p=x[0]
    //mc=x[1]
    //mk=x[2]
    //mr=x[3]
    //mh=x[4]
    //me=x[5]
    //Tc=x[6]
    //Tk=x[7]
    //Tr=x[8]
    //Th=x[9]
    //Te=x[10]
    //Vc=x[11]
    //Vk=x[12]
    //Vr=x[13]
    //Vh=x[14]
    //Ve=x[15]

    vector<double> v;
    v.push_back(101234);
    v.push_back(0.000001);
    v.push_back(0.000001);
    v.push_back(0.000001);
    v.push_back(0.000001);
    v.push_back(0.000001);
    v.push_back(300);
    v.push_back((23.2+40.)/2+273.15);
    v.push_back((((23.2+40.)/2+273.15)+(542+273.15))/2);
    v.push_back(542+273.15);
    v.push_back(300);
    v.push_back(0.000166);
    v.push_back(0.000);
    v.push_back(0.000036);
    v.push_back(0.00000614);
    v.push_back(0.000069);
    ODEpoint P0(0,v);

    auto fvc = [&](double* x, double* par) {
        return A*ac*w*(cos(w*x[16])-cos(w*x[16]-M_PI/2));
    };
    TF1 FVC("FVC", fvc, 0, 1000, 0); // npar=0, ndim=1 (default)
    FVC.SetNpx(3000);

    auto fve = [&](double* x, double* par) {
        return A*ae*w*cos(w*x[16]);
    };
    TF1 FVE("FVE", fve, 0, 1000, 0); // npar=0, ndim=1 (default)
    FVE.SetNpx(3000);

    auto fp = [&](double* x, double* par) {
        return -g*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The);
    };
    TF1 FP("FP", fp, 0, 1000, 0); // npar=0, ndim=1 (default)
    FP.SetNpx(3000);
    
    auto fmc = [&](double* x, double* par) {
        return (x[0]*A*ac*w*cos(w*x[16])-g*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The)*x[11]/g)/(R*Tck);
    };
    TF1 FMC("FMC", fmc, 0, 1000, 0); // npar=0, ndim=1 (default)
    FMC.SetNpx(3000);

    auto fmk = [&](double* x, double* par) {
        return x[2]*(-g)*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The)/x[0];
    };
    TF1 FMK("FMK", fmk, 0, 150, 0); // npar=0, ndim=1 (default)
    FMK.SetNpx(3000);

    auto fmr = [&](double* x, double* par) {
        return x[3]*(-g)*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The)/x[0];
    };
    TF1 FMR("FMR", fmr, 0, 150, 0); // npar=0, ndim=1 (default)
    FMR.SetNpx(3000);

    auto fmh = [&](double* x, double* par) {
        return x[4]*(-g)*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The)/x[0];
    };
    TF1 FMH("FMH", fmh, 0, 150, 0); // npar=0, ndim=1 (default)
    FMH.SetNpx(3000);

    auto fme = [&](double* x, double* par) {
        return -(x[0]*A*ac*w*cos(w*x[16])-g*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The)*x[11]/g)/(R*Tck)+(x[2]+x[3]+x[4])*(g)*x[0]*(A*ac*w*cos(w*x[16])/Tck+A*ae*w*cos(w*x[16]-M_PI/2)/The)/(x[15]/Tck+g*(x[12]/x[7]+x[13]/x[8]+x[14]/x[9])+x[15]/The)/x[0];
    };
    TF1 FME("FME", fme, 0, 150, 0); // npar=0, ndim=1 (default)
    FME.SetNpx(3000);

    auto ftc = [&](double* x, double* par) {
        return (x[0]*x[11]/(R*x[1])-x[6])/h;
    };
    TF1 FTC("FTC", ftc, 0, 150, 0); // npar=0, ndim=1 (default)
    FTC.SetNpx(3000);

    auto fte = [&](double* x, double* par) {
        return (x[0]*x[15]/(R*x[5])-x[10])/h;
    };
    TF1 FTE("FTE", fte, 0, 150, 0); // npar=0, ndim=1 (default)
    FTE.SetNpx(3000);

    auto ftk = [&](double* x, double* par) {
        return 0*x[0];
    };
    TF1 FTK("FTK", ftk, 0, 150, 0); // npar=0, ndim=1 (default)
    FTK.SetNpx(3000);

    auto ftr = [&](double* x, double* par) {
        return 0*x[0];
    };
    TF1 FTR("FTR", ftr, 0, 150, 0); // npar=0, ndim=1 (default)
    FTR.SetNpx(3000);

    auto fth = [&](double* x, double* par) {
        return 0*x[0];
    };
    TF1 FTH("FTH", fth, 0, 150, 0); // npar=0, ndim=1 (default)
    FTH.SetNpx(3000);

    auto fvk = [&](double* x, double* par) {
        return R*x[2]*x[7]/x[0];
    };
    TF1 FVK("FVK", fvk, 0, 150, 0); // npar=0, ndim=1 (default)
    FVK.SetNpx(3000);

    auto fvr = [&](double* x, double* par) {
        return R*x[3]*x[8]/x[0];
    };
    TF1 FVR("FVR", fvr, 0, 150, 0); // npar=0, ndim=1 (default)
    FVR.SetNpx(3000);

    auto fvh = [&](double* x, double* par) {
        return R*x[4]*x[9]/x[0];
    };
    TF1 FVH("FVH", fvh, 0, 150, 0); // npar=0, ndim=1 (default)
    FVH.SetNpx(3000);

    vector<TF1> VF;
    VF.push_back(FP);
    VF.push_back(FMC);
    VF.push_back(FMK);
    VF.push_back(FMR);
    VF.push_back(FMH);
    VF.push_back(FME);
    VF.push_back(FTC);
    VF.push_back(FTK);
    VF.push_back(FTR);
    VF.push_back(FTH);
    VF.push_back(FTE);
    VF.push_back(FVC);
    VF.push_back(FVK);
    VF.push_back(FVR);
    VF.push_back(FVH);
    VF.push_back(FVE);
    ODEsolver S(VF);
    double tmax = 75;
    vector<ODEpoint> P = S.RK4(P0, h, tmax);

    return 0;
}