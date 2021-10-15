#include "ODEpoint.h"

using namespace std;

ODEpoint::ODEpoint(){
    t=0;
    Ndim=0;
}   

ODEpoint::~ODEpoint(){
    var.clear();
}

ODEpoint::ODEpoint(double tval, double* funct, int Ndimf){
    t=tval;
    Ndim=Ndimf;
    for (int i = 0; i<Ndim; ++i){
        var.push_back(funct[i]);
    }
} 

ODEpoint::ODEpoint(double tval, vector<double> funct){
    t=tval;
    var=funct;
    Ndim=var.size();
} 

ODEpoint::ODEpoint(const ODEpoint& P){
    t=P.t;
    Ndim=P.Ndim;
    var=P.var;
}

vector<double> ODEpoint::Get_Var_vec() const{
    return var;
}   

double* ODEpoint::Get_Var_ptr() const{
    double* a = new double[Ndim];
    for (int i = 0; i<Ndim; ++i){
        a[i]=var[i];
    }
    return a;
}  

double* ODEpoint::Get_VarTime() const{
    double* a = new double[Ndim+1];
    for (int i = 0; i<Ndim; ++i){
        a[i]=var[i];
    }
    a[Ndim]=t;
    return a;
}

int ODEpoint::GetNdim() const{
    return Ndim;
}   

double ODEpoint::Get_Time() const{
    return t;
}   

void ODEpoint::Set_Time(double tval){
    t = tval;
}  

void ODEpoint::Set_Var(vector<double> funct){
    var = funct;
    Ndim = var.size();
}   

//operators
ODEpoint& ODEpoint::operator=(const ODEpoint& P){
    var=P.var;
    Ndim=P.Ndim;
    t=P.t;
}

const double& ODEpoint::operator[](int i) const{
    return var[i];
}  

double& ODEpoint::operator[](int i){
    return var[i];
}

void ODEpoint::Print() const{
    cout<<"t = "<<t<<endl;
    for (int i = 0; i<Ndim; ++i){
        cout<<"var "<<i<<" = "<<var[i]<<endl;
    }
}