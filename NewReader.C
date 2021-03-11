#include"NewReader.h"

//Constructor
NewReader::NewReader(string infile):FileName(infile){
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif

  ifstream DataFile(FileName);
  string line = "";

  string TempoString;
  string VariavelString;


  vector<double> Tempo;
  int nlines=0;

  while(getline(DataFile, line)){
    stringstream ss(line);
    getline(ss, TempoString, ',');
    getline(ss, VariavelString, '\n');

    //Tempo.push_back(stod(TempoString));
    DataVector.push_back(stod(VariavelString));
    cout << stod(TempoString) << "---" << stod(VariavelString)<<endl;
    nlines++;
  }
  DataFile.close();
}





