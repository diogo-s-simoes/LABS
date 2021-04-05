#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {
    const double cH2O=4200;
    const double Cv=718;
    const double R=8.3145;

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
    const double dM3=0.621e-3;

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

    double F1=0.338338;
    double F2=0.726827;
    double F3=0.941244;

    double Pff0=U0*I0;
    double Pfq1=U1*I1;
    double Pfq2=U2*I2;
    double Pfq3=U3*I3;

    double Pfq0=cH2O*dM0*(Tf0-Ti0);
    double Pff1=cH2O*dM1*(Tf1-Ti1);
    double Pff2=cH2O*dM2*(Tf2-Ti2);
    double Pff3=cH2O*dM3*(Tf3-Ti3);

    double Pwgas0=W0/Tw0;
    double Pwgas1=W1/Tw1;
    double Pwgas2=W2/Tw2;
    double Pwgas3=W3/Tw3;
    //cout<<Pwgas0<<endl;

    double Pmot0=-Pwgas0;/////////how to calculate P_atrito?/////////
    double Pmot1=2*M_PI/Tw1*lProny*F1;
    double Pmot2=2*M_PI/Tw2*lProny*F2;
    double Pmot3=2*M_PI/Tw3*lProny*F3;

    //cout<<Pwgas1<<"//"<<Pmot1<<endl;

    double Pperdas0=Pff0+Pmot0-Pfq0;
    double Pperdas1=Pfq1-Pff1-Pmot1;
    double Pperdas2=Pfq2-Pff2-Pmot2;
    double Pperdas3=Pfq3-Pff3-Pmot3;

    double Patrito1=Pwgas1-Pmot1;
    double Patrito2=Pwgas2-Pmot2;
    double Patrito3=Pwgas3-Pmot3;

    double e10=Pfq0/Pmot0;
    double n11=Pmot1/Pfq1;
    double n12=Pmot2/Pfq2;
    double n13=Pmot3/Pfq3;

    double e20=(Pfq0+Pperdas0)/(-Pwgas0);
    double n21=Pmot1/(Pmot1+Pff1);
    double n22=Pmot2/(Pmot2+Pff2);
    double n23=Pmot3/(Pmot3+Pff3);

    double n31=Pwgas1/(Pwgas1+Pff1);
    double n32=Pwgas2/(Pwgas2+Pff2);
    double n33=Pwgas3/(Pwgas3+Pff3);

    double a0=(((Ti0+Tf0)/2)/(((Ti0+Tf0)/2)-(Tres0))-e20)/(Cv/(R*log(Vmax/Vmin)));
    double a1=((1-(Ti1+Tf1)/(2*Tres1))/n31-1)/(Cv/(R*log(Vmax/Vmin))*(1-(Ti1+Tf1)/(2*Tres1)));
    double a2=((1-(Ti2+Tf2)/(2*Tres2))/n32-1)/(Cv/(R*log(Vmax/Vmin))*(1-(Ti2+Tf2)/(2*Tres2)));
    double a3=((1-(Ti3+Tf3)/(2*Tres3))/n33-1)/(Cv/(R*log(Vmax/Vmin))*(1-(Ti3+Tf3)/(2*Tres3)));

    double eca0=((Ti0+Tf0)/2)/(((Ti0+Tf0)/2)-(Tres0))-a0*Cv/(R*log(Vmax/Vmin));
    double nca1=(1-(Ti1+Tf1)/(2*Tres1))/(1+a1*Cv/(R*log(Vmax/Vmin))*(1-(Ti1+Tf1)/(2*Tres1)));
    double nca2=(1-(Ti2+Tf2)/(2*Tres2))/(1+a2*Cv/(R*log(Vmax/Vmin))*(1-(Ti2+Tf2)/(2*Tres2)));
    double nca3=(1-(Ti3+Tf3)/(2*Tres3))/(1+a3*Cv/(R*log(Vmax/Vmin))*(1-(Ti3+Tf3)/(2*Tres3)));

    double ec0=((Ti0+Tf0)/2)/(((Ti0+Tf0)/2)-(Tres0));
    double nc1=(1-(Ti1+Tf1)/(2*Tres1));
    double nc2=(1-(Ti2+Tf2)/(2*Tres2));
    double nc3=(1-(Ti3+Tf3)/(2*Tres3));

    //cout<<e10<<"<"<<e20<<"<"<<a0<<"<"<<ec0<<endl;
    //cout<<n11<<"<"<<n21<<"<"<<n31<<"<"<<a1<<"<"<<nc1<<endl;
    //cout<<n12<<"<"<<n22<<"<"<<n32<<"<"<<a2<<"<"<<nc2<<endl;
    //cout<<n13<<"<"<<n23<<"<"<<n33<<"<"<<a3<<"<"<<nc3<<endl;

    /////////////////////////////////////////Erros de alpha/////////////////////////////////////

    double cte=(Cv/(R*log(Vmax/Vmin)));
    double num=(1-(Ti1+Tf1)/(2*Tres1))/n31-1;
    double denom=(Cv/(R*log(Vmax/Vmin))*(1-(Ti1+Tf1)/(2*Tres1)));
    double pf1=( ( 1/(-2*Tres1*n31)*(1/cte)*(1-(Ti1+Tf1)/(2*Tres1)))-(num/(-cte*2*Tres1)))/(denom*denom);
    double pfT=( (Ti1+Tf1)*2*denom/(4*Tres1*Tres1*n31)-((num*(Ti1+Tf1))/(cte*2*Tres1*Tres1)))/(denom*denom);
    double pfN=(-(1-(Ti1+Tf1)/(2*Tres1))/(n31*n31))/denom;
    double deltaa=abs(pf1)*0.5/a1+abs(pf1)*0.3/a1+pfT*2/a1+0.0015*pfN/a1;
    cout<<"Maquina termica ensaio 1"<<endl;
    /*cout<<pf1<<"  "<<abs(pf1)*Ti1*0.5/a1<<"  "<<abs(pf1)*Tf1*0.5/a1<<endl;
    cout<<pfT<<"  "<<pfT*Tres1*0.5/a1<<endl;
    cout<<pfN<<"  "<<0.0015*abs(pfN)*n31/a1<<  endl;*/
    cout<<a1<<" +/- "<<abs(deltaa)*a1<<endl;

    num=(1-(Ti2+Tf2)/(2*Tres2))/n32-1;
    denom=(Cv/(R*log(Vmax/Vmin))*(1-(Ti2+Tf2)/(2*Tres2)));
    pf1=( ( 1/(-2*Tres2*n32)*(1/cte)*(1-(Ti2+Tf2)/(2*Tres2)))-(num/(-cte*2*Tres2)))/(denom*denom);
    pfT=( (Ti2+Tf2)*2*denom/(4*Tres2*Tres2*n32)-((num*(Ti2+Tf2))/(cte*2*Tres2*Tres2)))/(denom*denom);
    pfN=(-(1-(Ti2+Tf2)/(2*Tres2))/(n32*n32))/denom;
    deltaa=abs(pf1)*0.2/a2+abs(pf1)*0.1/a2+pfT*1/a2+0.002*pfN/a2;


    cout<<"Maquina termica ensaio 2"<<endl;
    cout<<a2<<" +/- "<<abs(deltaa)*a2<<endl;


    num=(1-(Ti3+Tf3)/(2*Tres3))/n33-1;
    denom=(Cv/(R*log(Vmax/Vmin))*(1-(Ti3+Tf3)/(2*Tres3)));
    pf1=( ( 1/(-2*Tres3*n33)*(1/cte)*(1-(Ti3+Tf3)/(2*Tres3)))-(num/(-cte*2*Tres3)))/(denom*denom);
    pfT=( (Ti3+Tf3)*2*denom/(4*Tres3*Tres3*n33)-((num*(Ti3+Tf3))/(cte*2*Tres3*Tres3)))/(denom*denom);
    pfN=(-(1-(Ti3+Tf3)/(2*Tres3))/(n33*n33))/denom;
    deltaa=abs(pf1)*0.3/a3+abs(pf1)*0.1/a3+pfT*1/a3+0.00086*pfN/a3;


    cout<<"Maquina termica ensaio 3"<<endl;
    cout<<a3<<" +/- "<<abs(deltaa)*a3<<endl;

    cout<<"Bomba de calor"<<endl;
    //a0=(((Ti0+Tf0)/2)/(((Ti0+Tf0)/2)-(Tres0))-e20)/(Cv/(R*log(Vmax/Vmin)));
    double xx=((Ti0+Tf0)/2)-(Tres0);
    deltaa=0.5/a0*abs(  1/cte*-Tres0/(xx*xx) )+1.5/a0*abs( 1/cte*1/(xx*xx) )+0.062/a0*abs(-1/cte);

    cout<<a0<<" +/- "<<abs(deltaa)*a0<<endl;
    

    return 0;
}