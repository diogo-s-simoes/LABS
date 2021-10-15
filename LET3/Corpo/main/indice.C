#include <cmath>

#include "NewReader.h"

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"

int main(){


/*ALFA: Angulo alfa do prisma= 60.00 graus

TETA_1: Posição angular do prisma quando a face de incidência está perpendicular ao feixe de luz incidente = 286 59`
TETA_2: Posição angular do prisma na posição usada durante as medições= 239 57`                                 
EPSILON: Posição angular do braço do detetor quando está colinear com o braço da fonte de luz =274 21` 30``

Dados contidos nos ficheiro cn01_xx...cn03_xx: 
-BETA: coluna 1-posição angular do braço do detetor em graus, 
-coluna 2-tensão fornecida pelo detetor (0.01 mv)

condições de aquisição dos ficheiros, V-tensão na lâmpada, I-corrente na lâmpada
ficheiro  V(V)  I(A)
cn_01_xx  12.42 1.734
cn_02_xx  8.42  1.417
cn_03_xx  4.997 1.091

*/
double ALPHA = 60.0*M_PI/180;
double TETA_1 = 286.983333*M_PI/180;
double TETA_2 = 239.95*M_PI/180;
double EPSILON = 274.3583333*M_PI/180;

double TETA = TETA_1 - TETA_2; //mais ou menos 47 graus





  NewReader ficheiro_1("data/cn_01_011.txt");
  NewReader ficheiro_2("data/cn_02_011.txt");
  NewReader ficheiro_3("data/cn_03_011.txt");


  vector<double> instante_1;
  vector<double> instante_2;
  vector<double> instante_3;

  vector <vector<double>> data_1;
  vector <vector<double>> data_2;
  vector <vector<double>> data_3;

  int Nlines = ficheiro_1.GetNrInstantes();


//cout << endl<<Nlines<<endl;
//INSTANTE = (BETA, TENSÃO DETETOR)

  for(int i=0; i<Nlines; i++){
    instante_1.push_back(ficheiro_1.GetTempo(i)* M_PI/180);
    instante_1.push_back(ficheiro_1.GetDataVector(i));
    data_1.push_back(instante_1);
    instante_1.clear();

    instante_2.push_back(ficheiro_2.GetTempo(i)* M_PI/180);
    instante_2.push_back(ficheiro_2.GetDataVector(i));
    data_2.push_back(instante_2);
    instante_2.clear();

    instante_3.push_back(ficheiro_3.GetTempo(i)* M_PI/180);
    instante_3.push_back(ficheiro_3.GetDataVector(i));
    data_3.push_back(instante_3);
    instante_3.clear();
    //cout << ficheiro_3.GetTempo(i) << ";   "<<ficheiro_3.GetDataVector(i)<<endl;
  }

double delta_1;
double delta_2;
double delta_3;

double V1=12.42;
double I1=1.734;
double V2=8.42;
double I2=1.417;
double V3=4.997;
double I3=1.091;


double n_1;
double n_2;
double n_3;

vector<double> indice_1;
vector<double> indice_2;
vector<double> indice_3;

for(int i=0; i<Nlines; i++){
  delta_1 = EPSILON - data_1.at(i)[0]; //JÁ ESTÁ EM RAD
  n_1 = pow(sin(TETA)*sin(TETA) + pow(sin(delta_1-TETA+ALPHA)+cos(ALPHA)*sin(TETA), 2)/(sin(ALPHA)*sin(ALPHA)), 0.5);
  indice_1.push_back(n_1);

  //cout<<data_1.at(i)[0]<<endl; //CERTO
  //cout<<delta_1<<endl; //CERTO
  //cout<<n_1<<endl; //ERRADO

  delta_2 = EPSILON - data_2.at(i)[0];
  n_2 = pow(sin(TETA)*sin(TETA) + pow(sin(delta_2-TETA+ALPHA)+cos(ALPHA)*sin(TETA), 2)/(sin(ALPHA)*sin(ALPHA)), 0.5);
  indice_2.push_back(n_2);
  //cout<<n_2<<endl; //ERRADO

  delta_3 = EPSILON - data_3.at(i)[0];
  n_3 = pow(sin(TETA)*sin(TETA) + pow(sin(delta_3-TETA+ALPHA)+cos(ALPHA)*sin(TETA), 2)/(sin(ALPHA)*sin(ALPHA)), 0.5);
  indice_3.push_back(n_3);
  cout<<n_3<<endl; //ERRADO
}

//////////////////////

    NewReader ndata("data/ntable.txt");
    NewReader Ldata("data/Ltable.txt");

    int Nlines2 = ndata.GetNrInstantes();
    
    double* nv=new double[Nlines2];
    double* Lv=new double[Nlines2];

    for(int i=0; i<Nlines2; i++){
        nv[Nlines2-1-i]=ndata.GetTempo(i);
        Lv[Nlines2-1-i]=Ldata.GetTempo(i);
    }

    Spline3Interpolator spn(Nlines2,nv,Lv);

///////////////////////////
///////////////////////////

    NewReader Rdata("data/Rtable.txt");
    NewReader Tdata("data/Ttable.txt");

    int Nlines3 = Rdata.GetNrInstantes();
    
    double* Rv=new double[Nlines3];
    double* Tv=new double[Nlines3];

    for(int i=0; i<Nlines3; i++){
        Rv[i]=Rdata.GetTempo(i)*0.4911;
        Tv[i]=Tdata.GetTempo(i);
    }

    Spline3Interpolator spt(Nlines3,Rv,Tv);

////////////////////////

TGraphErrors G1;
TGraphErrors G2;
TGraphErrors G3;

indice_1[0]=indice_1[2];
indice_1[1]=indice_1[2];
indice_2[0]=indice_1[3];
indice_2[1]=indice_1[3];
indice_2[2]=indice_1[3];

for(int i=0; i<Nlines; i++){
    G1.SetPoint(i,spn.Interpolate(indice_1[i]),data_1[i][1]);
    G2.SetPoint(i,spn.Interpolate(indice_2[i]),data_2[i][1]);
    G3.SetPoint(i,spn.Interpolate(indice_3[i]),data_3[i][1]);
    G1.SetPointError(i,0,0);
    G2.SetPointError(i,0,0);
    G3.SetPointError(i,0,0);
}

double T1= spt.Interpolate(V1/I1);
double T2= spt.Interpolate(V2/I2);
double T3= spt.Interpolate(V3/I3);

cout<<"T1= "<<T1<<endl<<"T2= "<<T2<<endl<<"T3= "<<T3<<endl;

double Lmax1=0; double Lmax2=0; double Lmax3=0;
double imax1=0; double imax2=0; double imax3=0;
double Dmax1=0; double Dmax2=0; double Dmax3=0;
for (int i=0; i<Nlines; i++){
    if(data_1[i][1]>Dmax1){
        Dmax1=data_1[i][1];
        imax1=i;
        Lmax1=G1.GetX()[i];
    }
    if(data_2[i][1]>Dmax2){
        Dmax2=data_2[i][1];
        imax2=i;
        Lmax2=G2.GetX()[i];
    }
    if(data_3[i][1]>Dmax3){
        Dmax3=data_3[i][1];
        imax3=i;
        Lmax3=G3.GetX()[i];
    }
}

double h=6.62607015e-34;
double c=299792458;
double k=1.380649e-23;

auto lPlanck = [&](double *x,double *p=nullptr){
    return (2*M_PI*h*c*c/pow(x[0]*1e-9,5)/(exp(h*c/(k*x[0]*1e-9*p[0]))-1))/p[1];
};

double omega=2.8977729e-3;

TF1* fPlanck = new TF1("Lei de Planck", lPlanck, 0.,10000,2);
fPlanck->SetLineColor(kOrange);
fPlanck->SetParameter(1,1.);
fPlanck->SetParameter(0,T1);
double Lwien1=omega/T1;
double Lwien2=omega/T2;
double Lwien3=omega/T3;
double Pmax1=fPlanck->Eval(omega/T1*1e9);
fPlanck->SetParameter(0,T2);
double Pmax2=fPlanck->Eval(omega/T2*1e9);
fPlanck->SetParameter(0,T3);
double Pmax3=fPlanck->Eval(omega/T3*1e9);

TCanvas* c1 = new TCanvas();
G1.SetMarkerSize(0.5);
G1.SetMarkerStyle(16);
G1.SetMarkerColor(kRed);
G1.SetLineWidth(2);
G1.SetLineColor(kRed);

G2.SetMarkerSize(0.5);
G2.SetMarkerStyle(16);
G2.SetMarkerColor(kGreen);
G2.SetLineWidth(2);
G2.SetLineColor(kGreen);

G3.SetMarkerSize(0.5);
G3.SetMarkerStyle(16);
G3.SetMarkerColor(kBlue);
G3.SetLineWidth(2);
G3.SetLineColor(kBlue);

TAxis *g3ax = G3.GetXaxis();
TAxis *g3ay = G3.GetYaxis();
g3ax->SetTitle("#lambda (nm)");
g3ay->SetTitle("I (mV)");
TAxis *g2ax = G2.GetXaxis();
TAxis *g2ay = G2.GetYaxis();
g2ax->SetTitle("#lambda (nm)");
g2ay->SetTitle("I (mV)");
TAxis *g1ax = G1.GetXaxis();
TAxis *g1ay = G1.GetYaxis();
g1ax->SetTitle("#lambda (nm)");
g1ay->SetTitle("I (mV)");
G1.Draw("AL");
G2.Draw("SAME");
G3.Draw("SAME");

auto legend1 = new TLegend(0.45,0.73,0.9,0.9);
    legend1->SetTextFont(62);
    legend1->SetTextSize(0.05);
    legend1->AddEntry(&G1,"Ensaio 1 (T=2416.76K)","l");
    legend1->AddEntry(&G2,"Ensaio 2 (T=2104.32K)","l");
    legend1->AddEntry(&G3,"Ensaio 3 (T=1724.58K)","l");
    legend1->Draw("same");
c1->SaveAs("nco.png");
c1->Clear();
spn.Draw();
c1->SaveAs("n_L_interpolate.png");
c1->Clear();


for(int i=0; i<Nlines; i++){
    G1.SetPoint(i,spn.Interpolate(indice_1[i]),data_1[i][1]/Dmax1);
    G2.SetPoint(i,spn.Interpolate(indice_2[i]),data_2[i][1]/Dmax2);
    G3.SetPoint(i,spn.Interpolate(indice_3[i]),data_3[i][1]/Dmax3);
}

TAxis *pax = fPlanck->GetXaxis();
TAxis *pay = fPlanck->GetYaxis();
pax->SetTitle("#lambda (nm)");
pay->SetTitle("I (normalizado)");

fPlanck->SetParameter(0,T1);
fPlanck->SetParameter(1,Pmax1);
fPlanck->Draw("");
fPlanck->GetHistogram()->GetYaxis()->SetTitle("I (normalizado)");
fPlanck->GetHistogram()->GetXaxis()->SetTitle("#lambda (nm)");
G1.Draw("SAMEL");
c1->Modified();
auto legend2 = new TLegend(0.45,0.7,0.9,0.9);
    legend2->SetTextFont(62);
    legend2->SetTextSize(0.06);
    legend2->AddEntry(&G1,"Ensaio 1","l");
    legend2->AddEntry(fPlanck,"Lei de Planck","l");
    legend2->AddEntry("temp","T=2416.76K","");
    legend2->Draw("same");
c1->SaveAs("Planck1.png");
c1->Clear();

fPlanck->SetParameter(0,T2);
fPlanck->SetParameter(1,Pmax2);
fPlanck->Draw("");
fPlanck->GetHistogram()->GetYaxis()->SetTitle("I (normalizado)");
fPlanck->GetHistogram()->GetXaxis()->SetTitle("#lambda (nm)");
G2.Draw("SAMEL");
c1->Modified();
auto legend3 = new TLegend(0.45,0.7,0.9,0.9);
    legend3->SetTextFont(62);
    legend3->SetTextSize(0.06);
    legend3->AddEntry(&G2,"Ensaio 2","l");
    legend3->AddEntry(fPlanck,"Lei de Planck","l");
    legend3->AddEntry("temp","T=2104.32K","");
    legend3->Draw("same");
c1->SaveAs("Planck2.png");
c1->Clear();

fPlanck->SetParameter(0,T3);
fPlanck->SetParameter(1,Pmax3);
fPlanck->Draw("");
fPlanck->GetHistogram()->GetYaxis()->SetTitle("I (normalizado)");
fPlanck->GetHistogram()->GetXaxis()->SetTitle("#lambda (nm)");
G3.Draw("SAMEL");
c1->Modified();
auto legend4 = new TLegend(0.45,0.7,0.9,0.9);
    legend4->SetTextFont(62);
    legend4->SetTextSize(0.06);
    legend4->AddEntry(&G3,"Ensaio 3","l");
    legend4->AddEntry(fPlanck,"Lei de Planck","l");
    legend4->AddEntry("temp","T=1724.58K","");
    legend4->Draw("same");
c1->SaveAs("Planck3.png");
c1->Clear();

TGraphErrors GWien;
GWien.SetPoint(0,T1,Lmax1*1e-9);
GWien.SetPoint(1,T2,Lmax2*1e-9);
GWien.SetPoint(2,T3,Lmax3*1e-9);
GWien.SetPointError(0,1,1e-9*0.5*(spn.Interpolate(indice_1[imax1+1])-spn.Interpolate(indice_1[imax1-1])));
GWien.SetPointError(1,1,1e-9*0.5*(spn.Interpolate(indice_2[imax2+1])-spn.Interpolate(indice_2[imax2-1])));
GWien.SetPointError(2,1,1e-9*0.5*(spn.Interpolate(indice_3[imax3+1])-spn.Interpolate(indice_3[imax3-1])));

auto lFit = [&](double *x,double *p=nullptr){
    return p[0]/x[0]+p[1];
};
TF1* fFit = new TF1("FIT", lFit, -10000,10000,1);

fFit->SetParameter(0,0);
//fFit->SetParameter(1,-100000);

GWien.Fit(fFit);

TAxis *wax = GWien.GetXaxis();
TAxis *way = GWien.GetYaxis();
wax->SetTitle("T (K)");
way->SetTitle("#lambda (m)");
GWien.SetMarkerColor(kBlue);
GWien.SetMarkerStyle(16);
GWien.Draw("AP");
fFit->Draw("SAME");
auto legend5 = new TLegend(0.55,0.7,0.9,0.9);
    legend5->SetTextFont(62);
    legend5->SetTextSize(0.06);
    legend5->AddEntry(fFit,"#lambda_{max} = #omega/T","l");
    legend5->AddEntry("temp","#omega=2.493","");
    legend5->Draw("same");
c1->SaveAs("Wien.png");
c1->Clear();
}