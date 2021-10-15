#ifndef _Derivator_H
#define _Derivator_H

#include "Func1D.h"

using namespace std;

class Derivator: public Func1D{

	public:
		Derivator(TF1 *f=NULL);
		~Derivator();

	double Deriv_1(double x, double h, int type=0);
	double Deriv_2(double x, double h, int type=0);
	double Deriv_3(double x, double h, int type=0);
	double Deriv_4(double x, double h, int type=0);
	double Deriv_n(double x, double h, int type=0, int n=1);
	double Deriv5P_1(double x, double h);
	double Deriv5P_2(double x, double h);
	double funcDeriv_n(double* x, double* p);
	TF1* GetDeriv(int n, double h, int type);

	int factorial(int n);
	int nCr(int n, int r);
};

#endif