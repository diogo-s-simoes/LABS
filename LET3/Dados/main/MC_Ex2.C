#include "Integrator.h"

#include <iostream>
#include <vector>
#include <iomanip>

#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"

using namespace std;

int main(){


  //declarar função integranda
  auto f = [](double *x,double *p=nullptr){
    return sqrt(1.+(1.-x[0]/4.)*(1.-x[0]/4.)*exp(-x[0]/2.));
  };

  TF1* L= new TF1("L", f, 0.,15.,0.);

  Integrator Qn(0.,15.,L);



  vector<double> QL15;

  int nmax=13;

  //Calcular valor do integral pela quadratura composta de Gauss para n 10,20,40,...,10*2^13
  for(int n=0;n<=nmax;n++){
    QL15.push_back(Qn.GaussQuadrature(pow(2,n)*10));
  }



  //apresentação dos resultados de 10*2^n, n de 0 a 12
  cout<<"Quadratura de Gauss Composta"<<endl;
  cout<<"n ; Q_n ; Q(2n)-Qn ; (Q(2n)-Q_n)/(Qn-Q(n/2))"<<endl;
  cout<<setprecision(15)<<"10 &"<<QL15.at(0)<<" & "<<fabs(QL15.at(1)-QL15.at(0))<<" & NA"<<endl;

  for(int n=1;n<nmax;n++){
    cout<<setprecision(15)<<pow(2,n)*10<<" & "<<QL15.at(n)<<" & "<<fabs(QL15.at(n+1)-QL15.at(n))<<" & "<<fabs((QL15.at(n+1)-QL15.at(n))/(QL15.at(n)-QL15.at(n-1)))<<endl;
  }

  QL15.clear();






  //Calcular valor do integral pelo metodo composto de Simpson para n 10,20,40,...,10*2^13
  for(int n=0;n<=nmax;n++){
    double integ;
    Qn.Simpson(pow(2,n)*10,integ);
    QL15.push_back(integ);
  }


  //apresentação dos resultados de 10*2^n, n de 0 a 12
  cout<<endl<<endl<<endl<<endl;
  cout<<"Metodo de Simpson Composto"<<endl;
  cout<<"n ; Q_n ; Q(2n)-Qn ; (Q(2n)-Q_n)/(Qn-Q(n/2))"<<endl;
  cout<<setprecision(15)<<"10 &"<<QL15.at(0)<<" & "<<fabs(QL15.at(1)-QL15.at(0))<<" & NA"<<endl;

  for(int n=1;n<nmax;n++){
    cout<<setprecision(15)<<pow(2,n)*10<<" & "<<QL15.at(n)<<" & "<<fabs(QL15.at(n+1)-QL15.at(n))<<" & "<<fabs((QL15.at(n+1)-QL15.at(n))/(QL15.at(n)-QL15.at(n-1)))<<endl;
  }


  QL15.clear();






  //Calcular valor do integral pelo metodo composto dos Trapézios para n 10,20,40,...,10*2^13
  for(int n=0;n<=nmax;n++){
    double integ;
    Qn.Trapezoidal(pow(2,n)*10,integ);
    QL15.push_back(integ);
  }


  //apresentação dos resultados de 10*2^n, n de 0 a 12
  cout<<endl<<endl<<endl<<endl;
  cout<<"Metodo dos Trapézios Composto"<<endl;
  cout<<"n ; Q_n ; Q(2n)-Qn ; (Q(2n)-Q_n)/(Qn-Q(n/2))"<<endl;
  cout<<setprecision(15)<<"10 &"<<QL15.at(0)<<" & "<<fabs(QL15.at(1)-QL15.at(0))<<" & NA"<<endl;

  for(int n=1;n<nmax;n++){
    cout<<setprecision(15)<<pow(2,n)*10<<" & "<<QL15.at(n)<<" & "<<fabs(QL15.at(n+1)-QL15.at(n))<<" & "<<fabs((QL15.at(n+1)-QL15.at(n))/(QL15.at(n)-QL15.at(n-1)))<<endl;
  }






  
  double *arrayX = new double[int(15/.15)];
  double *arrayInteg = new double[int(15/.15)];


  //calcular valores do integral no intervalo [0,.15*xmax]
  for(int xmax=1;xmax<15/.15;xmax++){
    Qn.setInterval(0,.15*xmax);

    double Qx1,Qx2;
    int n=1;

    //Garantir que o erro é menor do que 10^-6
    do{
      Qx1=Qn.GaussQuadrature(n);
      Qx2=Qn.GaussQuadrature(2*n);
      n*=2;
    }while(fabs(Qx2-Qx1)>1e-6);

    arrayX[xmax]=.15*xmax;
    arrayInteg[xmax]=Qx2;
  }



  //Desenhar gráfico
  TGraph GR1 (int(15/.15), arrayX, arrayInteg); 

  GR1.SetLineColor(kRed);
  GR1.SetLineWidth(3);
  GR1.SetTitle("L(x)");


  TCanvas *cc = new TCanvas("cc", "", 0,0,1000,800);
  GR1.Draw();
  cc->Modified();
  cc->Update();
  cc->SaveAs("L(x).png");

}