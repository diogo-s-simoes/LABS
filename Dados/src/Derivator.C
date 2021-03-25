#include "Derivator.h"
#include <stdexcept>

Derivator::Derivator(int n, double *fx,double *fy=nullptr,TF1 *fp=nullptr):N(n),x(new double[n]),y(new double[n]),Func1D(fp){
  if(!fy && fp){
    for (int i = 0; i < N; ++i){
      x[i]=fx[i];
      y[i]=this->Eval(x[i]);
    }
  }
  else if(!fy && !fp){
    throw std::invalid_argument("No function or y values\n");
  }
  else{
    for (int i = 0; i < N; ++i){
      y[i]=fy[i];
      x[i]=fx[i];
    }
  }
}

Derivator::~Derivator(){
	if(x) delete[] x;
	if(y) delete[] y;
}

double Derivator::FirstDerivative(double p){
  double deriv=((f->Eval(p-2*h)+8*f->Eval(p+h))-(8*f->Eval(p-h)+f->Eval(p+2*h)))/(12*h);
  return deriv;
}

double Derivator::SecondDerivative(double p){
  double deriv2=(-f->Eval(p-2*h)+16*f->Eval(p-h)-30*f->Eval(p)+16*f->Eval(p+h)-f->Eval(p+2*h))/(12*h*h);
  return deriv2;
}