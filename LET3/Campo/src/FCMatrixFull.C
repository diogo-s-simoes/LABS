#include "FCMatrixFull.h"
#include "FCMatrixAlgorithm.h"

using namespace std;
    
FCMatrixFull::FCMatrixFull(){
    classname="FCMatrixFull";
    Vec v0;
    M.push_back(v0);
}

FCMatrixFull::~FCMatrixFull(){}

FCMatrixFull::FCMatrixFull(double** fM, int fm, int fn){
    classname="FCMatrixFull";
    for (int i = 0; i<fm; ++i){
        M.push_back(Vec(fn,fM[i]));
    }
}

FCMatrixFull::FCMatrixFull(double* fM, int fm, int fn){
    classname="FCMatrixFull";
    Vec v(fn);
    for (int i = 0; i< fm; ++i){
        for (int j = 0; j<fn; ++j){
            v[j]=fM[i*fn+j];
        }
        M.push_back(v);
    }
}

FCMatrixFull::FCMatrixFull(const vector<Vec>& V){
    classname="FCMatrixFull";
    M=V;
}

Vec& FCMatrixFull::operator[](int i){
    return M[i];
}

FCMatrixFull& FCMatrixFull::operator=(FCMatrix& M2){
    for(int i = 0; i<M2.nRows(); ++i){
        M.push_back(M2.GetRow(i));
    }
    return *this;
}

FCMatrixFull FCMatrixFull::operator+(const FCMatrix& M2){
    int n = this->nCols();
    Vec v(n);
    vector<Vec> Va;
    for(int i = 0; i<M2.nRows(); ++i){
        for(int j = 0; j<M2.nCols(); ++j){
            v[j]=M[i][j]+M2.GetRow(i)[j];
        }   
        Va.push_back(v);
    }
    FCMatrixFull Ma(Va);
    return Ma;
}

FCMatrixFull FCMatrixFull::operator-(const FCMatrix& M2){
    int n = this->nCols();
    Vec v(n);
    vector<Vec> Va;
    for(int i = 0; i<M2.nRows(); ++i){
        for(int j = 0; j<M2.nCols(); ++j){
            v[j]=M[i][j]-M2.GetRow(i)[j];
        }   
        Va.push_back(v);
    }
    FCMatrixFull Ma(Va);
    return Ma;
}

FCMatrixFull FCMatrixFull::operator*(const FCMatrix& M2){
    int n = this->nCols();
    Vec v(n);
    vector<Vec> Va;
    for(int i = 0; i<this->nRows(); ++i){
        for(int j = 0; j<M2.nCols(); ++j){
            v[j]=(this->GetRow(i)).dot(M2.GetCol(j));
        }
        Va.push_back(v);
    }
    FCMatrixFull Ma(Va);
    return Ma;
}

Vec FCMatrixFull::operator*(Vec& V1){
    Vec v(V1.size());
    for(int i = 0; i<this->nRows(); ++i){
        v[i]=M[i].dot(V1);
    }
    return v;
}

FCMatrixFull FCMatrixFull::operator*(double b){
    FCMatrixFull Ma(M);
    for(int i = 0; i<this->nRows(); ++i){
        for(int j = 0; j<this->nCols(); ++j){
            Ma[i][j]=M[i][j]*b;
        }
    }
    return Ma;
}

int FCMatrixFull::nRows() const{
    return M.size();
}

int FCMatrixFull::nCols() const{
    return M[0].size();
}

Vec FCMatrixFull::GetRow(int i) const{
    return M[i];
}

Vec FCMatrixFull::GetCol(int j) const{
    Vec v(M.size());
    for(int i = 0; i < M.size(); ++i){
        v[i]=M[i][j];
    }
    return v;
}

double FCMatrixFull::determinant() const{
    FCMatrixFull M1(M);
    FCMatrixAlgorithm::LUdecomposition(M1);
    double det = 1;
    for (int i = 0; i<M1.nRows(); ++i){
        det*=M[i][i];
    }
    return det;
}

int FCMatrixFull::GetRowMax(int i) const{
    double k = 0;
    int J;
    int n=M[0].size();
    for(int j = 0; j<n; ++j){
        if(fabs(M[i][j])>k){
            k=fabs(M[i][j]);
            J=j;
        }
    }
    return J;
}

int FCMatrixFull::GetColMax(int j) const{
    double k = 0;
    int I = 0;
    int m=M.size();
    for(int i = 0; i<m; ++i){
        if(fabs(M[i][j])>=k){
            k=fabs(M[i][j]);
            I=i;
        }
    }
    return I;
}

void FCMatrixFull::Print() const{
    for(int i = 0; i<this->nRows(); ++i){
        cout<<M[i]<<endl;
    }
}

void FCMatrixFull::swapRows(int i1, int i2){
    Vec aux(M[i1]);
    M[i1]=M[i2];
    M[i2]=aux;
}