#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"



int main(){

  double *eps = new double[4];
  double *tpt = new double[4];



  eps[0]=.1;
  eps[1]=.3;
  eps[2]=.5;
  eps[3]=1.;

  tpt[0]=103.4;
  tpt[1]=62.8;
  tpt[2]=50.5;
  tpt[3]=40.5;


  Spline3Interpolator please(4,eps,tpt);


  TCanvas *c1=new TCanvas;

  please.Draw();

  c1->SaveAs("bin/T(eps).png");



  c1->Clear();

  NewtonInterpolator please2(4,tpt,eps);

  please2.Draw();

  c1->SaveAs("bin/T(eps)2.png");

  c1->Clear();


  auto lCeninhas = [](double *x,double *p=nullptr){
    return p[0]/pow(x[0],4);
  };

  TF1* fCeninhas = new TF1("PAIN", lCeninhas, 0.,1.,2);

  fCeninhas->SetParameter(0,.1);

  TGraph gCeninhas(4,tpt,eps);

  gCeninhas.Fit(fCeninhas);

  gCeninhas.SetMarkerStyle(16);
  gCeninhas.SetMarkerColor(kBlue);
  gCeninhas.SetMarkerSize(.5);

  gCeninhas.Draw("AL");
  //fCeninhas->Draw("same");



  c1->SaveAs("bin/T(eps)Fit.png");


  //R=e*s*T^4
  //T(e)=(R/e/s)^1/4
}