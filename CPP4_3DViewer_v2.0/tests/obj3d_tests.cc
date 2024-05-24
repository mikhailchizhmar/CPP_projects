/**
 * @file obj3d_tests.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief test obj3d class
 * @version 0.1
 * @date 2023-09-26
 * @copyright Copyright (c) 2023
 */
#include <gtest/gtest.h>
#define protected public
#define private public

#include "s21_3dviewer_v2_tests.h"

namespace S21Test {

using namespace s21;

// arrange fixture
class Obj3dTest : public ::testing::Test {
 protected:
  void SetUp() {}
  void TearDown() {}
  Obj3d obj;
};

/*---------------obj3d-------------------*/
TEST_F(Obj3dTest, simple_test1) {
  // Arrange
  // Act
  EXPECT_DOUBLE_EQ(3.14, 3.14);  // Assert
  EXPECT_EQ(21, 21);             // Assert
  EXPECT_TRUE(true);             // Assert
}

TEST_F(Obj3dTest, open_file_fail) {
  const char *file_name{"sadflasdf"};  // Arrange
  FILE *f = NULL;                      // Arrange
  f = obj.openFile_(file_name);        // Act
  EXPECT_EQ(f, nullptr);               // Assert
}

TEST_F(Obj3dTest, open_file_ok) {
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  FILE *f = NULL;                                     // Arrange
  f = obj.openFile_(file_name);                       // Act
  EXPECT_NE(f, nullptr);                              // Assert
  fclose(f);
}

TEST_F(Obj3dTest, count_vtx_fct) {
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  FILE *f = NULL;                                     // Arrange
  f = obj.openFile_(file_name);                       // Act
  obj.read_obj_(f);
  // EXPECT_EQ(obj.vtx_count, 8);   // Assert
  // EXPECT_EQ(obj.fct_count, 12);  // Assert
  // fclose(f);
  EXPECT_EQ(obj.vtx_arr.size() / 3, 8);  // Assert
  EXPECT_EQ(obj.polygons.size(), 12);    // Assert
}

TEST_F(Obj3dTest, read_vertexes) {
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  FILE *f = NULL;                                     // Arrange
  f = obj.openFile_(file_name);                       // Act
  obj.read_obj_(f);
  EXPECT_DOUBLE_EQ(obj.vtx_arr[0], .5);    // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[1], -.5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[2], -.5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[3], .5);    // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[4], -.5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[5], .5);    // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[6], -.5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[7], -.5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[8], .5);    // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[9], -.5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[10], -.5);  // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[11], -.5);  // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[12], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[13], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[14], -.5);  // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[15], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[16], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[17], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[18], -.5);  // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[19], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[20], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[21], -.5);  // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[22], .5);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[23], -.5);  // Accert
  EXPECT_EQ(obj.polygons[3].size(), 3);    // Accert
  EXPECT_EQ(obj.polygons[3][0], 6 - 1);    // Accert
  EXPECT_EQ(obj.polygons[3][1], 7 - 1);    // Accert
  EXPECT_EQ(obj.polygons[3][2], 3 - 1);    // Accert
  // fclose(f);
  // obj.free_obj3d_();  // Act
}

TEST_F(Obj3dTest, fill_obj3d_vertexes) {
  const char *file_name{"../data-samples/deer.obj"};  // Arrange
  FILE *f = NULL;                                     // Arrange
  f = obj.openFile_(file_name);                       // Act
  obj.read_obj_(f);
  EXPECT_DOUBLE_EQ(obj.vtx_arr[0], -295.424526);  // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[1], 482.015262);   // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[2], .010099);      // Accert
  // fclose(f);
}

TEST_F(Obj3dTest, fill_facet_ok) {
  const char *bf{"f 5/4/ 562/7/10 123/25/25 5 58//86 12/ 74// "};  // Arrange
  // obj.vtx_count = 1;                                               // Arrange
  // obj.fct_count = 1;                                               // Arrange
  // obj.s21_alloc_mem_();                                            // Act
  // obj.fill_facets_(bf, 0);                                         // Act
  obj.fill_facets_(bf);                  // Act
  EXPECT_EQ(obj.polygons[0].size(), 7);  // Accert
  // EXPECT_EQ(7, obj.fct_vtx[0]);                                    // Accert
  EXPECT_EQ(obj.polygons[0][0], 5 - 1);    // Accert
  EXPECT_EQ(obj.polygons[0][1], 562 - 1);  // Accert
  EXPECT_EQ(obj.polygons[0][2], 123 - 1);  // Accert
  EXPECT_EQ(obj.polygons[0][3], 5 - 1);    // Accert
  EXPECT_EQ(obj.polygons[0][4], 58 - 1);   // Accert
  EXPECT_EQ(obj.polygons[0][5], 12 - 1);   // Accert
  EXPECT_EQ(obj.polygons[0][6], 74 - 1);   // Accert
}

TEST_F(Obj3dTest, count_vtx_of_facet_ok) {
  const char *bf = "f 5/4 562/7/10 123/25/25 5 58//86 12/ 74// ";  // Arrange
  // obj.vtx_count = 2;                                               // Arrange
  // obj.fct_count = 1;                                               // Arrange
  // obj.s21_alloc_mem_();                                            // Act
  int count = obj.count_vtx_of_facet_(bf);  // Act
  EXPECT_EQ(7, count);                      // Accert
}

TEST_F(Obj3dTest, parse_vertices_ok) {
  const char *bf =
      "f 551/25 562/70 547/84 123/25/25 5 58//86 12/ 74// ";  // Arrange
  // obj.vtx_count = 2;                                          // Arrange
  // obj.fct_count = 8;                                          // Arrange
  // obj.s21_alloc_mem_();                                       // Act
  // obj.polygons[0].vertexes =
  // (unsigned int *)calloc(8, sizeof(unsigned int));  // Act
  // int count = obj.parse_vertices_(bf, 0);               // Act
  int count = obj.parse_vertices_(bf);     // Act
  EXPECT_EQ(8, count);                     // Accert
  EXPECT_EQ(obj.polygons[0][0], 551 - 1);  // Accert
  EXPECT_EQ(obj.polygons[0][1], 562 - 1);  // Accert
  EXPECT_EQ(obj.polygons[0][2], 547 - 1);  // Accert
  EXPECT_EQ(obj.polygons[0][3], 123 - 1);  // Accert
  EXPECT_EQ(obj.polygons[0][4], 5 - 1);    // Accert
  EXPECT_EQ(obj.polygons[0][5], 58 - 1);   // Accert
  EXPECT_EQ(obj.polygons[0][6], 12 - 1);   // Accert
  EXPECT_EQ(obj.polygons[0][7], 74 - 1);   // Accert
}

TEST_F(Obj3dTest, center_obj3d) {
  const char *file_name{"../data-samples/deer.obj"};  // Arrange
  FILE *f = NULL;                                     // Arrange
  f = obj.openFile_(file_name);                       // Act
  obj.read_obj_(f);
  obj.centerObj();
  EXPECT_DOUBLE_EQ(obj.vtx_arr[0], -248.5330995);          // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[1], -248.021791);           // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[2], -0.51575049999999256);  // Accert
}

TEST_F(Obj3dTest, load_from_file) {
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  obj.loadFromFile(file_name);                        // Act
  EXPECT_DOUBLE_EQ(obj.vtx_arr[0], .5);               // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[1], -.5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[2], -.5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[3], .5);               // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[4], -.5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[5], .5);               // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[6], -.5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[7], -.5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[8], .5);               // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[9], -.5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[10], -.5);             // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[11], -.5);             // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[12], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[13], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[14], -.5);             // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[15], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[16], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[17], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[18], -.5);             // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[19], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[20], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[21], -.5);             // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[22], .5);              // Accert
  EXPECT_DOUBLE_EQ(obj.vtx_arr[23], -.5);             // Accert
  // EXPECT_EQ(obj.fct_vtx[3], 3);                       // Accert
  EXPECT_EQ(obj.polygons[3].size(), 3);  // Accert
  EXPECT_EQ(obj.polygons[3][0], 6 - 1);  // Accert
  EXPECT_EQ(obj.polygons[3][1], 7 - 1);  // Accert
  EXPECT_EQ(obj.polygons[3][2], 3 - 1);  // Accert
}

TEST_F(Obj3dTest, get_Vetrexes) {
  const char *file_name{"../data-samples/deer.obj"};    // Arrange
  obj.loadFromFile(file_name);                          // Act
  EXPECT_DOUBLE_EQ(obj.getVertexes()[0], -295.424526);  // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[1], 482.015262);   // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[2], 0.010099);     // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[3], -408.458285);  // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[4], 487.153254);   // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[5], 41.93742);     // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[9], -130.518803);  // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[10], 464.632037);  // Accert
  EXPECT_DOUBLE_EQ(obj.getVertexes()[11], 0.007556);    // Accert
}

}  // namespace S21Test
