#include "Integrator.h"
#include "Func1D.h"
#include <iostream>


Integrator::Integrator(double fx0, double fx1, const TF1 *ff){
	x0=fx0;
	x1=fx1;
	F = new TF1(*ff);
}

Integrator::~Integrator(){
	delete F;
}

void Integrator::Trapezoidal(int n, double& integ, double& err){
	integ=0;
	err=0;
	double h = (x1-x0)/n;
	for(int i=0;i<n+1;i++){
 		if(i==0)
 			integ+=(h/2)*Evaluate(x0);
 		else if(i==n)
 			integ+=(h/2)*Evaluate(x1);
 		else 
 			integ+=(h)*Evaluate(x0+i*h);
		err+=fabs(pow(h,3)*Derivator(F).Deriv5P_2(x0+i*h+h/2,h)/12);	
 	}
}

void Integrator::TrapezoidalAdaptive(double& integ, double& err){
	integ= (Evaluate(x0)+Evaluate(x1))*(x1-x0)/2;
	double k;
	double b=0;
	double s;
	for(k=2; fabs(integ-b)>err; ++k){
		s=0;
		for(int i = 1; i<=pow(2,k-2); ++i){
			s+=Evaluate(x0+(2*i-1)*(x1-x0)/pow(2,k-1));
		}
		b=integ;
		integ=0.5*integ+(x1-x0)/pow(2,k-1)*s;
	}
}

void Integrator::Simpson(int n, double& integ, double& err){
	integ=0.;
	err=0.;
	double x = x0;
	double h = (x1-x0)/n;
	int q = (n+1)%2;

	while (x+2*h<x1){
		integ+=(Evaluate(x)+4*Evaluate(x+h)+Evaluate(x+2*h))*h/2;
		x+=2*h;
	}

	for(int i=0; i<n+q; ++i){
	 	if(i==0 ){
	 		integ+= (h/3)*Evaluate(x0);
        }
	 	else if(i==n){
			integ += (h/3)*Evaluate(x1);
        }
        else if(i%2==1){ //i is odd 
			integ += (h/3)*4*Evaluate(x0+i*h);
        }
        else if(i%2==0){ //i is even 
			integ += (h/3)*2*Evaluate(x0+i*h);
        }
        //err+=pow(h,5)*Derivator(F).Deriv_4(x0+i*h,h,0)/180.;
	}

	if(!q){
		integ+= fabs((h/12)*(-Evaluate(x1-2*h)+8*Evaluate(x1-h)+5*Evaluate(x1)));
	}
}

void Romberg(int n, double& Integral, double& Error){
	//todo
}