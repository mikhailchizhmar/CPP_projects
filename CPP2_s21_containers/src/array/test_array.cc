#include <gtest/gtest.h>

#include "s21_array.h"

TEST(constructor_test_array, test1) {
  s21::array<int, 5> a;
  ASSERT_EQ(a.size(), 5);
}

TEST(constructor_test_array, test2) {
  s21::array<char, 3> a = {'a', 'b', 'c'};
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a[0], 'a');
  ASSERT_EQ(a[1], 'b');
  ASSERT_EQ(a[2], 'c');
}

TEST(constructor_test_array, test3) {
  s21::array<int, 3> a = {4, 5, 6};
  s21::array<int, 3> b(a);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(a[0], b[0]);
  ASSERT_EQ(a[1], b[1]);
  ASSERT_EQ(a[2], b[2]);
}

TEST(constructor_test_array, test4) {
  s21::array<int, 3> a = {3, 2, 1};
  s21::array<int, 3> b(std::move(a));
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(3, b[0]);
  ASSERT_EQ(2, b[1]);
  ASSERT_EQ(1, b[2]);
}

TEST(constructor_test_array, test5) {
  s21::array<int, 3> a = {3, 2, 1};
  s21::array<int, 3> b = std::move(a);
  ASSERT_EQ(b.size(), 3);
  ASSERT_EQ(3, b[0]);
  ASSERT_EQ(2, b[1]);
  ASSERT_EQ(1, b[2]);
}

TEST(access_test_array, test1) {
  s21::array<double, 3> a = {0.6, 0.34, 0.89};
  ASSERT_EQ(a.at(0), 0.6);
  ASSERT_EQ(a.at(1), 0.34);
  ASSERT_EQ(a.at(2), 0.89);
  ASSERT_THROW(a.at(-1), std::out_of_range);
  ASSERT_THROW(a.at(5), std::out_of_range);
}

TEST(access_test_array, test2) {
  s21::array<double, 3> a = {0.9, 0.8, 0.7};
  ASSERT_EQ(a.front(), a[0]);
  ASSERT_EQ(a.front(), *a.data());
  ASSERT_EQ(a.back(), a[2]);
}

TEST(iterator_test_array, test1) {
  s21::array<double, 5> a = {0.9, 0.8, 0.7, 0.6, 0.5};
  int i = 0;
  for (s21::array<double, 5>::iterator iter = a.begin(); iter < a.end();
       iter++) {
    ASSERT_EQ(*iter, a[i]);
    i++;
  }
}

TEST(iterator_test_array, test2) {
  s21::array<double, 0> a;
  ASSERT_EQ(a.begin(), a.end());
}

TEST(capacity_test_array, test1) {
  s21::array<double, 5> a;
  ASSERT_FALSE(a.empty());
}

TEST(capacity_test_array, test2) {
  s21::array<double, 0> a;
  ASSERT_TRUE(a.empty());
}

TEST(capacity_test_array, test3) {
  s21::array<double, 10> a;
  ASSERT_EQ(a.max_size(), 10);
}

TEST(modifiers_test_array, test1) {
  s21::array<int, 4> a = {1, 2, 3, 4};
  s21::array<int, 4> b = {9, 8, 7, 6};

  a.swap(b);
  ASSERT_EQ(a[0], 9);
  ASSERT_EQ(a[1], 8);
  ASSERT_EQ(a[2], 7);
  ASSERT_EQ(a[3], 6);
  ASSERT_EQ(b[0], 1);
  ASSERT_EQ(b[1], 2);
  ASSERT_EQ(b[2], 3);
  ASSERT_EQ(b[3], 4);
}

TEST(modifiers_test_array, test2) {
  s21::array<std::string, 4> a;

  a.fill("s21");
  ASSERT_EQ(a[0], "s21");
  ASSERT_EQ(a[1], "s21");
  ASSERT_EQ(a[2], "s21");
  ASSERT_EQ(a[3], "s21");
}
