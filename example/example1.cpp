#include <iostream>
#include "../particle_filter/Generic_particle_filter.hpp"

using namespace std;

int main(void)
{
  int num_of_dimension = 1; 
  int num_of_particle = 5;
  Estimator 
	particle_filter(new GenericParticleFilter(num_of_dimension, num_of_particle));

	particle_filter.estimate();

  return 0;
}
