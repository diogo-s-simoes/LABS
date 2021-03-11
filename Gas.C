#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {

	NewReader ICV("ICV.txt");
	NewReader ICP("ICP.txt");
	NewReader ICT("ICT.txt");

	vector<double> instante;

	vector <vector<double>> todos;
	int Nlines = ICV.GetNrInstantes();

	for(int i=0; i<Nlines; i++){
		instante.push_back(ICV.GetTempo(i));
		instante.push_back(ICV.GetDataVector(i));
		instante.push_back(ICP.GetDataVector(i));
		instante.push_back(ICT.GetDataVector(i));

		todos.push_back(instante);
        instante.clear();
	}

    cout<<"AAAAAAA"<<endl;

    LETintegral lIC(todos);

    cout<<lIC.integrate(3,1)<<endl;
	
	  {
    TGraph PVgraphIC;

    for(int i=0;i<IC.size();i++){
      PVgraphIC.SetPoint(i,IC[i][1],IC[i][2]);
    }


    TGraph PVgraphIE;

    for(int i=0;i<IE.size();i++){
      PVgraphIE.SetPoint(i,IE[i][1],IE[i][2]);
    }


    TGraph PVgraphAC;

    for(int i=0;i<AC.size();i++){
      PVgraphAC.SetPoint(i,AC[i][1],AC[i][2]);
    }


    TGraph PVgraphAE;

    for(int i=0;i<AE.size();i++){
      PVgraphAE.SetPoint(i,AE[i][1],AE[i][2]);
    }


    PVgraphIC.Draw();
    PVgraphIE.Draw("same");
    PVgraphAC.Draw("same");
    PVgraphAE.Draw("same");

    c1->SaveAs("PVgraph.pdf");


  }

	return 0;
}
