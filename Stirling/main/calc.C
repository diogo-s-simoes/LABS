#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {
    const double Vmin=140e-6;
    const double Vmax=278e-6;
    const double lProny=0.247;
    const double dEmb=6.0e-2;
    const double rEmb=3.0;

    const double U0=3.632;
    const double I0=3.158;
    const double dM0=0.559e-3;

    const double U1=14.32;	
    const double I1=12.6;
    const double dM1=0.595e-3;

    const double U2=16.00;
    const double I2=14.3;
    const double dM2=0.626e-3;

    const double U3=17.59;
    const double I3=15.6;
    const double dM3=0.621;

    const double Tres0=287.9;
    const double Ti0=294.3;
    const double Tf0=301.2;

    const double Tres1=452+273.15;
    const double Ti1=21.8+273.15;
    const double Tf1=40.5+273.15;

    const double Tres2=542+273.15;	
    const double Ti2=23.2+273.15;
    const double Tf2=40.0+273.15;

    const double Tres3=572+273.15;
    const double Ti3=25.0+273.15;
    const double Tf3=45.5+-0.1+273.15;

    const double W0=-870*M_PI*rEmb*rEmb/10000;
    const double Tw0=0.445;

    const double W1=902*M_PI*rEmb*rEmb/10000;	
    const double Tw1=0.342;
    const double Uf1=0.0445;

    const double W2=1068*M_PI*rEmb*rEmb/10000;
    const double Tw2=0.313;
    const double Uf2=0.0965;

    const double W3=5.09983;		
    const double Tw3=0.271;
    const double Uf3=0.1252;

    cout<<W0<<endl<<W1<<endl<<W2<<endl<<W3<<endl;
    return 0;
}