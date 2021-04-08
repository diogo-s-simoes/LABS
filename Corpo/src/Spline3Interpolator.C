#include "Spline3Interpolator.h"

using namespace std;

Spline3Interpolator::Spline3Interpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) :
DataPoints(fN, fx, fy),
F0(nullptr),
cInterpolator(nullptr) {
  if (fF0) F0 = new TF1(*fF0);
  FInterpolator = new TF1("FInterpolator", this, &Spline3Interpolator::fInterpolator, xmin, xmax, 0);
  FDerivator = new TF1("FDerivator", this, &Spline3Interpolator::fDerivator, xmin, xmax, 0);
  SetCurvatureLines();
  EvenlySpaced=false;
}

Spline3Interpolator::~Spline3Interpolator() {
  if (FInterpolator) delete FInterpolator;
  if (F0) delete F0;
  if (cInterpolator) delete cInterpolator;
  if (FDerivator) delete FDerivator;
}

Spline3Interpolator::Spline3Interpolator(const Spline3Interpolator& LI) :
Spline3Interpolator(LI.N, LI.x, LI.y, LI.F0) {;}


//Contains formula that calculates values of the segments
double Spline3Interpolator::SegmentCalc(double xval,int i) const{
	double result=K[i]/6*(  ( (xval-x[i+1])*(xval-x[i+1])*(xval-x[i+1]) )   /   (x[i]-x[i+1])  -(xval-x[i+1])*(x[i]-x[i+1])  )- K[i+1]/6*(  ( (xval-x[i])*(xval-x[i])*(xval-x[i]) )   /   (x[i]-x[i+1])  -(xval-x[i])*(x[i]-x[i+1])  )+ ( y[i]*(xval-x[i+1])-y[i+1]*(xval-x[i]) )/ ( x[i]-x[i+1] );
  return result;
}

//Contains Formula that calculates values of the segments
double Spline3Interpolator::SegmentDerivCalc(double xval,int i) const{
  double result=K[i]/6*(  ( 3*(xval-x[i+1])*(xval-x[i+1]) )   /   (x[i]-x[i+1])  -(x[i]-x[i+1])  )- K[i+1]/6*(  ( 3*(xval-x[i])*(xval-x[i]) )   /   (x[i]-x[i+1])  -(xval-x[i])*(x[i]-x[i+1])  )+ ( y[i]-y[i+1] )/ ( x[i]-x[i+1] );
  return result;
}

double Spline3Interpolator::Derivate(double xval) const{
  double result=0.;
  bool isAt =false;  //Diz se o valor esta nos intervalos dos nossos pontos ou nao
  int segment=0;
  int i;

  //detect segment
  //Supondo que x está ordenado por ordem crescente

  if(EvenlySpaced)
  {
    i=(xval-x[0])/(x[N-1]-x[0])*(N-1);

    return K[i]/6*(  ( 3*(xval-x[i+1])*(xval-x[i+1]) )   /   (x[i]-x[i+1])  -(x[i]-x[i+1])  )- K[i+1]/6*(  ( 3*(xval-x[i])*(xval-x[i]) )   /   (x[i]-x[i+1])  -(xval-x[i])*(x[i]-x[i+1])  )+ ( y[i]-y[i+1] )/ ( x[i]-x[i+1] );;
  }


  if(!EvenlySpaced)
  {
    for (int i=0; i<N-1;i++)
    {
      
      //Verificar onde está o xval
        if (xval>x[i] && xval<=x[i+1])
        {
          segment=i;
          isAt=true;
        }
         
        if (isAt==true)
        {
          break;
        }
    }


      //Flag as extrapolation or solve
        if(isAt==false)
        {
          if(xval < x[0])
              {
                return 0; 
              }
          else if(xval>x[N-1])
              {
                
                return 0;
              }
        }
        else
        {

          result = SegmentDerivCalc(xval, segment);
        }
    }  

  return result;
}

double Spline3Interpolator::Interpolate(double xval) const{

  //cout << __PRETTY_FUNCTION__ << endl;
  //cout << endl << xval << endl;

  double result=0.;
  bool isAt =false;  //Diz se o valor esta nos intervalos dos nossos pontos ou nao
  int segment=0;

  //detect segment
  //Supondo que x está ordenado por ordem crescente
  for (int i=0; i<N-1;i++)
  {
    
    //Verificar onde está o xval
	  	if (xval>x[i] && xval<x[i+1])
	  	{
	  		//cout << "xval is at segment C" << i << i+1 << endl << endl;
	  		segment=i;
	  		isAt=true;
        //cout << "here" << endl;
	  	}
	  	else if(xval==x[i]) {
	  		result=y[i];
	  		isAt=true;
        return result;
        //cout << "here2" << endl;

	  	}
	  	else if(xval==x[i+1]) {
	  		result=y[i+1];
	  		isAt=true;
        return result;
        //cout << "here3" << endl;
	  	}


	  	if (isAt==true)
      {
        //cout << "saiu!" << endl;
	  		break;
      }
  }


		//Flag as extrapolation or solve
		  if(isAt==false)
		  {
		  	//cout << "xval not in the segments, extrapolation needed" << endl;
        //double media= (y[N-1]+y[0])/2;
        if(xval < x[0])
            {
              return y[0]; 
            }
        else if(xval>x[N-1])
            {
              
              return y[N-1];
            }
		  }
		  else
		  {

		  	result = SegmentCalc(xval, segment);
        //cout << result << endl;
		  }

     // cout << endl << xval << " " << result << endl;
	
	

  return result;
}


void Spline3Interpolator::Draw() const {
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
}

const TCanvas& Spline3Interpolator::GetCanvas()  {
  cInterpolator = new TCanvas("cInterpolator","", 0,0,800,600);
  DataPoints::Draw();
  FInterpolator->SetLineColor(38);
  FInterpolator->SetLineWidth(4);
  FInterpolator->Draw("same");
  return *cInterpolator;
}

void Spline3Interpolator::SetFunction(TF1* f) {
  F0 = f;
}

void  Spline3Interpolator::SetCurvatureLines(){ 
    cout<<"Curves"<<endl;
    vector<Vec> v;
    Vec v1(N-3,0.0);
    Vec v2(N-2,0.0);
    Vec v3(N-3,0.0);
  	//Vetor b
  	Vec tri_b(N-2,0.0);


  	for(int i=1;i<N-2;i++)
  	{
      
  		v1[i-1]=x[i]-x[i+1];
  		v3[i-1]=x[i]-x[i+1];

  	}

  	for(int i=0;i<N-2;i++)
  	{
      
  		v2[i]=2*(x[i]-x[i+2]);
  		tri_b[i]=6*   ( (     (y[i]-y[i+1])     /     (x[i]-x[i+1])  )   -   (  (y[i+1]-y[i+2])   /   (x[i+1]-x[i+2])    )   );
      //cout << y[i] << y[i+1] << y[i+2] << x[i] << x[i+1] << x[i+2] << endl; 
      //cout << "Valor de b" << tri_b[i] << endl;
      //cout << "Valor da Diagonal" << v2[i] << endl;
  	}

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);


     FCMatrixBanded Tri_mat(v); 

     //Tri_mat.Print();
     //tri_b.Print();
     //cout << endl;

    FCMatrixFull Tri_full = Tri_mat.convert_2Full();

     EqSolver banded(Tri_full,tri_b);  

     //Tri_mat.Print();
     //tri_b.Print();
  
    Vec result;
    result=banded.GaussEliminationSolver();  
    //result.Print();
    
    //Assign  the private member  K[] array pointer…
    Vec Aux(N,0.0);
    K=Aux;
    K[0]=0;
    K[N-1]=0;
    
    for(int j=1;j<N-1;j++)
    {
      
    	K[j]=result[j-1];
      cout << K[j] << endl;

    }
} 

void Spline3Interpolator::IsEvenlySpaced(bool option){
  EvenlySpaced=option;
}

std::ostream& operator<< (std::ostream& s, const Spline3Interpolator& LI) {
  s << "Spline3 Interpolator " << "x:[" << LI.xmin << "," << LI.xmax << "]" << std::endl;
  for (int i=0; i<LI.N; ++i) {
    s << std::fixed << std::setprecision(3)
      << "(" << LI.x[i] << "," << LI.y[i] << ") f(x)=" << LI.Interpolate(LI.x[i]) << " " ;
  }
  s << "\n";
  return s;
}

void Spline3Interpolator::Print(string FILE) {
  fstream file;
  file.open(FILE, ios::out);
  file<<"[Spline3::Print]: "<<endl;
  for (int i=0; i<N; i++) {
    file<<"[Spline3] (x="<<x[i]<<", y="<<y[i]<<") "<<endl;;  
  }
  file<<endl;
  file<<FInterpolator<<endl;
  file<<endl;
  file<<"FILE: "<<FILE.c_str()<<endl;
  file.close();
}