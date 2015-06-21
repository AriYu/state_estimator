#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <iostream>
#include <memory>
#include <algorithm>
#include <opencv2/core/core.hpp>

class Particle{
public:
  // コンストラクタ
  Particle() : weight_(0) {}
  Particle(int dim) : weight_(0) {
	stateResize(dim);
  }
  // 状態ベクトルのサイズを変更
  void stateResize(int dim){
	state_ =  cv::Mat::zeros(dim, 1, CV_64F);
  }
  // デストラクタ
  ~Particle(){}
public:
  cv::Mat state_;
  double weight_;
};

using ParticlePtr = std::shared_ptr<Particle>;

class ParticleManager{
public:
  // プロット専用インターフェイス
  class Plotter {
  public:
	virtual ~Plotter(){}
	// プロット
	virtual void plot(const Particle& particle) = 0;
  };
public:
  // コンストラクタ
  ParticleManager(){}
  ParticleManager(int dim, int num){
	createParticles(dim, num);
  }
  // 巡回
  void each(std::function<void (Particle&)> action){
	std::for_each(particles_.begin(), particles_.end(),
					[&](const ParticlePtr& particle){
					action(*particle);});
  }
  void createParticles(int dim, int num){
	for(int i = 0; i < num; i++){ 
	  ParticlePtr particle_ptr(new Particle(dim));
	  particles_.push_back(particle_ptr);
	}
  }
  // 状態遷移
  void process(std::function<void (Particle&)> processmodel){
  	each([&](Particle& particle) {
  		processmodel(particle);
  	  });
  }
  // プロット
  void plot(Plotter& plotter){
	each([&](Particle& particle) {plotter.plot(particle);});
  }

  // コピー禁止
  ParticleManager(const ParticleManager& other) = delete;
  ParticleManager& operator= (const ParticleManager& other) = delete;
private:
  std::vector<ParticlePtr> particles_;
};

class ConsoleParticlePlotter : public ParticleManager::Plotter {
public:
  virtual void plot(const Particle& particle) override {
	std::cout << "State : " << particle.state_ << std::endl;
	std::cout << "weight : " << particle.weight_ << std::endl;
  }
};

#endif // PARTICLE_H_
