#ifndef __Vec__
#define __Vec__

#include <iostream> // ostream

class Vec {

 public:

    // constructors
    Vec(int i = 0, double x=0); // Vec v;
    Vec(int , const double*);
    Vec(const Vec&);

    // destructor
    ~Vec();

    // operators
    double  operator[](int i) const;
    double& operator[](int i);

    void operator=(const Vec&); // A=B
    Vec operator+(const Vec&);    
    Vec operator-(const Vec&);
    Vec operator*(const Vec&);
    Vec operator*(double) const;
    const Vec& operator+=(const Vec&);
    const Vec& operator-=(const Vec&);
    Vec operator-();
    Vec operator+();

    //(...)
    /*
    the overloading of then * operator allows multiply a vector by a
    scalar:
    Vec * scalar
    */
     //Vec.operator*(double) <=> A*5.
  
  
    // friend methods
    friend std::ostream& operator<<(std::ostream&, const Vec&);
    
    friend Vec operator*(double, const Vec&);


    // additional methods
    double dot(const Vec&); // double result = a.dot(b)
    void swap(int, int);
    int size() const;
    double sumAbs();
    void SetEntries(int n ,double* a);
  
    // friend methods
    friend std::ostream& operator<<(std::ostream&, const Vec&);
    //  friend Vec operator*(double, const Vec&); // 5*A
  
 private:
  int N; // number of elements
  double *entries; // array
  
};
#endif