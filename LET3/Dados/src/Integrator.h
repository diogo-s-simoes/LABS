#ifndef __Integrator__
#define __Integrator__

#include "Func1D.h"

class Integrator: public Func1D {

 public:
  // construtors and destructor 
  Integrator(double fx0=0., double fx1=1., const TF1 *fp=nullptr) : x0(fx0), x1(fx1), Func1D(fp) {};
  Integrator(double fx0, double fx1, const TF1& fp) : Integrator(fx0, fx1, &fp) {};  
  ~Integrator() = default;

  // integrator methods
  void setInterval(double fx0,double fx1);
  
  void Trapezoidal(int n, double& Integral);
  void Simpson(int n, double& Integral);
  double GaussQuadrature(int n);
  
protected:
  double x0; // function range for integration
  double x1;
}; 

#endif