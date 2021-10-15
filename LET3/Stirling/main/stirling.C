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

#define XCANVAS 1800
#define YCANVAS 1200

#define vol_max 278E-6
#define vol_min 140E-6

using namespace std;


int main()
{

	/////////////////////////////////////////////////////////

	double gamma=1.4;
	double R=8.3144621;

	double T=0.268;
	double t=0;
	double dt=5E-9;
	double omega=2*M_PI/T;

	double vmin=140E-6;
	double vmax=278E-6;
	double thot=825.15;
	double tcold=306.60;
	double amp=0.5*(vmax-vmin)/(M_PI*pow(3E-2,2));
	double d=0.04908;
	double phi=acos(1);

	double Ap=M_PI*pow(3E-2, 2);

	//double xp=(vmax+vmin)/2/Ap+amp; double dxp;
	
	double xd=1.5*amp; double dxd; //UMESH AQUI (>= amp)
	cout<<xd<<"\t"<<phi<< "\t"<<d/amp<< "\t"<< d<< "\t"<<amp<<endl;

	//double vh=111E-6-amp*Ap;
	double toll=0.165303;

	double alpha=xd+amp*(cos(omega*toll+M_PI/2)-cos(omega*toll));


	double xp=alpha+amp; double dxp;	

	
	double vc=Ap*(xp-xd); double dvc;
	double ve=Ap*xd; double dve;

	double p=2012.5+101325-6000; double dp;
	//double tck;
	//double the;
	double vr=0.01*vmin; cout<<"vr"<<vr<<endl; //UMESH AQUI

	double vh=vmax-(vc+ve+vr); cout<<"vh"<<vh<<endl;
	double tr=(thot-tcold)/log(thot/tcold);
	double te=(thot+tcold)/2; cout<<te<<endl; //UMESH AQUI
	double tc=(thot+tcold)/2-200; cout<<tc<<endl; //UMESH AQUI
	double mc=p*vc/R/tc; double dmc;
	double mr=p*vr/R/tr; double dmr;
	double me=p*ve/R/te; double dme;
	double mh=p*vh/R/thot; double dmh;
	double mhe=0;
	double M=mc+mr+me+mh;
	double the=0;
	
	TCanvas* c=new TCanvas("", "", 0, 0, XCANVAS, YCANVAS);
	TCanvas* c1=new TCanvas();
	TCanvas* c2=new TCanvas();

	TMultiGraph* banana= new TMultiGraph();

	TGraph* graph=new TGraph(100000000/10000);
	TGraph* graph1=new TGraph(100000000/10000);
	TGraph* graph2=new TGraph(100000000/10000);

	cout<<"meme"<<":\t"<<vc<<"\t"<<ve<<"\t"<<vr<< "\t"<<p<<endl;
	
	double vbabe=vmax;

	for(int i=0; i<100000000; ++i)
	{
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

		if(i%10000==0) graph->SetPoint(i/10000, vc+ve+vh+vr, p);
		if(i%10000==0) graph1->SetPoint(i/1000, t, vc+ve+vh+vr);
		//if(i%1000==0) graph2->SetPoint(i/1000, t, ve);

		if(vh+vc+ve+vr<vbabe)vbabe=vh+vc+ve+vr;

		//if(i%1000000==0)cout<<i<<":\t"<<vc+ve+vh+vr<< "\t"<<vc<< "\t"<<vr<< "\t"<<ve<< "\t"<<endl;

		//if(t>T) break;

	}

	cout<<"babe"<<vbabe<<endl;

	c->cd();
	banana->Add(graph);

	banana->Draw("ACP");


	c1->cd();
	graph1->Draw("AP");
	//c2->cd();
	//graph2->Draw("ACP");
	c->SaveAs("g.png");
	c1->SaveAs("g1.png");
	//c2->SaveAs("g2.png");


}