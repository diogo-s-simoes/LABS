#include "Vec.h"
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <numeric>

#include "TROOT.h"

///////////////////// constructors

Vec::Vec(int i, double x) : N(i) { // default constructor
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (N<0) throw std::invalid_argument(Form("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  if (N==0) {
    entries = nullptr;
  } else {
    entries = new double[N];
    std::fill_n(entries, N, x);
  }
}

Vec::Vec(int i, const double* x) : Vec(i) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  //if (x)
    std::copy(x, x+i, entries);
  //else  
    //throw std::invalid_argument(Form("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
}

Vec::Vec(const Vec& v) : Vec(v.N, v.entries) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

////////////////////// destructor
Vec::~Vec() {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (entries) delete [] entries;
}

///////////////////// operators
double Vec::operator[](int i) const {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i>=N) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

double& Vec::operator[](int i){
  #ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i>=N) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

void Vec::operator=(const Vec& v) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &v) {
    if (v.N != N) {
      N = v.N;
      delete [] entries;
      entries = new double[N];
    }
    std::copy(v.entries, v.entries+N, entries);    
  }
}

const Vec& Vec::operator+= (const Vec& v) { 
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif
  if (v.N != N) {
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  }
  for (int i=0; i<N; ++i) {
    entries[i] += v[i];
  }
  return *this;
}

Vec Vec::operator*(double x) const {
  #ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
  #endif
  double a[N];
  for (int i=0; i<N; ++i) {
    a[i] = entries[i] * x;
  }
  return Vec(N, a);
} 

///////////////////// friend methods

std::ostream& operator<<(std::ostream& s, const Vec& v) {
  s << "[";
  for (int i=0; i<v.N; ++i) {
    s << std::fixed << std::setprecision(6) << v.entries[i];
    if (i<v.N-1) s << ", ";
  }
  s << "]";
  return s;
}

  ///////////////////// additional methods

double Vec::dot(const Vec& v) {
  if (v.N != N)
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));
  return std::inner_product(entries, entries+N, v.entries, 0);
}

void Vec::swap(int i, int j) {
  if (std::max(i,j)>=N)
    throw std::invalid_argument(Form("[%s] indices out of range...(N=%d max index=%d)!\n", __PRETTY_FUNCTION__, N, std::max(i,j)));
  if (i!=j) std::swap(entries[i], entries[j]);
}

double Vec::sumAbs() { 
  // summ of all absolute values
  return std::accumulate(entries, entries+N, 0, [](double accum, double x){return accum+fabs(x);});
}

int Vec::size() const { 
  return N;
}

void Vec::SetEntries(int n ,double* a){
    if(n!=N){
        N=n;
        delete [] entries;
        double* entries = new double[N];
        std::copy(a, a+N, entries);
    }
    else{
        std::copy(a, a+N, entries);
    }
}

Vec Vec::operator+(const Vec& V1){
    if(V1.size()!=N) throw std::invalid_argument(Form("Diff. sizes"));
    double aux[N];
    for (int i = 0; i<N; ++i){
        aux[i]=entries[i]+V1[i];
    }
    Vec v(N,aux);
    return v;
}

Vec Vec::operator*(const Vec& V1){
    if(V1.size()!=N) throw std::invalid_argument(Form("Diff. sizes"));
    double aux[N];
    for (int i = 0; i<N; ++i){
        aux[i]=entries[i]*V1[i];
    }
    Vec v(N,aux);
    return v;
}

Vec Vec::operator-(const Vec& V1){
    if(V1.size()!=N) throw std::invalid_argument(Form("Diff. sizes"));
    double aux[N];
    for (int i = 0; i<N; ++i){
        aux[i]=entries[i]-V1[i];
    }
    Vec v(N,aux);
    return v;
}

const Vec& Vec::operator-=(const Vec& V1){
    if(V1.size()!=N) throw std::invalid_argument(Form("Diff. sizes"));
    for (int i = 0; i<N; ++i){
        entries[i]-=V1[i];
    }
    return *this;
}

Vec Vec::operator-(){
  double aux[N];
    for (int i = 0; i<N; ++i){
        aux[N]=-entries[i];
    }
    Vec v(N,aux);
    return v;
}

Vec Vec::operator+(){
  return *this;
}