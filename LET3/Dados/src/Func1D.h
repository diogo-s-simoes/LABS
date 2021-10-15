#ifndef __Func1D__
#define __Func1D__

#include "TF1.h"

class Func1D {

 public:
  // constructor, destructor
  Func1D(const TF1* fp=nullptr);
  Func1D(const TF1&);
  Func1D(const Func1D&);
  virtual ~Func1D();

  // drawing
  void Draw() const;

  // evaluate
  double Eval(double) const;
  
 protected:

  void Settings();
  
  TF1* f;
  
};


#endif