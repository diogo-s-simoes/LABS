#include "ODEsolver.h"
#include "ODEpoint.h"

ODEsolver::ODEsolver(vector<TF1> FF){
    F=FF;
}

ODEsolver::ODEsolver(){
}

ODEsolver::~ODEsolver(){
    F.clear();
}

vector<ODEpoint> ODEsolver::Euler(const ODEpoint& P0, double h, double T){
    ODEpoint P = P0;
    vector<ODEpoint> V;
    V.push_back(P);
    int n = ceil((T-P.Get_Time())/h);
    for (int i = 1; i<n; ++i){
        P=EulerIterator(P,h);
        V.push_back(P);
    }
    return V;
}

vector<ODEpoint> ODEsolver::Heun(const ODEpoint& P0, double h, double T){
    ODEpoint P = P0;
    vector<ODEpoint> V;
    V.push_back(P);
    int n = ceil((T-P.Get_Time())/h);
    for (int i = 1; i<n; ++i){
        P=HeunIterator(P,h);
        V.push_back(P);
    }
    return V;
}

vector<ODEpoint> ODEsolver::RK2(const ODEpoint& P0, double h, double T){
    ODEpoint P = P0;
    vector<ODEpoint> V;
    V.push_back(P);
    int n = ceil((T-P.Get_Time())/h);
    for (int i = 1; i<n; ++i){
        P=RK2Iterator(P,h);
        V.push_back(P);
    }
    return V;
}

vector<ODEpoint> ODEsolver::RK4(const ODEpoint& P0, double h, double T){
    ODEpoint P = P0;
    vector<ODEpoint> V;
    V.push_back(P);
    int n = ceil((T-P.Get_Time())/h);
    for (int i = 1; i<n; ++i){
        P=RK4Iterator(P,h);
        V.push_back(P);
    }
    return V;
}

vector<ODEpoint> ODEsolver::LeapFrog(const ODEpoint& P0, double h, double T){
    ODEpoint P1 = P0;
    ODEpoint P2 = EulerIterator(P1, h);
    ODEpoint Paux;
    vector<ODEpoint> V;
    V.push_back(P1);
    V.push_back(P2);
    int n = ceil((T-P1.Get_Time())/h);
    for (int i = 2; i<n; ++i){
        Paux = P2;
        P2=LPIterator(P1, P2, h);
        P1=Paux;
        V.push_back(P2);
    }
    return V;
}

vector<ODEpoint> ODEsolver::RK4AS(const ODEpoint& P0, double h, double T, double delta){
    ODEpoint P = P0;
    int dim = P.GetNdim();
    double A[6] = {0,1./5,3./10,3./5,1,7./8};
    double B[6][5] = {{0,0,0,0,0},
                      {1./5,0,0,0,0},
                      {3./40,9./40,0,0,0},
                      {3./10,-9./10,6./5,0,0},
                      {-11./54,5./2,-70./27,35./27,0},
                      {1631./55296,175./512, 575./13824, 44274./110592, 253./4096}};
    double C[6] = {37./378,0,250./621,125./594,0,512./1771};
    double D[6] = {2825./27648, 0, 18575./48384, 13525./55296, 1./4};
    
    vector<ODEpoint> V;
    V.push_back(P);

    while(P.Get_Time()<=T){
        double t = P.Get_Time();
        double* vartime = P.Get_VarTime();
        double* y0 = P.Get_Var_ptr();

        double err=10;

        while(err>delta){

            err=0;
            double** K = new double*[dim];
            double* aux = new double[dim+1];
            double* E = new double[dim];

            for(int i = 0; i<dim; ++i){
                K[i] = new double[6];
                K[i][0]=h*F[i].EvalPar(vartime);
                for (int u = 0; u<6; ++u){
                    for (int v = 0; v<dim; ++v){
                        aux[v]=y0[i];
                        for (int l = 0; l<u; ++l){
                            aux[v]+=B[u][l]*K[i][l];
                        }
                        aux[dim]=t+h*A[u];
                    }
                    K[i][u]=h*F[i].EvalPar(aux);
                }
                E[i]=0;
                for (int u = 0; u<6; ++u){
                    E[i]+=(C[u]-D[u])*K[i][u];
                }
                err+=E[i]*E[i];
            }
            err/=dim;
            err=sqrt(err);
            if(err<delta) break;

            h=0.9*h*pow(delta/err,1./5);
        }
        P = RK4Iterator(P,h);
        V.push_back(P);
    }
    return V;
}

vector<ODEpoint> ODEsolver::Shoot(const ODEpoint& P0, const ODEpoint& Pf, double h){
    ODEpoint A = P0;
    ODEpoint B = Pf;

    double* varA = A.Get_VarTime();
    double* varB = B.Get_VarTime();

    auto g = [&](double* x, double* par) {
        varA[1]=x[0];
        return RK4(ODEpoint(A.Get_Time(), varA, 2), h, B.Get_Time()).back()[0]-varB[0];
    };
    TF1 G("G", g, 0, 1000, 0);
    G.SetNpx(3000);

    double eps=1.e-6;
    double x0=varA[1]-1;
    double x1=varA[1];
    double xaux;
    while(fabs(x1-x0)>eps){
        xaux=x1;
        x1=x1-G.Eval(x1)*(x1-x0)/(G.Eval(x1)-G.Eval(x0));
        x0=xaux;
    }

    varA[1]=x1;
    ODEpoint O(A.Get_Time(), varA, 2);
    double T = B.Get_Time();
    return RK4(O, h, T);
}

vector<ODEpoint> ODEsolver::FDiff(int option, const ODEpoint& P0, const ODEpoint& Pf, double h, const TF1& a, const TF1& b, const TF1& c, const TF1& G){
    double t0=P0.Get_Time();
    double t1=Pf.Get_Time();
    double l0;
    double l1;
    if(!option){
        l0=P0[0];
        l1=Pf[0];
    }
    else{
        l0=P0[1];
        l1=Pf[1];
    }

    int N = (t1-t0)/h;

    double* g = new double[N+1];
    if(!option){
        g[0] = l0;
        g[N]=l1;
    }
    else{
        g[0]=G.Eval(t0)+2*h*l0*(a.Eval(t0)/(h*h)-b.Eval(t0)/(2*h));
        g[N]=G.Eval(t1)-2*h*l1*(a.Eval(t1)/(h*h)-b.Eval(t1)/(2*h));
    }
    
    double** m = new double*[3];
    m[0] = new double[N];
    m[1] = new double[N+1];
    m[2] = new double[N];

    if(!option){
        m[0][0]=0;
        m[1][0]=1;
        m[1][N]=1;
        m[2][N-1]=0;
    }
    else{
        m[0][0]=2*a.Eval(t0)/(h*h);
        m[1][0]=c.Eval(t0)-2*a.Eval(t0)/(h*h);
        m[1][N]=c.Eval(t1)-2*a.Eval(t1)/(h*h);
        m[2][N-1]=2*a.Eval(t1)/(h*h);
    }

    for (int i = 1; i<N; ++i){
        m[0][i]=a.Eval(t0+i*h)/(h*h)+b.Eval(t0+i*h)/(2*h);
        m[1][i]=c.Eval(t0+i*h)-2*a.Eval(t0+i*h)/(h*h);
        m[2][i-1]=a.Eval(t0+i*h)/(h*h)-b.Eval(t0+i*h)/(2*h);
        g[i]=G.Eval(t0+i*h);
    }

    FCMatrixBanded MB(m,N+1,N+1);
    Vec v(N+1, g);
    FCMatrixFull MF = MB.convert_2Full();
    EqSolver ES(MF,v);
    Vec yf = ES.GaussEliminationSolver();
    vector<ODEpoint> O;

    for(int i = 0; i<N+1; ++i){
        O.push_back(ODEpoint(t0+i*h,&yf[i],1));
    }

    return O;
}

void ODEsolver::SetODEfunc(vector<TF1> FF){
    F=FF;
}

vector<TF1>& ODEsolver::GetODEfunc(){
    return F;
}

ODEpoint ODEsolver::EulerIterator(const ODEpoint& P0, double h){
    ODEpoint P = P0;
    int dim = P.GetNdim();
    double* y0 = P.Get_Var_ptr();
    double* y1 = new double[dim];
    double t = P.Get_Time();
    double* vartime = P.Get_VarTime(); 
    for(int i = 0; i<dim; ++i){
        y1[i]=y0[i]+h*F[i].EvalPar(vartime);
    }
    t+=h;
	ODEpoint G(t, y1, dim);
    return G;
}

ODEpoint ODEsolver::HeunIterator (const ODEpoint& P0, double h){
    ODEpoint P = P0;
    int dim = P.GetNdim();
    double* y0 = P.Get_Var_ptr();
    double* y1 = new double[dim];
    double t = P.Get_Time();
    double* vartime = P.Get_VarTime();
    double* aux = new double[dim+1];
    double alpha = 1;

    for(int i = 0; i<dim; ++i){
        aux[i]=y0[i]+alpha*h*F[i].EvalPar(vartime);
    }
    aux[dim]=t+alpha*h;

    for(int i = 0; i<dim; ++i){
        y1[i] = y0[i] + h*((1-1/(2*alpha))*F[i].EvalPar(vartime)+(1/(2*alpha))*F[i].EvalPar(aux));
    }
    t+=h;
    ODEpoint G(t, y1, dim);
    return G;
}

ODEpoint ODEsolver::RK2Iterator(const ODEpoint& P0, double h){
    ODEpoint P = P0;
    int dim = P.GetNdim();
    double* y0 = P.Get_Var_ptr();
    double* y1 = new double[dim];
    double t = P.Get_Time();
    double* vartime = P.Get_VarTime();
    double* aux = new double[dim+1];
    double alpha = 0.5;

    for(int i = 0; i<dim; ++i){
        aux[i]=y0[i]+alpha*h*F[i].EvalPar(vartime);
    }
    aux[dim]=t+alpha*h;

    for(int i = 0; i<dim; ++i){
        y1[i] = y0[i] + h*((1-1/(2*alpha))*F[i].EvalPar(vartime)+(1/(2*alpha))*F[i].EvalPar(aux));
    }
    t+=h;
    ODEpoint G(t, y1, dim);
    return G;
}

ODEpoint ODEsolver::RK4Iterator(const ODEpoint& P0, double h){
	ODEpoint P = P0;
    int dim = P.GetNdim();
    double* y0 = P.Get_Var_ptr();
    double* y1 = new double[dim];
    double t = P.Get_Time();
    double* vartime = P.Get_VarTime();
	double* aux = new double[dim+1];
    double* K1 = new double[dim];
	double* K2 = new double[dim];
	double* K3 = new double[dim];
	double* K4 = new double[dim];

	for (int i = 0; i<dim; ++i){
		K1[i] = h*F[i].EvalPar(vartime);
	}
	for (int i = 0; i<dim; ++i){
		aux[i] = y0[i]+K1[i]/2;
	}
	aux[dim]=t+h/2;
	for (int i = 0; i<dim; ++i){
		K2[i] = h*F[i].EvalPar(aux);
	}
	for (int i = 0; i<dim; ++i){
		aux[i] = y0[i]+K2[i]/2;
	}
	aux[dim]=t+h/2;
	for (int i = 0; i<dim; ++i){
		K3[i] = h*F[i].EvalPar(aux);
	}
	for (int i = 0; i<dim; ++i){
		aux[i] = y0[i]+K3[i];
	}
	aux[dim]=t+h;
	for (int i = 0; i<dim; ++i){
		K4[i] = h*F[i].EvalPar(aux);
	}
	for (int i = 0; i<dim; ++i){
		y1[i] = y0[i]+(1./6.)*(K1[i]+2*K2[i]+2*K3[i]+K4[i]);
	}

	t+=h;
    ODEpoint G(t, y1, dim);
    return G;
}

ODEpoint ODEsolver::LPIterator(const ODEpoint& PA, const ODEpoint& PB, double h){
    ODEpoint P1 = PA;
    ODEpoint P2 = PB;
    int dim = P1.GetNdim();
    double* y1 = P1.Get_Var_ptr();
    double* yf = new double[dim];
    double t = P2.Get_Time();
    double* vartime = P2.Get_VarTime(); 
    for(int i = 0; i<dim; ++i){
        yf[i]=y1[i]+2*h*F[i].EvalPar(vartime);
    }
    t+=h;
	ODEpoint G(t, yf, dim);
    return G;
}