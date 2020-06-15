#include "optimisation.hpp"

int main() {

  for (uint i = 0; i < 5; i++) {
    simulated_annealing(10000000,10) ;
    cout << endl ;
  }


  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> magn_t ;
  data_in_vector("average/average_Magnitude.txt", magn_t) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase_deg.txt", phase_t) ;

  // double res = cost(, freq, magn_t, phase_t) ;
  // cout << "resfinal = " << res << endl ;

  return 0;
}
