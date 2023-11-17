#include <gtest/gtest.h>

#include "project_task.h"

using namespace std;

TEST(test, test_1) {
  KarnaughMap new_map("0000000000000001");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "abcd");
}

TEST(test, test_2) {
  KarnaughMap new_map("0111111111111111");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "d V c V b V a");
}

TEST(test, test_3) {
  KarnaughMap new_map("1010101010110001");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "b'd' V a'd' V acd");
}

TEST(test, test_4) {
  KarnaughMap new_map("0001010111001101");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "a'cd V bd V ac'");
}

TEST(test, test_5) {
  KarnaughMap new_map("1111111111111111");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "1");
}

TEST(test, test_6) {
  KarnaughMap new_map("0000000000000000");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "0");
}

TEST(test, test_7) {
  KarnaughMap new_map("0001000000010000");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "b'cd");
}

TEST(test, test_8) {
  KarnaughMap new_map("1010101000000000");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "a'd'");
}

TEST(test, test_9) {
  KarnaughMap new_map("0100010001000100");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "c'd");
}

TEST(test, test_10) {
  KarnaughMap new_map("1010101010110001");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "b'd' V a'd' V acd");
}

TEST(test, test_11) {
  KarnaughMap new_map("0001010111001101");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "a'cd V bd V ac'");
}

TEST(test, test_12) {
  KarnaughMap new_map("1001111011001110");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "c'd' V a'b'cd V bc' V bd' V ac'");
}

TEST(test, test_13) {
  KarnaughMap new_map("0110101100101011");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "a'b'c'd V cd' V bd' V bc");
}

TEST(test, test_14) {
  KarnaughMap new_map("1001011010100101");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "b'c'd' V a'b'cd V bc'd V a'bcd' V abd V ab'd'");
}

TEST(test, test_15) {
  KarnaughMap new_map("1110000010100000");
  new_map.to_DNF();
  ASSERT_EQ(new_map.DNF, "b'd' V a'b'c'");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
