#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <random> // For the uniform_real_distribution

using namespace std ;

struct complex {
  double real, img ;
};

// File into vector
void data_in_vector(string, vector<double>&) ;

// Vector into data
void magn_into_data(string, double, double, double, double, double, double, vector<double>) ;
void phase_into_data(string, double, double, double, double, double, double, vector<double>) ;

// Get the impedance
complex get_z(double, double, double, double, double, double, double) ;

// Magnitude and Phase
double magnitude(complex z) ;
double phase(complex z) ;

// Function cost to minimize
double cost(double, double, double, double, double, double, vector<double>, vector<double>, vector<double>) ;


// Optimisation algorithm : Simulated annealing
void rand_start_values(double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, double&, uint&, uint&, uint&, uint&, double&, double&, double&, double&, double&, double&, double&, double&) ;
void rand_values(double&, double&, double&, double&, double&, double&, double, double, double, double, double, double, double, double, double, double, double, double) ;
void simulated_annealing(double, double) ;
