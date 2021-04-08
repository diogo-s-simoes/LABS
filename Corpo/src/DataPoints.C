#include "DataPoints.h"

DataPoints::DataPoints() :
N(0), // nb of elements = 0
x(nullptr), y(nullptr), // set null pointers
  gPoints(nullptr) {};

DataPoints::DataPoints(unsigned int fN, const double* fx, const double* fy) : N(fN), x(new double[N]), y(new double[N]) {
  // manage wrong args
  if (!fx || !fy)
    throw std::invalid_argument(Form("[%s] null arrays!!!", __PRETTY_FUNCTION__));

  // copy arrays
  std::copy(fx, fx+N, x);
  std::copy(fy, fy+N, y);

  //retrieve min and max values
  SetMinMaxX();
  SetMinMaxY();

  // create graph
  gPoints = new TGraph(N, x, y);
  gPoints->SetMarkerStyle(20);
  gPoints->SetMarkerColor(kRed+2);
  gPoints->SetMarkerSize(1.5);

  gPoints->GetXaxis()->SetRangeUser(xmin-0.1*fabs(xmin), xmax+0.1*fabs(xmax));
  gPoints->GetYaxis()->SetRangeUser(ymin-0.1*fabs(ymin), ymax+0.1*fabs(ymax));
}

DataPoints::~DataPoints(){
    delete [] x;
    delete [] y;
    delete gPoints;
}

void DataPoints::Draw() const {
  gPoints->Draw("AP");
}


const TGraph& DataPoints::GetGraph() const {
  return *gPoints;
}

void DataPoints::SetMinMaxX() {
  auto it = std::minmax_element(x, x+N);
  xmin = *it.first;
  xmax = *it.second;
  cout<<"xmin: "<<xmin<<" xmax: "<<xmax<<endl;
}

void DataPoints::SetMinMaxY() {
  auto it = std::minmax_element(y, y+N);
  ymin = *it.first;
  ymax = *it.second;
  cout<<"ymin: "<<ymin<<" ymax: "<<ymax<<endl;
}

std::ostream& operator<< (std::ostream& s, const DataPoints& D) {
  s << "Nb points stored: " << D.N << std::endl;
  for (int i=0; i<D.N; ++i) {
    s << std::fixed << std::setprecision(3)
      << "(" << D.x[i] << "," << D.y[i] << ")" ;
  }
  return s;
}

void DataPoints::Print(string FILE) {
  fstream file;
  file.open(FILE, ios::out);
  file<<"[Datapoints::Print]: "<<endl;;
  for (int i=0; i<N; i++) {
    file<<"[Datapoints] (x="<<x[i]<<", y="<<y[i]<<") "<<endl;;  
  }
  file<<endl;
  file<<"FILE: "<<FILE.c_str()<<endl;
  file.close();
}