#include <gtest/gtest.h>

#include "SmartCalculator.h"
using namespace std;

TEST(validation_test, test_1) {
  s21::SmartCalculator a("123.789", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("6.09");
  ASSERT_NO_THROW(a.validation());

  a.setInput("9.");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput(".7");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("8. 2");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("56 .3");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("92 . 7");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("k.1");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("7.k");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("3.8.0");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("3..0");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_2) {
  s21::SmartCalculator a("+7", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("-9");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(3-6) + 2");
  ASSERT_NO_THROW(a.validation());

  a.setInput("x - 9");
  ASSERT_NO_THROW(a.validation());

  a.setInput("f - 0");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput(". + 34");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("6 ^ 4");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(32+ 7) / 5");
  ASSERT_NO_THROW(a.validation());

  a.setInput("x * 7");
  ASSERT_NO_THROW(a.validation());

  a.setInput("*6");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("(^23)");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("$ / 3");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("3  + (2 * 7)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("2 * x");
  ASSERT_NO_THROW(a.validation());

  a.setInput("4 ^ cos(7)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("3-");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("(6+)");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("3/ d");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("3+^ x");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_3) {
  s21::SmartCalculator a("(-7)", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("(");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput(")");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("()");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput(")(");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("((-7) + (+3))");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(34)*(-6)(");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("(-95) + ((123)");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_4) {
  s21::SmartCalculator a("mod 4", 0);
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("4mod");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("5ma");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("5mod 3");
  ASSERT_NO_THROW(a.validation());

  a.setInput("6 mod x");
  ASSERT_NO_THROW(a.validation());

  a.setInput("x mod 9");
  ASSERT_NO_THROW(a.validation());

  a.setInput("x mod x");
  ASSERT_NO_THROW(a.validation());

  a.setInput("6mod(-8)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("7modh");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("(-4)mod5");
  ASSERT_NO_THROW(a.validation());

  a.setInput("&mod8");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_5) {
  s21::SmartCalculator a("5 mod x", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("6 - x");
  ASSERT_NO_THROW(a.validation());

  a.setInput("x*23");
  ASSERT_NO_THROW(a.validation());

  a.setInput("7 / (x - 9)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(6 ^ x)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(4)x");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("x8");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("x.7");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("xh");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_6) {
  s21::SmartCalculator a("5 mod 9", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("21");
  ASSERT_NO_THROW(a.validation());

  a.setInput("6 - 34");
  ASSERT_NO_THROW(a.validation());

  a.setInput("8*23");
  ASSERT_NO_THROW(a.validation());

  a.setInput("7 / (32 - 9)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(6 ^ 45)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(4)33");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("9.5- 9764");
  ASSERT_NO_THROW(a.validation());

  a.setInput("8p");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_7) {
  s21::SmartCalculator a("cos(9*x)", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("3 + sin(5)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("1 / tan(54 - x)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("2 * acos(21)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("6 ^ asin(90)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("atan(12/x)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("2 / sqrt(123)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("ln(6 * x) - 7");
  ASSERT_NO_THROW(a.validation());

  a.setInput("log(5) ^ 4");
  ASSERT_NO_THROW(a.validation());

  a.setInput("lo g(5) ^ 4");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("atan (12/x)");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("lag(5) ^ 7");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("sin 5");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("cos(5");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("tan()");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("4 atan(9)");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_8) {
  s21::SmartCalculator a("cos(9*h)", 0);
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("3 + & sin(5)");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("szfhrewtn");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("5,9 + 7");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(validation_test, test_9) {
  s21::SmartCalculator a("(sin(2)+cos(3)) * sqrt(5)", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("ln(10) - sin(2) / sqrt(3)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("tan(4) * cos(5) ^ sin(6)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("acos(0.5) + atan(0.8) * log(2)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("sqrt(9) + ln(4) - tan(1) / cos(2)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("sin(1) * cos(2) + sqrt(3) ^ tan(0.5)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("2 / sqrt(123)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("10 mod 3 + atan(0.6) - log(2)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("(sin(1) + cos(2) / sqrt(3)) * ln(4)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("sqrt(16) - tan(1) * acos(0.2)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("log (4) + sin(2) - cos(1) / sqrt(5)");
  ASSERT_THROW(a.validation(), logic_error);
  a.setInput("log(4x) + sin(2,7) - cos(1) / sqrt(5)");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("log(4) + sin(27) - cos(1) / sqr(5)");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput(
      "sin(1) * cos(2) + sqrt(3) ^ tan(0.5) * (sin(2)+cos(3)) * sqrt(5) / "
      "ln(10) - sin(2) / sqrt(3) ^ tan(4) * cos(5) ^ sin(6) - acos(0.5) + "
      "atan(0.8) * log(2) + 23456 * sqrt(9) + ln(4) - tan(1) / cos(2) - sin(1) "
      "* cos(2) + sqrt(3) ^ tan(0.5) + 123 + sin(-x) *55");
  ASSERT_NO_THROW(a.validation());
}

TEST(validation_test, test_10) {
  s21::SmartCalculator a("3*5e-56+sin(5)", 0);
  ASSERT_NO_THROW(a.validation());

  a.setInput("3e-1");
  ASSERT_NO_THROW(a.validation());

  a.setInput("4e5 - 6");
  ASSERT_NO_THROW(a.validation());

  a.setInput("1e-5 * x");
  ASSERT_NO_THROW(a.validation());

  a.setInput("10e7 ^ 3");
  ASSERT_NO_THROW(a.validation());

  a.setInput("1e-6 mod 8");
  ASSERT_NO_THROW(a.validation());

  a.setInput("sin(1e-6)");
  ASSERT_NO_THROW(a.validation());

  a.setInput("e-5");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("2e-5.5");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("2e+5");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("5e*3");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("7eh");
  ASSERT_THROW(a.validation(), logic_error);

  a.setInput("2e-5f7+8");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(calculation_test, test_1) {
  s21::SmartCalculator a("(sin(2)+cos(3)) * sqrt(5)", 0);
  ASSERT_NO_THROW(a.validation());
  ASSERT_NEAR(a.calculate(), -0.1804396614654603, 1e-7);

  a.setInput("ln(10) - sin(2) / sqrt(3)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 1.7776019788428044, 1e-7);

  a.setInput("tan(4) * cos(5) ^ sin(6)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 1.646407308, 1e-7);

  a.setInput("acos(0.5) + atan(0.8) * log(2)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 1.250314814, 1e-7);

  a.setInput("sqrt(9) + ln(4) - tan(1) / cos(2)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 8.128741949036312, 1e-7);

  a.setInput("sin(1) * cos(2) + sqrt(x) ^ tan(0.5)");
  ASSERT_NO_THROW(a.validation());
  a.setX(3);
  ASSERT_NEAR(a.calculate(), 0.9998011863733898, 1e-7);

  a.setInput("2 / sqrt(123)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 0.18033392693348646, 1e-7);

  a.setInput("10 mod 3 + atan(0.6) - log(2)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 1.239389505, 1e-7);

  a.setInput("(sin(1) + cos(2) / sqrt(3)) * ln(4)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 0.8334519488395, 1e-7);

  a.setInput("sqrt(16) - tan(1) * acos(0.2)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 1.8672260480493925, 1e-7);

  a.setInput("x");
  ASSERT_NO_THROW(a.validation());
  a.setX(123);
  ASSERT_NEAR(a.calculate(), 123.0, 1e-7);

  a.setInput("x ^ x");
  ASSERT_NO_THROW(a.validation());
  a.setX(2);
  ASSERT_NEAR(a.calculate(), 4, 1e-7);

  a.setInput("x - asin(0.5)");
  ASSERT_NO_THROW(a.validation());
  a.setX(1);
  ASSERT_NEAR(a.calculate(), 0.4764012244017, 1e-7);

  a.setInput("5+10+97+0 * log(12)");
  a.setX(1);
  ASSERT_NO_THROW(a.validation());
  ASSERT_NEAR(a.calculate(), 112, 1e-7);

  a.setInput("2^2^3");
  ASSERT_NO_THROW(a.validation());
  a.setX(1);
  ASSERT_NEAR(a.calculate(), 64, 1e-7);

  a.setInput("2^(2^3)");
  ASSERT_NO_THROW(a.validation());
  a.setX(1);
  ASSERT_NEAR(a.calculate(), 256, 1e-7);

  a.setInput("cos(3-1)/sin(5)*tan(1)^1");
  ASSERT_NO_THROW(a.validation());
  a.setX(1);
  ASSERT_NEAR(a.calculate(), 0.675872240, 1e-7);

  a.setInput(
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))");
  ASSERT_NO_THROW(a.validation());
  a.setX(1);
  ASSERT_NEAR(a.calculate(), -30.0721649, 1e-7);

  a.setInput("ln(10)-(-log(2))");
  ASSERT_NO_THROW(a.validation());
  a.setX(1);
  ASSERT_NEAR(a.calculate(), 2.603615089, 1e-7);

  a.setInput("(cos(()))");
  ASSERT_THROW(a.validation(), logic_error);
}

TEST(calculation_test, test_2) {
  s21::SmartCalculator a("sin(2e-3)+cos(3e3) * sqrt(5)", 0);
  ASSERT_NO_THROW(a.validation());
  ASSERT_NEAR(a.calculate(), -2.17969172471, 1e-7);

  a.setInput("2e-3 + 3");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 3.002, 1e-7);

  a.setInput("sqrt(1e6) - tan(11e-3) * acos(0.2)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_NEAR(a.calculate(), 999.98493557, 1e-7);

  a.setInput("acos(15)+asin(30)/(atan(2)*sqrt(9))");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_THROW(a.calculate(), logic_error);

  a.setInput("3/(x-x)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_THROW(a.calculate(), range_error);

  a.setInput("-5/(9 * 0)");
  ASSERT_NO_THROW(a.validation());
  a.setX(0);
  ASSERT_THROW(a.calculate(), length_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}