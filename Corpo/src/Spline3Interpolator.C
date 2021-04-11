#include "Spline3Interpolator.h"
#include "EqSolver.h"
#include "FCMatrixFull.h"
#include <fstream>


Spline3Interpolator::Spline3Interpolator(int n, double *arrx, double *arry,TF1* fF0): 
DataPoints(n, arrx, arry), 
F0(nullptr),
cInterpolator(nullptr) { 
  if (fF0){F0 = new TF1(*fF0);}

  K = new double[N];

  SetCurvatureLines();

  FInterpolator = new TF1("FInterpolator", this, &Spline3Interpolator::fInterpolator, xmin, xmax, 0);
 }


Spline3Interpolator::~Spline3Interpolator(){
  if(F0) delete F0;
  if(FInterpolator) delete FInterpolator;
  if(cInterpolator) delete cInterpolator;
  if(K) delete K;
}

Spline3Interpolator::Spline3Interpolator(const Spline3Interpolator& A):
Spline3Interpolator(A.N, A.x, A.y, A.F0){;}


void Spline3Interpolator::SetResolution(int n) const{
  F0->SetNpx(n);
  FInterpolator->SetNpx(n);
}


TF1* Spline3Interpolator::GetInterpolationFunction() const{
  return FInterpolator;
}

const TCanvas& Spline3Interpolator::GetCanvas(){
  cInterpolator = new TCanvas("cInterpolator","", 0,0,800,600);
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
  return *cInterpolator;
}

//void Spline3Interpolator::Print(std::string FILE) const{
  //std::cout << "a" << std::endl;
  /*std::ofstream myfile(FILE);

  if(myfile.is_open()){
   // myfile<<FInterpolator<<std::endl;
    myfile<<N<<std::endl;
    for(int i=0;i<N;i++)
      myfile<<(x[i])<<" "<<(y[i])<<std::endl;
  }
  myfile.close();*/
//}


std::ostream& operator<< (std::ostream& s, const Spline3Interpolator& A){

  s << "Spline3Interpolator. Interval:" << " x=[" << A.xmin << ";" << A.xmax<<"]"<<std::endl;
  for(int i=0; i<A.N; i++){
    s << std::fixed << std::setprecision(3) <<"(" <<A.x[i] << ","<< A.y[i] << ")"<<std::endl;
  }
  return s;


}

void Spline3Interpolator::Draw(){
  DataPoints::Draw();
  FInterpolator->SetLineColor(kBlue);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
}


void Spline3Interpolator::SetCurvatureLines(){

    Vec auxi(N-2);
    vector<Vec> auxi2;
    for (int i=0; i<N-2;++i){
        auxi2.push_back(auxi);
    }

  FCMatrixFull curv(auxi2);
  //curv.ZeroFill(N-2,N-2);

  for(int i=0;i<N-3;i++){
    curv[i][i]=2*(x[i]-x[i+2]);
    curv[i][i+1]=(x[i]-x[i+1]);
    curv[i+1][i]=(x[i+1]-x[i+2]);
  }
  curv[N-3][N-3]=2*(x[N-3]-x[N-1]);
  

  Vec Coefs(N-2);


  for(int i=0;i<N-2;i++)
    Coefs[i]=(6*((y[i]-y[i+1])/(x[i]-x[i+1])-(y[i+1]-y[i+2])/(x[i+1]-x[i+2])));
  

  EqSolver Ksolver(curv,Coefs);

  Coefs=Ksolver.GaussEliminationSolver();


  K[0]=0;
  K[N-1]=0;

  for(int i=0;i<Coefs.size();i++)
    K[i+1]=Coefs[i];
}


double Spline3Interpolator::Interpolate(double c){
 int minm;
  for(int i=0;i<N;i++){
    if(x[i]>c){
      minm=i-1;
      break;
    } 
  }

  double P=0;

  //cout<<minm<<endl;


  P=K[minm]/6*((c-x[minm+1])*(c-x[minm+1])*(c-x[minm+1])/(x[minm]-x[minm+1])-(c-x[minm+1])*(x[minm]-x[minm+1]))
  - K[minm+1]/6*((c-x[minm])*(c-x[minm])*(c-x[minm])/(x[minm]-x[minm+1])-(c-x[minm])*(x[minm]-x[minm+1]))
  + (y[minm]*(c-x[minm+1])-y[minm+1]*(c-x[minm]))/(x[minm]-x[minm+1]);


  return P;

}