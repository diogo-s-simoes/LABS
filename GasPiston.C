#include "LETintegral.h"

int main(){
    vector<double> t;
    vector<double> V;
    vector<double> P;
    vector<double> T;

    vector<double> aux;
    vector<vector<double>> G;

    for (int i = 0; i<t.size(); ++i){
        aux[0]=t[i];
        aux[1]=V[i];
        aux[2]=P[i];
        aux[3]=T[i];
        G.push_back(aux);
    }
    return 0;
}
