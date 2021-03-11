
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

    cout<<lIC.integrate(3,1)<<endl;
	
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


    PVgraphIC.Draw();
    PVgraphIE.Draw("same");
    PVgraphAC.Draw("same");
    PVgraphAE.Draw("same");

    c1->SaveAs("PVgraph.pdf");


  }

	return 0;
}