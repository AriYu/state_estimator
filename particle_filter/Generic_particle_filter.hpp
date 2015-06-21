#ifndef Generic_particle_filter_H_
#define Generic_particle_filter_H_

#include "../estimator/estimator.hpp"
#include "./particle.hpp"

class GenericParticleFilter : public Filter {
public:
  // コンストラクタ
  GenericParticleFilter(int dim, int num):
	particle_manager_(dim, num){}
  // 更新する
  virtual void update() override {
	particle_manager_.process([&](Particle& particle)
							  {particle.weight_ = 1;});

	ConsoleParticlePlotter console_plotter;
	particle_manager_.plot(console_plotter);
  }

private:
  ParticleManager particle_manager_;
};

#endif // Generic_particle_filter_H_
