#ifndef ESTIMATOR_H_
#define ESTIMATOR_H_

#include <iostream>

class Filter{
public:
  // 仮想デストラクタ
  virtual ~Filter(){}
  // 更新する
  virtual void update() = 0;
};

class Estimator{
public:
  // コンストラクタ
  Estimator(Filter* filter):
	filter_(filter){
  }
  // デストラクタ
  ~Estimator(){
	delete filter_;
  }
  // 推定
  void estimate(){
	filter_->update();
  }
private:
  Filter* filter_;

};

#endif // ESTIMATOR_H_
