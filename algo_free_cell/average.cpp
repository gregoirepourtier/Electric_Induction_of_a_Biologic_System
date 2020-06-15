#include "optimisation.hpp"


int main() {

  vector<double> Zt0 ;
  data_in_vector("Experiments_FC/Mag_exp0.txt",Zt0) ;
  vector<double> Zt1 ;
  data_in_vector("Experiments_FC/Mag_exp1.txt",Zt1) ;
  vector<double> Zt2 ;
  data_in_vector("Experiments_FC/Mag_exp2.txt",Zt2) ;
  vector<double> Zt3 ;
  data_in_vector("Experiments_FC/Mag_exp3.txt",Zt3) ;
  vector<double> Zt4 ;
  data_in_vector("Experiments_FC/Mag_exp4.txt",Zt4) ;
  vector<double> Zt5 ;
  data_in_vector("Experiments_FC/Mag_exp5.txt",Zt5) ;
  vector<double> Zt6 ;
  data_in_vector("Experiments_FC/Mag_exp6.txt",Zt6) ;
  vector<double> Zt7 ;
  data_in_vector("Experiments_FC/Mag_exp7.txt",Zt7) ;
  vector<double> Zt8 ;
  data_in_vector("Experiments_FC/Mag_exp8.txt",Zt8) ;
  vector<double> Zt9 ;
  data_in_vector("Experiments_FC/Mag_exp9.txt",Zt9) ;

  vector<double> freq ;
  data_in_vector("Experiments_FC/frequence.txt",freq) ;


  ofstream outfile("average/average_Magnitude.dat") ;

  for (uint i = 0 ; i < Zt0.size(); i++) {
    outfile << freq[i] << " " << (Zt0[i]+Zt1[i]+Zt2[i]+Zt3[i]+Zt4[i]+Zt5[i]+Zt6[i]+Zt7[i]+Zt8[i]+Zt9[i])/10.0 << endl ;
  }

  return 0;
}
