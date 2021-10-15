#include "FCmath.h"
#include <stdexcept>


int FCmath::Factorial(int n,int step=1){
  int res=1;

  if(n<0)
    throw std::invalid_argument("Ñegative number for factorial\n");
  if(step<=0)
    throw std::invalid_argument("Step is not positive\n");
  for(int i=n;i>0;i-=step)
    res*=i;

  return res;
}



int FCmath::Permutations(int n,int k){
  
  if(n<0)
    throw std::invalid_argument("Negative number of elements\n");
  if(k<0)
    throw std::invalid_argument("Negative number of selected elements \n");
  return FCmath::Factorial(n)/FCmath::Factorial(n-k);
}


int FCmath::Combinations(int n,int k){
  if(n<0)
    throw std::invalid_argument("Negative number of elements\n");
  if(k<0)
    throw std::invalid_argument("Negative number of selected elements \n");
  return FCmath::Permutations(n,k)/FCmath::Factorial(k);
}
