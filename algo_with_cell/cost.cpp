#include "optimisation.hpp"


void data_in_vector(string file, vector<double>& vec){
  ifstream infile(file) ;
  double freq, save ;

  for(uint i=0; i<20; i++){
    infile >> freq >> save;
    vec.push_back(save);
  }
}

void magn_into_data(string filename, double Ri, double Rm, double Rc, double Ci, double Cm, double Cc, double alpha_i, double alpha_m, double alpha_c, vector<double>frequence){
  ofstream outfile(filename) ;
  complex z ;

  for(uint i = 0; i < frequence.size() ; i++){
      z = get_z(Ri, Rm, Rc, Ci, Cm, Cc, alpha_i, alpha_m, alpha_c, frequence[i]) ;
      outfile << frequence[i] << " " << magnitude(z) << endl ;
  }
}

void phase_into_data(string filename, double Ri, double Rm, double Rc, double Ci, double Cm, double Cc, double alpha_i, double alpha_m, double alpha_c, vector<double>frequence){
  ofstream outfile(filename) ;
  complex z ;

  for (uint i = 0; i < frequence.size(); i++) {
    z = get_z(Ri, Rm, Rc, Ci, Cm, Cc, alpha_i, alpha_m, alpha_c, frequence[i]) ;
    outfile << frequence[i] << " " << phase(z) << endl ;
  }
}


complex get_z(double Ri, double Rm, double Rc, double Ci, double Cm, double Cc, double alpha_i, double alpha_m, double alpha_c, double freq){

  complex z ;
  double num_real_electrode, num_img_electrode, deno_electrode ;
  double real_electrolyte, img_electrolyte ;
  double real_cell, img_cell ;
  double deno ;
  double w = 2*M_PI*freq ;

  num_real_electrode = Ri+(Ri*Ri*Ci*pow(w,alpha_i)*cos((M_PI/2)*alpha_i)) ; 
  num_img_electrode = Ri*Ri*Ci*pow(w,alpha_i)*sin((M_PI/2)*alpha_i) ; 
  deno_electrode = 1 + (Ri*Ci*pow(w,alpha_i)*2*cos((M_PI/2)*alpha_i)) + (Ri*Ri*Ci*Ci*pow(w,2*alpha_i)) ; 

  real_electrolyte = ((Rm+(Rm*Rm*Cm*pow(w,alpha_m)*cos((M_PI/2)*alpha_m)))/(1 + (Rm*Cm*pow(w,alpha_m)*2*cos((M_PI/2)*alpha_m)) + (Rm*Rm*Cm*Cm*pow(w,2*alpha_m)))) ;
  img_electrolyte = ((Rm*Rm*Cm*pow(w,alpha_m)*sin((M_PI/2)*alpha_m))/(1 + (Rm*Cm*pow(w,alpha_m)*2*cos((M_PI/2)*alpha_m)) + (Rm*Rm*Cm*Cm*pow(w,2*alpha_m)))) ;

  real_cell = (Rc +((cos((M_PI/2)*alpha_c))/(Cc*pow(w,alpha_c)))) ; 
  img_cell = ((-sin((M_PI/2)*alpha_c))/(Cc*pow(w,alpha_c))) ;

  deno = (real_cell*real_cell) + (2*real_cell*real_electrolyte) + (real_electrolyte*real_electrolyte) + (img_cell*img_cell) + (2*img_cell*img_electrolyte) + (img_electrolyte*img_electrolyte) ;

  z.real = ((2*num_real_electrode)/deno_electrode) + (((real_cell*real_cell*real_electrolyte) + (real_cell*real_electrolyte*real_electrolyte) + (real_cell*img_electrolyte*img_electrolyte) + (real_electrolyte*img_cell*img_cell))/(deno)) ;
  z.img  = ((2*num_img_electrode)/deno_electrode) + (((img_cell*img_cell*img_electrolyte) + (img_cell*img_electrolyte*img_electrolyte) + (real_cell*real_cell*img_electrolyte) + (real_electrolyte*real_electrolyte*img_cell))/(deno)) ;

  return z ;
}

double magnitude(complex z){
  return sqrt((z.real*z.real)+(z.img*z.img)) ;
}

double phase(complex z){
  return ((asin(z.img/magnitude(z))*180)/M_PI) ;
}



double cost(double Ri, double Rm, double Rc, double Ci, double Cm, double Cc, double alpha_i, double alpha_m, double alpha_c, vector<double> freq, vector<double> magn_t, vector<double> phase_t){

  double res = 0 ;
  complex z ;

  vector<double> magn_c (freq.size()) ; // Initialisation of the magnitude to calculate
  vector<double> phase_c (freq.size()) ; // Initialisation of the phase to calculate

  // Make the calcul of the hypothetics magn and phase
  for (uint i = 0; i < freq.size(); i++) {
    z =  get_z(Ri, Rm, Rc, Ci, Cm, Cc, alpha_i, alpha_m, alpha_c, freq[i]) ;
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
    // res += fabs(magn_t[i] - magn_c[i])/fabs(max_magn) + fabs(phase_t[i] - phase_c[i])/fabs(max_phase) ; // norme 1 avec normalisation
    // cout << "norm_magn = " << fabs(magn_t[i] - magn_c[i])/fabs(max_magn) << endl ;
    // cout << "norm_phase = " << 5*fabs(phase_t[i] - phase_c[i])/fabs(max_phase) << endl ;
    // cout << endl ;
    // res += pow((fabs(magn_t[i] - magn_c[i])), 2) + pow((fabs(phase_t[i] - phase_c[i])), 2) ; // norme 2
    // res += pow((fabs(magn_t[i] - magn_c[i])), 2)/fabs(max_magn) + pow((fabs(phase_t[i] - phase_c[i])), 2)/fabs(max_phase) ; // norme 2 avec normalisation
  }


  return res ; // sqrt(res) pour norme 2
}
