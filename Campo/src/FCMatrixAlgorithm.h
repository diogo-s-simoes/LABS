#ifndef __FCMA__
#define __FCMA__
#include <iostream>
#include <vector>
#include <cmath>
#include "Vec.h"
#include "FCMatrix.h"
#include "FCMatrixFull.h"

using namespace std;

class FCMatrixAlgorithm{
    public:
    
    static void GaussElimination(FCMatrix& M1, Vec& V1);
    static FCMatrixFull LUdecomposition(FCMatrix& M1);

};
#endif