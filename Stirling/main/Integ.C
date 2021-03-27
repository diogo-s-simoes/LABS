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

    TGraph GP;
    TGraph GS;

    for(int i=0; i<Nlines; i++){
        if(i<2||i>=Nlines-2){
            instante.push_back(tS.GetTempo(i));
            instante.push_back(tS.GetDataVector(i));
            instante.push_back(tP.GetDataVector(i));
        }
        else{
            instante.push_back(tS.GetTempo(i));
            instante.push_back((tS.GetDataVector(i-2)+tS.GetDataVector(i-1)+tS.GetDataVector(i)+tS.GetDataVector(i+1)+tS.GetDataVector(i+2))/5.);
            instante.push_back((tP.GetDataVector(i-2)+tP.GetDataVector(i-1)+tP.GetDataVector(i)+tP.GetDataVector(i+1)+tP.GetDataVector(i+2))/5.);
        }

        data.push_back(instante);
        GP.SetPoint(i,instante[0],instante[2]);
        GS.SetPoint(i,instante[0],instante[1]);
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

    cout<<itg.integrate(2,1)<<endl;
    cout<<Wg<<endl;

    cout<<data.back()[0]-data[0][0]<<endl;

    TCanvas* c1 = new TCanvas();
    GS.Draw("APL");
    c1->SaveAs("S(t).png");
    c1->Clear();
    GP.Draw("APL");
    c1->SaveAs("P(t).png");

    return 0;
}
