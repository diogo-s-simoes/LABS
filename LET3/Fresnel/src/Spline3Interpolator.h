#ifndef __Spline3Interpolator__
#define __Spline3Interpolator__

#include "DataPoints.h"
#include "TF1.h"


class Spline3Interpolator: public DataPoints{
public:
// constructors and destructor
Spline3Interpolator(int n=0, double *arrx=nullptr, double *arry=nullptr,TF1* fF0=nullptr);
~Spline3Interpolator();

// copy constructor
Spline3Interpolator(const Spline3Interpolator&);

// interpolation methods
double Interpolate(double x);
void Draw(); //draw everything (points and interpolation function)
void SetResolution(int n=200) const; // deals with SetNpx method of TF1
const TCanvas& GetCanvas();
TF1* GetInterpolationFunction() const;

void SetCurvatureLines();

// output
//void Print(std::string FILE="") const; // print results
friend std::ostream& operator<< (std::ostream&, const Spline3Interpolator&);

private:
double fInterpolator(double *fx, double *par) {return Interpolate(fx[0]);}
double *K=nullptr;

TF1* FInterpolator; //interpolation function
TF1* F0; //eventual underlying function
TCanvas* cInterpolator; // includes data points and curve*/
};
#endif
