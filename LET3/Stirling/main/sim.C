#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

#include "TGraphErrors.h"
#include "TGraph2DErrors.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"
#include "TPad.h"
#include "TSystem.h"
#include "TGaxis.h"

using namespace std;

int main(){

	double gamma=1.4;
	double R=8.3144621;

	double T=0.271;
	double t=0;
	double dt=5E-9;
	double omega=2*M_PI/T;

	double vmin=140E-6;
	double vmax=278E-6;
	double thot=845.15;
	double tcold=308.40;
	double amp=0.5*(vmax-vmin)/(M_PI*0.03*0.03);
	double d=0.04908;
	double phi=0;

	double Ap=M_PI*0.03*0.03;
	
	double xd=1.5*amp; double dxd;
	cout<<xd<<"\t"<<phi<< "\t"<<d/amp<< "\t"<< d<< "\t"<<amp<<endl;

	double toll=0.165303;

	double alpha=xd+amp*(cos(omega*toll+M_PI/2)-cos(omega*toll));


	double xp=alpha+amp; double dxp;	

	
	double vc=Ap*(xp-xd); double dvc;
	double ve=Ap*xd; double dve;

	double p=2012.5+101325-6000; double dp;

	double vr=0.01*vmin; cout<<"vr"<<vr<<endl;

	double vh=vmax-(vc+ve+vr); cout<<"vh"<<vh<<endl;
	double tr=(thot-tcold)/log(thot/tcold);
	double te=(thot+tcold)/2; cout<<te<<endl;
	double tc=(thot+tcold)/2-200; cout<<tc<<endl;
	double mc=p*vc/R/tc; double dmc;
	double mr=p*vr/R/tr; double dmr;
	double me=p*ve/R/te; double dme;
	double mh=p*vh/R/thot; double dmh;
	double mhe=0;
	double M=mc+mr+me+mh;
	double the=0;

	TCanvas* c1=new TCanvas();

	TGraph* graphpv=new TGraph(100000000/10000);
    TGraph* graphts=new TGraph(100000000/10000);

	for(int i=0; i<100000000; ++i){
		if(mhe>0) the=te; else the=thot;

		dxp=-2*M_PI/T*amp*sin(2*M_PI/T*t);
		dxd=-2*M_PI/T*amp*sin(2*M_PI/T*t+M_PI/2);

		dvc=Ap*(dxp-dxd);
		dve=Ap*dxd;

		dp=-gamma*p*(dvc/tc+dve/te)/(vc/tc+gamma*vr/tr+gamma*(vh/thot)+ve/te);

		dmc=(p*dvc+vc*dp/gamma)/(R*tc);
		dmr=mr*dp/p;
		dmh=mh*dp/p;

		xp+=dxp*dt;
		xd+=dxd*dt;

		p+=dp*dt;

		mc+=dmc*dt;
		mr+=dmr*dt;
		mh+=dmh*dt;
		me=M-(mc+mr+mh);
		mhe=-dmc-dmh;

		vc+=dvc*dt;
		ve+=dve*dt;

		tc=p*vc/R/mc;
		te=p*ve/R/me;

		t+=dt;

		if(i%10000==0) graphpv->SetPoint(i/10000, vc+ve+vh+vr, p);
        if(i%10000==0) graphts->SetPoint(i/10000, M*5./2.*R*log(tc)+M*R*log(vc+ve+vh+vr), tc);

	}

    graphpv->SetLineColor(kGreen);
    graphts->SetLineColor(kOrange);
    graphpv->SetLineWidth(2);
    graphts->SetLineWidth(2);

	graphpv->Draw("AL");
	c1->SaveAs("PVsim.png");

    c1->Clear();

    graphts->Draw("AL");
    c1->SaveAs("TSsim.png");
}