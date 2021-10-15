#ifndef __DataPoints__
#define __DataPoints__

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include <cstdio>
#include "TAxis.h"

using namespace std;

class DataPoints {
    
    public:

    DataPoints();
    DataPoints(unsigned int fN, const double* fx, const double* fy);
    virtual ~DataPoints();

    virtual double Interpolate(double xval) {return 0.;}
    virtual void Draw() const;
    const TGraph& GetGraph() const;

    friend std::ostream& operator<< (std::ostream&, const DataPoints&);
    virtual void Print(string FILE);
    
    protected:
    int N;
    double *x, *y;

    TGraph* gPoints;

    double xmin, xmax;
    double ymin, ymax;

    void SetMinMaxX();
    void SetMinMaxY();
};
#endif
