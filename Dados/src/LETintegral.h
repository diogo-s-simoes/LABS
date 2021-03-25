#ifndef _letIntegrator_
#define _letIntegrator_

#include "Derivator.h"

using namespace std;

class LETintegral{

	public:
		LETintegral(vector<vector<double>> fV);

        void order(int var);
		double integrate(int y, int x);

	protected:
		vector<vector<double>> V;
};

#endif
