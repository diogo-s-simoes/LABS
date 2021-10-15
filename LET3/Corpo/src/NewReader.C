#include"NewReader.h"

//Constructor
NewReader::NewReader(string infile=" aa "): FILENAME(infile){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  ifstream DataFile(infile);
  string line = "";

  string TempoString;
  string VariavelString;
  nlines=0;
  while(getline(DataFile, line)){
    stringstream ss(line);
    getline(ss, TempoString, ',');
    getline(ss, VariavelString, '\n');

    Tempo.push_back(stod(TempoString));
    DataVector.push_back(stod(VariavelString));
    //cout << "Tempo:"<< stod(TempoString) << "; Var:" << stod(VariavelString)<<endl;
    nlines++;
  }
  DataFile.close();
}
NewReader::NewReader(const NewReader& A) : NewReader(A.Tempo, A.DataVector) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

const NewReader NewReader::operator=(const NewReader& A){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &A) {
    Tempo= A.Tempo;
    DataVector=A.DataVector;    
  }
  return *this;
}





