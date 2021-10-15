#include <cmath>

#include "NewReader.h"

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TAxis.h"

int main(){

  NewReader tS("data/S(t)_corrected.txt");
  NewReader tP("data/P(t)_corrected.txt");

  vector<double> instante;

  vector <vector<double>> data;
  int Nlines = tS.GetNrInstantes();

  TGraph G;

  for(int i=0; i<Nlines; i++){
    instante.push_back(tS.GetTempo(i));
    instante.push_back(tS.GetDataVector(i));
    instante.push_back(tP.GetDataVector(i)*100+1);

    data.push_back(instante);
    G.SetPoint(i,instante[0],instante[2]);
    instante.clear();
  }


  double R = 8.3145;
  double Area = M_PI*9.*1e-4;
  double Smin = 0.8708e-04;
  double Smax = 0.4937e-01;
  double Pmin = 0.8752e+03;
  double Pmax = 0.9835e+05;
  double Patm = 101425.;
  double Tmax = 845.15;
  double Tmin = 308.4;


  Area=138./(Smax-Smin)*1e-6;



  //  double Vmax =  (Smax-Smin)*Area*(Patm+Pmax)/((Patm+Pmax)-(Patm+Pmin)*Tmax/Tmin);

  double Vmax = 278.*1e-6;
  double Vmin = 140.*1e-6;


  double n1 = Vmax*(Patm+Pmin)/(Tmin*R);
  double n2 = Vmin*(Patm+Pmax)/(Tmax*R);

  cout<<Vmax<<"   "<<(n1+n2)/2.<<" \\pm "<<(n1-n2)/2.<<endl;


  double n = (n1+n2)/2.;

cout<<(Smax-Smin)*Area<<endl;

  vector<vector<double>> VPTS;

  for(int i=0; i<data.size(); i++){
    vector<double> temp;

    temp.push_back(Vmax - (Smax-data[i][1]*.01)*Area);
    temp.push_back(Patm+data[i][2]);
    temp.push_back(temp[0]*temp[1]/(n*R));
    temp.push_back(n*5./2.*R*log(temp[2])+n*R*log(temp[0]));
    temp.push_back(n*7./2.*R*log(temp[1]*pow(temp[0],7./5.)));
    temp.push_back(n*7./2.*R*log(temp[2])+n*R*log(temp[1]));
    //cout<<temp[1]<<endl;
    VPTS.push_back(temp);

  }



  TGraph PV,TS,TS2;
  double Saverage=0;

  for(int i=0;i<VPTS.size();i++){
    PV.SetPoint(i,VPTS[i][0],VPTS[i][1]);
    TS.SetPoint(i,VPTS[i][3], VPTS[i][2]);
    Saverage+=VPTS[i][3];
    TS2.SetPoint(i,VPTS[i][2],VPTS[i][4]);
  }
  Saverage/=VPTS.size();

  TCanvas *c1=new TCanvas();

    TAxis *ax_t = PV.GetXaxis();
    TAxis *ay_t = PV.GetYaxis();

    ay_t->SetTitle("P(Pa)");
    ax_t->SetTitle("V(m^{3})");
    
    
  PV.SetLineWidth(2);
  PV.SetLineColor(kRed);
  PV.Draw("AL");
  

  c1->SaveAs("PVgraph.png");
  c1->Clear();





    TAxis *ax2 = TS.GetXaxis();
    TAxis *ay2 = TS.GetYaxis();

    ax2->SetTitle("S(J/K)");
    ay2->SetTitle("T(K)");
    
  TS.SetLineWidth(2);
  TS.SetLineColor(kBlue);
  TS.Draw("AL");
  //TS2.Draw("AL");
  c1->SaveAs("TSgraph.png");
  c1->Clear();

    //////////////////////////////////////////////////////////7777


    double gamma=1.4;
	R=8.3144621;

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

	double Ap=M_PI*pow(3E-2, 2);
	
	double xd=1.5*amp; double dxd;

	double toll=0.165303;

	double alpha=xd+amp*(cos(omega*toll+M_PI/2)-cos(omega*toll));


	double xp=alpha+1.5*amp; double dxp;	

	
	double vc=Ap*(xp-xd); double dvc;
	double ve=Ap*xd; double dve;

	double p=101325; double dp;

	double vr=2*vmin; cout<<"vr"<<vr<<endl;

    //double vk=(vmax-(vc+ve+vr))/2;
	double vh=(vmax-(vc+ve+vr)); cout<<"vh"<<vh<<endl;
	double tr=(thot-tcold)/log(thot/tcold);
	double te=570; cout<<te<<endl;
	double tc=380; cout<<tc<<endl;
	double mc=p*vc/R/tc; double dmc;
	double mr=p*vr/R/tr; double dmr;
	double me=p*ve/R/te; double dme;
	double mh=p*vh/R/thot; double dmh;
	double mhe=0;
	double M=mc+mr+me+mh;
	double the=0;

    cout<<"M= "<<M<<endl;

	//TCanvas* c1=new TCanvas();

	TGraph* graphpv=new TGraph();
    TGraph* graphts=new TGraph();

    double W=0;
    double Pfq=0;
    double Pff=0;

	for(int i=0; i<100000000; ++i){
		if(mhe>0) the=te; else the=thot;

		dxp=-2*M_PI/T*amp*sin(2*M_PI/T*t);
		dxd=-2*M_PI/T*amp*sin(2*M_PI/T*t+M_PI/2);

		dvc=Ap*(dxp-dxd);
		dve=Ap*dxd;

		dp=-gamma*p*(dvc/tc+dve/te)/(vc/tc+gamma*vr/tr+gamma*(vh/(thot))+ve/te);

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
        if(i%10000==0) graphts->SetPoint(i/10000, M*5./2.*R*log(p*(vc+ve+vh+vr)/((mc+me+mh+mr)*R))+M*R*log(vc+ve+vh+vr)+Saverage-0.5, p*(vc+ve+vh+vr)/((mc+me+mh+mr)*R));
        if(t>T) break;

        W+=p*(dve+dvc)*dt;
	}

    graphpv->SetLineColor(kGreen);
    graphts->SetLineColor(kOrange);
    graphpv->SetLineWidth(2);
    graphts->SetLineWidth(2);
    TAxis* xaxis = graphpv->GetXaxis();
    TAxis* yaxis = graphpv->GetYaxis();
    xaxis->SetTitle("V (m^3)");
    yaxis->SetTitle("p (Pa)");

	graphpv->Draw("AL");
    PV.Draw("SAME");
	c1->SaveAs("PVsim.png");

    c1->Clear();

    graphts->Draw("AL");
    TS.Draw("SAME");
    c1->SaveAs("TSsim.png");

    cout<<W<<endl;



}




//Smin 0.8708e-04 m          Pmax 0.9835e+05 Pa


//Smax 0.4937e-01 m          Pmin 0.8752e+03 Pa