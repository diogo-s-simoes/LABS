#ifndef __ODESOLVER__
#define __ODESOLVER__

#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>
#include "TF1.h"
#include "ODEpoint.h"
#include <vector>
#include "FCMatrixBanded.h"
#include "FCMatrixAlgorithm.h"
#include "EqSolver.h"

using namespace std;

class ODEsolver{
    
    public:

    ODEsolver(vector<TF1> FF);
    ODEsolver();
    ~ODEsolver();

    vector<ODEpoint> Euler(const ODEpoint& P0, double h, double T);
    vector<ODEpoint> Heun(const ODEpoint& P0, double h, double T);
    vector<ODEpoint> RK2(const ODEpoint& P0, double h, double T);
    vector<ODEpoint> RK4(const ODEpoint& P0, double h, double T);
    vector<ODEpoint> RK4AS(const ODEpoint& P0, double h, double T, double delta);
    vector<ODEpoint> Shoot(const ODEpoint& P0, const ODEpoint& Pf, double h);
    static vector<ODEpoint> FDiff(int option, const ODEpoint& P0, const ODEpoint& Pf, double h, const TF1& a, const TF1& b, const TF1& c, const TF1& G);
    vector<ODEpoint> LeapFrog(const ODEpoint& P0, double h, double T);

    void SetODEfunc(vector<TF1> F);
    vector<TF1>& GetODEfunc();
    TF1& GetODEfunc(int i){return F[i];}
    
    private:

    ODEpoint EulerIterator(const ODEpoint&, double h);
    ODEpoint HeunIterator (const ODEpoint&, double h);
    ODEpoint RK2Iterator(const ODEpoint&, double h);
    ODEpoint RK4Iterator(const ODEpoint&, double h);
    ODEpoint LPIterator(const ODEpoint&, const ODEpoint&, double h);

    vector<TF1>	F;	
};
#endif