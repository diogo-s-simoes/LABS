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
    DataReader ficheiro_1("data/Tabela1_PolS_FacePlana.txt");
    DataReader ficheiro_2("data/Tabela2_PolS_FaceCurva.txt");
    DataReader ficheiro_3("data/Tabela3_PolP_FacePlana.txt");
    DataReader ficheiro_4("data/Tabela4_PolP_FaceCurva.txt");

    vector<double> ang1;
    vector<double> ang2;
    vector<double> ang3;
    vector<double> ang4;

    for(int i=0;i<ficheiro_1.GetLines();++i){
        for(int j =0;j<3;++j){
            ang1.push_back(atof(ficheiro1.GetData()[i][j]));
        }
    }
    return 0;
}