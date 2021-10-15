#include "Func1D.h"
#include <string>
using namespace std;

Func1D::Func1D(TF1* ff)
{

	F = new TF1;
	F=ff;

}

Func1D::~Func1D()
{
  
}

void Func1D::SetFunc(TF1* f1)
{
	
	F = new TF1;
	F=f1;
}

TF1* Func1D::GetFunc() const
{
	return F;
}

void Func1D::Draw()
{
 /*if (Nplots == 0) {
   //create application
    TApplication * MyRootApp;
    MyRootApp = new TApplication("Just an example...", NULL, NULL);
    MyRootApp->SetReturnFromRun(true);
  }*/

  	//Creates Canvas
	TCanvas *c2 = new TCanvas("c1","c1",600,500);

	gPad->Clear();
	gStyle->SetLabelSize(0.06,"X");
	gStyle->SetLabelSize(0.06,"Y");

	gPad->DrawFrame(F->GetXmin(), F->GetMinimum(), 
                  F->GetXmax(), F->GetMaximum(), "Func1D");

	//Se F nao for null desenhar!
	if(F!=NULL)
	{	
		F->SetLineColor(kBlue);
		F->SetLineWidth(4);
		F->SetLineStyle(1);
		F->Draw("Same");
	}

 
	    
	  c2->Update();
	  c2->SaveAs("func1D.eps");
	  gPad->WaitPrimitive();

	  //delete MyRootApp;
	  delete c2;

	  //Nplots++;

 }

double Func1D::Evaluate(double x){
	return F->Eval(x);
}