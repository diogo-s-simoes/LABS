#ifndef _FCMatrixBanded_H
#define _FCMatrixBanded_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "FCMatrix.h"
#include "FCMatrixFull.h"

class FCMatrixBanded : public FCMatrix {
	public:
		// constructors
		FCMatrixBanded();
		FCMatrixBanded(double** fM, int fm, int fn=0);
		FCMatrixBanded(double* fM, int fm, int fn=0);
		FCMatrixBanded(vector<Vec> v);// copy constructor
		FCMatrixBanded(const FCMatrixBanded &M2);
		~FCMatrixBanded(){};

		// operators
		FCMatrixBanded& operator=(const FCMatrixBanded &A) ; // equal 2 matrices of any kind
		FCMatrixBanded operator+(const FCMatrixBanded &A) const;
		FCMatrixFull operator+(const FCMatrixFull &B) const; // add 2 matrices of any kind
		FCMatrixFull convert_2Full() const;
		FCMatrixBanded operator-(const FCMatrixBanded &A) const; // sub 2 matrices of any kind
		FCMatrixFull operator-(const FCMatrixFull &A) const;
		FCMatrixBanded operator*(double lambda) const; // mul matrix of any kind by scalar
        FCMatrixFull operator*(const FCMatrix& A) const;
		
		Vec& operator[] (int i);
		Vec GetDiagonal(int i) const;


		// virtual inherited...
		int nRows() const;
		int nCols() const;
		int GetRowMax(int i) const;
		int GetColMax(int i) const;

		Vec GetRow(int i) const; // retrieve row i
		Vec GetCol(int i) const; // retrieve column i...

		double determinant() const;

		void Print() const;

        void swapRows(int i1, int i2);


	};

#endif