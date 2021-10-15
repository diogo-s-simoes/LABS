#include <cmath>
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPad.h"
#include "TF1.h"
#include "TH1D.h"
#include "NewReader.h"
#include "LETintegral.h"
#include "Spline3Interpolator.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "DataReader.h"

int main(){

    DataReader distancia_data("data/distancia.txt");

    int Nlines_distancia = distancia_data.GetLines();

    cout << Nlines_distancia << endl;
    
    TGraphErrors* Gdist = new TGraphErrors();
    Gdist->SetMarkerStyle(kFullSquare);
    Gdist->SetMarkerSize(1);
    Gdist->SetMarkerColor(kGreen+2);
    Gdist->SetLineWidth(4);
    Gdist->SetLineColor(kBlue-1);
    Gdist->SetFillColor(2);
    Gdist->SetFillStyle(3001);
    Gdist->GetXaxis()->SetTitle("Distance(cm)");
    Gdist->GetYaxis()->SetTitle("Counts (Corrected)");

    //atof(&(ficheiro1.GetData()[i][j][0]))

    for (int i = 0; i<Nlines_distancia; ++i){

        Gdist->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);
        //Distancia real = distancia + 3.7 - 2.1 + 1.2
        //Radiacao real = radiacao - 0.32*120

        Gdist->SetPointError(i, 0.05 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));
        //Erro horizontal (x) = 0.05cm
        //Erro vertical (Radiaçao) = doutro histograma 1 PLACEHOLDER
    }


    auto l_inversesquarelaw = [](double *x,double *p=nullptr){
      return p[0]/ (x[0]*x[0]);
      //p[0]=A
      //x[0]=d (distancia)
    };

    TF1* f_inversesquarelaw= new TF1("inverse", l_inversesquarelaw, -1e9,1e9,1);



    f_inversesquarelaw->SetParameter(0,1.);

    Gdist->Fit(f_inversesquarelaw);

    double A = f_inversesquarelaw->GetParameter(0);


    TCanvas* c1 = new TCanvas("","",1920,1080);





    gStyle->SetOptStat(0);
  
    gPad->SetGrid(1, 1);
    gStyle->SetLegendBorderSize(0);

       
  gStyle->SetOptFit(111);
  gStyle -> SetStatBorderSize(5);
  gStyle -> SetStatFontSize(1);
  gStyle -> SetStatFont(62);
  gStyle -> SetStatTextColor(1);
  gStyle -> SetStatColor(3);
  gStyle -> SetStatStyle(0);
  gStyle -> SetStatX(0.85);
  gStyle -> SetStatY(0.85);
  gStyle -> SetStatW(0.2165);



    Gdist->Draw("AP");
    c1->SaveAs("Distancia.png");
    c1->Clear();
    




    return 0;
}
