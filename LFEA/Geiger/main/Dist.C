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




    TGraphErrors* GBlindagem = new TGraphErrors();
    GBlindagem->SetMarkerSize(1);
    GBlindagem->SetMarkerColor(kGreen+2);
    GBlindagem->SetMarkerStyle(kFullSquare);
    GBlindagem->SetLineWidth(4);
    GBlindagem->SetLineColor(kBlue-1);
    GBlindagem->SetFillColor(2);
    GBlindagem->SetFillStyle(3001);
    GBlindagem->GetXaxis()->SetTitle("Distance(cm)");
    GBlindagem->GetYaxis()->SetTitle("Counts (Corrected)");


    TGraphErrors* GMais = new TGraphErrors();
    GMais->SetMarkerSize(1);
    GMais->SetMarkerColor(kGreen+2);
    GMais->SetMarkerStyle(kFullSquare);
    GMais->SetLineWidth(4);
    GMais->SetLineColor(kBlue-1);
    GMais->SetFillColor(2);
    GMais->SetFillStyle(3001);
    GMais->GetXaxis()->SetTitle("Distance(cm)");
    GMais->GetYaxis()->SetTitle("Counts (Corrected)");


    for (int i = 0; i<Nlines_distancia; ++i){

        Gdist->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);
   GBlindagem->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);
        GMais->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);
        //Distancia real = distancia + 3.7 - 2.1 + 1.2
        //Radiacao real = radiacao - 0.32*120

        Gdist->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));
   GBlindagem->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));
      GMais->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));
        //Erro horizontal (x) = 0.05cm
        //Erro vertical (Radiaçao) = doutro histograma 1 PLACEHOLDER
    }


    auto l_inversesquarelaw = [](double *x,double *p=nullptr){
      return p[0]/ (x[0]*x[0]);
      //p[0]=A
      //x[0]=d (distancia)
    };

    auto l_comblindagem = [](double *x,double *p=nullptr){
      return p[0]/ (x[0]*x[0])*exp(-p[1]*x[0]);
      //p[0]=A
      //p[1]= blindagem bling bling
      //x[0]=d (distancia)
    };
    auto l_mais = [](double *x,double *p=nullptr){
      return p[0]/ (x[0]*x[0]+ p[1]) + p[2];
      //p[0]=A
      //p[1]= parametro idk
      //p[2]= e so para diminuir erros lolz
      //x[0]=d (distancia)
    };

    TF1* f_inversesquarelaw= new TF1("inverse", l_inversesquarelaw, -1e9,1e9,1);
    TF1* f_comblindagem= new TF1("comblindagem", l_comblindagem, -1e9,1e3,2);
    TF1* f_mais= new TF1("mais", l_mais, -1e9,1e9,3);

    f_inversesquarelaw->SetParameter(0,1.);
    f_comblindagem->SetParameter(0,151700.);
    f_comblindagem->SetParameter(1,0.04251);
    f_mais->SetParameter(0,1.);
    f_mais->SetParameter(1,0.01);
    f_mais->SetParameter(2,0.01);

    Gdist->Fit(f_inversesquarelaw);
    GBlindagem->Fit(f_comblindagem);
    GMais->Fit(f_mais);

    double A1 = f_inversesquarelaw->GetParameter(0);
    double B1 = f_comblindagem->GetParameter(0);
    double B2 = f_comblindagem->GetParameter(1);

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

    Gdist->SetTitle("Variacao com a distancia: Tl-204");
    Gdist->Draw("AP");
    c1->SaveAs("Distancia.png");
    c1->Clear();
    c1->Update();

    GBlindagem->SetTitle("Variacao com a distancia: Tl-204");
    GBlindagem->Draw("AP");
    f_comblindagem->Draw("same");
    c1->SaveAs("DistBlindagem.png");
    c1->Clear();
    c1->Update();
    

    GMais->SetTitle("Variacao com a distancia: Tl-204");
    GMais->Draw("AP");
    c1->SaveAs("DistMais.png");
    c1->Clear();
        
    double radius = 3.355/2;
    double* dists = new double[7];
    double cos_theta=0;
    double* sangles = new double[7];
    for (int i=0; i<7; ++i){
        dists[i]=atof(&(distancia_data.GetData()[i][0][0]))+2.8+5;
    }
    for (int i=0; i<7; ++i){
        cos_theta=dists[i]/sqrt(dists[i]*dists[i]+radius*radius);
        sangles[i]=2*M_PI*(1-cos_theta);
    }

    double Cs1_EM=1;
    double Cs2_EM=1;
    double Tl_EM=1;

    TGraphErrors* Geff_Tl = new TGraphErrors();
    Geff_Tl->SetMarkerSize(1);
    Geff_Tl->SetMarkerColor(kGreen+2);
    Geff_Tl->SetMarkerStyle(kFullSquare);
    Geff_Tl->SetLineWidth(4);
    Geff_Tl->SetLineColor(kBlue-1);
    Geff_Tl->SetFillColor(2);
    Geff_Tl->SetFillStyle(3001);
    Geff_Tl->GetXaxis()->SetTitle("Distance(cm)");
    Geff_Tl->GetYaxis()->SetTitle("Efficiency");

    TGraphErrors* Geff_Cs1 = new TGraphErrors();
    Geff_Cs1->SetMarkerSize(1);
    Geff_Cs1->SetMarkerColor(kGreen+2);
    Geff_Cs1->SetMarkerStyle(kFullSquare);
    Geff_Cs1->SetLineWidth(4);
    Geff_Cs1->SetLineColor(kBlue-1);
    Geff_Cs1->SetFillColor(2);
    Geff_Cs1->SetFillStyle(3001);
    Geff_Cs1->GetXaxis()->SetTitle("Distance(cm)");
    Geff_Cs1->GetYaxis()->SetTitle("Efficiency");

    TGraphErrors* Geff_Cs2 = new TGraphErrors();
    Geff_Cs2->SetMarkerSize(1);
    Geff_Cs2->SetMarkerColor(kGreen+2);
    Geff_Cs2->SetMarkerStyle(kFullSquare);
    Geff_Cs2->SetLineWidth(4);
    Geff_Cs2->SetLineColor(kBlue-1);
    Geff_Cs2->SetFillColor(2);
    Geff_Cs2->SetFillStyle(3001);
    Geff_Cs2->GetXaxis()->SetTitle("Distance(cm)");
    Geff_Cs2->GetYaxis()->SetTitle("Efficiency");

    for (int i=0; i<7; ++i){
        Geff_Tl->SetPoint(i,dists[i],atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);
        Geff_Cs1->SetPoint(i,dists[i],atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120);
        Geff_Cs2->SetPoint(i,dists[i],atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120);
    }

    auto l_eff_Tl = [&](double *x,double *p=nullptr){
      return p[0]*Tl_EM*(2*M_PI*(1-(x[0]/sqrt(x[0]*x[0]+radius*radius))))/(4*M_PI)*exp(-p[1]*x[0]);
    };
    TF1* f_eff_Tl= new TF1("constant", l_eff_Tl, -1e9,1e9,2);
    auto l_eff_Cs1 = [&](double *x,double *p=nullptr){
      return p[0]*Cs1_EM*(2*M_PI*(1-(x[0]/sqrt(x[0]*x[0]+radius*radius))))/(4*M_PI)*exp(-p[1]*x[0]);
    };
    TF1* f_eff_Cs1= new TF1("constant", l_eff_Cs1, -1e9,1e9,2);
    auto l_eff_Cs2 = [&](double *x,double *p=nullptr){
      return p[0]*Cs2_EM*(2*M_PI*(1-(x[0]/sqrt(x[0]*x[0]+radius*radius))))/(4*M_PI)*exp(-p[1]*x[0]);
    };
    TF1* f_eff_Cs2= new TF1("constant", l_eff_Cs2, -1e9,1e9,2);

    Geff_Tl->Fit(f_eff_Tl);
    Geff_Cs1->Fit(f_eff_Cs1);
    Geff_Cs2->Fit(f_eff_Cs2);

    Geff_Tl->Draw("AP");
    c1->SaveAs("eff_Tl.png");
    c1->Clear();

    Geff_Cs1->Draw("AP");
    c1->SaveAs("eff_Cs1.png");
    c1->Clear();

    Geff_Cs2->Draw("AP");
    c1->SaveAs("eff_Cs2.png");
    c1->Clear();


    return 0;
}
