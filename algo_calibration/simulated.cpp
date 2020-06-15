#include "optimisation.hpp"


void rand_start_values(double& R0, double& C0, double& alpha0,double& eps1,double& eps2,double& eps3) {

  random_device rd ;
  default_random_engine gen(rd()) ;

  uint N_r_1 = 245, N_r_2 = 255 ; // Intervall for the Resistance
  double N_c_1 = 1e-6, N_c_2 = 1e-4 ; //Intervall for the Capacity
  double N_alpha_1 = 0.15, N_alpha_2 = 0.25 ;

  eps1 = (N_r_2 - N_r_1)*0.1 ; // Get the step for the Resistance (10%)
  eps2 = (N_c_2 - N_c_1)*0.1 ; // Get the step for the Capacity (10%)
  eps3 = (N_alpha_2 - N_alpha_1)*0.1 ;  // Get the step for the alpha (10%)

  uniform_real_distribution<double> distribution1(N_r_1, N_r_2) ;
  uniform_real_distribution<double> distribution2(N_c_1, N_c_2) ;
  uniform_real_distribution<double> distribution3(N_alpha_1, N_alpha_2) ;

  R0 = distribution1(gen) ;
  C0 = distribution2(gen) ;
  alpha0 = distribution3(gen) ;
}

void rand_values(double& R1, double& C1, double& alpha1, double R0, double C0, double alpha0, double eps1, double eps2, double eps3) {
  random_device rd ;
  default_random_engine gen(rd()) ;

  uniform_real_distribution<double> distribution1(R0-eps1, R0+eps1) ;
  uniform_real_distribution<double> distribution2(C0-eps2, C0+eps2) ;
  uniform_real_distribution<double> distribution3(alpha0-eps3, alpha0+eps3) ;


  R1 = distribution1(gen) ;
  C1 = distribution2(gen) ;
  alpha1 = distribution3(gen) ;
}


void simulated_annealing(double T_max, double T_min) {

  double R0, C0, alpha0 ;
  double R1, C1, alpha1 ;
  double eps1, eps2, eps3 ;
  double q0, q1 ;
  double R_min, C_min, alpha_min ;

  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> magn_t ;
  data_in_vector("average/average_Magnitude.txt", magn_t) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase.txt", phase_t) ;


  rand_start_values(R0, C0, alpha0, eps1, eps2, eps3) ; // initialize the values
  q0 = cost(R0, C0, alpha0, freq, magn_t, phase_t) ; // Calculate the function "cost" for R0,C0,alpha0

  double minimum = q0 ;
  double T = T_max ;

  while (T > T_min) {
    for (uint i = 1; i < 5000; i++) {
      do {
        rand_values(R1, C1, alpha1, R0, C0, alpha0, eps1, eps2, eps3) ;
      } while((alpha1<0.15)||(alpha1>0.25)||(R1<245)||(R1>255)||(C1<1e-6)||(C1>1e-4)) ;

       q1 = cost(R1, C1, alpha1, freq, magn_t, phase_t) ;

       random_device rd ;
       default_random_engine gen(rd()) ;

       uniform_real_distribution<double> distribution1(0,1) ;
       double prob = distribution1(gen) ;

       if (minimum > q1) {
         minimum = q1 ;
         R_min = R1 ;
         C_min = C1 ;
         alpha_min = alpha1 ;
       }

       if (q0 > q1) {
         q0 = q1 ;
         R0 = R1 ;
         C0 = C1 ;
         alpha0 = alpha1 ;
       }
       else if ((exp(-(q1-q0)/T)) > prob){ // Good probability law to follow ?
         R0 = R1 ;
         C0 = C1 ;
         alpha0 = alpha1 ;
         q0 = q1 ;
       }
     }
     T *= 0.99 ; // Coefficient permettant de réduire le T pour atteindre le T-min
  }
  cout << "min = " << minimum << endl ;
  cout << "R_min = " << R_min << endl ;
  cout << "C_min = " << C_min << endl ;
  cout << "alpha_min = " << alpha_min << endl ;
}
