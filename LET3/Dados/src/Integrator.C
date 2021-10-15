#include "Integrator.h"


#include <type_traits>
#include <typeinfo>
#include <vector>



  // integrator methods


void Integrator::setInterval(double fx0,double fx1){
  x0=fx0;
  x1=fx1;
}



void Integrator::Trapezoidal(int n, double& Integral){

  Integral=0;  
  double slice=(x1-x0)/n;

  Integral = this->Eval(x0);
  Integral += this->Eval(x1); 
  for(int i=1;i<n;i++)
    Integral += 2*this->Eval(x0+i*slice);
  
  Integral*=slice/2;

}



void Integrator::Simpson(int n, double& Integral){

 Integral=0;
 double h = (x1-x0)/n;
  if(n%2==0){
    for(int i=1; i<n; i+=2){
      Integral+= (this->Eval(x0+(i-1)*h)+ 4*this->Eval(x0+i*h)+this->Eval(x0+(i+1)*h));
    }
    Integral*=h/3;
   }
  else{    
    for(int i=1; i<n-1; i+=2){
      Integral+=(this->Eval(x0+(i-1)*h)+ 4*this->Eval(x0+i*h)+this->Eval(x0+(i+1)*h));
    }
    Integral*=h/3;

    Integral+= h/12 * (-this->Eval(x0+(n-2)*h)+8*this->Eval(x0+(n-1)*h)+5*this->Eval(x1));
  }

}





double Integrator::GaussQuadrature(int n){
  double A1=5/9.,A2=8/9.,A3=5/9.;
  double h=(x1-x0)/n;

  double Qn=0.;
  for(int i=0;i<n;i++){
    Qn+= A1 * this->Eval(x0 + h*i + h*(1.-sqrt(3./5.))/2.); 
    Qn+= A2 * this->Eval(x0 + h*i + h/2.); 
    Qn+= A3 * this->Eval(x0 + h*i + h*(1.+sqrt(3./5.))/2.); 
  }

  Qn*=h/2.;

  return Qn;
}