#ifndef __FCmath__
#define __FCmath__

class FCmath{
public:
  FCmath()=default;
  ~FCmath()=default;
  
  static int Factorial(int n,int step);
  static int Permutations(int n,int k);
  static int Combinations(int n,int k);

};




#endif