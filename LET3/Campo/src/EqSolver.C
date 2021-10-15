#include "EqSolver.h"
#include "FCMatrixAlgorithm.h"

EqSolver::EqSolver(){}

EqSolver::EqSolver(const FCMatrix& M1, const Vec& V1){
    if (M1.GetClassname()=="FCMatrixFull"){
        M=new FCMatrixFull;
    }
    if (M1.GetClassname()=="FCMatrixBanded"){
        M=new FCMatrixBanded;
    }
    *M=M1;
    b=V1;
}

void EqSolver::SetConstants(const Vec& V1){
    b=V1;
}

void EqSolver::SetMatrix(const FCMatrix& M1){
    *M=M1;
}

Vec EqSolver::GaussEliminationSolver(){

    FCMatrixAlgorithm::GaussElimination(*M,b);

    Vec x(M->nCols());
    double minus;
    for(int i = (M->nCols())-1; i>=0; --i){
        minus = 0;
        for(int n = i+1; n<M->nCols(); ++n){
            minus+=(((M->GetRow(i))[n])*(x[n]));
            //cout<<n<<endl;
        }
        x[i]=(b[i]-minus)/(M->GetRow(i))[i];
        //cout<<i<<endl;
    }
    return x;
}

Vec EqSolver::LUdecompositionSolver(){
    int n = M->nCols();
    Vec x(n);
    Vec y(n);
    FCMatrixFull L = FCMatrixAlgorithm::LUdecomposition(*M);
    double minus;

    for(int i = 0; i<n; ++i){
        minus = 0;
        for(int n = 0; n<i; ++n){
            minus+=L[i][n]*y[n];
        }
    y[i]=(b[i]-minus)/L[i][i];
    }

    for(int i = (M->nCols())-1; i>=0; --i){
        minus = 0;
        for(int n = i+1; n<M->nCols(); ++n){
            minus+=(((*M)[i][n])*(x[n]));
        }
        x[i]=(y[i]-minus)/(*M)[i][i];
    }
    return x;    
}