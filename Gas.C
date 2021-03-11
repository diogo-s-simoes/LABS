
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {

	NewReader ICV("ICV.txt");
	NewReader ICP("ICP.txt");
	NewReader ICT("ICT.txt");

    NewReader IEV("IEV.txt");
	NewReader IEP("IEP.txt");
	NewReader IET("IET.txt");

    NewReader ACV("ACV.txt");
	NewReader ACP("ACP.txt");
	NewReader ACT("ACT.txt");

    NewReader AEV("AEV.txt");
	NewReader AEP("AEP.txt");
	NewReader AET("AET.txt");

	vector<double> instante;

	vector <vector<double>> vIC;
	int Nlines = ICV.GetNrInstantes();

	for(int i=0; i<Nlines; i++){
		instante.push_back(ICV.GetTempo(i));
		instante.push_back(ICV.GetDataVector(i));
		instante.push_back(ICP.GetDataVector(i));
		instante.push_back(ICT.GetDataVector(i));

		vIC.push_back(instante);
        instante.clear();
	}

    vector <vector<double>> vIE;
	Nlines = ICV.GetNrInstantes();

	for(int i=0; i<Nlines; i++){
		instante.push_back(IEV.GetTempo(i));
		instante.push_back(IEV.GetDataVector(i));
		instante.push_back(IEP.GetDataVector(i));
		instante.push_back(IET.GetDataVector(i));

		vIE.push_back(instante);
        instante.clear();
	}

    vector <vector<double>> vAC;
	Nlines = ICV.GetNrInstantes();

	for(int i=0; i<Nlines; i++){
		instante.push_back(ACV.GetTempo(i));
		instante.push_back(ACV.GetDataVector(i));
		instante.push_back(ACP.GetDataVector(i));
		instante.push_back(ACT.GetDataVector(i));

		vAC.push_back(instante);
        instante.clear();
	}

    vector <vector<double>> vAE;
	Nlines = ICV.GetNrInstantes();

	for(int i=0; i<Nlines; i++){
		instante.push_back(AEV.GetTempo(i));
		instante.push_back(AEV.GetDataVector(i));
		instante.push_back(AEP.GetDataVector(i));
		instante.push_back(AET.GetDataVector(i));

		vAE.push_back(instante);
        instante.clear();
	}

    cout<<"AAAAAAA"<<endl;

    LETintegral lIC(vIC);
    LETintegral lIE(vIE);
    LETintegral lAC(vAC);
    LETintegral lAE(vAE);

    double Wic=lIC.integrate(2,1);
    double Wie=lIE.integrate(2,1);
    double Wac=lAC.integrate(2,1);
    double Wae=lAE.integrate(2,1);
	
	  {
    TGraph PVgraphIC;

    for(int i=0;i<vIC.size();i++){
      PVgraphIC.SetPoint(i,vIC[i][1],vIC[i][2]);
    }


    TGraph PVgraphIE;

    for(int i=0;i<vIE.size();i++){
      PVgraphIE.SetPoint(i,vIE[i][1],vIE[i][2]);
    }


    TGraph PVgraphAC;

    for(int i=0;i<vAC.size();i++){
      PVgraphAC.SetPoint(i,vAC[i][1],vAC[i][2]);
    }


    TGraph PVgraphAE;

    for(int i=0;i<vAE.size();i++){
      PVgraphAE.SetPoint(i,vAE[i][1],vAE[i][2]);
    }

    TCanvas* c1 = new TCanvas();
  
    auto lIdealGas = [](double *x,double *p=nullptr){
      return p[0]*pow(x[0],p[1]);//p[1] * pow(x[0],p[0]);
    };

    TF1* fIdealGas= new TF1("L", lIdealGas, 1.,500.,2);

    fIdealGas->SetParameter(0,10000);



    TAxis *ax_t = PVgraphIC.GetXaxis();
    TAxis *ay_t = PVgraphIC.GetYaxis();

    ax_t->SetLimits(80,220);
    ay_t->SetRangeUser(30,250);

    ax_t->SetTitle("V(m^3)");
    ay_t->SetTitle("P(Pa)");

    PVgraphIC.SetTitle("Compressao Isotermica");
    PVgraphIC.SetMarkerColor(kGreen-2);
    PVgraphIC.SetLineColor(kGreen-2);
    PVgraphIC.SetMarkerSize(.5);
    PVgraphIC.SetMarkerStyle(8);

    fIdealGas->SetLineColor(kGreen-2);
    PVgraphIC.Fit(fIdealGas);
    PVgraphIC.Draw("AP");


    PVgraphIE.SetTitle("Expansao Isotermica");
    PVgraphIE.SetMarkerColor(kRed-2);
    PVgraphIE.SetLineColor(kRed-2);
    PVgraphIE.SetMarkerSize(.5);
    PVgraphIE.SetMarkerStyle(8);

    fIdealGas->SetLineColor(kRed-2);
    PVgraphIE.Fit(fIdealGas);
    PVgraphIE.Draw("P same");
    


    PVgraphAC.SetTitle("Compressao Adiabatica");
    PVgraphAC.SetMarkerColor(kBlue-2);
    PVgraphAC.SetLineColor(kBlue-2);
    PVgraphAC.SetMarkerSize(.5);
    PVgraphAC.SetMarkerStyle(8);

    fIdealGas->SetLineColor(kBlue-2);
    PVgraphAC.Fit(fIdealGas);
    PVgraphAC.Draw("P same");
    


    PVgraphAE.SetTitle("Expansao Adiabatica");
    PVgraphAE.SetMarkerColor(94);
    PVgraphAE.SetLineColor(94);
    PVgraphAE.SetMarkerSize(.5);
    PVgraphAE.SetMarkerStyle(8);

    fIdealGas->SetLineColor(94);
    PVgraphAE.Fit(fIdealGas);
    PVgraphAE.Draw("P same");

    c1->BuildLegend(.75,.75,.9,.9);

    c1->SaveAs("PVgraph.pdf");
  }

	return 0;
}
