/**
 * @file obj3d.h
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief header of object3d class
 * @version 0.1
 * @date 2023-11-26
 * @copyright Copyright (c) 2023
 */
#ifndef _SRC_MODEL_OBJ3D_H_
#define _SRC_MODEL_OBJ3D_H_

#include <iostream>
#include <string>
#include <vector>

namespace s21 {

constexpr int BUFF_SIZE = (16 * 4096);  //!< 64KB buffer
// constexpr int DIMEN = 3;                //!< dimension of space

/**
 * @brief structure that contain axis min/max info
 */
struct axis_t {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
};
/**
 * @brief structure that contain axis center info
 */
struct centers_t {
  double x_center;
  double y_center;
  double z_center;
};

/**
 * @brief Resource Acquisition Is Initialization class of 3d object
 * @class Obj3d
 */
class Obj3d {
 protected:
  unsigned int total_indices;  /*!< total amount of all facets indices*/
  std::vector<double> vtx_arr; /*!< array of vertexes x1,y1,z1,x2..*/
  std::vector<std::vector<unsigned int>> polygons; /*!< array of facets*/
  centers_t centers;                               /*!< object's center*/
  axis_t bounds;                                   /*!< object's dimesions*/

 public:
  /**
   * @brief Construct a new Obj 3d object
   */
  Obj3d() { initObj3d_(); };
  /**
   * @brief Destroy the Obj 3d object
   */
  ~Obj3d() { free_obj3d_(); };
  /**
   * @brief centers object in a window
   */
  void centerObj();
  /**
   * @brief
   * @param f const char * file name
   * @return bool status of operation
   */
  bool loadFromFile(const char *);
  // getters
  /**
   * @brief Get the Vertexes array
   * @return const double*
   */
  const double *getVertexes() const noexcept;
  /**
   * @brief Get the Bounds of object
   * @return axis_t
   */
  axis_t GetBounds() const noexcept;
  /**
   * @brief Get the Polygons of object
   * @return array of polygon
   */
  std::vector<std::vector<unsigned int>> &GetPolygons();
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
   * @return unsigned int count of vetexes of the facet
   */
  unsigned int GetFctVtx(unsigned int);
  /**
   * @brief Get the Total Indices of object
   * @return unsigned int count
   */
  unsigned int GetTotalIndices();
  // setters
  /**
   * @brief Set the Bounds of object
   * @return axis_t&
   */
  axis_t &SetBounds() noexcept;
  /**
   * @brief Set the Vertexes object
   * @return std::vector<double>*
   */
  std::vector<double> *setVertexes() noexcept;

 private:
  /**
   * @brief check if file openable
   * @param f const char * file name
   * @return file ptr or null
   */
  FILE *openFile_(const char *);
  /**
   * @brief intializing obj3d struct with NULL and 0
   * @sa used in read_obj_()
   */
  void initObj3d_();
  /**
   * @brief read 3d object file and count vertexes and facets
   * and set them to res->vtx_count and res->fct_count
   * and allocated memory for object and fill memory
   * @warning opened file doesn't close, don't forget to close it
   * @warning also don't forget to freeing an allocated memory after use it
   * @sa contain s21_alloc_mem_(), fill_obj3d_()
   */
  bool read_obj_(FILE *);
  /**
   * @brief reading the file a second time and
   * parse vertexes and faces from the
   * file and fill it to memory structure
   * @param[in] f ptr to obj file
   * @return bool status of operation
   * @warning Don't forget to free memory free_obj3d()
   * @sa contain fill_facets_()
   */
  int fill_obj3d_(FILE *);
  /**
   * @brief freeing allocated memory
   * @sa used in s21_alloc_mem_() and used by yourself and in destructor
   */
  void free_obj3d_();
  /**
   * @brief parses main/max values for each axis (x, y, z)
   * @param[in] x x value of a point
   * @param[in] y y value of a point
   * @param[in] z z value of a point
   * @param[in] first_line flag to indicate first line for initializing values
   * in first iteration
   * @sa used in fill_obj3d_()
   */
  void parseMaxMin_(double, double, double, int);
  /**
   * @brief count vertexes of facets, then
   * allocate memory for it and fill it
   * @param[in] buffer ptr to sting with property of facet
   * @param[in] index index of current handled facet
   * @return bool status of operation #st enum
   * @sa free_obj3d_(), fill_obj3d_()
   * @sa contain count_vtx_of_facet_(), parse_vertices_()
   */
  bool fill_facets_(const char *);
  /**
   * @brief counts how many vertices are registered for the polygon
   * @param[in] buffer ptr to string of facet beginnig 'f' and separated by
   * space like "f 5 3 1"
   * @return int amount vertices
   * @sa used in fill_facets_()
   */
  unsigned int count_vtx_of_facet_(const char *);
  /**
   * @brief parse vertices from buffer and put it to obj3d
   * structure according their index and sequence number
   * @param[in] buffer string with facet property like "f 3/4/5 34//3 564"
   * @param[in] index index of facet in a row
   * @return int count of vetices of the facet
   * @sa used in fill_facets_()
   */
  unsigned int parse_vertices_(const char *);
  /**
   * @brief compares min and max axis values to passed comparable
   * @param[out] have_min min value of chosen axis
   * @param[out] have_max max value of chosen axis
   * @param[in] comparable the value with which the min and max values of the
   * axes are compared
   * @sa used in parseMaxMin()
   */
  void compareNums_(double &, double &, double);
  /**
   * @brief calculates the center of an axis
   * @param[out] minVal axis minimal value
   * @param[out] maxVal axis maximal value
   * @return double value a axis center
   * @sa used in centerObj()
   */
  double centersFormula_(double &, double &);

};  // Obj3d

}  // namespace s21

#endif  //_SRC_MODEL_OBJ3D_H_