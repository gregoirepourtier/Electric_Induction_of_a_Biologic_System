#include "optimisation.hpp"


void rand_start_values(double& Ri_0, double& Rm_0, double& Ci_0, double& Cm_0, double& alpha_i_0, double& alpha_m_0, 
                       double& eps1, double& eps2, double& eps3, double& eps4, double& eps5, double& eps6, 
                       uint& N_ri_1, uint& N_ri_2, uint& N_rm_1, uint& N_rm_2, double& N_ci_1, double& N_ci_2, double& N_cm_1, double& N_cm_2, 
                      double& N_alpha_i_1, double& N_alpha_i_2, double& N_alpha_m_1, double& N_alpha_m_2) {

  random_device rd ;
  default_random_engine gen(rd()) ;

  N_ri_1 = 300, N_ri_2 = 330 ; // Range for the Resistance (Ri)
  N_rm_1 = 240, N_rm_2 = 270 ; // Range for the Resistance (Rm)
  N_ci_1 = 1e-8, N_ci_2 = 1e-7 ; // Range for the Capacity (Ci)
  N_cm_1 = 1e-8, N_cm_2 = 1e-6 ; // Range for the Capacity (Cm)
  N_alpha_i_1 = 0.87, N_alpha_i_2 = 0.95 ;
  N_alpha_m_1 = 0.5, N_alpha_m_2 = 0.7 ;

  eps1 = (N_ri_2 - N_ri_1)*0.1 ; // Get the step for the Resistance Ri (10%)
  eps2 = (N_rm_2 - N_rm_1)*0.1 ; // Get the step for the Resistance Rm (10%)
  eps3 = (N_ci_2 - N_ci_1)*0.1 ; // Get the step for the Capacity Ci (10%)
  eps4 = (N_cm_2 - N_cm_1)*0.1 ; // Get the step for the Capacity Cm (10%)
  eps5 = (N_alpha_i_2 - N_alpha_i_1)*0.1 ;  // Get the step for the alpha_i (10%)
  eps6 = (N_alpha_m_2 - N_alpha_m_1)*0.1 ;  // Get the step for the alpha_m (10%)

  uniform_real_distribution<double> distribution1(N_ri_1, N_ri_2) ;
  uniform_real_distribution<double> distribution2(N_rm_1, N_rm_2) ;
  uniform_real_distribution<double> distribution3(N_ci_1, N_ci_2) ;
  uniform_real_distribution<double> distribution4(N_cm_1, N_cm_2) ;
  uniform_real_distribution<double> distribution5(N_alpha_i_1, N_alpha_i_2) ;
  uniform_real_distribution<double> distribution6(N_alpha_m_1, N_alpha_m_2) ;

  Ri_0 = distribution1(gen) ;
  Rm_0 = distribution2(gen) ;
  Ci_0 = distribution3(gen) ;
  Cm_0 = distribution4(gen) ;
  alpha_i_0 = distribution5(gen) ;
  alpha_m_0 = distribution6(gen) ;

}

void rand_values(double& Ri_1, double& Rm_1, double& Ci_1, double& Cm_1, double& alpha_i_1, double& alpha_m_1, double Ri_0, double Rm_0, double Ci_0, double Cm_0, double alpha_i_0, double alpha_m_0, double eps1, double eps2, double eps3, double eps4, double eps5, double eps6) {
  random_device rd ;
  default_random_engine gen(rd()) ;

  uniform_real_distribution<double> distribution1(Ri_0-eps1, Ri_0+eps1) ;
  uniform_real_distribution<double> distribution2(Rm_0-eps2, Rm_0+eps2) ;
  uniform_real_distribution<double> distribution3(Ci_0-eps3, Ci_0+eps3) ;
  uniform_real_distribution<double> distribution4(Cm_0-eps4, Cm_0+eps4) ;
  uniform_real_distribution<double> distribution5(alpha_i_0-eps5, alpha_i_0+eps5) ;
  uniform_real_distribution<double> distribution6(alpha_m_0-eps6, alpha_m_0+eps6) ;

  Ri_1 = distribution1(gen) ;
  Rm_1 = distribution2(gen) ;
  Ci_1 = distribution3(gen) ;
  Cm_1 = distribution4(gen) ;
  alpha_i_1 = distribution5(gen) ;
  alpha_m_1 = distribution6(gen) ;
}


void simulated_annealing(double T_max, double T_min) {

  double Ri_0, Rm_0, Ci_0, Cm_0, alpha_i_0, alpha_m_0 ;
  double Ri_1, Rm_1, Ci_1, Cm_1, alpha_i_1, alpha_m_1 ;
  double eps1, eps2, eps3, eps4, eps5, eps6 ;
  double q0, q1 ;
  double Ri_min, Rm_min, Ci_min, Cm_min, alpha_i_min, alpha_m_min ;
  uint N_ri_1, N_ri_2, N_rm_1, N_rm_2 ; 
  double N_ci_1, N_ci_2, N_cm_1, N_cm_2, N_alpha_i_1, N_alpha_i_2, N_alpha_m_1, N_alpha_m_2 ;

  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> magn_t ;
  data_in_vector("average/average_Magnitude.txt", magn_t) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase_deg.txt", phase_t) ;


  rand_start_values(Ri_0, Rm_0, Ci_0, Cm_0, alpha_i_0, alpha_m_0, eps1, eps2, eps3, eps4, eps5, eps6, N_ri_1, N_ri_2, N_rm_1, N_rm_2, N_ci_1, N_ci_2, N_cm_1, N_cm_2, N_alpha_i_1, N_alpha_i_2, N_alpha_m_1, N_alpha_m_2) ; // initialize the values
  q0 = cost(Ri_0, Rm_0, Ci_0, Cm_0, alpha_i_0, alpha_m_0, freq, magn_t, phase_t) ; // Calculate the function "cost" for Ri_0,Ci_0,Rm_0,Cm_0,alpha_i_0,alpha_m_0

  double minimum = q0 ;
  double T = T_max ;

  while (T > T_min) {
    for (uint i = 1; i < 5000; i++) {
      do {
        rand_values(Ri_1, Rm_1, Ci_1, Cm_1, alpha_i_1, alpha_m_1, Ri_0, Rm_0, Ci_0, Cm_0, alpha_i_0, alpha_m_0, eps1, eps2, eps3, eps4, eps5, eps6) ;
      } while((alpha_i_1<N_alpha_i_1)||(alpha_i_1>N_alpha_i_2)||(alpha_m_1<N_alpha_m_1)||(alpha_m_1>N_alpha_m_2)||(Ri_1<N_ri_1)||(Ri_1>N_ri_2)||(Rm_1<N_rm_1)||(Rm_1>N_rm_2)||(Ci_1<N_ci_1)||(Ci_1>N_ci_2)||(Cm_1<N_cm_1)||(Cm_1>N_cm_2)) ;

       q1 = cost(Ri_1, Rm_1, Ci_1, Cm_1, alpha_i_1, alpha_m_1, freq, magn_t, phase_t) ;

       random_device rd ;
       default_random_engine gen(rd()) ;

       uniform_real_distribution<double> distribution1(0,1) ;
       double prob = distribution1(gen) ;

       if (minimum > q1) {
         minimum = q1 ;
         Ri_min = Ri_1 ;
         Rm_min = Rm_1 ;
         Ci_min = Ci_1 ;
         Cm_min = Cm_1 ;
         alpha_i_min = alpha_i_1 ;
         alpha_m_min = alpha_m_1 ;
       }

       if (q0 > q1) {
         q0 = q1 ;
         Ri_0 = Ri_1 ;
         Rm_0 = Rm_1 ;
         Ci_0 = Ci_1 ;
         Cm_0 = Cm_1 ;
         alpha_i_0 = alpha_i_1 ;
         alpha_m_0 = alpha_m_1 ;
       }
       else if ((exp(-(q1-q0)/T)) > prob){
         Ri_0 = Ri_1 ;
         Ci_0 = Ci_1 ;
         Rm_0 = Rm_1 ;
         Cm_0 = Cm_1 ;
         alpha_i_0 = alpha_i_1 ;
         alpha_m_0 = alpha_m_1 ;
         q0 = q1 ;
       }
     }
     T *= 0.99 ; // Coefficient permettant de réduire le T pour atteindre le T-min
  }
  cout << "min = " << minimum << endl ;
  cout << "Ri_min = " << Ri_min << endl ;
  cout << "Rm_min = " << Rm_min << endl ;
  cout << "Ci_min = " << Ci_min << endl ;
  cout << "Cm_min = " << Cm_min << endl ;
  cout << "alpha_i_min = " << alpha_i_min << endl ;
  cout << "alpha_m_min = " << alpha_m_min << endl ;
}
