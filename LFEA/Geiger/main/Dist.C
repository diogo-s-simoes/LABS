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
    


//////////////TALIO///////////////////////////////////
    TGraphErrors* TlGDist = new TGraphErrors();
    TlGDist->SetMarkerStyle(kFullSquare);
    TlGDist->SetMarkerSize(1);
    TlGDist->SetMarkerColor(kRed);
    TlGDist->SetLineWidth(3);
    TlGDist->SetLineColor(kBlue-1);
    TlGDist->SetFillColor(2);
    TlGDist->SetFillStyle(3001);
    TlGDist->GetXaxis()->SetTitle("Distance(cm)");
    TlGDist->GetYaxis()->SetTitle("Counts (Corrected)");

    TGraphErrors* TlBlindagem = new TGraphErrors();
    TlBlindagem->SetMarkerSize(1);
    TlBlindagem->SetMarkerColor(kRed);
    TlBlindagem->SetMarkerStyle(kFullSquare);
    TlBlindagem->SetLineWidth(3);
    TlBlindagem->SetLineColor(kBlue-1);
    TlBlindagem->SetFillColor(2);
    TlBlindagem->SetFillStyle(3001);
    TlBlindagem->GetXaxis()->SetTitle("Distance(cm)");
    TlBlindagem->GetYaxis()->SetTitle("Counts (Corrected)");

    TGraphErrors* TlMais = new TGraphErrors();
    TlMais->SetMarkerSize(1);
    TlMais->SetMarkerColor(kRed);
    TlMais->SetMarkerStyle(kFullSquare);
    TlMais->SetLineWidth(3);
    TlMais->SetLineColor(kBlue-1);
    TlMais->SetFillColor(2);
    TlMais->SetFillStyle(3001);
    TlMais->GetXaxis()->SetTitle("Distance(cm)");
    TlMais->GetYaxis()->SetTitle("Counts (Corrected)");

//////////////cesio com tampa//////////////////////////////////////
    TGraphErrors* CsTDist = new TGraphErrors();
    CsTDist->SetMarkerStyle(kFullSquare);
    CsTDist->SetMarkerSize(1);
    CsTDist->SetMarkerColor(kMagenta+2);
    CsTDist->SetLineWidth(3);
    CsTDist->SetLineColor(kBlue-1);
    CsTDist->SetFillColor(2);
    CsTDist->SetFillStyle(3001);
    CsTDist->GetXaxis()->SetTitle("Distance(cm)");
    CsTDist->GetYaxis()->SetTitle("Counts (Corrected)");

    TGraphErrors* CsTBlindagem = new TGraphErrors();
    CsTBlindagem->SetMarkerSize(1);
    CsTBlindagem->SetMarkerColor(kMagenta+2);
    CsTBlindagem->SetMarkerStyle(kFullSquare);
    CsTBlindagem->SetLineWidth(3);
    CsTBlindagem->SetLineColor(kMagenta-1);
    CsTBlindagem->SetFillColor(2);
    CsTBlindagem->SetFillStyle(3001);
    CsTBlindagem->GetXaxis()->SetTitle("Distance(cm)");
    CsTBlindagem->GetYaxis()->SetTitle("Counts (Corrected)");

    TGraphErrors* CsTMais = new TGraphErrors();
    CsTMais->SetMarkerSize(1);
    CsTMais->SetMarkerColor(kMagenta+2);
    CsTMais->SetMarkerStyle(kFullSquare);
    CsTMais->SetLineWidth(3);
    CsTMais->SetLineColor(kBlue-1);
    CsTMais->SetFillColor(2);
    CsTMais->SetFillStyle(3001);
    CsTMais->GetXaxis()->SetTitle("Distance(cm)");
    CsTMais->GetYaxis()->SetTitle("Counts (Corrected)");


//////////////CESIO SEM TAMPA///////////////////////////////////
    TGraphErrors* CssDist = new TGraphErrors();
    CssDist->SetMarkerStyle(kFullSquare);
    CssDist->SetMarkerSize(1);
    CssDist->SetMarkerColor(kGreen+2);
    CssDist->SetLineWidth(3);
    CssDist->SetLineColor(kBlue-1);
    CssDist->SetFillColor(1);
    CssDist->SetFillStyle(3004);
    CssDist->GetXaxis()->SetTitle("Distance(cm)");
    CssDist->GetYaxis()->SetTitle("Counts (Corrected)");

    TGraphErrors* CssBlindagem = new TGraphErrors();
    CssBlindagem->SetMarkerSize(1);
    CssBlindagem->SetMarkerColor(kGreen+2);
    CssBlindagem->SetMarkerStyle(kFullSquare);
    CssBlindagem->SetLineWidth(3);
    CssBlindagem->SetLineColor(kBlue-1);
    CssBlindagem->SetFillColor(1);
    CssBlindagem->SetFillStyle(3004);
    CssBlindagem->GetXaxis()->SetTitle("Distance(cm)");
    CssBlindagem->GetYaxis()->SetTitle("Counts (Corrected)");

    TGraphErrors* CssMais = new TGraphErrors();
    CssMais->SetMarkerSize(1);
    CssMais->SetMarkerColor(kGreen+2);
    CssMais->SetMarkerStyle(kFullSquare);
    CssMais->SetLineWidth(3);
    CssMais->SetLineColor(kBlue-1);
    CssMais->SetFillColor(1);
    CssMais->SetFillStyle(3004);
    CssMais->GetXaxis()->SetTitle("Distance(cm)");
    CssMais->GetYaxis()->SetTitle("Counts (Corrected)");














/////////////PONTOS//////////////////////////
    for (int i = 0; i<Nlines_distancia; ++i){
   TlGDist->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120 - );         //Distancia real = distancia + 3.7 - 2.1 + 1.2
   TlBlindagem->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);     //Radiacao real = radiacao - 0.32*120
   TlMais->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120);         //Erro horizontal (x) = 0.05cm
   TlGDist->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));                                 //Erro vertical (Radiaçao) = do histograma estatistico
   TlBlindagem->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));
   TlMais->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][1][0]))- 0.32*120));



   CsTDist->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120);
   CsTBlindagem->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120);
   CsTMais->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120);
   CsTDist->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120));
   CsTBlindagem->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120));
   CsTMais->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120));



   CssDist->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120);
   CssBlindagem->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120);
   CssMais->SetPoint(i,atof(&(distancia_data.GetData()[i][0][0]))+2.8 , atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120);
   CssDist->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120));
   CssBlindagem->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120));
   CssMais->SetPointError(i, 0.2 , 0.0109061* (atof(&(distancia_data.GetData()[i][3][0]))- 0.32*120));
    }





//////////////////////////FUNCOES A FITAR////////////////////////////////////

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




    f_inversesquarelaw->SetLineColor(kBlue+1);
    f_comblindagem->SetLineColor(kBlue+1);
    f_mais->SetLineColor(kBlue+1);

    TlGDist->Fit(f_inversesquarelaw);
    TlBlindagem->Fit(f_comblindagem);
    TlMais->Fit(f_mais);

    TCanvas* c1 = new TCanvas("","",1920,1080);





    gStyle->SetOptStat(0);
    gPad->SetGrid(1, 1);
    gStyle->SetLegendBorderSize(0);
  gStyle->SetOptFit(111);
  gStyle -> SetStatBorderSize(5);
  gStyle -> SetStatFontSize(0.2);
  gStyle -> SetStatFont(62);
  gStyle -> SetStatTextColor(1);
  gStyle -> SetStatColor(6);
  gStyle -> SetStatStyle(1);
  gStyle -> SetStatX(0.85);
  gStyle -> SetStatY(0.85);
  gStyle -> SetStatW(0.2165);

    TlGDist->SetTitle("Tl-204");
    TlGDist->Draw("AP");
    c1->SaveAs("TlDist.png");
    c1->Clear();
    c1->Update();

    TlBlindagem->SetTitle("Tl-204");
    TlBlindagem->Draw("AP");
    f_comblindagem->Draw("same");
    c1->SaveAs("TlBlindagem.png");
    c1->Clear();
    c1->Update();

    TlMais->SetTitle("Tl-204");
    TlMais->Draw("AP");
    c1->SaveAs("TlMais.png");
    c1->Clear();






    f_inversesquarelaw->SetLineColor(kGreen+2);
    f_comblindagem->SetLineColor(kGreen+2);
    f_mais->SetLineColor(kGreen+2);


    CsTDist->Fit(f_inversesquarelaw);
    CsTBlindagem->Fit(f_comblindagem);
    CsTMais->Fit(f_mais);

    CsTDist->SetTitle("Cs-137 com tampa");
    CsTDist->Draw("AP");
    c1->SaveAs("CsTDist.png");
    c1->Clear();
    c1->Update();

    CsTBlindagem->SetTitle("Cs-137 com tampa");
    CsTBlindagem->Draw("AP");
    f_comblindagem->Draw("same");
    c1->SaveAs("CsTBlindagem.png");
    c1->Clear();
    c1->Update();
    
    CsTMais->SetTitle("Cs-137 com tampa");
    CsTMais->Draw("AP");
    c1->SaveAs("CsTMais.png");
    c1->Clear();



    f_inversesquarelaw->SetLineColor(kMagenta);
    f_comblindagem->SetLineColor(kMagenta);
    f_mais->SetLineColor(kMagenta);

    CssDist->Fit(f_inversesquarelaw);
    CssBlindagem->Fit(f_comblindagem);
    CssMais->Fit(f_mais);


    CssDist->SetTitle("Cs-137 sem tampa");
    CssDist->Draw("AP");
    c1->SaveAs("CssDist.png");
    c1->Clear();
    c1->Update();

    CssBlindagem->SetTitle("Cs-137 sem tampa");
    CssBlindagem->Draw("AP");
    f_comblindagem->Draw("same");
    c1->SaveAs("CssBlindagem.png");
    c1->Clear();
    c1->Update();
    
    CssMais->SetTitle("Cs-137 sem tampa");
    CssMais->Draw("AP");
    c1->SaveAs("CssMais.png");
    c1->Clear();
        



    ///////Eficiencia/////////////////


    double radius = 3.355/2;
    double* dists = new double[7];
    double cos_theta=0;
    double* sangles = new double[7];
    for (int i=0; i<7; ++i){
        dists[i]=atof(&(distancia_data.GetData()[i][0][0]))+2.8;
    }
    for (int i=0; i<7; ++i){
        cos_theta=dists[i]/sqrt(dists[i]*dists[i]+radius*radius);
        sangles[i]=2*M_PI*(1-cos_theta);
    }

    double Cs1_EM=0.69265*3.7*1e4*120*0.94*0.5;
    double Cs2_EM=0.69265*3.7*1e4*120*(0.94*0.5+0.06);
    double Tl_EM=0.053186*3.7*1e4*120*0.971;

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
        Geff_Cs2->SetPoint(i,dists[i],atof(&(distancia_data.GetData()[i][3][0]))-0.32*120-(dists[i],atof(&(distancia_data.GetData()[i][2][0]))- 0.32*120));
    }

    auto l_eff_Tl = [&](double *x,double *p=nullptr){
      return p[0]*Tl_EM*(2*M_PI*(1-(x[0]/sqrt(x[0]*x[0]+radius*radius))))/(4*M_PI)/*exp(-0.025*x[0])*/;
    };
    TF1* f_eff_Tl= new TF1("constant", l_eff_Tl, -1e9,1e9,2);
    auto l_eff_Cs1 = [&](double *x,double *p=nullptr){
      return p[0]*Cs1_EM*(2*M_PI*(1-(x[0]/sqrt(x[0]*x[0]+radius*radius))))/(4*M_PI)/*exp(-0.025*x[0])*/;
    };
    TF1* f_eff_Cs1= new TF1("constant", l_eff_Cs1, -1e9,1e9,2);
    auto l_eff_Cs2 = [&](double *x,double *p=nullptr){
      return p[0]*Cs2_EM*(2*M_PI*(1-(x[0]/sqrt(x[0]*x[0]+radius*radius))))/(4*M_PI)/*exp(-0.025*x[0])*/;
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
