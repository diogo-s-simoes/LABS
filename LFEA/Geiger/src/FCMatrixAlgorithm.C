#include "FCMatrixAlgorithm.h"

void FCMatrixAlgorithm::GaussElimination(FCMatrix& M1, Vec& V1){
    int nr = M1.nRows();
    int nc = M1.nCols();
    int drow;
    double lambda;
    for(int i = 0; i<nr-1; ++i){
        drow=M1.GetColMax(i);
        if(drow>i){
            (M1).swapRows(drow,i);
            V1.swap(drow,i);
        }
        for	(int r=i+1;r<nr;r++){	
			lambda=(M1.GetRow(r))[i]/(M1.GetRow(i))[i];		//scaling	factor	
			(M1)[r]=(M1.GetRow(r))-((M1.GetRow(i))*lambda);		//calculate the new row-i	
			V1[r]=V1[r]-(V1[i]*lambda);		//calculate new	vector	v	index-i
        }	
    }
}

FCMatrixFull FCMatrixAlgorithm::LUdecomposition(FCMatrix& M1){
    int n = M1.nRows();
    Vec v0(n,0.0);
    vector<Vec> Vu;
    vector<Vec> Vl;
    for (int i = 0; i<n; ++i){
        Vu.push_back(v0);
        Vl.push_back(v0);
        Vl[i][i]=1;
    }
    FCMatrixFull L(Vl);
    FCMatrixFull U(Vu);

    //setup of L and U matrices ^^^^^^^

    for (int i = 0; i<n;++i){
        for(int j = i; j<n; ++j){
            U[i][j]=M1[i][j];
            for(int k = 0; k<i; ++k){
                U[i][j]=U[i][j]-L[i][k]*U[k][j];
            }
        }
        for(int j = i+1; j<n; ++j){
            L[j][i]=M1[j][i];
            for(int k = 0; k<i; ++k){
                L[j][i]=L[j][i]-L[j][k]*U[k][i];
            }
            L[j][i]=L[j][i]/U[i][i];
        }
    }
    M1=U;
    return L;
}