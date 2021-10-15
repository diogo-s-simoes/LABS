#ifndef H_Func1_H
#define H_Func1_H

#include <string>
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TApplication.h"
#include "TStyle.h"
#include <cstdio>
#include <string>

using namespace std;

class Func1D {
	public:
 	
	 //Constructor receives TF1 or default NULL
	Func1D(TF1* ff=NULL);

	~Func1D();

	//Set manually the function of the object
	void SetFunc(TF1* f1);

	//Returns function of the object
	TF1* GetFunc() const;

	//Draws Function on screen and saves eps
	void Draw();

	//Returns value of the function at x
	double Evaluate(double x);
	
	protected:
	
	TF1* F;

};
#endif
