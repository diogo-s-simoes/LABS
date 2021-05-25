#include <cmath>
#include "DataReader.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TApplication.h"
#include "TPaveText.h"
#include "Spline3Interpolator.h"
#include "NewtonInterpolator.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphErrors.h"

double angconv(double g, double m, double s){
    return (M_PI/180.)*(g+m/60.+s/(30.*120.));
}

int main(){
    DataReader ficheiro1("data/Tabela1_PolS_FacePlana.txt");
    DataReader ficheiro2("data/Tabela2_PolS_FaceCurva.txt");
    DataReader ficheiro3("data/Tabela3_PolP_FacePlana.txt");
    DataReader ficheiro4("data/Tabela4_PolP_FaceCurva.txt");

    vector<vector<double>> data1;
    vector<vector<double>> data2;
    vector<vector<double>> data3;
    vector<vector<double>> data4;

    vector<double> temp1;
    vector<double> temp2;
    vector<double> temp3;
    vector<double> temp4;

    int N=ficheiro1.GetLines();

    for(int i=0;i<ficheiro1.GetLines();++i){
        for(int j =0;j<9;++j){
            temp1.push_back(atof(&(ficheiro1.GetData()[i][j][0])));
            temp2.push_back(atof(&(ficheiro2.GetData()[i][j][0])));
            temp3.push_back(atof(&(ficheiro3.GetData()[i][j][0])));
            temp4.push_back(atof(&(ficheiro4.GetData()[i][j][0])));
        }
        data1.push_back(temp1);
        data2.push_back(temp2);
        data3.push_back(temp3);
        data4.push_back(temp4);
        temp1.clear();
        temp2.clear();
        temp3.clear();
        temp4.clear();
    }

    vector<double> ang1;
    vector<double> ang2;
    vector<double> ang3;
    vector<double> ang4;

    for(int i=0;i<ficheiro1.GetLines();++i){
        ang1.push_back(angconv(data1[i][0],data1[i][1],data1[i][2]));
        ang2.push_back(angconv(data2[i][0],data2[i][1],data2[i][2]));
        ang3.push_back(angconv(data3[i][0],data3[i][1],data3[i][2]));
        ang4.push_back(angconv(data4[i][0],data4[i][1],data4[i][2]));
        
        if(ang1[i]>300*(M_PI/180.))
        ang1[i]=ang1[i]-320*(M_PI/180.);
        else
        ang1[i]=(ang1[i]+360*(M_PI/180.))-320*(M_PI/180.);

        if(ang2[i]>300*(M_PI/180.))
        ang2[i]=ang2[i]-320*(M_PI/180.);
        else
        ang2[i]=(ang2[i]+360*(M_PI/180.))-320*(M_PI/180.);
    
        if(ang3[i]>75*(M_PI/180.))
        ang3[i]=70*(M_PI/180.)-(ang3[i]-360*(M_PI/180.));
        else
        ang3[i]=70*(M_PI/180.)-ang3[i];
        if(ang4[i]>75*(M_PI/180.))
        ang4[i]=70*(M_PI/180.)-(ang4[i]-360*(M_PI/180.));
        else
        ang4[i]=70*(M_PI/180.)-ang4[i];
    }

    vector<double> ref1;
    vector<double> ref2;
    vector<double> ref3;
    vector<double> ref4;

    for(int i=0;i<ficheiro1.GetLines();++i){
        if(data1[i][8]==0) ref1.push_back(0); else ref1.push_back(((data1[i][6]+data1[i][7])/2.)/data1[i][8]);
        if(data2[i][8]==0) ref2.push_back(0); else ref2.push_back(((data2[i][6]+data2[i][7])/2.)/data2[i][8]);
        if(data3[i][8]==0) ref3.push_back(0); else ref3.push_back(((data3[i][6]+data3[i][7])/2.)/data3[i][8]);
        if(data4[i][8]==0) ref4.push_back(0); else ref4.push_back(((data4[i][6]+data4[i][7])/2.)/data4[i][8]);
    }

    vector<double> tra1;
    vector<double> tra2;
    vector<double> tra3;
    vector<double> tra4;

    for(int i=0;i<ficheiro1.GetLines();++i){
        if(data1[i][5]==0) tra1.push_back(0); else tra1.push_back(((data1[i][3]+data1[i][4])/2.)/data1[i][5]);
        if(data2[i][5]==0) tra2.push_back(0); else tra2.push_back(((data2[i][3]+data2[i][4])/2.)/data2[i][5]);
        if(data3[i][5]==0) tra3.push_back(0); else tra3.push_back(((data3[i][3]+data3[i][4])/2.)/data3[i][5]);
        if(data4[i][5]==0) tra4.push_back(0); else tra4.push_back(((data4[i][3]+data4[i][4])/2.)/data4[i][5]);
    }

    TGraph G_tra1;
    TGraph G_tra2;
    TGraph G_tra3;
    TGraph G_tra4;
    TGraph G_ref1;
    TGraph G_ref2;
    TGraph G_ref3;
    TGraph G_ref4;
    for(int i=0; i<N;++i){
        //if(tra1[i]!=0)
            G_tra1.SetPoint(i,ang1[i],tra1[i]);
        //if(tra2[i]!=0)
            G_tra2.SetPoint(i,ang2[i],tra2[i]);
        //if(tra3[i]!=0)
            G_tra3.SetPoint(i,ang3[i],tra3[i]);
        //if(tra4[i]!=0)
            G_tra4.SetPoint(i,ang4[i],tra4[i]);
        //if(ref1[i]!=0)
            G_ref1.SetPoint(i,ang1[i],ref1[i]);
        //if(ref2[i]!=0)
            G_ref2.SetPoint(i,ang2[i],ref2[i]);
        //if(ref3[i]!=0)
            G_ref3.SetPoint(i,ang3[i],ref3[i]);
        //if(ref4[i]!=0)
            G_ref4.SetPoint(i,ang4[i],ref4[i]);
    }

    TCanvas* c1 = new TCanvas();



    auto lRefS = [](double *x,double *p=nullptr){
        return 0.181/0.0235*pow((p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2.);
    };

    TF1* fRefS= new TF1("L", lRefS, 0.,1.6,2);


    auto lRefP = [](double *x,double *p=nullptr){
        return .2105/0.0515*pow((p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };

    TF1* fRefP= new TF1("L", lRefP, 0.,1.6,2);



    auto lTransS = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*
        0.181/0.0235*
        p[1]/p[0]*
        sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*
        pow(1+(p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };

    TF1* fTransS= new TF1("L", lTransS, 0.,1.6,2);


    auto lTransP = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*.2105/0.0515*p[1]/p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*pow(p[0]/p[1]*(1+(p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))),2);
    };

    TF1* fTransP= new TF1("L", lTransP, 0.,1.6,2);


    fTransS->SetParameter(0,1);
    fTransS->SetParameter(1,1.48);    
    fTransP->SetParameter(0,1);
    fTransP->SetParameter(1,1.48);    
    fRefP->SetParameter(0,1);
    fRefP->SetParameter(1,1.48);
    fRefS->SetParameter(0,1);
    fRefS->SetParameter(1,1.48);



    G_tra1.Draw("AL");
    fTransS->Draw("same");
    c1->SaveAs("tra1.png");
    c1->Clear();
    G_tra3.Draw("AL");
    fTransP->Draw("same");
    c1->SaveAs("tra3.png");
    c1->Clear();
    G_ref1.Draw("AL");
    fRefS->Draw("same");
    c1->SaveAs("ref1.png");
    c1->Clear();
    G_ref3.Draw("AL");
    fRefP->Draw("same");
    c1->SaveAs("ref3.png");
    c1->Clear();






    auto lRefS1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*0.181/0.0235*pow((p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2.);
    //pow(({p*\cos(x)-p_{2}*\sqrt{1-\sin(x)*\sin(x)*(p/p_{2})*(p/p_{2})}}/{p*\cos(x)+p_{2}*\sqrt{1-\sin(x)*\sin(x)*(p/p_{2})*(p/p_{2})}}\right)^{2}0.181/0.0245\cdot\left(p\cdot p_{2}\cdot\frac{4}{\left(p+p_{2}\right)^{2}}),2)
    };
    TF1* fRefS1= new TF1("L", lRefS1, 0.,1.6,2);


    auto lRefP1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*.2105/0.0515*pow((p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };
    TF1* fRefP1= new TF1("L", lRefP1, 0.,1.6,2);



    auto lTransS1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*
        0.181/0.0235*
        p[1]/p[0]*
        sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*
        pow(1+(p[0]*cos(x[0])-p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[0]*cos(x[0])+p[1]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))),2);
    };
    TF1* fTransS1= new TF1("L", lTransS1, 0.,1.6,2);


    auto lTransP1 = [](double *x,double *p=nullptr){
        return 4*p[0]*p[1]/(p[0]+p[1])/(p[0]+p[1])*.2105/0.0515*p[1]/p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1]))/cos(x[0])*pow(p[0]/p[1]*(1+(p[1]*cos(x[0])-p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))/(p[1]*cos(x[0])+p[0]*sqrt(1-sin(x[0])*sin(x[0])*(p[0]/p[1])*(p[0]/p[1])))),2);
    };
    TF1* fTransP1= new TF1("L", lTransP1, 0.,1.6,2);



    fTransS1->SetParameter(0,1.48);
    fTransS1->SetParameter(1,1);
    fTransP1->SetParameter(0,1.48);
    fTransP1->SetParameter(1,1);    
    fRefP1->SetParameter(0,1.48);
    fRefP1->SetParameter(1,1);
    fRefS1->SetParameter(0,1.48);
    fRefS1->SetParameter(1,1.);



    TGraph gTransS1,gTransP1,gRefS1,gRefP1;

    for(int i=0;i<1000000;i++){
        if(fTransS1->Eval(i*1.6/1000000)<10)
            gTransS1.SetPoint(i,i*1.6/1000000,fTransS1->Eval(i*1.6/1000000));

        if(fTransP1->Eval(i*1.6/1000000)<10)
            gTransP1.SetPoint(i,i*1.6/1000000,fTransP1->Eval(i*1.6/1000000));
        
        if(fRefS1->Eval(i*1.6/1000000)<10)
            gRefS1.SetPoint(i,i*1.6/1000000,fRefS1->Eval(i*1.6/1000000));
        
        if(fRefP1->Eval(i*1.6/1000000)<10)
            gRefP1.SetPoint(i,i*1.6/1000000,fRefP1->Eval(i*1.6/1000000));
//        cout<<i*1.6/1000000<<"   "<<fRefP1->Eval(i*1.6/10000)<<"   "<<fTransP1->Eval(i*1.6/10000)<<endl;
    }



    TAxis *ax_t = G_ref2.GetXaxis();
    TAxis *ay_t = G_ref2.GetYaxis();

    ax_t->SetLimits(0,1.6);
    ay_t->SetRangeUser(0,10);

    TAxis *ax_t1 = G_ref4.GetXaxis();
    TAxis *ay_t1 = G_ref4.GetYaxis();

    ax_t1->SetLimits(0,1.6);
    ay_t1->SetRangeUser(0,10);




    G_tra2.Draw("AL");
    gTransS1.Draw("same");
    //fTransS1->Draw("same");
    c1->SaveAs("tra2.png");
    c1->Clear();
    G_tra4.Draw("AL");
    gTransP1.Draw("same");
    //fTransP1->Draw("same");
    c1->SaveAs("tra4.png");
    c1->Clear();
    G_ref2.Draw("AL");
    gRefS1.Draw("same");
    //fRefS1->Draw("same");
    c1->SaveAs("ref2.png");
    c1->Clear();
    G_ref4.Draw("AL");
    gRefP1.Draw("same");
    //fRefP1->Draw("same");
    c1->SaveAs("ref4.png");
    c1->Clear();


    auto lAlp = [](double *x,double *p=nullptr){
        return x[0]*exp(-p[0]*0.025)+p[1];
    };
    TF1* fAlp= new TF1("FALP", lAlp, 0.,50.,1);

    auto lAlp2 = [](double *x,double *p=nullptr){
        return x[0]*exp(-p[0]*0.05)+p[1];
    };
    TF1* fAlp2= new TF1("FALP2", lAlp2, 0.,50.,1);

    TGraph Gar1;   Gar1.SetMarkerStyle(33);
    TGraph Gat1;   Gat1.SetMarkerStyle(33);
    TGraph Gar2;   Gar2.SetMarkerStyle(33);
    TGraph Gat2;   Gat2.SetMarkerStyle(33);
    TGraph Gar3;   Gar3.SetMarkerStyle(33);
    TGraph Gat3;   Gat3.SetMarkerStyle(33);
    TGraph Gar4;   Gar4.SetMarkerStyle(33);
    TGraph Gat4;   Gat4.SetMarkerStyle(33);
    TGraph Galpha; Galpha.SetMarkerStyle(33);

    Gat1.SetMarkerSize(2);
    Gat2.SetMarkerSize(2);
    Gat3.SetMarkerSize(2);
    Gat4.SetMarkerSize(2);
    Gar2.SetMarkerSize(2);
    Gar4.SetMarkerSize(2);
    Galpha.SetMarkerSize(2);

    Gat1.SetMarkerColor(kBlue+2);
    Gat2.SetMarkerColor(kBlue+2);
    Gar2.SetMarkerColor(kBlue+2);
    Gat3.SetMarkerColor(kBlue+2);
    Gat4.SetMarkerColor(kBlue+2);
    Gar4.SetMarkerColor(kBlue+2);
    Galpha.SetMarkerColor(kBlue+2);

    for(int i=0; i<N; ++i){
        Gar1.SetPoint(i,   fRefS->Eval(G_ref1.GetX()[i]),G_ref1.GetY()[i]);
        Gat1.SetPoint(i, fTransS->Eval(G_tra1.GetX()[i]),G_tra1.GetY()[i]);
        Gar3.SetPoint(i,   fRefP->Eval(G_ref3.GetX()[i]),G_ref3.GetY()[i]);
        Gat3.SetPoint(i, fTransP->Eval(G_tra3.GetX()[i]),G_tra3.GetY()[i]);
        //Galpha.SetPoint(i,   fRefS->Eval(G_ref1.GetX()[i]),G_ref1.GetY()[i]);
        Galpha.SetPoint(i, fTransS->Eval(G_tra1.GetX()[i]),G_tra1.GetY()[i]);
        //Galpha.SetPoint(i,   fRefP->Eval(G_ref3.GetX()[i]),G_ref3.GetY()[i]);
        Galpha.SetPoint(i, fTransP->Eval(G_tra3.GetX()[i]),G_tra3.GetY()[i]);
    }

    for(int i=0; i<9; ++i){
        if(G_ref2.GetY()[i]>0) Gar2.SetPoint(i,  fRefS1->Eval(G_ref2.GetX()[i]),G_ref2.GetY()[i]);
        Gat2.SetPoint(i,fTransS1->Eval(G_tra2.GetX()[i]),G_tra2.GetY()[i]);
        if(G_ref4.GetY()[i]>0) Gar4.SetPoint(i,  fRefP1->Eval(G_ref4.GetX()[i]),G_ref4.GetY()[i]);
        Gat4.SetPoint(i,fTransP1->Eval(G_tra4.GetX()[i]),G_tra4.GetY()[i]);
        //Galpha.SetPoint(i,  fRefS1->Eval(G_ref2.GetX()[i]),G_ref2.GetY()[i]);
        Galpha.SetPoint(i,fTransS1->Eval(G_tra2.GetX()[i]),G_tra2.GetY()[i]);
        //Galpha.SetPoint(i,  fRefP1->Eval(G_ref4.GetX()[i]),G_ref4.GetY()[i]);
        Galpha.SetPoint(i,fTransP1->Eval(G_tra4.GetX()[i]),G_tra4.GetY()[i]);
    }

    for(int i=9; i<N; ++i){
        if(G_ref2.GetY()[i]>0) Gar2.SetPoint(i, 7.17, G_ref2.GetY()[i]);
        //Gat2.SetPoint(i,fTransS1->Eval(G_tra2.GetX()[i]),G_tra2.GetY()[i]);
        if(G_ref4.GetY()[i]>0) Gar4.SetPoint(i, 3.75, G_ref4.GetY()[i]);
        //Gat4.SetPoint(i,fTransP1->Eval(G_tra4.GetX()[i]),G_tra4.GetY()[i]);
        //Galpha.SetPoint(i,  fRefS1->Eval(G_ref2.GetX()[i]),G_ref2.GetY()[i]);
        //Galpha.SetPoint(i,fTransS1->Eval(G_tra2.GetX()[i]),G_tra2.GetY()[i]);
        //Galpha.SetPoint(i,  fRefP1->Eval(G_ref4.GetX()[i]),G_ref4.GetY()[i]);
        //Galpha.SetPoint(i,fTransP1->Eval(G_tra4.GetX()[i]),G_tra4.GetY()[i]);
    }

    fAlp->SetLineColor(kViolet); 
    fAlp->SetLineWidth(3);
    fAlp2->SetLineColor(kViolet); 
    fAlp2->SetLineWidth(3);


    //Gar1.Fit(fAlp);
    Gat1.Fit(fAlp);    //4.22477
    Gar2.Fit(fAlp2);   //6.57601
    Gat2.Fit(fAlp);    //4.26575
    //Gar3.Fit(fAlp);
    Gat3.Fit(fAlp);    //6.1149
    Gar4.Fit(fAlp2);   //5.51132
    Gat4.Fit(fAlp);    //5.48525
    Galpha.Fit(fAlp);  //6.28117
    
    TAxis *ax = Gat1.GetXaxis();
    TAxis *ay = Gat1.GetYaxis();
    ax->SetTitle("#Iota_{0}");
    ay->SetTitle("#Iota");
    //ax->SetLimits(1.5,8);
    //ay->SetRangeUser(0,7.1);
    Gat1.Draw("AP");
    c1->SaveAs("aT1.png");
    c1->Clear();
    
    TAxis *ax1 = Gar2.GetXaxis();
    TAxis *ay1 = Gar2.GetYaxis();
    ax1->SetTitle("#Iota_{0}");
    ay1->SetTitle("#Iota");
    ax1->SetLimits(0.005,7.8);
    ay1->SetRangeUser(0,6);
    Gar2.Draw("AP");
    c1->SaveAs("aR2.png");
    c1->Clear();

    TAxis *ax2 = Gat2.GetXaxis();
    TAxis *ay2 = Gat2.GetYaxis();
    ax2->SetTitle("#Iota_{0}");
    ay2->SetTitle("#Iota");
    Gat2.Draw("AP");
    c1->SaveAs("aT2.png");
    c1->Clear();

    TAxis *ax3 = Gat3.GetXaxis();
    TAxis *ay3 = Gat3.GetYaxis();
    ax3->SetTitle("#Iota_{0}");
    ay3->SetTitle("#Iota");
    Gat3.Draw("AP");
    c1->SaveAs("aT3.png");
    c1->Clear();

    TAxis *ax4 = Gar4.GetXaxis();
    TAxis *ay4 = Gar4.GetYaxis();
    ax4->SetTitle("#Iota_{0}");
    ay4->SetTitle("#Iota");
    ax4->SetLimits(0.005,4.12);
    ay4->SetRangeUser(0,3.3);
    Gar4.Draw("AP");
    c1->SaveAs("aR4.png");
    c1->Clear();

    TAxis *ax5 = Gat4.GetXaxis();
    TAxis *ay5 = Gat4.GetYaxis();
    ax5->SetTitle("#Iota_{0}");
    ay5->SetTitle("#Iota");
    Gat4.Draw("AP");
    c1->SaveAs("aT4.png");
    c1->Clear();

    TAxis *ax6 = Galpha.GetXaxis();
    TAxis *ay6 = Galpha.GetYaxis();
    ax6->SetTitle("#Iota_{0}");
    ay6->SetTitle("#Iota");
    Galpha.Draw("AP");
    c1->SaveAs("alpha.png");
    c1->Clear();

    return 0;
}