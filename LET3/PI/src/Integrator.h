#ifndef _Integrator_H
#define _Integrator_H

#include "Func1D.h"
#include "Derivator.h"

using namespace std;

class Integrator: public Func1D{

	public:
		Integrator(double fx0, double fx1, const TF1 *ff=nullptr);
		Integrator(double fx0, double fx1, const TF1& f):Integrator(fx0, fx1, &f) {};
		~Integrator();

		void Trapezoidal(int n, double& integ, double& err);
		void TrapezoidalAdaptive(double& integ, double& err);
    	void Simpson(int n, double& integ, double& err);
  		void Romberg(int n, double& Integral, double& Error);

	protected:
		double x0;
		double x1;
};

#endif