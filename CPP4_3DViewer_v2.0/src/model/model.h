/**
 * @file model.h
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief model class header
 * @version 0.1
 * @date 2023-11-26
 * @copyright Copyright (c) 2023
 */
#ifndef _SRC_MODEL_MODEL_H_
#define _SRC_MODEL_MODEL_H_
#include <memory>

#include "./obj3d.h"
#include "./strategy.h"

namespace s21 {
/**
 * @brief a model class
 * contain all of logic
 * @class Model
 */
class Model final : public Obj3d {
 public:
  /**
   * @brief Construct a new Model object
   */
  Model(IStrategy *s = nullptr) : strategy_(s){};
  /**
   * @brief Destroy the Model object
   */
  ~Model() { delete strategy_; };
  /**
   * @brief rescales initial object to fit in chosen scale factor
   * @param[in] scaleVal scale factor
   * @sa used gui part for initial rescaling
   */
  void initialRescaleObj(double);
  /**
   * @brief Set the new Affine transformation
   * @param strategy ptr to need affine transformation
   */
  Model &setAffine(IStrategy *);
  /**
   * @brief doing particular affine transformation
   * @param value for transformation
   */
  void doAffine(double);

 private:
  IStrategy *strategy_; /*<! contain particular affine transformation */
  /**
   * @brief calculates the max distance between max and min of an axis amoung
   * all axes
   * @return double value of a max distance between max and min of an axis
   * @sa used in rescaleObj()
   */
  double findMaxAxisDistance_();
  /**
   * @brief common move function
   * @param[in] value to move
   * @param[out] max value of object
   * @param[out] min value of object
   * @param[in] offset of vertex coord: 0=x,1=y,2=z
   */
  // void move_(double, double &, double &, int);
};

}  // namespace s21
#endif  //_SRC_MODEL_MODEL_H_