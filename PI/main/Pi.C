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
#include "TRandom3.h"
#include "ODEsolver.h"

int main(){
    vector<double> v;
    v.push_back(0.1);
    v.push_back(0);
    ODEpoint P0(0,v);

    auto fn = [&](double* x, double* par) {
        return x[1];
    };
    TF1 Fn("Fn", fn, 0, 1000, 0); // npar=0, ndim=1 (default)
    Fn.SetNpx(3000);
    
    auto fp = [&](double* x, double* par) {
        return 6*7.26*x[0]-(9./2.)*x[0]*x[0]+3;
    };
    TF1 Fp("Fp", fp, 0, 1000, 0); // npar=0, ndim=1 (default)
    Fp.SetNpx(3000);

    vector<TF1> VF;
    VF.push_back(Fn);
    VF.push_back(Fp);
    ODEsolver S(VF);
    double h = 0.001;
    double tmax = 10;
    vector<ODEpoint> P = S.RK4(P0, h, tmax);

    double* x = new double[int(tmax/h)];
    double* y = new double[int(tmax/h)];
    for (int i = 0; i<P.size(); ++i){
        x[i]=P[i].Get_Time();
        y[i]=P[i].Get_Var_ptr()[0];
    }

    TGraph G(int(tmax/h),x,y);

    TApplication A("A",0,0);
    TCanvas c("c","", 0, 0, 600,600);
    G.SetMarkerStyle(20);
    G.SetMarkerColor(kBlue);
    G.SetMarkerSize(0.5);
    G.Draw("");
    c.Update();
    A.Run();
    return 0;
}
    return 0;
}