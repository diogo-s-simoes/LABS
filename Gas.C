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

	return 0;
}