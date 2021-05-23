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

    TGraph G_tra1; G_tra1.SetTitle("Transmitido, Polarizacao S, Face Plana"); 
    TGraph G_tra2; G_tra2.SetTitle("Transmitido, Polarizacao S, Face Curva");
    TGraph G_tra3; G_tra3.SetTitle("Transmitido, Polarizacao P, Face Plana");
    TGraph G_tra4; G_tra4.SetTitle("Transmitido, Polarizacao P, Face Curva");
    TGraph G_ref1; G_ref1.SetTitle("Refletido, Polarizacao S, Face Plana");
    TGraph G_ref2; G_ref2.SetTitle("Refletido, Polarizacao S, Face Curva");
    TGraph G_ref3; G_ref3.SetTitle("Refletido, Polarizacao P, Face Plana");
    TGraph G_ref4; G_ref4.SetTitle("Refletido, Polarizacao P, Face Curva");
    for(int i=0; i<N;++i){
        G_tra1.SetPoint(i,ang1[i],tra1[i]);
        G_tra2.SetPoint(i,ang2[i],tra2[i]);
        G_tra3.SetPoint(i,ang3[i],tra3[i]);
        G_tra4.SetPoint(i,ang4[i],tra4[i]);
        G_ref1.SetPoint(i,ang1[i],ref1[i]);
        G_ref2.SetPoint(i,ang2[i],ref2[i]);
        G_ref3.SetPoint(i,ang3[i],ref3[i]);
        G_ref4.SetPoint(i,ang4[i],ref4[i]);
    }

    TCanvas* c1 = new TCanvas();
    G_tra1.Draw("AL");
    c1->SaveAs("tra1.png");
    c1->Clear();
    G_tra2.Draw("AL");
    c1->SaveAs("tra2.png");
    c1->Clear();
    G_tra3.Draw("AL");
    c1->SaveAs("tra3.png");
    c1->Clear();
    G_tra4.Draw("AL");
    c1->SaveAs("tra4.png");
    c1->Clear();
    G_ref1.Draw("AL");
    c1->SaveAs("ref1.png");
    c1->Clear();
    G_ref2.Draw("AL");
    c1->SaveAs("ref2.png");
    c1->Clear();
    G_ref3.Draw("AL");
    c1->SaveAs("ref3.png");
    c1->Clear();
    G_ref4.Draw("AL");
    c1->SaveAs("ref4.png");
    c1->Clear();

    double thCs=(angconv(4,43,0)+angconv(3,45,0)+angconv(4,55,0)+angconv(3,50,0)+angconv(4,39,9)+angconv(3,40,0))/6.+40*(M_PI/180.);
    double thCp=70*(M_PI/180.)-(angconv(27,23,30)+angconv(27,50,0)+angconv(27,36,30)+angconv(28,0,0)+angconv(27,19,30)+angconv(28,2,30))/6.;

    double thB_c=70*(M_PI/180.)-angconv(36,7,30);
    double thB_f=70*(M_PI/180.)-angconv(13,28,30);

    double ns=1/sin(thCs);
    double np=1/sin(thCp);
    double nc=1/tan(thB_c);
    double nf=tan(thB_f);
    double nt=(nc+np+nf+ns)/4.;
    cout<<"ns: "<<ns<<endl;
    cout<<"np: "<<np<<endl;
    cout<<"nf: "<<nf<<endl;
    cout<<"nc: "<<nc<<endl;
    cout<<"indice de refracao= "<<nt<<endl;

    double Itp=((0.211+0.210)/2.)/0.0515;
    double Its=((0.179+0.183)/2.)/0.0235;
    cout<<"Ip= "<<Itp<<endl<<"Is= "<<Its<<endl;

    auto lItp = [&](double *x,double *p=nullptr){
    return Itp;
    };
    TF1 *fItp = new TF1("Itp", lItp, -10000,10000,0);
    auto lIts = [&](double *x,double *p=nullptr){
    return Its;
    };
    TF1 *fIts = new TF1("Its", lIts, -10000,10000,0);

    TGraph G_It1; G_It1.SetTitle("Intensidade total, polarizacao S, face P");
    TGraph G_It2; G_It2.SetTitle("Intensidade total, polarizacao S, face C");
    TGraph G_It3; G_It3.SetTitle("Intensidade total, polarizacao P, face P");
    TGraph G_It4; G_It4.SetTitle("Intensidade total, polarizacao S, face C");
    for(int i=0; i<N;++i){
        G_It1.SetPoint(i,ang1[i],tra1[i]+ref1[i]);
        G_It2.SetPoint(i,ang2[i],tra1[i]+ref2[i]);
        G_It3.SetPoint(i,ang3[i],tra1[i]+ref3[i]);
        G_It4.SetPoint(i,ang4[i],tra1[i]+ref4[i]);
    }

    G_It1.Draw("AL");
    fIts->Draw("SAME");
    c1->SaveAs("It1.png");
    c1->Clear();
    G_It2.Draw("AL");
    fIts->Draw("SAME");
    c1->SaveAs("It2.png");
    c1->Clear();
    G_It3.Draw("AL");
    fItp->Draw("SAME");
    c1->SaveAs("It3.png");
    c1->Clear();
    G_It4.Draw("AL");
    fItp->Draw("SAME");
    c1->SaveAs("It4.png");
    c1->Clear();

    vector<double> glassA;
    vector<double> glassB;
    glassA.push_back(000*(M_PI/180.));
    glassA.push_back(45*(M_PI/180.));
    glassA.push_back(90*(M_PI/180.));
    glassA.push_back(135*(M_PI/180.));
    glassA.push_back(180*(M_PI/180.));
    
    glassA.push_back(-90*(M_PI/180.));
    glassA.push_back(-45*(M_PI/180.));
    glassA.push_back(000*(M_PI/180.));
    glassA.push_back(45*(M_PI/180.));
    glassA.push_back(90*(M_PI/180.));

    glassB.push_back(((0.048+0.048)/2.)/0.0233);
    glassB.push_back(((0.032+0.033)/2.)/0.0231); 
    glassB.push_back(((0.0007+0.0008)/2.)/0.0231);
    glassB.push_back(((0.016+0.015)/2.)/0.0232);
    glassB.push_back(((0.049+0.048)/2.)/0.0233); 

    glassB.push_back(((0.0004+0.004)/2.)/0.0544);
    glassB.push_back(((0.020+0.019)/2.)/0.0544);
    glassB.push_back(((0.061+0.062)/2.)/0.0547);
    glassB.push_back(((0.028+0.028)/2.)/0.0537);
    glassB.push_back(((0.0004+0.0004)/2.)/0.0536);

    TGraph G_glass_S;
    TGraph G_glass_P;
    G_glass_S.SetMarkerColor(kBlue);
    G_glass_S.SetMarkerStyle(16);
    G_glass_P.SetMarkerColor(kBlue);
    G_glass_P.SetMarkerStyle(16);

    for(int i=0; i<5; ++i){
        G_glass_S.SetPoint(i,glassA[i],glassB[i]);
        G_glass_P.SetPoint(i,glassA[i+5],glassB[i+5]);
    }

    auto lFit = [&](double *x,double *p=nullptr){
    return p[0]+p[1]*fabs(cos(x[0]));
    };
    TF1 *fFit = new TF1("FIT", lFit, -10000,10000,2);

    G_glass_S.Fit(fFit);
    G_glass_S.Draw("APL");
    c1->SaveAs("Glass_s.png");
    fFit->Draw("SAME");
    c1->Clear();
    G_glass_P.Fit(fFit);
    G_glass_P.Draw("APL");
    fFit->Draw("SAME");
    c1->SaveAs("Glass_p.png");
    c1->Clear();

    return 0;
}