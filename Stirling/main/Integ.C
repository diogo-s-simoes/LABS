#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {

    NewReader tS("data/S(t)_corrected.txt");
    NewReader tP("data/P(t)_corrected.txt");

    vector<double> instante;

    vector <vector<double>> data;
    int Nlines = tS.GetNrInstantes();

    TGraph G;

    for(int i=0; i<Nlines; i++){
        instante.push_back(tS.GetTempo(i));
        instante.push_back(tS.GetDataVector(i));
        instante.push_back(tP.GetDataVector(i));

        data.push_back(instante);
        G.SetPoint(i,instante[0],instante[2]);
        instante.clear();
    }
    
    //for(int i=0; i<Nlines; i++){
    //    cout<<data[i][0]<<endl;
    //}

    LETintegral itg(data);

    //itg.order(1);

    //for(int i=0; i<Nlines; i++){
    //    cout<<itg.V[i][1]<<endl;
    //}

    const double dEmb=6.0;

    double Wg=itg.integrate(2,1)*M_PI*dEmb*dEmb/(4*10000);

    cout<<Wg<<endl;

    cout<<data.back()[0]-data[0][0]<<endl;

    TCanvas* c1 = new TCanvas();
    G.Draw("APL");
    c1->SaveAs("P(t).png");

    return 0;
}
