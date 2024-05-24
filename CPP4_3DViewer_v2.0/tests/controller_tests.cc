/**
 * @file s21_controller_tests.cc
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * newtonbe@student.21-school.ru
 * wellpetr@student.21-school.ru
 * @brief unit test controller class
 * @version 0.1
 * @date 2023-11-03
 * @copyright Copyright (c) 2023
 */

#include "s21_3dviewer_v2_tests.h"

namespace S21Test {

using namespace s21;

// arrange fixture i don't have enough time
class ControllerTest : public ::testing::Test {
 protected:
  void SetUp() {
    std::cout << std::setprecision(2) << std::fixed;
    ctrl.loadFromFile("../data-samples/parallepiped.obj");  // Act
  }
  void TearDown() {}
  Facade fc;
  Controller ctrl{fc};
};

TEST_F(ControllerTest, init_and_center_3dObj) {
  // Arrange
  ctrl.loadFromFile("../data-samples/deer.obj");             // Act
  EXPECT_DOUBLE_EQ(ctrl.getVtx()[0], -248.5330995);          // Accert
  EXPECT_DOUBLE_EQ(ctrl.getVtx()[1], -248.021791);           // Accert
  EXPECT_DOUBLE_EQ(ctrl.getVtx()[2], -0.51575049999999256);  // Accert
}

TEST_F(ControllerTest, init_and_center_3dObj2) {
  // Arrange
  ctrl.loadFromFile("../data-samples/deer.obj");             // Act
  EXPECT_DOUBLE_EQ(ctrl.getVtx()[0], -248.5330995);          // Accert
  EXPECT_DOUBLE_EQ(ctrl.getVtx()[1], -248.021791);           // Accert
  EXPECT_DOUBLE_EQ(ctrl.getVtx()[2], -0.51575049999999256);  // Accert
}

TEST_F(ControllerTest, getPolygons) {
  // Arrange
  // Act
  EXPECT_EQ(ctrl.GetPolygons().data()[0][0], 1 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[0][1], 2 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[0][2], 3 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[0][3], 4 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[1][0], 2 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[1][1], 6 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[1][2], 7 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[1][3], 3 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[2][0], 5 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[2][1], 6 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[2][2], 7 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[2][3], 8 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[3][0], 1 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[3][1], 4 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[3][2], 8 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[3][3], 5 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[4][0], 1 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[4][1], 2 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[4][2], 6 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[4][3], 5 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[5][0], 4 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[5][1], 3 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[5][2], 7 - 1);  // Accert
  EXPECT_EQ(ctrl.GetPolygons().data()[5][3], 8 - 1);  // Accert
}

TEST_F(ControllerTest, getVtxCount) {
  // Arrange
  // Act
  EXPECT_EQ(ctrl.GetVtxCount(), 8);  // Accert
}

TEST_F(ControllerTest, getFacetCount) {
  // Arrange
  // Act
  EXPECT_EQ(ctrl.GetFctCount(), 6);  // Accert
}

TEST_F(ControllerTest, getFctVtx) {
  // Arrange
  // Act
  // for(auto facet:ctrl.GetFctVtx())
  for (int i{}; i != 6; ++i) EXPECT_EQ(ctrl.GetFctVtx(i), 4);  // Accert
}

TEST_F(ControllerTest, getTotalIndices) {
  // Arrange
  // Act
  EXPECT_EQ(ctrl.GetTotalIndices(), 24);  // Accert
}

TEST_F(ControllerTest, rescale_object) {
  const double true_coord[]{
      -3.14, 1.57,  -1.57, 3.14,  1.57,  -1.57, 3.14,  1.57,
      1.57,  -3.14, 1.57,  1.57,  -3.14, -1.57, -1.57, 3.14,
      -1.57, -1.57, 3.14,  -1.57, 1.57,  -3.14, -1.57, 1.57,
  };                                                    // Arrange
  double scale = 3.14;                                  // Arrange
  ctrl.rescaleObj(scale);                               // Act
  for (int i{}; i < 24; ++i) {                          // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
    // std::cout << ", i=" << ctrl.getVtx()[i];
  }
}

TEST_F(ControllerTest, init_rescale_object) {
  const double true_coord[]{
      -2, 1,  -1, 2, 1,  -1, 2, 1,  1, -2, 1,  1,
      -2, -1, -1, 2, -1, -1, 2, -1, 1, -2, -1, 1};      // Arrange
  double scale = 2;                                     // Arrange
  ctrl.initialRescaleObj(scale);                        // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, move_x) {
  const double true_coord[]{
      1, 0.5,  -0.5, 3, 0.5,  -0.5, 3, 0.5,  0.5, 1, 0.5,  0.5,
      1, -0.5, -0.5, 3, -0.5, -0.5, 3, -0.5, 0.5, 1, -0.5, 0.5,
  };                                                    // Arrange
  double value = 2;                                     // Arrange
  ctrl.moveX(value);                                    // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, move_y) {
  const double true_coord[]{
      -1, -2.5, -0.5, 1, -2.5, -0.5, 1, -2.5, 0.5, -1, -2.5, 0.5,
      -1, -3.5, -0.5, 1, -3.5, -0.5, 1, -3.5, 0.5, -1, -3.5, 0.5,
  };                                                    // Arrange
  double value = -3;                                    // Arrange
  ctrl.moveY(value);                                    // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, move_z) {
  const double true_coord[]{
      -1, 0.5,  -0.36, 1, 0.5,  -0.36, 1, 0.5,  0.64, -1, 0.5,  0.64,
      -1, -0.5, -0.36, 1, -0.5, -0.36, 1, -0.5, 0.64, -1, -0.5, 0.64,
  };                                                    // Arrange
  double value = .14;                                   // Arrange
  ctrl.moveZ(value);                                    // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, rotate_z) {
  const double true_coord[]{
      0.001075284328891202,  -1.118033471665142997, -0.500000000000000000,
      -0.895071947929449108, 0.669959855535972815,  -0.500000000000000000,
      -0.895071947929449108, 0.669959855535972815,  0.500000000000000000,
      0.001075284328891202,  -1.118033471665142997, 0.500000000000000000,
      0.895071947929449108,  -0.669959855535972815, -0.500000000000000000,
      -0.001075284328891202, 1.118033471665142997,  -0.500000000000000000,
      -0.001075284328891202, 1.118033471665142997,  0.500000000000000000,
      0.895071947929449108,  -0.669959855535972815, 0.500000000000000000,
  };                                                    // Arrange
  double value = 90;                                    // Arrange
  ctrl.rotateZ(value);                                  // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, rotate_y) {
  const double true_coord[]{
      0.770326772936087645,  0.500000000000000000,  -0.810306524037584963,
      0.186049155468415328,  0.500000000000000000,  1.102445332771421205,
      -0.770326772936087645, 0.500000000000000000,  0.810306524037584963,
      -0.186049155468415328, 0.500000000000000000,  -1.102445332771421205,
      0.770326772936087645,  -0.500000000000000000, -0.810306524037584963,
      0.186049155468415328,  -0.500000000000000000, 1.102445332771421205,
      -0.770326772936087645, -0.500000000000000000, 0.810306524037584963,
      -0.186049155468415328, -0.500000000000000000, -1.102445332771421205,
  };                                                    // Arrange
  double value = -27;                                   // Arrange
  ctrl.rotateY(value);                                  // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, rotate_x) {
  const double true_coord[]{
      -1.000000000000000000, -0.585528844955944372, -0.396429024826081056,
      1.000000000000000000,  -0.585528844955944372, -0.396429024826081056,
      1.000000000000000000,  0.396429024826081056,  -0.585528844955944372,
      -1.000000000000000000, 0.396429024826081056,  -0.585528844955944372,
      -1.000000000000000000, -0.396429024826081056, 0.585528844955944372,
      1.000000000000000000,  -0.396429024826081056, 0.585528844955944372,
      1.000000000000000000,  0.585528844955944372,  0.396429024826081056,
      -1.000000000000000000, 0.585528844955944372,  0.396429024826081056,
  };                                                    // Arrange
  double value = 237;                                   // Arrange
  ctrl.rotateX(value);                                  // Act
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

TEST_F(ControllerTest, get_vtx) {
  const double true_coord[]{
      -1.00, 0.50,  -0.50, 1.00,  0.50,  -0.50, 1.00,  0.50,
      0.50,  -1.00, 0.50,  0.50,  -1.00, -0.50, -0.50, 1.00,
      -0.50, -0.50, 1.00,  -0.50, 0.50,  -1.00, -0.50, 0.50,
  };                                                    // Arrange
  for (int i{}; i < 24; ++i)                            // Accert
    EXPECT_DOUBLE_EQ(ctrl.getVtx()[i], true_coord[i]);  // Accert
  // std::cout << ctrl.getVtx()[i] << ",";
}

}  // namespace S21Test