#include "NewtonInterpolator.h"

using namespace std;

NewtonInterpolator::NewtonInterpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) :
DataPoints(fN, fx, fy),
F0(nullptr),
cInterpolator(nullptr) {
  if (fF0) F0 = new TF1(*fF0);
  FInterpolator = new TF1("FInterpolator", this, &NewtonInterpolator::fInterpolator, xmin, xmax, 0);
}

NewtonInterpolator::~NewtonInterpolator() {
  if (FInterpolator) delete FInterpolator;
  if (F0) delete F0;
  if (cInterpolator) delete cInterpolator;
}

NewtonInterpolator::NewtonInterpolator(const NewtonInterpolator& LI) :
NewtonInterpolator(LI.N, LI.x, LI.y, LI.F0) {;}

double NewtonInterpolator::Interpolate(double xval) const{
    double result=0.;
	double A,aux=1.0;
	int i;
	//First Value of the polynomial
	A=y[0];

	for(int k=1;k<N;k++){
		for (i=0;i<k;i++)
		{
			aux*=(xval-x[i]);
		}
		
			A+=DiffTable(0,k)*aux;

			aux=1.0;
	}
	return A;
}

double NewtonInterpolator::DiffTable(int i,int j) const{
	if(i==j){
	    return y[i];
    }
	else{
	    return (DiffTable(i+1,j)-DiffTable(i,j-1))/(x[j]-x[i]);
	}
}

void NewtonInterpolator::Draw() const {
  DataPoints::Draw();
  FInterpolator->SetLineColor(28);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
}

const TCanvas& NewtonInterpolator::GetCanvas()  {
  cInterpolator = new TCanvas("cInterpolator","", 0,0,800,600);
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
  return *cInterpolator;
}

void NewtonInterpolator::SetFunction(const TF1* fF0) {
  if (fF0) F0 = new TF1(*fF0);
}

//////////////////////////////////////// output

std::ostream& operator<< (std::ostream& s, const NewtonInterpolator& LI) {
  s << "Newton Interpolator " << "x:[" << LI.xmin << "," << LI.xmax << "]" << std::endl;
  for (int i=0; i<LI.N; ++i) {
    s << std::fixed << std::setprecision(3)
      << "(" << LI.x[i] << "," << LI.y[i] << ") f(x)=" << LI.Interpolate(LI.x[i]) << " " ;
  }
  s << "\n";
  return s;
}

void NewtonInterpolator::Print(string FILE) {
  fstream file;
  file.open(FILE, ios::out);
  file<<"[Newton::Print]: "<<endl;
  for (int i=0; i<N; i++) {
    file<<"[Newton] (x="<<x[i]<<", y="<<y[i]<<") "<<endl;;  
  }
  file<<endl;
  file<<FInterpolator<<endl;
  file<<endl;
  file<<"FILE: "<<FILE.c_str()<<endl;
  file.close();
}