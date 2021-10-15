#include "Derivator.h"
#include "Func1D.h"
#include <iostream>


Derivator::Derivator(TF1 *ff){
    cout<<"constructor"<<endl;
	F = new TF1;
	F=ff;
}

Derivator::~Derivator(){
	delete F;
}


double Derivator::Deriv_n(double x, double h,  int type, int n){
    cout<<"deriv"<<endl;
    double sum=0;
	//n is the order of the derivative
	switch(type){
		case 0:
		//CENTRAL
			for(int i=0; i<=n; ++i){
				sum+=pow(-1,i)*nCr(n,i)*Evaluate(x+ ((double)n/2-i)*h);
			}
		break;

		case 1:
		//FORWARD
			for(int i=0; i<=n; ++i){
				sum+=pow(-1,i)*nCr(n,i)*Evaluate(x+(n-i)*h);
			}
		break;
	
		case 2:
		//BACKWARD
			for(int i=0; i<=n; ++i){
				sum+=pow(-1,i)*nCr(n,i)*Evaluate(x-i*h);
			}
		break;		
	}
	return sum/pow(h,n);
}

double Derivator::Deriv5P_1(double x, double h){
	return ((Evaluate(x-2*h)+8*Evaluate(x+h))-(8*Evaluate(x-h)+Evaluate(x+2*h)))/(12*h);
}

double Derivator::Deriv5P_2(double x, double h){
	return (-Evaluate(x-2*h)+16*Evaluate(x-h)-30*Evaluate(x)+16*Evaluate(x+h)-Evaluate(x+2*h))/(12*h*h);
}

double Derivator::funcDeriv_n(double* x, double* p)
{
	return Deriv_n(x[0], p[0], p[1], p[2]);
}

TF1* Derivator::GetDeriv(int n, double h, int type)
{
  double xmin, xmax;
  F->GetRange(xmin, xmax);

  TF1* f = new TF1("f", this, &Derivator::funcDeriv_n, xmin, xmax, 3);
  f->SetParameters(n, h, type);

  return f;
}

double Derivator::Deriv_1(double x, double h, int type)
{
	return Deriv_n(x,h, type, 1);
}

double Derivator::Deriv_2(double x, double h, int type)
{
	return Deriv_n(x,h,type, 2);
}

double Derivator::Deriv_3(double x, double h, int type)
{
	return Deriv_n(x,h, type,3);
}

double Derivator::Deriv_4(double x, double h, int type)
{
	return Deriv_n(x,h, type,4);
}

int Derivator::factorial(int n)
{
	int total_sofar;

	if (n>0)
	 {
		total_sofar = n * factorial(n-1);
	 }


	else if (n==0)
	{
		total_sofar = 1;
	}

	else
	{
		cout << " ##### Impossível calcular factorial de números negativos #####" << endl;
	    return 0;
	}
		
	return total_sofar;
}

int Derivator::nCr(int n, int r){
	int nCr=0;
	nCr=factorial(n)/(factorial(r)*factorial(n-r));
	return nCr;
}