#ifndef __FCM__
#define __FCM__
#include <iostream>
#include <vector>
#include <cmath>
#include "Vec.h"

using namespace std;

class FCMatrix{
    public:
    FCMatrix();
    FCMatrix(double** fM, int fm, int fn);
    FCMatrix(double* fM, int fm, int fn);
    FCMatrix(const vector<Vec>& V);
    ~FCMatrix(){};

    virtual Vec& operator[](int i) = 0;
    
    virtual int nRows() const = 0;
    virtual int nCols() const = 0;
    virtual Vec GetRow(int i = 0) const = 0;
    virtual Vec GetCol(int j = 0) const = 0; 
    virtual double determinant() const = 0;
    virtual int GetRowMax(int i = 0) const = 0;
    virtual int GetColMax(int j = 0) const = 0;
    virtual void swapRows(int, int)=0;

    virtual void Print() const = 0;
    
    string GetClassname() const;

    protected:
    vector<Vec> M;
    string classname;
};
#endif