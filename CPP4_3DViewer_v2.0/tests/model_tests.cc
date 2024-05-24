/**
 * @file model_tests.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief test model class
 * @version 0.1
 * @date 2023-09-26
 * @copyright Copyright (c) 2023
 */
// #include <gtest/gtest.h>
// #define private public

#include "s21_3dviewer_v2_tests.h"

namespace S21Test {

using namespace s21;

// arrange fixture
class ModelTest : public ::testing::Test {
 protected:
  void SetUp() {}
  void TearDown() {}
  Model m;
  // Facade m{m1};
};

/*---------------differentiated payment-------------------*/
TEST_F(ModelTest, simple_test1) {
  // Arrange
  // Act
  EXPECT_DOUBLE_EQ(3.14, 3.14);  // Assert
  // EXPECT_EQ(m.getRes(12, 9), 21);  // Assert
  EXPECT_TRUE(true);  // Assert
}

TEST_F(ModelTest, init_rescale_object) {
  const double true_coord[]{
      2.00000,  -2.00000, -2.00000, 2.00000,  -2.00000, 2.00000,
      -2.00000, -2.00000, 2.00000,  -2.00000, -2.00000, -2.0000,
      2.00000,  2.00000,  -2.00000, 2.0000,   2.00000,  2.00000,
      -2.00000, 2.00000,  2.00000,  -2.00000, 2.00000,  -2.00000,
  };                                                  // Arrange
  double scale = 2;                                   // Arrange
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  m.loadFromFile(file_name);                          // Act
  m.initialRescaleObj(scale);                         // Act
  for (int i{}; i < 24; ++i) {                        // Accert
    // std::cout << "index: " << i << std::endl;
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
  }                                                       // Accert
}

TEST_F(ModelTest, init_rescale_object2) {
  const double true_coord[]{
      0, 2, 0, 4, 2, 0, 4, 2, 2, 0, 2, 2, 0, 0, 0, 4, 0, 0, 4, 0, 2, 0, 0, 2,
  };                                                          // Arrange
  double scale = 2;                                           // Arrange
  const char *file_name{"../data-samples/parallepiped.obj"};  // Arrange
  m.loadFromFile(file_name);                                  // Act
  m.initialRescaleObj(scale);                                 // Act
  for (int i{}; i < 24; ++i)                                  // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);      // Accert
}

TEST_F(ModelTest, move_x) {
  const double true_coord[]{
      2.500000, -0.500000, -0.500000, 2.500000, -0.500000, 0.500000,
      1.500000, -0.500000, 0.500000,  1.500000, -0.500000, -0.50000,
      2.500000, 0.500000,  -0.500000, 2.50000,  0.500000,  0.500000,
      1.500000, 0.500000,  0.500000,  1.500000, 0.500000,  -0.500000,
  };
  double distance = 2;                                    // Arrange
  const char *file_name{"../data-samples/cube.obj"};      // Arrange
  m.loadFromFile(file_name);                              // Act
  m.setAffine(new MoveX);                                 // Act
  m.doAffine(distance);                                   // Act
  for (int i{}; i < 24; ++i)                              // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
  // std::cout << ",i=" << m.getVertexes()[i];
}

TEST_F(ModelTest, move_y) {
  const double true_coord[]{
      0.500000,  -3.500000, -0.500000, 0.500000,  -3.500000, 0.500000,
      -0.500000, -3.500000, 0.500000,  -0.500000, -3.500000, -0.50000,
      0.500000,  -2.500000, -0.500000, 0.50000,   -2.500000, 0.500000,
      -0.500000, -2.500000, 0.500000,  -0.500000, -2.500000, -0.500000,
  };
  double distance = -3;                               // Arrange
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  m.loadFromFile(file_name);                          // Act
  // m.moveY(distance);                                      // Act
  m.setAffine(new MoveY);                                 // Act
  m.doAffine(distance);                                   // Act
  for (int i{}; i < 24; ++i)                              // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
}

TEST_F(ModelTest, move_z) {
  const double true_coord[]{
      0.500000,  -0.500000, 0.00000, 0.500000,  -0.500000, 1.00000,
      -0.500000, -0.500000, 1.00000, -0.500000, -0.500000, 0.0000,
      0.500000,  0.500000,  0.00000, 0.50000,   0.500000,  1.00000,
      -0.500000, 0.500000,  1.00000, -0.500000, 0.500000,  0.00000,
  };
  double distance = .5;                               // Arrange
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  m.loadFromFile(file_name);                          // Act
  // m.moveZ(distance);                                      // Act
  m.setAffine(new MoveZ);                                 // Act
  m.doAffine(distance);                                   // Act
  for (int i{}; i < 24; ++i)                              // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
}

TEST_F(ModelTest, rotate_x) {
  const double true_coord[]{
      0.500000,  0.67103513986486396,  -0.22296152373569386,
      0.500000,  -0.22296152373569386, -0.67103513986486396,
      -0.500000, -0.22296152373569386, -0.67103513986486396,
      -0.500000, 0.67103513986486396,  -0.22296152373569386,
      0.500000,  0.22296152373569386,  0.67103513986486396,
      0.50000,   -0.67103513986486396, 0.22296152373569386,
      -0.500000, -0.67103513986486396, 0.22296152373569386,
      -0.500000, 0.22296152373569386,  0.67103513986486396,
  };
  double value = 90;                                  // Arrange
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  m.loadFromFile(file_name);                          // Act
  // m.rotateX(value);                                       // Act
  m.setAffine(new RotateX);                               // Act
  m.doAffine(value);                                      // Act
  for (int i{}; i < 24; ++i)                              // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
}

TEST_F(ModelTest, rotate_y) {
  const double true_coord[]{
      -0.67103513986486396, -0.5,      -0.22296152373569386,
      0.22296152373569386,  -0.5,      -0.67103513986486396,
      0.67103513986486396,  -0.500000, 0.22296152373569386,
      -0.22296152373569386, -0.500000, 0.67103513986486396,
      -0.67103513986486396, 0.500000,  -0.22296152373569386,
      0.22296152373569386,  0.500000,  -0.67103513986486396,
      0.67103513986486396,  0.500000,  0.22296152373569386,
      -0.22296152373569386, 0.500000,  0.67103513986486396,
  };
  double value = 90;                                  // Arrange
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  m.loadFromFile(file_name);                          // Act
  // m.rotateY(value);                                       // Act
  m.setAffine(new RotateY);                               // Act
  m.doAffine(value);                                      // Act
  for (int i{}; i < 24; ++i)                              // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
}

TEST_F(ModelTest, rotate_z) {
  const double true_coord[]{
      0.22296152373569386,  0.67103513986486396,  -0.500000,
      0.22296152373569386,  0.67103513986486396,  0.500000,
      0.67103513986486396,  -0.22296152373569386, 0.500000,
      0.67103513986486396,  -0.22296152373569386, -0.50000,
      -0.67103513986486396, 0.22296152373569386,  -0.500000,
      -0.67103513986486396, 0.22296152373569386,  0.500000,
      -0.22296152373569386, -0.67103513986486396, 0.500000,
      -0.22296152373569386, -0.67103513986486396, -0.500000,
  };
  double value = 90;                                  // Arrange
  const char *file_name{"../data-samples/cube.obj"};  // Arrange
  m.loadFromFile(file_name);                          // Act
  // m.rotateZ(value);                                       // Act
  m.setAffine(new RotateZ);                               // Act
  m.doAffine(value);                                      // Act
  for (int i{}; i < 24; ++i)                              // Accert
    EXPECT_DOUBLE_EQ(m.getVertexes()[i], true_coord[i]);  // Accert
}

}  // namespace S21Test
