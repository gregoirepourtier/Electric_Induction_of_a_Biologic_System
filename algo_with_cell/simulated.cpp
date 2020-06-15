#include "optimisation.hpp"


void rand_start_values(double& Ri_0, double& Rm_0, double& Rc_0, double& Ci_0, double& Cm_0, double& Cc_0, double& alpha_i_0, double& alpha_m_0, double& alpha_c_0,
                       double& eps1, double& eps2, double& eps3, double& eps4, double& eps5, double& eps6, double& eps7, double& eps8, double& eps9,
                       double& N_ri_1, double& N_ri_2, double& N_rm_1, double& N_rm_2, double& N_rc_1, double& N_rc_2, double& N_ci_1, double& N_ci_2, double& N_cm_1, double& N_cm_2, double& N_cc_1, double& N_cc_2,
                      double& N_alpha_i_1, double& N_alpha_i_2, double& N_alpha_m_1, double& N_alpha_m_2, double& N_alpha_c_1, double& N_alpha_c_2) {

  random_device rd ;
  default_random_engine gen(rd()) ;

  N_ri_1 = 320. , N_ri_2 = 320. ; // Range for the Resistance (Ri)
  N_rm_1 = 250. , N_rm_2 = 250. ; // Range for the Resistance (Rm)
  N_rc_1 = 30., N_rc_2 = 100. ; // Range for the Resistance (Rc)
  N_ci_1 = 2.5e-08, N_ci_2 = 2.5e-08 ; // Range for the Capacity (Ci)
  N_cm_1 = 1e-07, N_cm_2 = 1e-07 ; // Range for the Capacity (Cm)
  N_cc_1 = 1e-5, N_cc_2 = 1e-3 ; // Range for the Capacity (Cc)
  N_alpha_i_1 = 0.9 , N_alpha_i_2 = 0.9 ;
  N_alpha_m_1 = 0.6 , N_alpha_m_2 = 0.6 ;
  N_alpha_c_1 = 0., N_alpha_c_2 = 1. ;

  eps1 = (N_ri_2 - N_ri_1)*0.1 ; // Get the step for the Resistance Ri (10%)
  eps2 = (N_rm_2 - N_rm_1)*0.1 ; // Get the step for the Resistance Rm (10%)
  eps3 = (N_rc_2 - N_rc_1)*0.1 ; // Get the step for the Resistance Rc (10%)
  eps4 = (N_ci_2 - N_ci_1)*0.1 ; // Get the step for the Capacity Ci (10%)
  eps5 = (N_cm_2 - N_cm_1)*0.1 ; // Get the step for the Capacity Cm (10%)
  eps6 = (N_cc_2 - N_cc_1)*0.1 ; // Get the step for the Capacity Cc (10%)
  eps7 = (N_alpha_i_2 - N_alpha_i_1)*0.1 ;  // Get the step for the alpha_i (10%)
  eps8 = (N_alpha_m_2 - N_alpha_m_1)*0.1 ;  // Get the step for the alpha_m (10%)
  eps9 = (N_alpha_c_2 - N_alpha_c_1)*0.1 ;  // Get the step for the alpha_c (10%)

  uniform_real_distribution<double> distribution1(N_ri_1, N_ri_2) ;
  uniform_real_distribution<double> distribution2(N_rm_1, N_rm_2) ;
  uniform_real_distribution<double> distribution3(N_rc_1, N_rc_2) ;
  uniform_real_distribution<double> distribution4(N_ci_1, N_ci_2) ;
  uniform_real_distribution<double> distribution5(N_cm_1, N_cm_2) ;
  uniform_real_distribution<double> distribution6(N_cc_1, N_cc_2) ;
  uniform_real_distribution<double> distribution7(N_alpha_i_1, N_alpha_i_2) ;
  uniform_real_distribution<double> distribution8(N_alpha_m_1, N_alpha_m_2) ;
  uniform_real_distribution<double> distribution9(N_alpha_c_1, N_alpha_c_2) ;

  Ri_0 = distribution1(gen) ;
  Rm_0 = distribution2(gen) ;
  Rc_0 = distribution3(gen) ;
  Ci_0 = distribution4(gen) ;
  Cm_0 = distribution5(gen) ;
  Cc_0 = distribution6(gen) ;
  alpha_i_0 = distribution7(gen) ;
  alpha_m_0 = distribution8(gen) ;
  alpha_c_0 = distribution9(gen) ;

}

void rand_values(double& Ri_1, double& Rm_1, double& Rc_1, double& Ci_1, double& Cm_1, double& Cc_1, double& alpha_i_1, double& alpha_m_1, double& alpha_c_1,
                 double Ri_0, double Rm_0, double Rc_0, double Ci_0, double Cm_0, double Cc_0, double alpha_i_0, double alpha_m_0, double alpha_c_0,
                 double eps1, double eps2, double eps3, double eps4, double eps5, double eps6, double eps7, double eps8, double eps9) {

  random_device rd ;
  default_random_engine gen(rd()) ;

  uniform_real_distribution<double> distribution1(Ri_0-eps1, Ri_0+eps1) ;
  uniform_real_distribution<double> distribution2(Rm_0-eps2, Rm_0+eps2) ;
  uniform_real_distribution<double> distribution3(Rc_0-eps3, Rc_0+eps3) ;
  uniform_real_distribution<double> distribution4(Ci_0-eps4, Ci_0+eps4) ;
  uniform_real_distribution<double> distribution5(Cm_0-eps5, Cm_0+eps5) ;
  uniform_real_distribution<double> distribution6(Cc_0-eps6, Cc_0+eps6) ;
  uniform_real_distribution<double> distribution7(alpha_i_0-eps7, alpha_i_0+eps7) ;
  uniform_real_distribution<double> distribution8(alpha_m_0-eps8, alpha_m_0+eps8) ;
  uniform_real_distribution<double> distribution9(alpha_c_0-eps9, alpha_c_0+eps9) ;

  Ri_1 = distribution1(gen) ;
  Rm_1 = distribution2(gen) ;
  Rc_1 = distribution3(gen) ;
  Ci_1 = distribution4(gen) ;
  Cm_1 = distribution5(gen) ;
  Cc_1 = distribution6(gen) ;
  alpha_i_1 = distribution7(gen) ;
  alpha_m_1 = distribution8(gen) ;
  alpha_c_1 = distribution9(gen) ;
}


void simulated_annealing(double T_max, double T_min) {

  double Ri_0, Rm_0, Rc_0, Ci_0, Cm_0, Cc_0, alpha_i_0, alpha_m_0, alpha_c_0 ;
  double Ri_1, Rm_1, Rc_1, Ci_1, Cm_1, Cc_1, alpha_i_1, alpha_m_1, alpha_c_1 ;
  double eps1, eps2, eps3, eps4, eps5, eps6, eps7, eps8, eps9 ;
  double q0, q1 ;
  double Ri_min, Rm_min, Rc_min, Ci_min, Cm_min, Cc_min, alpha_i_min, alpha_m_min, alpha_c_min ;
  double N_ri_1, N_ri_2, N_rm_1, N_rm_2, N_rc_1, N_rc_2 ; 
  double N_ci_1, N_ci_2, N_cm_1, N_cm_2, N_cc_1, N_cc_2, N_alpha_i_1, N_alpha_i_2, N_alpha_m_1, N_alpha_m_2, N_alpha_c_1, N_alpha_c_2 ;

  vector<double> freq ;
  data_in_vector("average/frequence.txt", freq) ;

  vector<double> magn_t ;
  data_in_vector("average/average_Magnitude.txt", magn_t) ;

  vector<double> phase_t ;
  data_in_vector("average/average_Phase_deg.txt", phase_t) ;


  rand_start_values(Ri_0, Rm_0, Rc_0, Ci_0, Cm_0, Cc_0, alpha_i_0, alpha_m_0, alpha_c_0, eps1, eps2, eps3, eps4, eps5, eps6, eps7, eps8, eps9, N_ri_1, N_ri_2, N_rm_1, N_rm_2, N_rc_1, N_rc_2, N_ci_1, N_ci_2, N_cm_1, N_cm_2, N_cc_1, N_cc_2, N_alpha_i_1, N_alpha_i_2, N_alpha_m_1, N_alpha_m_2, N_alpha_c_1, N_alpha_c_2) ; // initialize the values
  q0 = cost(Ri_0, Rm_0, Rc_0, Ci_0, Cm_0, Cc_0, alpha_i_0, alpha_m_0, alpha_c_0, freq, magn_t, phase_t) ; // Calculate the function "cost" for Ri_0,Ci_0,Rm_0,Cm_0,Rc_0,Cc_0,alpha_i_0,alpha_m_0,alpha_c_0

  double minimum = q0 ;
  double T = T_max ;

  while (T > T_min) {
    for (uint i = 1; i < 20000; i++) {
      do {
        rand_values(Ri_1, Rm_1, Rc_1, Ci_1, Cm_1, Cc_1, alpha_i_1, alpha_m_1, alpha_c_1, Ri_0, Rm_0, Rc_0, Ci_0, Cm_0, Cc_0, alpha_i_0, alpha_m_0, alpha_c_0, eps1, eps2, eps3, eps4, eps5, eps6, eps7, eps8, eps9) ;
      } while((alpha_i_1<N_alpha_i_1)||(alpha_i_1>N_alpha_i_2)||(alpha_m_1<N_alpha_m_1)||(alpha_m_1>N_alpha_m_2)||(alpha_c_1<N_alpha_c_1)||(alpha_c_1>N_alpha_c_2)||(Ri_1<N_ri_1)||(Ri_1>N_ri_2)||(Rm_1<N_rm_1)||(Rm_1>N_rm_2)||(Rc_1<N_rc_1)||(Rc_1>N_rc_2)||(Ci_1<N_ci_1)||(Ci_1>N_ci_2)||(Cm_1<N_cm_1)||(Cm_1>N_cm_2)||(Cc_1<N_cc_1)||(Cc_1>N_cc_2)) ;

       q1 = cost(Ri_1, Rm_1, Rc_1, Ci_1, Cm_1, Cc_1, alpha_i_1, alpha_m_1, alpha_c_1, freq, magn_t, phase_t) ;

       random_device rd ;
       default_random_engine gen(rd()) ;

       uniform_real_distribution<double> distribution1(0,1) ;
       double prob = distribution1(gen) ;

       if (minimum > q1) {
         minimum = q1 ;
         Ri_min = Ri_1 ;
         Rm_min = Rm_1 ;
         Rc_min = Rc_1 ;
         Ci_min = Ci_1 ;
         Cm_min = Cm_1 ;
         Cc_min = Cc_1 ;
         alpha_i_min = alpha_i_1 ;
         alpha_m_min = alpha_m_1 ;
         alpha_c_min = alpha_c_1 ;
       }

       if (q0 > q1) {
         q0 = q1 ;
         Ri_0 = Ri_1 ;
         Rm_0 = Rm_1 ;
         Rc_0 = Rc_1 ;
         Ci_0 = Ci_1 ;
         Cm_0 = Cm_1 ;
         Cc_0 = Cc_1 ;
         alpha_i_0 = alpha_i_1 ;
         alpha_m_0 = alpha_m_1 ;
         alpha_c_0 = alpha_c_1 ;
       }
       else if ((exp(-(q1-q0)/T)) > prob){
         Ri_0 = Ri_1 ;
         Ci_0 = Ci_1 ;
         Rc_0 = Rc_1 ;
         Rm_0 = Rm_1 ;
         Cm_0 = Cm_1 ;
         Cc_0 = Cc_1 ;
         alpha_i_0 = alpha_i_1 ;
         alpha_m_0 = alpha_m_1 ;
         alpha_c_0 = alpha_c_1 ;
         q0 = q1 ;
       }
     }
     T *= 0.99 ; // Coefficient permettant de réduire le T pour atteindre le T-min
  }
  cout << "min = " << minimum << endl ;
  cout << "Ri_min = " << Ri_min << endl ;
  cout << "Rm_min = " << Rm_min << endl ;
  cout << "Rc_min = " << Rc_min << endl ;
  cout << "Ci_min = " << Ci_min << endl ;
  cout << "Cm_min = " << Cm_min << endl ;
  cout << "Cc_min = " << Cc_min << endl ;
  cout << "alpha_i_min = " << alpha_i_min << endl ;
  cout << "alpha_m_min = " << alpha_m_min << endl ;
  cout << "alpha_c_min = " << alpha_c_min << endl ;
}

