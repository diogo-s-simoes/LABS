#ifndef __NewI__
#define __NewI__

#include "DataPoints.h"
#include <iostream>
#include <cstdlib>
#include <TF1.h>

using namespace std;

class NewtonInterpolator : public DataPoints {

    public:
    
    NewtonInterpolator(unsigned int N=0, const double *x=NULL, const double *y=NULL, const TF1* fF0=NULL);
    ~NewtonInterpolator();
    NewtonInterpolator(const NewtonInterpolator&);
    
    double Interpolate(double) const;
    const TF1& GetInterpolationFunction() const { return *FInterpolator; }
    void SetResolution(int n=200) const { FInterpolator->SetNpx(n); }
    void Draw() const;
    const TCanvas& GetCanvas();

    // underlying function
    void SetFunction(const TF1*);

    // output
    friend std::ostream& operator<< (std::ostream&, const NewtonInterpolator&);
    void Print(string FILE);

    double DiffTable(int i, int j) const;

    private:
    
    double fInterpolator(double *fx, double *par) {
        return Interpolate(fx[0]);
    }
    
    TF1* FInterpolator; //interpolation function
    TF1* F0; //eventual underlying function
    TCanvas* cInterpolator;
};
#endif