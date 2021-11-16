#include <cmath>
#include "TGraph.h"
#include "TGraph2D.h"
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
#include "TH2D.h"

double Norm360(double x){
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}

double Norm180(double x){
    x = fmod(x + 180,360);
    if (x < 0)
        x += 360;
    return x - 180;
}

double xConv(double Da, double Db, double T0, double T9){
    double S0=sin(T0*M_PI/180.);
    double S9=sin(T9*M_PI/180.);
    double C0=cos(T0*M_PI/180.);
    double C9=cos(T9*M_PI/180.);
    return -(Da*Db*S9*(Db+Da*(S0+C0)))/(Db*Db+Da*Db*(C0+C9)+Da*Da*(-S9*S0+C0*C9));
}

double yConv(double Da, double Db, double T0, double T9){
    double S0=sin(T0*M_PI/180.);
    double S9=sin(T9*M_PI/180.);
    double C0=cos(T0*M_PI/180.);
    double C9=cos(T9*M_PI/180.);
    return (Da*Db*S0*(Db+Da*(S9+C9)))/(Db*Db+Da*Db*(C0+C9)+Da*Da*(-S9*S0+C0*C9));
}


int main(){

    double distA=15.3;
    double distB=15.3;

    DataReader dataA("data/sin_0_180.txt");
    DataReader dataB("data/sin_195_345.txt");

    double NlinesA = dataA.GetLines();
    double NlinesB = dataB.GetLines();

    TH2D* hFull = new TH2D("Full","Sinograma1",13,-32.5,32.5,24,-7.5,345+7.5);
    hFull->SetMarkerSize(2);
    hFull->SetMarkerColor(kBlue+2);
    hFull->SetMarkerStyle(kFullSquare);
    hFull->SetLineWidth(2);
    hFull->SetLineColor(kBlue-1);
    hFull->SetFillColor(1);
    hFull->SetFillStyle(3004);
    hFull->GetXaxis()->SetTitle("#theta (rad)");
    hFull->GetYaxis()->SetTitle("#phi (rad)");
    hFull->SetTitle("Sinograma Completo (#theta/#phi)");


    TH2D* hMirror = new TH2D("Mirror","Sinograma2",13,-32.5,32.5,12,-7.5,165+7.5);
    hMirror->SetMarkerSize(2);
    hMirror->SetMarkerColor(kBlue+2);
    hMirror->SetMarkerStyle(kFullSquare);
    hMirror->SetLineWidth(2);
    hMirror->SetLineColor(kBlue-1);
    hMirror->SetFillColor(1);
    hMirror->SetFillStyle(3004);
    hMirror->GetXaxis()->SetTitle("#theta (rad)");
    hMirror->GetYaxis()->SetTitle("#phi (rad)");
    hMirror->SetTitle("Sinograma Refletido (#theta/#phi)");

    TH2D* hFull_c = new TH2D("Full_Corrected","Sinograma3",24,-180-7.5,165+7.5,70,-180-2.5,165+2.5);
    hFull_c->SetMarkerSize(2);
    hFull_c->SetMarkerColor(kBlue+2);
    hFull_c->SetMarkerStyle(kFullSquare);
    hFull_c->SetLineWidth(2);
    hFull_c->SetLineColor(kBlue-1);
    hFull_c->SetFillColor(1);
    hFull_c->SetFillStyle(3004);
    hFull_c->GetXaxis()->SetTitle("#theta_{1} (rad)");
    hFull_c->GetYaxis()->SetTitle("#theta_{2} (rad)");
    hFull_c->SetTitle("Sinograma Completo (#theta_{1}/#theta_{2})");


    TH2D* hMirror_c = new TH2D("Mirror_Corrected","Sinograma4",70,-180-2.5,165+2.5,24,-180-7.5,165+7.5);
    hMirror_c->SetMarkerSize(2);
    hMirror_c->SetMarkerColor(kBlue+2);
    hMirror_c->SetMarkerStyle(kFullSquare);
    hMirror_c->SetLineWidth(2);
    hMirror_c->SetLineColor(kBlue-1);
    hMirror_c->SetFillColor(1);
    hMirror_c->SetFillStyle(3004);
    hMirror_c->GetXaxis()->SetTitle("#theta_{1} (rad)");
    hMirror_c->GetYaxis()->SetTitle("#theta_{2} (rad)");
    hMirror_c->SetTitle("Sinograma Refletido (#theta_{1}/#theta_{2})");

    //Histogramas do sinograma

    for (int i = 0; i<NlinesA; ++i){
        double phi = atof(&(dataA.GetData()[i][0][0]));
        double theta = atof(&(dataA.GetData()[i][1][0]));

        hFull->Fill(theta,phi,atof(&(dataA.GetData()[i][4][0]))/30.);
        hFull_c->Fill(Norm180(-phi),Norm180(-phi-theta),atof(&(dataA.GetData()[i][4][0]))/30.);
    }
    for (int i = 0; i<NlinesB; ++i){
        double phi = atof(&(dataB.GetData()[i][0][0]));
        double theta = atof(&(dataB.GetData()[i][1][0]));

        hFull->Fill(theta,phi,atof(&(dataB.GetData()[i][4][0]))/10.);
        hFull_c->Fill(Norm180(-phi),Norm180(-phi-theta),atof(&(dataB.GetData()[i][4][0]))/10.);
    }

    for (int i = 0; i<NlinesA-13; ++i){
        double phi = atof(&(dataA.GetData()[i][0][0]));
        double theta = atof(&(dataA.GetData()[i][1][0]));

        hMirror->Fill(theta,phi,atof(&(dataA.GetData()[i][4][0]))/30.);
        //hMirror->Fill(-theta,Norm360(phi+theta+180),atof(&(dataA.GetData()[i][4][0]))/30.);

        hMirror_c->Fill(Norm180(-phi),Norm180(-phi-theta),atof(&(dataA.GetData()[i][4][0]))/30.);
        hMirror_c->Fill(Norm180(-(phi+theta+180)),Norm180(-phi-180),atof(&(dataA.GetData()[i][4][0]))/30.);
    }

    TCanvas* c1 = new TCanvas("","",1920,1080);
    gStyle->SetOptStat(0);
    //gPad->SetGrid(1, 1);
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
    gStyle -> SetStatW(0.1365);
    gStyle->SetPalette(kRainBow);


    hFull->Draw("COL");
    c1->SaveAs("Sin_Full.png");
    c1->Clear();

    hFull_c->Draw("COL");
    c1->SaveAs("Sin_Full_C.png");
    c1->Clear();

    hMirror->Draw("COL");
    c1->SaveAs("Sin_Mirror.png");
    c1->Clear();

    hMirror_c->Draw("COL");
    c1->SaveAs("Sin_Mirror_C.png");
    c1->Clear();

    //cout dos dados para o excel

    cout<<"Theta/Phi"<<","<<0<<","<<15<<","<<30<<","<<45<<","<<60<<","<<75<<","<<90<<","<<105<<","<<120<<","<<135<<","<<150<<","<<165<<","<<180<<","<<195<<","<<210<<","<<225<<","<<240<<","<<255<<","<<270<<","<<285<<","<<300<<","<<315<<","<<330<<","<<345<<","<<endl;
    for(int i=0; i<13; ++i){
        cout<<30-5*i<<",";
        for(int j=0; j<24; ++j){
            if(j<13){
                if((j+1)%2==0)
                    cout<<atof(&(dataA.GetData()[j*13+i][4][0]))/30.<<",";
                if((j+1)%2==1)
                    cout<<atof(&(dataA.GetData()[j*13+12-i][4][0]))/30.<<",";
            }
            else{
               if((j+1)%2==0)
                    cout<<atof(&(dataB.GetData()[(j-13)*13+i][4][0]))/10.<<",";
                if((j+1)%2==1)
                    cout<<atof(&(dataB.GetData()[(j-13)*13+12-i][4][0]))/10.<<","; 
            }
        }
        cout<<endl;
    }

    //Resultado da tomografia

    DataReader dataC("data/resultF.txt");
    double NlinesC = dataC.GetLines();

    TH2D* hPET = new TH2D("TOMOGRAPHIC_RESULT","Tomografia",13,-30-2.5,30+2.5,13,-30-2.5,30+2.5);
    hPET->SetMarkerSize(2);
    hPET->SetMarkerColor(kBlue+2);
    hPET->SetMarkerStyle(kFullSquare);
    hPET->SetLineWidth(2);
    hPET->SetLineColor(kBlue-1);
    hPET->SetFillColor(1);
    hPET->SetFillStyle(3004);
    hPET->GetXaxis()->SetTitle("#theta (#phi=0#circ) [#circ]");
    hPET->GetYaxis()->SetTitle("#theta (#phi=90#circ) [#circ]");
    hPET->SetTitle("Reconstrucao Tomografica");

    TH2D* hPETxy = new TH2D("TOMOGRAPHIC_RESULT_XY","Tomografia_XY",15,-5,5,15,-5,5);
    hPETxy->SetMarkerSize(2);
    hPETxy->SetMarkerColor(kBlue+2);
    hPETxy->SetMarkerStyle(kFullSquare);
    hPETxy->SetLineWidth(2);
    hPETxy->SetLineColor(kBlue-1);
    hPETxy->SetFillColor(1);
    hPETxy->SetFillStyle(3004);
    hPETxy->GetXaxis()->SetTitle("x [cm]");
    hPETxy->GetYaxis()->SetTitle("y [cm]");
    hPETxy->SetTitle("Reconstrucao Tomografica");

    for (int i = 0; i<NlinesC; ++i){
        for (int j = 0; j<13; ++j){
            hPET->Fill(-30+j*5,-30+i*5,atof(&(dataC.GetData()[i][j][0])));
            hPETxy->Fill(-yConv(distA,distB,-30+j*5,-30+i*5),xConv(distA,distB,-30+j*5,-30+i*5),atof(&(dataC.GetData()[i][j][0])));
        }
    }

    //Este TGraph faz o overlay das posições reais das fontes
    TGraph2D* G_Aux = new TGraph2D();
    G_Aux->SetPoint(0,-2.5,0,5);
    G_Aux->SetPoint(1,1.25/2.,1.25,5);
    G_Aux->SetMarkerSize(3);
    G_Aux->SetMarkerColor(kBlack);
    G_Aux->SetMarkerStyle(kFullCircle);

    c1->SetPhi(130);
    c1->SetTheta(50);

    hPET->Draw("CONT4");
    c1->SaveAs("Tomography.png");
    c1->Clear();

    //c1->SetPhi(130);
    //c1->SetTheta(70);
    c1->SetPhi(0);
    c1->SetTheta(90);

    hPETxy->Draw("CONT4");
    G_Aux->Draw("SAMEP");
    c1->SaveAs("Tomography_xy.png");
    c1->Clear();

    return 0;
}
