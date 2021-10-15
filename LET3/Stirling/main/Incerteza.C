#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

int main()  {

  NewReader tS("data/S(t)_corrected.txt");
  NewReader tP("data/P(t)_corrected.txt");

  vector<double> instante;

  vector <vector<double>> data;
  int Nlines = tS.GetNrInstantes();

  TGraph G;

  for(int i=0; i<Nlines; i++){
    instante.push_back(tS.GetTempo(i));
    instante.push_back(tS.GetDataVector(i));
    instante.push_back(tP.GetDataVector(i));

    data.push_back(instante);
    G.SetPoint(i,instante[0],instante[2]);
    instante.clear();
  }



    {
      TCanvas *c1= new TCanvas;


      auto lLine = [](double *x,double *p=nullptr){
        return p[0]*x[0]+p[1];
      };

      TF1* fLine= new TF1("PAIN", lLine, 1.,500.,2);



      int n=1;
      double chi2=0.;

      int Len=10;

      for(int i=0;i<data.size()-Len;i+=Len){
        n++;
        TGraph support;

        for(int j=0;j<Len;j++)
          support.SetPoint(j,data[i+j][0],data[i+j][1]);

        support.Fit(fLine);
        
        chi2+=fLine->GetChisquare();

      }

      chi2/=n*Len;

      cout<<"Deslocamento Chi2 = "<<chi2<<endl;
    }



{
      TCanvas *c1= new TCanvas;


      auto lLine = [](double *x,double *p=nullptr){
        return p[0]*x[0]+p[1];
      };

      TF1* fLine= new TF1("PAIN", lLine, 1.,500.,2);



      int n=1;
      double chi2=0.;

      int Len=5;

      for(int i=0;i<data.size()-Len;i+=Len){
        n++;
        TGraph support;

        for(int j=0;j<Len;j++)
          support.SetPoint(j,data[i+j][0],data[i+j][2]);

        support.Fit(fLine);
        
        chi2+=fLine->GetChisquare();

      }

      chi2/=n*Len;

      cout<<"Pressão Chi2 = "<<chi2<<endl;
    }




  return 0;
}
