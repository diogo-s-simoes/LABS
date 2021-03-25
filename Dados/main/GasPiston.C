#include <cmath>
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





  {

    TGraph WaalsPV;

    for(int i=0;i<vIC.size();i++){
      WaalsPV.SetPoint(i,vIC[i][1],vIC[i][2]);
    }


    TGraph WaalsTV;

    for(int i=0;i<vIC.size();i++){
      WaalsTV.SetPoint(i,vIC[i][1],(vIC[i][1]/1.e6-0.00997346*1e-3*.0387)*(vIC[i][2]*1000+0.00997346*0.00997346 * 1e11*1.37/vIC[i][1]/vIC[i][1])/(8.3145*0.00997346));
    //      cout<<(vAC[i][1]/1.e6-0.00997346*1e-3*.0387)*(vAC[i][2]*1000+0.00997346*0.00997346 * 1e11*1.37/vAC[i][1]/vAC[i][1])/(8.3145*0.00997346)<<endl;
    }



    TGraph WaalsPV2;

    for(int i=0;i<vIE.size();i++){
      WaalsPV2.SetPoint(i,vIE[i][1],vIE[i][2]);
    }


    TGraph WaalsTV2;

    for(int i=0;i<vIE.size();i++){
      WaalsTV2.SetPoint(i,vIE[i][1],(vIE[i][1]/1.e6-0.0038602*1e-3*.0387)*(vIE[i][2]*1000+0.0038602*0.0038602 * 1e11*1.37/vIE[i][1]/vIE[i][1])/(8.3145*0.0038602));
      //      cout<<(vAE[i][1]/1.e6-0.00997346*1e-3*.0387)*(vAE[i][2]*1000+0.00997346*0.00997346 * 1e11*1.37/vAE[i][1]/vAE[i][1])/(8.3145*0.00997346)<<endl;
    }




    TCanvas* c1 = new TCanvas();
  
   

    auto lWaalsGAMMA = [](double *x,double *p=nullptr){                         //1e5+3+3
      return (p[0]*pow(x[0]/1.e6-0.00997346*1e-3*.0387,p[1])-0.00997346*0.00997346 * 1e11*1.37/x[0]/x[0])/1000.;    //n=.00997346    a=1e5*.0387    b=1e12*1.37
    };

    TF1* fWaalsGAMMA= new TF1("GAMMA", lWaalsGAMMA, 1.,500.,2);

    fWaalsGAMMA->SetParameters(0,10000.);
    fWaalsGAMMA->SetParameters(1,.72);



    auto lWaalsCv = [](double *x,double *p=nullptr){
      return p[0]/pow(x[0]*1e-3  -  0.00997346 *.0387 , p[1]);///8.31446/p[1]);    //n=.00997346    b=1e-3*.0387    
    };

    TF1* fWaalsCv =  new TF1("cv", lWaalsCv, 1.,500.,2);

    fWaalsCv->SetParameters(0,100);
    fWaalsCv->SetParameters(1,1.);


    WaalsPV.Fit(fWaalsGAMMA);
    WaalsTV.Fit(fWaalsCv);

    double Cv=1./fWaalsCv->GetParameter(1)*8.3145;

    cout<<"Cv    "<<Cv<<endl;



    auto lWaalsGAMMA2 = [](double *x,double *p=nullptr){                         //1e5+3+3
      return (p[0]*pow(x[0]/1.e6-0.0038602*1e-3*.0387,p[1])-0.0038602*0.0038602 * 1e11*1.37/x[0]/x[0])/1000.;    //n=.00997346    a=1e5*.0387    b=1e12*1.37
    };

    TF1* fWaalsGAMMA2= new TF1("GAMMA2", lWaalsGAMMA2, 1.,500.,2);

    fWaalsGAMMA2->SetParameters(0,10000.);
    fWaalsGAMMA2->SetParameters(1,.72);



    auto lWaalsCv2 = [](double *x,double *p=nullptr){
      return p[0]/pow(x[0]*1e-3  -  0.0038602 *.0387 , p[1]);///8.31446/p[1]);    //n=.00997346    b=1e-3*.0387    
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
    //  cout<<T<0106495<"   "<<Cp<<endl;

      WaalsCpT.SetPoint(i,T,Cp);
    }

    TGraph WaalsCpT2;

    for(int i=0;i<vAC.size();i++){    
      double T=(vAE[i][1]/1.e6-0.00370615*1e-3*.0387)*(vAE[i][2]*1000+0.00370615*0.00370615 * 1e11*1.37/vAE[i][1]/vAE[i][1])/(8.3145*0.00370615);
      double Cp = Cv+8.3145/(1.-0.00370615*1.e17*1.37/vAE[i][1]/vAE[i][1]/vAE[i][1]/8.3145/T*2.*(vAE[i][1]/1.e6-0.00370615*1e-3*.0387)*(vAE[i][1]/1.e6-0.00370615*1e-3*.0387));
      //cout<<T<<"   "<<Cp<<endl;

      WaalsCpT2.SetPoint(i,T,Cp);
    }

    
    TAxis *ax_t = WaalsCpT.GetXaxis();
    TAxis *ay_t = WaalsCpT.GetYaxis();

    ax_t->SetTitle("T(K)");
    ay_t->SetTitle("C_{p}(J/(K.mol))");


    ax_t->SetLimits(220,350);
    ay_t->SetRangeUser(29.7,30);


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




  {
    double n = 0.0106495, R=8.3145;
    for(int i=0;i<vAC.size();i++){
      double T = 1e-3*vAC[i][1]*vAC[i][2]/R/n;
      vAC[i][3]=T;
      double S = n*R*(2.5*log(T)+log(1.e-6*vAC[i][1]));
      vAC.at(i).push_back(S);
     // cout<<T<<"    "<<S<<endl;
    }

    TGraph Ugraph,Hgraph,Fgraph,Ggraph;

    double U=0.,H=0.,F=0.,G=0.;

    for(int i=0;i<vAC.size()-1;i++){
      //U = (vAC[i][3]*(vAC[i+1][4]-vAC[i][4]));

      U += (vAC[i][3]*(vAC[i+1][4]-vAC[i][4])-vAC[i][2]*(vAC[i+1][1]-vAC[i][1])*1e-3);
      Ugraph.SetPoint(i,vAC[i][0],U);

      H += (vAC[i][3]*(vAC[i+1][4]-vAC[i][4])+vAC[i][1]*(vAC[i+1][2]-vAC[i][2])*1e-3);
      Hgraph.SetPoint(i,vAC[i][0],H);

      F += (-vAC[i][4]*(vAC[i+1][3]-vAC[i][3])-vAC[i][2]*(vAC[i+1][1]-vAC[i][1])*1e-3);
      Fgraph.SetPoint(i,vAC[i][0],F);

      G += (-vAC[i][4]*(vAC[i+1][3]-vAC[i][3])+vAC[i][1]*(vAC[i+1][2]-vAC[i][2])*1e-3);
      Ggraph.SetPoint(i,vAC[i][0],G);



    //  cout<<U<<"   "<<H<<"   "<<F<<"   "<<G<<"   "<<endl;

    }


    TCanvas* c1 = new TCanvas();
    


    TAxis *ax_t = Ugraph.GetXaxis();
    TAxis *ay_t = Ugraph.GetYaxis();

    ax_t->SetTitle("T(K)");
    ay_t->SetTitle("C_{p}(J/(K.mol))");


    ax_t->SetLimits(0,100);
    ay_t->SetRangeUser(-20,20);


    Ugraph.SetTitle("var U(t)");
    Ugraph.SetMarkerColor(kBlue-2);
    Ugraph.SetLineColor(kBlue-2);
    Ugraph.SetMarkerSize(.3);
    Ugraph.SetMarkerStyle(8);

    Hgraph.SetTitle("var H(t)");
    Hgraph.SetMarkerColor(kYellow-2);
    Hgraph.SetLineColor(kYellow-2);
    Hgraph.SetMarkerSize(.3);
    Hgraph.SetMarkerStyle(8);

    Fgraph.SetTitle("var F(t)");
    Fgraph.SetMarkerColor(kGreen-2);
    Fgraph.SetLineColor(kGreen-2);
    Fgraph.SetMarkerSize(.3);
    Fgraph.SetMarkerStyle(8);

    Ggraph.SetTitle("var G(t)");
    Ggraph.SetMarkerColor(kRed-2);
    Ggraph.SetLineColor(kRed-2);
    Ggraph.SetMarkerSize(.3);
    Ggraph.SetMarkerStyle(8);

    Ugraph.Draw("AP");
    Hgraph.Draw("P same");
    Fgraph.Draw("P same");
    Ggraph.Draw("P same");


    c1->SaveAs("MaxwellAC.png");
  }






  {
    double n = 0.0038602, R=8.3145;
    for(int i=0;i<vIE.size();i++){
      double T = 1e-3*vIE[i][1]*vIE[i][2]/R/n;
      vIE[i][3]=T;
      double S = n*R*(2.5*log(T)+log(1.e-6*vIE[i][1]));
      vIE.at(i).push_back(S);
      //cout<<T<<"    "<<S<<endl;
    }

    TGraph Ugraph,Hgraph,Fgraph,Ggraph;

    double U=0.,H=0.,F=0.,G=0.;

    for(int i=0;i<vIE.size()-1;i++){

      U += (vIE[i][3]*(vIE[i+1][4]-vIE[i][4])-vIE[i][2]*(vIE[i+1][1]-vIE[i][1])*1e-3);
      Ugraph.SetPoint(i,vIE[i][0],U);

      H += (vIE[i][3]*(vIE[i+1][4]-vIE[i][4])+vIE[i][1]*(vIE[i+1][2]-vIE[i][2])*1e-3);
      Hgraph.SetPoint(i,vIE[i][0],H);

      F += (-vIE[i][4]*(vIE[i+1][3]-vIE[i][3])-vIE[i][2]*(vIE[i+1][1]-vIE[i][1])*1e-3);
      Fgraph.SetPoint(i,vIE[i][0],F);

      G += (-vIE[i][4]*(vIE[i+1][3]-vIE[i][3])+vIE[i][1]*(vIE[i+1][2]-vIE[i][2])*1e-3);
      Ggraph.SetPoint(i,vIE[i][0],G);



    //  cout<<U<<"   "<<H<<"   "<<F<<"   "<<G<<"   "<<endl;

    }


    TCanvas* c1 = new TCanvas();
    


    TAxis *ax_t = Ugraph.GetXaxis();
    TAxis *ay_t = Ugraph.GetYaxis();

    ax_t->SetTitle("t(ms)");
    ay_t->SetTitle("E(J)");


    ax_t->SetLimits(0,10000);
    ay_t->SetRangeUser(-10,10);


    Ugraph.SetTitle("var U(t)");
    Ugraph.SetMarkerColor(kBlue-2);
    Ugraph.SetLineColor(kBlue-2);
    Ugraph.SetMarkerSize(.3);
    Ugraph.SetMarkerStyle(8);

    Hgraph.SetTitle("var H(t)");
    Hgraph.SetMarkerColor(kYellow-2);
    Hgraph.SetLineColor(kYellow-2);
    Hgraph.SetMarkerSize(.3);
    Hgraph.SetMarkerStyle(8);

    Fgraph.SetTitle("var F(t)");
    Fgraph.SetMarkerColor(kGreen-2);
    Fgraph.SetLineColor(kGreen-2);
    Fgraph.SetMarkerSize(.3);
    Fgraph.SetMarkerStyle(8);

    Ggraph.SetTitle("var G(t)");
    Ggraph.SetMarkerColor(kRed-2);
    Ggraph.SetLineColor(kRed-2);
    Ggraph.SetMarkerSize(.3);
    Ggraph.SetMarkerStyle(8);

    Ugraph.Draw("AP");
    Hgraph.Draw("P same");
    Fgraph.Draw("P same");
    Ggraph.Draw("P same");


    c1->SaveAs("MaxwellIE.png");
  }








  return 0;
}
