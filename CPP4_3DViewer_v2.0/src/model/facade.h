/**
 * @file facade.h
 * @author nidorina (nidorina@student.21-school.ru)
 * @brief facade class header
 * @version 0.1
 * @date 2023-12-22
 * @copyright Copyright (c) 2023
 */

#ifndef _SRC_MODEL_FACADE_H_
#define _SRC_MODEL_FACADE_H_
#include "./model.h"
#include "./obj3d.h"
namespace s21 {

/**
 * @brief class that is simple interface to complicated logic
 */
class Facade {
 protected:
  Model model_; /*!< ref to instance of model*/

 public:
  /**
   * @brief Construct a new Facade object
   * @param m ref to instans of the Model
   */
  // Facade(Model& m) : model_(m){};
  /**
   * @brief load 3d object from file
   * @param[in] file_name const char*
   */
  void loadFromFile(const char* fname);
  /**
   * @brief Get the Vtx array
   * @return const double*
   */
  const double* getVtx() const noexcept;
  /**
   * @brief Get the Polygons of object
   * @return array of polygon
   */
  std::vector<std::vector<unsigned int>>& GetPolygons();
  /**
   * @brief Get the Vertexes Count of object
   * @return unsigned int count
   */
  unsigned int GetVtxCount();
  /**
   * @brief Get the Facets Count of object
   * @return unsigned int count
   */
  unsigned int GetFctCount();
  /**
   * @brief Get the bounded Vertexes of facet
   * @return unsigned int size of array of vetexes of the facet
   */
  unsigned int GetFctVtx(unsigned int);
  /**
   * @brief Get the Total Indices of object
   * @return unsigned int count
   */
  unsigned int GetTotalIndices();
  /**
   * @brief rescales initial object to fit in chosen scale factor
   * @param[in] Val scale factor
   * @sa used gui part for initial rescaling
   */
  void initialRescaleObj(double);
  /**
   * @brief rescales object to fit in chosen scale factor
   * @param[in] scaleApply scale factor
   * @sa used gui part for initial rescaling
   */
  void rescaleObj(double);
  /**
   * @brief move object by x axis
   * @param[in] value of move
   */
  void moveX(double);
  /**
   * @brief move object by y axis
   * @param[in] value of move
   */
  void moveY(double);
  /**
   * @brief move object by z axis
   * @param[in] value of move
   */
  void moveZ(double);
  /**
   * @brief rotate object around X axis
   * @param[in] value of rotate
   */
  void rotateX(double);
  /**
   * @brief rotate object around Y axis
   * @param[in] value of rotate
   */
  void rotateY(double);
  /**
   * @brief rotate object around Z axis
   * @param[in] value of rotate
   */
  void rotateZ(double);
};

}  // namespace s21
#endif  //_SRC_MODEL_FACADE_H_