#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std ;

void data_in_vector(string file, vector<double>& vec){
  ifstream infile(file) ;
  double freq, save ;

  for(uint i=0; i<20; i++){
    infile >> freq >> save;
    vec.push_back(save);
  }
}

int main() {

  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase_deg.txt", phase_t) ;

  ofstream outfile ("average/average_Phase_rad.txt") ;

  for (uint i = 0; i < freq.size(); i++) {
    outfile << freq[i] << " " << ((phase_t[i]*M_PI)/180) << endl ;
  }

  return 0;
}
