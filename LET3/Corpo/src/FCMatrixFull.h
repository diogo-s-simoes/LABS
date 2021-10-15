#ifndef __FCMF__
#define __FCMF__
#include <iostream>
#include <vector>
#include <cmath>
#include "Vec.h"
#include "FCMatrix.h"

using namespace std;

class FCMatrixFull : public FCMatrix{
    public:
    FCMatrixFull();
    FCMatrixFull(double** fM, int fm, int fn);
    FCMatrixFull(double* fM, int fm, int fn);
    FCMatrixFull(const vector<Vec>& V);
    ~FCMatrixFull();

    Vec& operator[](int i);
    FCMatrixFull& operator=(FCMatrix& M2);
    FCMatrixFull operator+(const FCMatrix& M2);
    FCMatrixFull operator-(const FCMatrix& M2);
    FCMatrixFull operator*(const FCMatrix& M2);
    Vec operator*(Vec& V1);
    FCMatrixFull operator*(double b);
    
    int nRows() const;
    int nCols() const;
    Vec GetRow(int i = 0) const;
    Vec GetCol(int j = 0) const;
    double determinant() const;
    int GetRowMax(int i = 0) const;
    int GetColMax(int j = 0) const;
    void swapRows(int i1, int i2);

    void Print() const;
};
#endif