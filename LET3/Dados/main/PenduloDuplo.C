#include "DataReader.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main(){
  DataReader Pendulum1("Modo1_Pendulo1.txt");
  DataReader Pendulum2("Modo1_Pendulo2.txt");
  //DataReader Pendulum1("Chaos_Pendulo1.txt");
  //DataReader Pendulum2("Chaos_Pendulo2.txt");
  
  vector<double> time,x1,y1,x2,y2,theta1,theta2;
  cout<<"aaaaaa"<<endl;
  time=Pendulum1.GetColumn(1);
  //theta1=Pendulum1.GetColumn(2);
  cout<<"aaaaaa"<<endl;
  x1=Pendulum1.GetColumn(3);
  cout<<"aaaaaa"<<endl;
  y1=Pendulum1.GetColumn(2);
  cout<<"aaaaaa1"<<endl;
  x2=Pendulum2.GetColumn(3);
  cout<<"aaaaaa"<<endl;
  y2=Pendulum2.GetColumn(2);
  cout<<"aaaaaa"<<endl;

  double L=.146,P= 0.103;

  L=L/P*sqrt(x1.at(0)*x1.at(0)+y1.at(0)*y1.at(0));

  for(int i=0;i<time.size();i++){
    theta1.push_back(atan((y1.at(i))/(x1.at(i)))+0.164061);
  }



  for(int i=0;i<time.size();i++){
    cout<<i<<endl;
    double temp = atan((y2.at(i)-L*sin(theta1[i]))/(x2.at(i)-L*cos(theta1[i])));


/*    
    if(y2.at(i)-cos(theta1.at(i)+0.164061)*L<0 && x2.at(i)-sin(theta1.at(i)+0.164061)*L>0){
      temp=-M_PI/2.+temp;
    }
    else if(y2.at(i)-cos(theta1.at(i)+0.164061)*L<0 && x2.at(i)-sin(theta1.at(i)+0.164061)*L<0){
      temp=M_PI/2.-temp;
    }
    */

    theta2.push_back(temp);
  }

  ofstream DataOut;
  DataOut.open("thetasModo1.txt");

  for(int i=0;i<time.size();i++){
    DataOut<<time.at(i)<<"   "<<theta1.at(i)/*fmod(theta1.at(i),M_PI)*/<<"   "<<theta2.at(i)<<endl;
  }

  DataOut.close();
}