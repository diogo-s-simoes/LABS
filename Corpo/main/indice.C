#include <cmath>

#include "NewReader.h"

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"

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

/////////////////

//cout << endl<<Nn<<endl;

  NewReader f_n_prisma("data/n_prisma.txt");
  NewReader f__comp_onda("data/comp_onda.txt");

  vector<double> n_prisma;
  vector<double> comp_onda;
TGraph G0;
  //INSTANTE = (NPRISMA, COMPRIMENTO ONDA)
  int Nn = ficheiro_1.GetNrInstantes();
  for(int i=0; i<Nn; i++){
    n_prisma.push_back(f_n_prisma.GetTempo(i));
    comp_onda.push_back(f__comp_onda.GetTempo(i));
    G0.SetPoint(i,n_prisma.at(i), comp_onda.at(i));
  }

cout << endl<<"OLA"<<endl;

    auto lCal = [](double *x,double *p=nullptr){
      return p[0]*x[0]+p[1];
    };

    TF1* fCal= new TF1("L", lCal, 1.,500.,2);

    fCal->SetParameter(0,0.1);
    fCal->SetParameter(1,0);

    G0.Fit(fCal);







cout << endl<<Nn<<endl;

///////////////////////////7

TGraph G1;
TGraph G2;
TGraph G3;

for(int i=0; i<Nlines; i++){
    G1.SetPoint(i,indice_1[i],data_1[i][1]);
    G2.SetPoint(i,indice_2[i],data_2[i][1]);
    G3.SetPoint(i,indice_3[i],data_3[i][1]);
}

TCanvas* c1 = new TCanvas();
G1.SetMarkerSize(0.5);
G1.SetMarkerStyle(16);
G1.SetMarkerColor(kBlue);
G1.SetLineWidth(2);
G1.SetLineColor(kRed);

G2.SetMarkerSize(0.5);
G2.SetMarkerStyle(16);
G2.SetMarkerColor(kBlue);
G2.SetLineWidth(2);
G2.SetLineColor(kGreen);

G3.SetMarkerSize(0.5);
G3.SetMarkerStyle(16);
G3.SetMarkerColor(kBlue);
G3.SetLineWidth(2);
G3.SetLineColor(kBlue);

TAxis *ax = G3.GetXaxis();
TAxis *ay = G3.GetYaxis();
ax->SetTitle("n");
ay->SetTitle("I (mV)");
//G3.Draw("AL");
//G2.Draw("SAME");
//G1.Draw("SAME");
G0.Draw("AL");
c1->SaveAs("nco.png");

}