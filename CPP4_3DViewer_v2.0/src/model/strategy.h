/**
 * @file strategy.h
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief  strategy pattern header
 * @version 0.1
 * @date 2023-12-21
 * @copyright Copyright (c) 2023
 */
#ifndef _SRC_MODEL_STRATEGY_H_
#define _SRC_MODEL_STRATEGY_H_
#include "./obj3d.h"
namespace s21 {
/**
 * @brief interfase of strategy pattern
 */
class IStrategy {
 public:
  /**
   * @brief Destroy the IStrategy object
   */
  virtual ~IStrategy() = default;
  /**
   * @brief doing concrete affine transformation
   * @param o ref to obj3d model
   * @param value of transformation
   */
  virtual void doAffine(Obj3d *, double) = 0;
};
/**
 * @brief move by x axis
 */
class MoveX : public IStrategy {
 public:
  /**
   * @brief realization move by x axis
   * @param Obj3d ptr moving object
   * @param double volume of move
   */
  void doAffine(Obj3d *, double) override;
};
/**
 * @brief move by y axis
 */
class MoveY : public IStrategy {
 public:
  /**
   * @brief realization move by z axis
   * @param Obj3d ptr moving object
   * @param double volume of move
   */
  void doAffine(Obj3d *, double) override;
};
/**
 * @brief move by z axis
 */
class MoveZ : public IStrategy {
 public:
  /**
   * @brief realization move by z axis
   * @param Obj3d ptr moving object
   * @param double volume of move
   */
  void doAffine(Obj3d *, double) override;
};
/**
 * @brief rotate about z axis
 */
class RotateZ : public IStrategy {
 public:
  /**
   * @brief realization rotate about z axis
   * @param Obj3d ptr rotating object
   * @param double volume for rotate
   */
  void doAffine(Obj3d *, double) override;
};
/**
 * @brief rotate about x axis
 */
class RotateX : public IStrategy {
 public:
  /**
   * @brief realization rotate about x axis
   * @param Obj3d ptr rotating object
   * @param double volume for rotate
   */
  void doAffine(Obj3d *, double) override;
};

/**
 * @brief rotate about y axis
 */
class RotateY : public IStrategy {
 public:
  /**
   * @brief realization rotate about y axis
   * @param Obj3d ptr rotating object
   * @param double volume for rotate
   */
  void doAffine(Obj3d *, double) override;
};

/**
 * @brief rescale object
 */
class Rescale : public IStrategy {
 public:
  /**
   * @brief realization rescale
   * @param Obj3d ptr of rescale object
   * @param double volume for rotate
   */
  void doAffine(Obj3d *, double) override;
};

}  // namespace s21
#endif  // _SRC_MODEL_STRATEGY_H_