#include <cmath>
#include "NewReader.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "LETintegral.h"

//VETORES: TEMPO VOLUME PRESSAO TEMPERATURA
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
  Nlines = IEV.GetNrInstantes();

  for(int i=0; i<Nlines; i++){
    instante.push_back(IEV.GetTempo(i));
    instante.push_back(IEV.GetDataVector(i));
    instante.push_back(IEP.GetDataVector(i));
    instante.push_back(IET.GetDataVector(i));

    vIE.push_back(instante);
    instante.clear();
  }

  vector <vector<double>> vAC;
  Nlines = ACV.GetNrInstantes();

  for(int i=0; i<Nlines; i++){
    instante.push_back(ACV.GetTempo(i));
    instante.push_back(ACV.GetDataVector(i));
    instante.push_back(ACP.GetDataVector(i));
    instante.push_back(ACT.GetDataVector(i));

    vAC.push_back(instante);
    instante.clear();
  }

  vector <vector<double>> vAE;
  Nlines = AEV.GetNrInstantes();

  for(int i=0; i<Nlines; i++){
    instante.push_back(AEV.GetTempo(i));
    instante.push_back(AEV.GetDataVector(i));
    instante.push_back(AEP.GetDataVector(i));
    instante.push_back(AET.GetDataVector(i));

    vAE.push_back(instante);
    instante.clear();
  }



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

    ax_t->SetTitle("V(m^{3})");
    ay_t->SetTitle("P(Pa)");

    PVgraphIC.SetTitle("Compressao Isotermica");
    PVgraphIC.SetMarkerColor(kGreen-2);
    PVgraphIC.SetLineColor(kGreen-2);
    PVgraphIC.SetMarkerSize(.4);
    PVgraphIC.SetMarkerStyle(8);

    fIdealGas->SetLineColor(kGreen-2);
    PVgraphIC.Fit(fIdealGas);
    PVgraphIC.Draw("AP");


    PVgraphIE.SetTitle("Expansao Isotermica");
    PVgraphIE.SetMarkerColor(kRed-2);
    PVgraphIE.SetLineColor(kRed-2);
    PVgraphIE.SetMarkerSize(.4);
    PVgraphIE.SetMarkerStyle(8);
    fIdealGas->SetLineColor(kRed-2);
    PVgraphIE.Fit(fIdealGas);
    PVgraphIE.Draw("P same");
    


    PVgraphAC.SetTitle("Compressao Adiabatica");
    PVgraphAC.SetMarkerColor(kBlue-2);
    PVgraphAC.SetLineColor(kBlue-2);
    PVgraphAC.SetMarkerSize(.4);
    PVgraphAC.SetMarkerStyle(8);
    fIdealGas->SetLineColor(kBlue-2);
    PVgraphAC.Fit(fIdealGas);
    PVgraphAC.Draw("P same");
    


    PVgraphAE.SetTitle("Expansao Adiabatica");
    PVgraphAE.SetMarkerColor(94);
    PVgraphAE.SetLineColor(94);
    PVgraphAE.SetMarkerSize(.4);
    PVgraphAE.SetMarkerStyle(8);
    fIdealGas->SetLineColor(94);
    PVgraphAE.Fit(fIdealGas);
    PVgraphAE.Draw("P same");

   // c1->BuildLegend(.7,.7,.9,.9);

    c1->SaveAs("PVgraph.png");
  }



  {

    TGraph WaalsPV;

    for(int i=0;i<vAC.size();i++){
      WaalsPV.SetPoint(i,vAC[i][1],vAC[i][2]);
    }


    TGraph WaalsTV;

    for(int i=0;i<vAC.size();i++){                  //n       //b
      WaalsTV.SetPoint(i,vAC[i][1],(vAC[i][1]/1.e6-0.0106495*1e-3*.0387)*(vAC[i][2]*1000+0.0106495*0.0106495 * 1e11*1.37/vAC[i][1]/vAC[i][1])/(8.3145*0.0106495));
//      cout<<(vAC[i][1]/1.e6-0.0106495*1e-3*.0387)*(vAC[i][2]*1000+0.0106495*0.0106495 * 1e11*1.37/vAC[i][1]/vAC[i][1])/(8.3145*0.0106495)<<endl;
    }



    TGraph WaalsPV2;
    for(int i=0;i<vAE.size();i++){
      WaalsPV2.SetPoint(i,vAE[i][1],vAE[i][2]);
    }


    TGraph WaalsTV2;
    for(int i=0;i<vAC.size();i++){
      WaalsTV2.SetPoint(i,vAE[i][1],(vAE[i][1]/1.e6-0.00370615*1e-3*.0387)*(vAE[i][2]*1000+0.00370615*0.00370615 * 1e11*1.37/vAE[i][1]/vAE[i][1])/(8.3145*0.00370615));
//      cout<<(vAE[i][1]/1.e6-0.0106495*1e-3*.0387)*(vAE[i][2]*1000+0.0106495*0.0106495 * 1e11*1.37/vAE[i][1]/vAE[i][1])/(8.3145*0.0106495)<<endl;
    }




    TCanvas* c1 = new TCanvas();
  
   

    auto lWaalsGAMMA = [](double *x,double *p=nullptr){                         //1e5+3+3
      return (p[0]*pow(x[0]/1.e6-0.0106495*1e-3*.0387,p[1])-0.0106495*0.0106495 * 1e11*1.37/x[0]/x[0])/1000.;    //n=.0106495    a=1e5*.0387    b=1e12*1.37
    };

    TF1* fWaalsGAMMA= new TF1("GAMMA", lWaalsGAMMA, 1.,500.,2);

    fWaalsGAMMA->SetParameters(0,10000.);
    fWaalsGAMMA->SetParameters(1,.72);



    auto lWaalsCv = [](double *x,double *p=nullptr){
      return p[0]/pow(x[0]*1e-3  -  0.0106495 *.0387 , p[1]);///8.31446/p[1]);    //n=.0106495    b=1e-3*.0387    
    };

    TF1* fWaalsCv =  new TF1("cv", lWaalsCv, 1.,500.,2);

    fWaalsCv->SetParameters(0,100);
    fWaalsCv->SetParameters(1,1.);


    WaalsPV.Fit(fWaalsGAMMA);
    WaalsTV.Fit(fWaalsCv);

    double Cv=1./fWaalsCv->GetParameter(1)*8.3145;

    cout<<"Cv    "<<Cv<<endl;



    auto lWaalsGAMMA2 = [](double *x,double *p=nullptr){                         //1e5+3+3
      return (p[0]*pow(x[0]/1.e6-0.00370615*1e-3*.0387,p[1])-0.00370615*0.00370615 * 1e11*1.37/x[0]/x[0])/1000.;    //n=.0106495    a=1e5*.0387    b=1e12*1.37
    };

    TF1* fWaalsGAMMA2= new TF1("GAMMA2", lWaalsGAMMA2, 1.,500.,2);

    fWaalsGAMMA2->SetParameters(0,10000.);
    fWaalsGAMMA2->SetParameters(1,.72);



    auto lWaalsCv2 = [](double *x,double *p=nullptr){
      return p[0]/pow(x[0]*1e-3  -  0.00370615 *.0387 , p[1]);///8.31446/p[1]);    //n=.0106495    b=1e-3*.0387    
    };

    TF1* fWaalsCv2 =  new TF1("cv2", lWaalsCv2, 1.,500.,2);

    fWaalsCv2->SetParameters(0,100);
    fWaalsCv2->SetParameters(1,1.);


    WaalsPV2.Fit(fWaalsGAMMA2);
    WaalsTV2.Fit(fWaalsCv2);

    double Cv2=1./fWaalsCv2->GetParameter(1)*8.3145;

    cout<<"Cv2    "<<Cv2<<endl;



    TGraph WaalsCpT;

    for(int i=0;i<vAC.size();i++){
      double T=(vAC[i][1]/1.e6-0.0106495*1e-3*.0387)*(vAC[i][2]*1000+0.0106495*0.0106495 * 1e11*1.37/vAC[i][1]/vAC[i][1])/(8.3145*0.0106495);
      double Cp = Cv+8.3145/(1.-0.0106495*1.e17*1.37/vAC[i][1]/vAC[i][1]/vAC[i][1]/8.3145/T*2.*(vAC[i][1]/1.e6-0.0106495*1e-3*.0387)*(vAC[i][1]/1.e6-0.0106495*1e-3*.0387));
    //  cout<<T<<"   "<<Cp<<endl;

      WaalsCpT.SetPoint(i,T,Cp);
    }

    TGraph WaalsCpT2;

    for(int i=0;i<vAC.size();i++){    
      double T=(vAE[i][1]/1.e6-0.00370615*1e-3*.0387)*(vAE[i][2]*1000+0.00370615*0.00370615 * 1e11*1.37/vAE[i][1]/vAE[i][1])/(8.3145*0.00370615);
      double Cp = Cv+8.3145/(1.-0.00370615*1.e17*1.37/vAE[i][1]/vAE[i][1]/vAE[i][1]/8.3145/T*2.*(vAE[i][1]/1.e6-0.00370615*1e-3*.0387)*(vAE[i][1]/1.e6-0.00370615*1e-3*.0387));
      cout<<T<<"   "<<Cp<<endl;

      WaalsCpT2.SetPoint(i,T,Cp);
    }

    
    TAxis *ax_t = WaalsCpT.GetXaxis();
    TAxis *ay_t = WaalsCpT.GetYaxis();

    ax_t->SetTitle("T(K)");
    ay_t->SetTitle("C_{p}(J/(K.mol))");


    ax_t->SetLimits(220,350);
    ay_t->SetRangeUser(29.80,29.93);


    WaalsCpT.SetTitle("C_{p}(T)");
    WaalsCpT.SetMarkerColor(kCyan-2);
    WaalsCpT.SetLineColor(kCyan-2);
    WaalsCpT.SetMarkerSize(.5);
    WaalsCpT.SetMarkerStyle(8);

    WaalsCpT.Draw("AP");
    //    fWaalsCv->Draw("AP");

    WaalsCpT2.SetTitle("C_{p}(T)");
    WaalsCpT2.SetMarkerColor(kRed-5);
    WaalsCpT2.SetLineColor(kRed-5);
    WaalsCpT2.SetMarkerSize(.5);
    WaalsCpT2.SetMarkerStyle(8);

    WaalsCpT2.Draw("P same");

    c1->SaveAs("WaalsCpT.png");
  }

  return 0;
}
