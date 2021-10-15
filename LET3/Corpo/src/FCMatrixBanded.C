#include "FCMatrixBanded.h"

using namespace std;

FCMatrixBanded::FCMatrixBanded()
{
	classname="FCMatrixBanded";

	Vec v0;
	Vec v1(2);
	Vec v2;
	M.push_back(v0);
	M.push_back(v1);
	M.push_back(v2);

}

FCMatrixBanded::FCMatrixBanded(double** fM, int fm, int fn){
	classname="FCMatrixBanded";

	Vec ud(fm-1,fM[0]);
	Vec d(fm,fM[1]);
	Vec ld(fm-1,fM[2]);

	M.push_back(ud);
	M.push_back(d);
	M.push_back(ld);
}

FCMatrixBanded::FCMatrixBanded(double*fM, int fm, int fn){
	
	classname="FCMatrixBanded";

	Vec ud(fm-1);
	Vec d(fm);
	Vec ld(fm-1);

	for(int i=0; i<fm-1;++i)
		ud[i]=fM[i];

	for(int j=0;j<fm;++j)
		d[j]=fM[fm-1+j];

	for(int k=0;k<fm-1;++k)
		ld[k]=fM[2*fm-1+k];

	M.push_back(ud);
	M.push_back(d);
	M.push_back(ld);


}

FCMatrixBanded::FCMatrixBanded(vector<Vec> v){

	classname="FCMatrixBanded";

	
	if(	(v[0].size()!=(v[1].size()-1) ) ||	(v[2].size()!=(v[1].size()-1) )	)
	{
		cout << "Nao tem o numero correto de elementos nas diagonais."  << endl;
		exit(EXIT_FAILURE);
	}

	//Fim dos testes

	M.push_back(v[0]);
	M.push_back(v[1]);
	M.push_back(v[2]);


}



FCMatrixBanded::FCMatrixBanded( const FCMatrixBanded &M2)
{
	//FAZER TESTES tipo checkar se o que recebe é uma banded

	if(M2.classname == "FCMatrixFull")
	{
		cout << "Nao pode igualar uma Full a uma Banded "<<endl;
		exit(EXIT_FAILURE);
	}

	//Fim do testes

	classname="FCMatrixBanded";

	M=M2.M;


}


FCMatrixFull FCMatrixBanded::operator+(const FCMatrixFull &B) const
{

	//Testes

	if((B.nRows())!=(this->nRows()) || (B.nCols())!=(this->nCols()))
	{
		cout << "Nao pode somar matrizes com dimensoes diferentes" << endl << "Retornando FCMatrixFull vazia" << endl << endl;
		FCMatrixFull Nada;
		return Nada;
	}

	//Fim dos testes

	FCMatrixFull F,Fsoma;
	
	
	F=this->convert_2Full();
	Fsoma=F+B;

	return Fsoma;
}

FCMatrixBanded FCMatrixBanded::operator+(const FCMatrixBanded &B) const
{

	//Testes

	if((B.nRows())!=(this->nRows()) || (B.nCols())!=(this->nCols()))
	{
		cout << "Nao pode somar matrizes com dimensoes diferentes" << endl << "Retornando FCMatrixFull vazia" << endl << endl;
		FCMatrixBanded Nada;
		return Nada;
	}

	//Fim dos testes

	FCMatrixBanded S;
	for(int i = 0; i<3; ++i){
		S[i]=this->GetDiagonal(i)+B.GetDiagonal(i);
	}
}

FCMatrixFull FCMatrixBanded::operator-(const FCMatrixFull &B) const
{
	//Testes

	FCMatrixFull F,Fsoma;
	if((B.nRows())!=(this->nRows()) || (B.nCols())!=(this->nCols()))
	{
		cout << "Nao pode somar matrizes com dimensoes diferentes" << endl << "Retornando FCMatrixFull vazia" << endl << endl;
		FCMatrixFull Nada;
		return Nada;
	}

	//Fim dos testes

	
	F=this->convert_2Full();
	Fsoma=F-B;

	return Fsoma;


}

FCMatrixBanded FCMatrixBanded::operator-(const FCMatrixBanded &B) const
{

	//Testes

	if((B.nRows())!=(this->nRows()) || (B.nCols())!=(this->nCols()))
	{
		cout << "Nao pode somar matrizes com dimensoes diferentes" << endl << "Retornando FCMatrixFull vazia" << endl << endl;
		FCMatrixBanded Nada;
		return Nada;
	}

	//Fim dos testes

	FCMatrixBanded S;
	for(int i = 0; i<3; ++i){
		S[i]=this->GetDiagonal(i)-B.GetDiagonal(i);
	}
}


	
FCMatrixFull FCMatrixBanded::operator*(const FCMatrix &A) const // mul 2 matrices of any kind
{
	//Testes

	FCMatrixFull F,Fprod;
	if((A.nRows())!=(this->nRows()) || (A.nCols())!=(this->nCols()))
	{
		cout << "Nao pode somar matrizes com dimensoes diferentes" << endl << "Retornando FCMatrixFull vazia" << endl << endl;
		FCMatrixFull Nada;
		return Nada;
	}

	//Fim dos testes

	
	F=this->convert_2Full();
	Fprod=F*A;

	return Fprod;

	
}
	

FCMatrixBanded FCMatrixBanded::operator*(double lambda) const // mul matrix of any kind by scalar	
{
	
	int nrows=this->nRows();
	Vec vaux;
	vector<Vec> aux;

	for(int i=0; i<nrows-1;i++)
	{
		vaux[i]=(GetDiagonal(0)[i]*lambda);
	}
	aux.push_back(vaux);
	for(int j=0; j<nrows;j++)
	{
		vaux[j]=(GetDiagonal(1)[j]*lambda);
	}
	aux.push_back(vaux);
	for(int i=0; i<nrows-1;i++)
	{
		vaux[i]=(GetDiagonal(0)[i]*lambda);
	}
	aux.push_back(vaux);

	
	FCMatrixBanded Sub(aux);
	return Sub;

}

FCMatrixFull FCMatrixBanded::convert_2Full() const{

	FCMatrixBanded B;
	B=*this;
	int nrows=B.nRows();
	if(nrows==1){
		Vec v1(1,B.GetDiagonal(1)[0]);
		vector<Vec> v2;
		v2.push_back(v1);
		FCMatrixFull AF(v2);
		return AF;
	}
	int ncols=B.nCols();
	Vec aux(ncols,0.);
	Vec aux1(ncols,0.);
	Vec aux2(ncols,0.);

	vector<Vec> v1;

	//Primeira Linha
	aux[0]=B.GetDiagonal(1)[0];
	
	aux[1]=B.GetDiagonal(0)[0];
	
	//Resto sao zeros;
	//Acrescentar ao vector
	v1.push_back(aux);

	for(int i=1;i<nrows-1;i++)
	{
		aux1[i-1]=B.GetDiagonal(2)[i-1];
		
		aux1[i]=B.GetDiagonal(1)[i];
		
		aux1[i+1]=B.GetDiagonal(0)[i];
		
		//Resto sao zeros;

		//Acrescentar ao vector
		v1.push_back(aux1);

		//Voltar aux1 a zeros
		for(int k=0; k<ncols-1; k++)
		
		{
			if(aux1[k]!=0)
				aux1[k]=0;
		}
	}
	//Ultima Linha
	aux2[nrows-1]=B.GetDiagonal(1)[nrows-1];
	aux2[nrows-2]=B.GetDiagonal(2)[nrows-2];
	//Resto sao zeros;
	//Acrescentar ao vector
	v1.push_back(aux2);

	FCMatrixFull F(v1);

	
	return F;


}

int FCMatrixBanded:: GetRowMax(int i) const
{
	double max=M[1][i];
	int index=i;

	if(index>(nCols()-1)|| index<0)
	{
		cout << "Indice inválido." << endl;
		exit(EXIT_FAILURE);
	}

	if(i==0)
	{
		if(M[0][i]>max)
			{
				max=M[0][i];
				index=i+1;
			}

		return index;
	}

	if(i==nRows()-1)
	{
		if(M[2][i-1]>max)
			{
				max=M[2][i-1];
				index=i-1;
			}

		return index;
	}

	if(M[0][i]>max)
	{
		max=M[0][i];
		index=i+1;
	}

	if(M[2][i-1]>max)
	{
		max=M[2][i-1];
		index=i-1;
	}


	return index;	
}

int FCMatrixBanded:: GetColMax(int i) const
{
	if(i>(nRows()-1)|| i<0)
	{
		cout << "Indice inválido." << endl;
		exit(EXIT_FAILURE);
	}

	double max=M[1][i];
	int index=i;

	if(i==0)
		{
			if(M[2][i]>max)
				{
					max=M[2][i];
					index=i+1;
				}

			return index;
		}

		if(i==nRows()-1)
		{
			if(M[0][i-1]>max)
				{max=M[0][i-1];
				}

			index=i-1;

			return index;
		}

		if(M[0][i-1]>max)
			{
				max=M[0][i-1];
				index=i-1;
			}

		if(M[2][i]>max)
			{
				max=M[2][i];
				index=i+1;

			}


	return index;	
}


Vec& FCMatrixBanded:: operator[](int i)
{
	if(i>2 || i<0)
	{
		cout << "Indice inválido." << endl;
		exit(EXIT_FAILURE);
	}

	return M[i];

}

int FCMatrixBanded::nRows() const
{
	Vec vaux(M[1]);
	return vaux.size();
}

int FCMatrixBanded::nCols() const{
	return M[1].size();
}

Vec FCMatrixBanded::GetRow(int i) const{

	if(i>(nRows()-1)|| i<0){
		cout << "Indice inválido." << endl;
		exit(EXIT_FAILURE);
	}

	Vec vrow(nCols());
	int index=0;

	if(i==0)
	{
		vrow[index]=M[1][i];
		++index;
		vrow[index]=M[0][i];
		++index;

		for(int l=0;l<nRows()-2;++l)
			{
				vrow[index]=0;
				++index;

			}

		return vrow;
	}

	if(i==nRows()-1)
	{
		for(int l=0;l<nRows()-2;++l)
			{
				vrow[index]=0;
				++index;
			}

		++index;
		vrow[index]=M[2][i-1];
		++index;
		vrow[index]=M[1][i];

		return vrow;
	}

	
	for(int k=0;k<i-1;++k)
		{
			vrow[index]=0;
			++index;
		}

		vrow[index]=M[2][i-1];
		++index;
		vrow[index]=M[1][i];
		++index;
		vrow[index]=M[0][i];
		++index;

		for(int l=0;l<nRows()-(i-1)-3;++l)
			{
				vrow[index+l]=0;

			}

	return vrow;

}


Vec FCMatrixBanded::GetCol(int i) const
{
	if(i>(nCols()-1)|| i<0)
	{
		cout << "Indice inválido." << endl;
		exit(EXIT_FAILURE);
	}

	Vec vrow(nRows());
	int index=0;

	if(i==0)
	{
		vrow[index]=M[1][i];
		cout<<M[1][i]<<endl;
		++index;
		vrow[index]=M[2][i];
		cout<<M[2][i]<<endl;
		++index;


		for(int l=0;l<nRows()-2;++l)
			{
				vrow[index]=0;
				++index;
			}


		return vrow;
	}

	if(i==nRows()-1)
	{
		for(int l=0;l<nRows()-2;++l)
			{
				vrow[index]=0;
				++index;
			}

		vrow[index]=M[0][i-1];
		++index;
		vrow[index]=M[1][i];

		return vrow;
	}

	
	for(int k=0;k<i-1;++k)
		{
			vrow[index]=0;
			++index;
		}

		vrow[index]=M[0][i-1];
		++index;
		vrow[index]=M[1][i];
		++index;
		vrow[index]=M[2][i];
		++index;

		for(int l=0;l<nRows()-(i-1)-3;++l)
			{
				vrow[index+l]=0;

			}

	return vrow;

}
/*
Vec FCMatrixBanded::GetCol(int i) const
{
	Vec vcol(nCols());

	int index=0;
	for(int k=0;k<i-1;++k)
		{
			vcol[k]=0;
			index=k;
		}

		++index;
		vcol[index]=M[2][i-1];
		++index;
		vcol[index]=M[1][i];
		++index;
		vcol[index]=M[0][i];
		++index;

		for(int l=0;l<nRows()-(i-1)-3;++l)
			{
				vcol[index+l]=0;

			}

	return vrow;

}*/

void FCMatrixBanded::Print() const
{
	//fazer setprecision e setw
	if(nRows()==1)
	{
		cout<<"|"<<setw(15)<<M[1][0]<<setw(15)<<"|"<<endl;
		//cout<<"vim aqui, tho";
	}
	else
	{
		cout<<"|"<<setw(15)<<setprecision(3)<<M[1][0]<<setw(15)<<M[0][0];

		for(int i=0;i<nRows()-2;++i)
			cout<<setw(15)<<"0";
		cout<<setw(15)<<"|"<<endl;

		for(int j=1;j<nRows()-1;++j)
		{
			cout<<"|";

			for(int k=0;k<j-1;++k)
				cout<<setw(15)<<"0";

			cout<<setw(15)<< setprecision(3) <<M[2][j-1]<<setw(15)<<M[1][j]<<setw(15)<<M[0][j];

			for(int l=0;l<nRows()-(j-1)-3;++l)
				{
					cout<<setw(15)<<"0";

				}

			cout<<setw(15)<<"|"<<endl;

		}
		cout<<"|";
		for(int i=0;i<nRows()-2;++i)
			cout<<setw(15)<<"0";

		cout<<setw(15)<< setprecision(3) <<M[2][nRows()-2]<<setw(15)<<M[1][nRows()-1]<<setw(15)<<"|"<<endl<<endl;
	}
}

Vec FCMatrixBanded::GetDiagonal(int i) const
{
	if(i>2|| i<0)
	{
		cout << "Indice inválido." << endl;
		exit(EXIT_FAILURE);
	}

	return M[i];
}

FCMatrixBanded& FCMatrixBanded:: operator=(const FCMatrixBanded & A)
{
	//Teste para ver se posso igualar



	M.clear();

	for(int i=0;i<3;i++)
	{

		M.push_back(A.GetDiagonal(i));
	}
	
	return *this;


}

double FCMatrixBanded::determinant() const{
	int n=nRows();

	double* f=new double[n+1];
	f[0]=1;
	f[1]=M[1][0];

	for (int i=2;i<n+1; i++){
		f[i]=M[1][i-1]*f[i-1]-M[2][i-2]*M[0][i-2]*f[i-2];
	}

	double det=f[n];

	delete[] f;
	return det;

}

void FCMatrixBanded::swapRows(int i1, int i2){
    double aux;
    for (int i = 0; i<3; ++i){
        aux=M[i][i1];
        M[i][i1]=M[i][i2];
        M[i][i2]=aux;
    }
}
