#include "optimisation.hpp"

int main() {


  for (uint i = 0; i < 5; i++) {
    simulated_annealing(100.,0.01) ;
    cout << endl ;
  }

  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> magn_t ;
  data_in_vector("average/average_Magnitude.txt", magn_t) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase.txt", phase_t) ;

  // magn_into_data("average/test_magn.txt",250,11e-6,0.2, freq) ;
  // phase_into_data("average/test_phase.txt",250,11e-6,0.2, freq) ;

  double res = cost(250,11e-6,0.2, freq, magn_t, phase_t) ;
  cout << "res = " << res << endl ;

  return 0;
}
