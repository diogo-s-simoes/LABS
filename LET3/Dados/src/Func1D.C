#include "Func1D.h"
#include "TApplication.h"
#include "TCanvas.h"
#include <iostream>

using namespace std;

Func1D::Func1D(const TF1* fp) : f(nullptr) {
  if (fp) {
    f = new TF1(*fp);
    Settings();
  }
}

Func1D::Func1D(const TF1& fp) : Func1D(&fp) {};

Func1D::Func1D(const Func1D& A): f(A.f){};


Func1D::~Func1D() {
  if (f) delete f;
}


/////////////////// methods

void Func1D::Settings() {
  f->SetNpx(1000);
  f->SetLineColor(38);
  f->SetLineWidth(4);
}

double Func1D::Eval(double xval) const {
  return f->Eval(xval);
}

void Func1D::Draw() const {
  TApplication A("A",0,0);
  TCanvas c("c", "Func1D canvas", 0, 0, 1000, 800);
  f->Draw();
  c.Update();
  A.Run();
}