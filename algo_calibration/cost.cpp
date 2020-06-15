#include "optimisation.hpp"


void data_in_vector(string file, vector<double>& vec){
  ifstream infile(file) ;
  double freq, save ;

  for(uint i=0; i<20; i++){
    infile >> freq >> save;
    vec.push_back(save);
  }
}

void magn_into_data(string filename, double R, double C, double alpha, vector<double>frequence){
  ofstream outfile(filename) ;
  complex z ;

  for(uint i = 0; i < frequence.size() ; i++){
      z = get_z(R,C,alpha,frequence[i]) ;
      outfile << frequence[i] << " " << magnitude(z) << endl ;
  }
}

void phase_into_data(string filename, double R, double C, double alpha, vector<double>frequence){
  ofstream outfile(filename) ;
  complex z ;

  for (uint i = 0; i < frequence.size(); i++) {
    z = get_z(R,C,alpha,frequence[i]) ;
    outfile << frequence[i] << " " << -1*phase(z) << endl ;
  }
}



complex get_z(double R, double C, double alpha, double freq){

  complex z ;
  double num_real, num_img, deno ;
  double w = 2*M_PI*freq ;

  num_real = R+(R*R*C*pow(w,alpha)*cos((M_PI/2)*alpha)) ;
  num_img = R*R*C*pow(w,alpha)*sin((M_PI/2)*alpha) ;
  deno = 1+(R*C*pow(w,alpha)*2*cos((M_PI/2)*alpha))+(R*R*C*C*pow(w,2*alpha)) ;

  z.real = num_real/deno ;
  z.img  = num_img/deno ;

  return z ;
}

double magnitude(complex z){
  return sqrt((z.real*z.real)+(z.img*z.img)) ;
}

double phase(complex z){
  return asin(z.img/magnitude(z)) ;
}



double cost(double R, double C, double alpha, vector<double> freq, vector<double> magn_t, vector<double> phase_t){

  double res = 0 ;
  complex z ;

  vector<double> magn_c (freq.size()) ; // Initialisation of the magnitude to calculate
  vector<double> phase_c (freq.size()) ; // Initialisation of the phase to calculate

  // Make the calcul of the hypothetics magn and phase
  for (uint i = 0; i < freq.size(); i++) {
    z = get_z(R, C, alpha, freq[i]) ;
    magn_c[i] = magnitude(z) ;
    phase_c[i] = phase(z) ;
  }

  // Normalisation of the cost
  double max_magn = magn_t[0] - magn_c[0], max_phase = phase_t[0] - phase_c[0] ;
  for(uint i = 1; i < freq.size(); i++){
    if (fabs(magn_t[i] - magn_c[i]) > fabs(max_magn)) {
      max_magn = magn_t[i] - magn_c[i] ;
    }
    if (fabs(phase_t[i] - phase_c[i]) > fabs(max_phase)) {
      max_phase = phase_t[i] - phase_c[i] ;
    }
  }

  for (uint i = 0; i < freq.size(); i++) {
    res += fabs(magn_t[i] - magn_c[i]) + fabs(phase_t[i] - phase_c[i]) ; // norme 1
    // cout << "magn = " << fabs(magn_t[i] - magn_c[i]) << endl ;
    // cout << "phase = " << fabs(phase_t[i] - phase_c[i]) << endl ;
    // cout << endl ;
    // cout << "magn_norm = " << fabs(magn_t[i] - magn_c[i])/fabs(max_magn) << endl ;
    // cout << "phase_norm = " << fabs(phase_t[i] - phase_c[i])/fabs(max_phase) << endl ;
    // cout << endl ;
    // res += fabs(magn_t[i] - magn_c[i])/fabs(max_magn) + fabs(phase_t[i] - phase_c[i])/fabs(max_phase) ; // norme 1 avec normalisation
    // res += pow((fabs(magn_t[i] - magn_c[i])), 2) + pow((fabs(phase_t[i] - phase_c[i])), 2) ; // norme 2
    // res += pow((fabs(magn_t[i] - magn_c[i])), 2)/fabs(max_magn) + pow((fabs(phase_t[i] - phase_c[i])), 2)/fabs(max_phase) ; // norme 2 avec normalisation
  }


  return res ; // sqrt(res) pour norme 2
}
