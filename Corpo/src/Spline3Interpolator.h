#ifndef H_Spline3Interpolator_H
#define H_Spline3Interpolator_H

#include "DataPoints.h"
#include "TF1.h"
#include "Vec.h"
#include "EqSolver.h"
#include "FCMatrixBanded.h"
#include "FCMatrixFull.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TApplication.h"
#include "TStyle.h"
#include <cstdio>
#include <string>

class Spline3Interpolator : public DataPoints {

 public: 

  Spline3Interpolator(unsigned int N=0, const double *x=NULL, const double *y=NULL, const TF1* fF0=NULL);
  ~Spline3Interpolator();
  Spline3Interpolator(const Spline3Interpolator&);
 
  double Derivate(double x) const;
  double SegmentCalc(double xval, int i) const;
  double SegmentDerivCalc(double xval, int i) const;

  double Interpolate(double) const;
  const TF1& GetInterpolationFunction() const { return *FInterpolator; }
  void SetResolution(int n=200) const { FInterpolator->SetNpx(n); }
  void Draw() const;
  const TCanvas& GetCanvas();

  // underlying function
  void SetFunction(const TF1*);

  // output
  friend std::ostream& operator<< (std::ostream&, const Spline3Interpolator&);
  void Print(string FILE);

  TF1* GetDerivativeFunction() {
    return FDerivator;
  }

  void SetFunction(TF1*);
  //void Print(string FILE=""); // print results

  void  SetCurvatureLines();
  void IsEvenlySpaced(bool);
  

 private:
    double fInterpolator(double *fx, double *par)
     {
      return Interpolate(fx[0]);
     }

    double fDerivator(double *fx, double *par)
    {
      return Derivate(fx[0]);
    }

    TF1* FInterpolator; //interpolation function
    TF1* FDerivator;
    TF1* F0;  //eventual underlying function
    Vec K;
    bool EvenlySpaced;
    TCanvas* cInterpolator;
  };

#endif

