#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {

    NewReader tS("data/S(t).dat");
    NewReader tP("data/P(t).dat");

    vector<double> instante;

    vector <vector<double>> data;
    int Nlines = tsP.GetNrInstantes();

    for(int i=0; i<Nlines; i++){
        instante.push_back(tS.GetTempo(i));
        instante.push_back(tS.GetDataVector(i));
        instante.push_back(tP.GetDataVector(i));

        data.push_back(instante);
        instante.clear();
    }

    LETintegral itg(data);

    double Wg=lIC.integrate(2,1);
    
    return 0;
}
