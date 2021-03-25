#include "LETintegral.h"
#include <iostream>

LETintegral::LETintegral(vector<vector<double>> fV){
    V=fV;
}

LETintegral::~LETintegral(){
    delete &V;
}

int cmpfunc0(const void* a, const void* b){ 
	vector<double> *n1= (vector<double>*)a;
	vector<double> *n2= (vector<double>*)b;
    if((*n1)[0] < (*n2)[0]) return -1; 
    else if((*n1)[0] > (*n2)[0]) return 1;
    else return 0;
}

int cmpfunc1(const void* a, const void* b){ 
	vector<double> *n1= (vector<double>*)a;
	vector<double> *n2= (vector<double>*)b;
    if((*n1)[1] < (*n2)[1]) return -1; 
    else if((*n1)[1] > (*n2)[1]) return 1;
    else return 0;
}

int cmpfunc2(const void* a, const void* b){ 
	vector<double> *n1= (vector<double>*)a;
	vector<double> *n2= (vector<double>*)b;
    if((*n1)[2] < (*n2)[2]) return -1; 
    else if((*n1)[2] > (*n2)[2]) return 1;
    else return 0;
}

int cmpfunc3(const void* a, const void* b){ 
	vector<double> *n1= (vector<double>*)a;
	vector<double> *n2= (vector<double>*)b;
    if((*n1)[3] < (*n2)[3]) return -1; 
    else if((*n1)[3] > (*n2)[3]) return 1;
    else return 0;
}

void LETintegral::order(int var){
	if(var==0)
    qsort(&V[0],V.size(),sizeof(V[0].size()),cmpfunc0);
    if(var==1)
    qsort(&V[0],V.size(),sizeof(V[0].size()),cmpfunc1);
    if(var==2)
    qsort(&V[0],V.size(),sizeof(V[0].size()),cmpfunc2);
    if(var==3)
    qsort(&V[0],V.size(),sizeof(V[0].size()),cmpfunc3);
}

double LETintegral::integrate(int y, int x){
    double res = 0;
    order(x);
    for(int i = 0; i<V.size()-1; ++i){
        res+=(V[i][y]+V[i+1][y])/2*(V[i+1][x]-V[i][x]);
    }
    return res;
}