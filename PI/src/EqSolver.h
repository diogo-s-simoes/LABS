#ifndef __EQSV__
#define __EQSV__
#include <iostream>
#include <vector>
#include <cmath>
#include "Vec.h"
#include "FCMatrix.h"
#include "FCMatrixFull.h"
#include "FCMatrixBanded.h"

using namespace std;

class EqSolver{
    public:
    EqSolver();
    EqSolver(const FCMatrix& M1, const Vec& V1);

    void SetConstants(const Vec& V1);
    void SetMatrix(const FCMatrix& M1);

    Vec GaussEliminationSolver();
    Vec LUdecompositionSolver();
    
    private:
    //FCMatrixFull LUdecomposition(FCMatrix& M1);
    //void GaussElimination(FCMatrix& M1, Vec& V1);
    FCMatrix* M;
    Vec b;
};
#endif