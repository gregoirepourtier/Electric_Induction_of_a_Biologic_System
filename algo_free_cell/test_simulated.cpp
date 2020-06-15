#include "optimisation.hpp"

int main() {

  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> magn_t ;
  data_in_vector("average/average_Magnitude.txt", magn_t) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase_deg.txt", phase_t) ;

  double res = cost(320,250,2.5e-8,1e-7,0.9,0.6, freq, magn_t, phase_t) ;
  cout << "res = " << res << endl ;
/*
  for (uint i = 0; i < 5; i++) {
    simulated_annealing(1000., 0.01) ;
    cout << endl ;
    cout << "res = " << res << endl ;
    cout << endl ;
  }
*/
  return 0;
}
