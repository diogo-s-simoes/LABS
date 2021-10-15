#ifndef __ODEPOINT__
#define __ODEPOINT__

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

class ODEpoint{ 
	
    public: 
	
    ODEpoint();//default constructor   
	~ODEpoint();//destructor 
	ODEpoint(double tval, double* funct, int Ndimf); //using double * 
	ODEpoint(double tval, vector<double> funct); //using vector<double> 
	ODEpoint(const ODEpoint&); //copy constructor   //member access functions

	vector<double> Get_Var_vec() const; //return the y1,...,yNdim dependent variables   
	double* Get_Var_ptr() const; //samebut as double *  
	double* Get_VarTime() const; //first the y1,...,yNdim then t
	int GetNdim() const; //return the number of dependent variables   
	double Get_Time() const; //return only the independent variable (t)   
	void Set_Time(double tval); //Set independent variable   
	void Set_Var(vector<double> funct);   

	//operators
	ODEpoint & operator=(const ODEpoint& P); 
	const double& operator[](int i) const;  
	double& operator[] (int i);

	void Print() const; 

	private:   
	
    double t;   
	vector<double> var; 
	int Ndim;
}; 
#endif
