

auto l2Dfit = [&](double *x,double *p=nullptr){
  double mu=;
  double l=.48;
  double A=16*1e-6;
  double n1=600;
  double n2=72;
  double V=.48*16*1e-6;
  double a;
  double ex=1.;

    return (x[0]*x[0]*p[0]*n1*-x[1]*x[1]*(p[0]*n2+R))/(V*a*pow(n1*n1*p[0]*V1-n2*(n2*p[0]+R)*V2,ex))*l/A/mu;
};

TF2 *f2Dfit= new TF2("F", l2Dfit, -1e6,1e6,-1e6,1e6,1);

TGraph2D G2D;

G2D.Fit(f2Dfit);