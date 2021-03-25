#ifndef __Derivator__
#define __Derivator__

#include "Func1D.h"


class Derivator: public Func1D{
public:
  Derivator(double fH=1e-6,const TF1 *fp=nullptr):h(fH), Func1D(fp){;}
  Derivator(int n, double *fx,double *fy,TF1 *fp);
 // Derivator(double fH, const Func1D A): h(fH), Func1D(A){;}

  double FirstDerivative(double);
  double SecondDerivative(double);


~Derivator();

private:
  double h;
  int N;
  double *x=nullptr;
  double *y=nullptr;

};



#endif