#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"



int main(){

  double *eps = new double[4];
  double *tpt = new double[4];



  eps[0]=log(.1);
  eps[1]=log(.3);
  eps[2]=log(.5);
  eps[3]=log(1.);

  tpt[0]=log(103.4+273.15);
  tpt[1]=log(62.8+273.15);
  tpt[2]=log(50.5+273.15);
  tpt[3]=log(40.8+273.15);


  Spline3Interpolator please(4,eps,tpt);
  TCanvas *c1=new TCanvas;
  please.Draw();
  c1->SaveAs("bin/T(eps)_spline.png");
  c1->Clear();

  NewtonInterpolator please2(4,tpt,eps);
  please2.Draw();
  c1->SaveAs("bin/T(eps)2_newton.png");
  c1->Clear();


//////////////////////////////////////////////////////////////////

  auto lCeninhas = [](double *x,double *p=nullptr){
    return p[0]-  p[1] * 4 * x[0];
  };

  TF1* fCeninhas = new TF1("PAIN", lCeninhas, 3,6,2);

  //fCeninhas->SetParameter(0,4.5);
  //fCeninhas->SetParameter(1,1.);


  TGraph* gCeninhas= new TGraph();
  gCeninhas->SetPoint(0, log(103.4+273.15), log(0.1));
  gCeninhas->SetPoint(1, log(62.8+273.15), log(0.3));
  gCeninhas->SetPoint(2, log(50.5+273.15), log(0.5));
  gCeninhas->SetPoint(3, log(40.8+273.15), log(1.));
  gCeninhas->Fit(fCeninhas);



  //PONTO (TEMPERATURA, EMISSIVIDADE)

   gCeninhas->SetMarkerColor(kBlue);
   gCeninhas->SetMarkerStyle(8);   
   gCeninhas->SetMarkerSize(0.8);


   fCeninhas->SetLineColor(kGreen);
   fCeninhas->SetLineStyle(1);


   TAxis *ax1= fCeninhas->GetXaxis();
   TAxis *ay2= fCeninhas->GetYaxis();

   ax1->SetTitle("T(K)");
   ay2->SetTitle("#epsilon");

  cout << endl<<endl<<endl<<fCeninhas->Eval(log(134+273.15)) <<endl;


  gCeninhas->Draw("AP");

  fCeninhas->Draw("same");

  gPad->SetGrid(1, 1); gPad->Update();

  auto legend4 = new TLegend(0.65,0.75,0.9,0.9);
    legend4->SetTextFont(62);
    legend4->SetTextSize(0.04);
    legend4->AddEntry(fCeninhas,"Ensaio 3","l");
    //legend4->AddEntry(fPlanck,"Lei de Planck","l");
    legend4->Draw("same");

  c1->SaveAs("bin/T(eps)Fit.png");


  //R=e*s*T^4
  //T(e)=(R/e/s)^1/4
}