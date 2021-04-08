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


  NewReader ficheiro_1("data/cn_01_011.dat");
  NewReader ficheiro_2("data/cn_02_011.dat");
  NewReader ficheiro_3("data/cn_03_011.dat");


  vector<double> instante_1;
  vector<double> instante_2;
  vector<double> instante_3;

  vector <vector<double>> dados_1;
  vector <vector<double>> dados_2;
  vector <vector<double>> dados_3;

  int Nlines = ficheiro_1.GetNrInstantes();



//INSTANTE = (BETA, TENSÃO DETETOR)

  for(int i=0; i<Nlines; i++){
    instante_1.push_back(ficheiro_1.GetTempo(i));
    instante_1.push_back(ficheiro_1.GetDataVector(i));
    data_1.push_back(instante);
    instante_1.clear();

    instante_2.push_back(ficheiro_2.GetTempo(i));
    instante_2.push_back(ficheiro_2.GetDataVector(i));
    data_2.push_back(instante);
    instante_2.clear();

    instante_3.push_back(ficheiro_3.GetTempo(i));
    instante_3.push_back(ficheiro_3.GetDataVector(i));
    data_3.push_back(instante);
    instante_3.clear();

    cout<<instante_3(3)<<endl;
  }
