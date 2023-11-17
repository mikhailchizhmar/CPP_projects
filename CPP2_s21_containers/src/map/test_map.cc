#include <map>

#include "gtest/gtest.h"
#include "s21_map.h"

// constructors
TEST(MapTest, ConstructorDefault) {
  s21::map<int, char> map;
  std::map<int, char> mapStd;
  EXPECT_EQ(map.empty(), mapStd.empty());
}

TEST(MapTest, InitializerConstructor) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.size(), 3UL);
  EXPECT_EQ(std_map.size(), 3UL);

  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");

  EXPECT_EQ(std_map[1], "one");
  EXPECT_EQ(std_map[2], "two");
  EXPECT_EQ(std_map[3], "three");
}

TEST(MapTest, InitializerConstructorDuplicate) {
  s21::map<int, std::string> map = {{1, "one"}, {1, "one-one"}};

  std::map<int, std::string> std_map = {{1, "one"}, {1, "one-one"}};

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(std_map.size(), 1UL);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(std_map[1], "one");
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, std::string> map;
  map[1] = "liza";
  map[2] = "new";

  std::map<int, std::string> std_map;
  std_map[1] = "liza";
  std_map[2] = "new";

  s21::map<int, std::string> copy = map;
  std::map<int, std::string> std_copy = std_map;

  EXPECT_EQ(copy[1], "liza");
  EXPECT_EQ(std_copy[1], "liza");
  EXPECT_EQ(copy[2], "new");
  EXPECT_EQ(std_copy[2], "new");

  EXPECT_EQ(copy.size(), std_copy.size());
  EXPECT_EQ(map.size(), std_map.size());
}

TEST(MapTest, MoveConstructorComparison) {
  s21::map<int, std::string> map;
  map[1] = "liza";
  map[2] = "new";

  std::map<int, std::string> std_map;
  std_map[1] = "liza";
  std_map[2] = "new";

  s21::map<int, std::string> moved = std::move(map);
  std::map<int, std::string> std_moved = std::move(std_map);

  EXPECT_TRUE(map.empty());
  EXPECT_TRUE(std_map.empty());

  EXPECT_EQ(moved.size(), std_moved.size());
  EXPECT_EQ(moved[1], std_moved[1]);
  EXPECT_EQ(moved[2], std_moved[2]);
}

// empty, size, max_size
TEST(MapTest, SizeEmptyMap) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(map.size(), 0UL);
  EXPECT_EQ(std_map.size(), 0UL);
}

TEST(MapTest, SizeSingleElement) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  std_map.insert({1, "one"});

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(std_map.size(), 1UL);
}

TEST(MapTest, SizeManyVal) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});

  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std_map.insert({3, "three"});

  EXPECT_EQ(map.size(), 3UL);
  EXPECT_EQ(std_map.size(), 3UL);
}

TEST(MapTest, SizeAfterRemove) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.erase(1);

  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std_map.erase(1);

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(std_map.size(), 1UL);
}

TEST(MapTest, EmptyMap) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  EXPECT_TRUE(map.empty());
  EXPECT_TRUE(std_map.empty());
}

TEST(MapTest, EmptyMapWithElements) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  std_map.insert({1, "one"});

  EXPECT_FALSE(map.empty());
  EXPECT_FALSE(std_map.empty());
}

TEST(MapTest, EmptyAfterRemoving) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.erase(1);
  map.erase(2);

  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std_map.erase(1);
  std_map.erase(2);

  EXPECT_TRUE(map.empty());
  EXPECT_TRUE(std_map.empty());
}

TEST(MapTest, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  EXPECT_LE(map.max_size(), std::numeric_limits<size_t>::max());
}

// contains, clear, insert, insert_or_assign, erase, swap, merge
TEST(MapTest, ContainsManyVal) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert(std::make_pair(4, "four"));

  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std_map.insert({3, "three"});
  std_map.insert(std::make_pair(4, "four"));

  EXPECT_TRUE(map.contains(3));
  EXPECT_TRUE(std_map.count(3));
  EXPECT_TRUE(map.contains(4));
  EXPECT_TRUE(std_map.count(4));
  EXPECT_EQ(map.size(), std_map.size());
}

TEST(MapTest, ClearManyVal) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});

  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std_map.insert({3, "three"});

  EXPECT_EQ(map.size(), std_map.size());

  map.clear();
  std_map.clear();

  EXPECT_TRUE(map.empty());
  EXPECT_TRUE(std_map.empty());
  EXPECT_EQ(map.size(), std_map.size());
}

TEST(MapTest, ClearOnEmptyMap) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  EXPECT_TRUE(map.empty());
  EXPECT_TRUE(std_map.empty());

  map.clear();
  std_map.clear();

  EXPECT_TRUE(map.empty());
  EXPECT_TRUE(std_map.empty());
  EXPECT_EQ(map.size(), std_map.size());
}

TEST(MapTest, InsertValueType) {
  s21::map<int, std::string> map;
  std::map<int, std::string> stdMap;

  map.insert({1, "one"});
  stdMap.insert({1, "one"});

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(stdMap.size(), 1UL);

  EXPECT_NE(map.find(1), map.end());
  EXPECT_NE(stdMap.find(1), stdMap.end());

  auto resultCustomDup = map.insert({1, "one"});
  auto resultStdDup = stdMap.insert({1, "one"});

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(stdMap.size(), 1UL);

  EXPECT_FALSE(resultCustomDup.second);
  EXPECT_FALSE(resultStdDup.second);
}

TEST(MapTest, InsertKeyAndObj) {
  s21::map<int, std::string> map;
  std::map<int, std::string> stdMap;

  auto resultMap = map.insert(std::make_pair(1, "one"));
  auto resultStd = stdMap.insert(std::make_pair(1, "one"));

  EXPECT_TRUE(resultMap.second);
  EXPECT_TRUE(resultStd.second);

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(stdMap.size(), 1UL);

  EXPECT_NE(map.find(1), map.end());
  EXPECT_NE(stdMap.find(1), stdMap.end());

  auto resultCustomDup = map.insert(std::make_pair(1, "one"));
  auto resultStdDup = stdMap.insert(std::make_pair(1, "one"));

  EXPECT_FALSE(resultCustomDup.second);
  EXPECT_FALSE(resultStdDup.second);

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(stdMap.size(), 1UL);
}

TEST(MapTest, InsertAssignNewElement) {
  s21::map<int, std::string> map;

  auto result = map.insert_or_assign(1, "one");

  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(map[1], "one");
}

TEST(MapTest, InsertAssignManyVall) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  auto custom_result = map.insert_or_assign(1, "one");
  auto std_result = std_map.insert_or_assign(1, "one");

  EXPECT_EQ(custom_result.second, std_result.second);
  EXPECT_EQ(map.size(), std_map.size());
  EXPECT_EQ(map[1], std_map[1]);

  custom_result = map.insert_or_assign(1, "new-one");
  std_result = std_map.insert_or_assign(1, "new-one");

  EXPECT_EQ(custom_result.second, std_result.second);
  EXPECT_EQ(map.size(), std_map.size());
  EXPECT_EQ(map[1], std_map[1]);

  for (int i = 2; i < 10; ++i) {
    map.insert_or_assign(i, "value" + std::to_string(i));
    std_map.insert_or_assign(i, "value" + std::to_string(i));
  }

  EXPECT_EQ(map.size(), std_map.size());

  for (int i = 1; i < 10; ++i) {
    EXPECT_EQ(map[i], std_map[i]);
  }
}

TEST(MapTest, EraseEmptyMap) {
  s21::map<int, std::string> map;

  auto it = map.begin();
  map.erase(it);

  EXPECT_TRUE(map.empty());
  EXPECT_EQ(map.size(), 0UL);
}

TEST(MapTest, EraseByIterator_MultipleElements) {
  s21::map<int, std::string> map;
  map.insert(std::make_pair(1, "one"));
  map.insert(std::make_pair(2, "two"));
  map.insert(std::make_pair(3, "three"));

  auto it = map.find(2);
  map.erase(it);

  EXPECT_EQ(map.size(), 2UL);
  EXPECT_EQ(map.find(2), map.end());
}

TEST(MapTest, SwapEmptyMaps) {
  s21::map<int, std::string> map1, map2;
  std::map<int, std::string> stdMap1, stdMap2;

  map1.swap(map2);
  stdMap1.swap(stdMap2);

  EXPECT_TRUE(map1.empty() && map2.empty());
  EXPECT_TRUE(stdMap1.empty() && stdMap2.empty());

  EXPECT_EQ(map1.size(), stdMap1.size());
  EXPECT_EQ(map2.size(), stdMap2.size());
}

TEST(MapTest, SwapSameSize) {
  s21::map<int, std::string> map1, map2;
  std::map<int, std::string> stdMap1, stdMap2;

  map1.insert({1, "one"});
  map2.insert({2, "two"});
  stdMap1.insert({1, "one"});
  stdMap2.insert({2, "two"});

  map1.swap(map2);
  stdMap1.swap(stdMap2);

  EXPECT_EQ(map1.find(2) != map1.end(), stdMap1.find(2) != stdMap1.end());
  EXPECT_EQ(map2.find(1) != map2.end(), stdMap2.find(1) != stdMap2.end());

  EXPECT_EQ(map1.size(), stdMap1.size());
  EXPECT_EQ(map2.size(), stdMap2.size());
}

TEST(MapTest, SwapDifferentSize) {
  s21::map<int, std::string> map1, map2;
  std::map<int, std::string> stdMap1, stdMap2;

  map1.insert({1, "one"});
  map1.insert({3, "three"});
  map2.insert({2, "two"});
  stdMap1.insert({1, "one"});
  stdMap1.insert({3, "three"});
  stdMap2.insert({2, "two"});

  map1.swap(map2);
  stdMap1.swap(stdMap2);

  EXPECT_EQ(map1.find(2) != map1.end(), stdMap1.find(2) != stdMap1.end());
  EXPECT_EQ(map2.find(1) != map2.end(), stdMap2.find(1) != stdMap2.end());
  EXPECT_EQ(map2.find(3) != map2.end(), stdMap2.find(3) != stdMap2.end());

  EXPECT_EQ(map1.size(), stdMap1.size());
  EXPECT_EQ(map2.size(), stdMap2.size());
}

TEST(MapTest, MergeEmptyMap) {
  s21::map<int, int> map1;
  s21::map<int, int> map2;
  std::map<int, int> stdMap1;
  std::map<int, int> stdMap2;

  map1.insert({1, 100});
  stdMap1.insert({1, 100});

  map1.merge(map2);
  stdMap1.merge(stdMap2);

  ASSERT_FALSE(map1.empty());
  ASSERT_TRUE(map2.empty());
  ASSERT_EQ(map1.size(), stdMap1.size());
  ASSERT_EQ(map2.size(), stdMap2.size());
}

TEST(MapTest, MergeManyVal) {
  s21::map<int, int> map1;
  s21::map<int, int> map2;
  std::map<int, int> stdMap1;
  std::map<int, int> stdMap2;

  map1.insert({1, 100});
  map2.insert({2, 200});
  stdMap1.insert({1, 100});
  stdMap2.insert({2, 200});

  map1.merge(map2);
  stdMap1.merge(stdMap2);

  ASSERT_FALSE(map1.empty());
  ASSERT_TRUE(map2.empty());
  ASSERT_EQ(map1.size(), 2U);
  ASSERT_EQ(map1.size(), stdMap1.size());
  ASSERT_EQ(map2.size(), stdMap2.size());
}

TEST(MapTest, MergeDuplicate) {
  s21::map<int, int> map1;
  s21::map<int, int> map2;
  std::map<int, int> stdMap1;
  std::map<int, int> stdMap2;

  map1.insert({1, 100});
  map1.insert({3, 300});
  map2.insert({2, 200});
  map2.insert({1, 100});

  stdMap1.insert({1, 100});
  stdMap1.insert({3, 300});
  stdMap2.insert({2, 200});
  stdMap2.insert({1, 100});

  map1.merge(map2);
  stdMap1.merge(stdMap2);

  ASSERT_EQ(map1.size(), 3U);
  ASSERT_EQ(map2.size(), 1U);
  ASSERT_EQ(map1.size(), stdMap1.size());
  ASSERT_EQ(map2.size(), stdMap2.size());
}

TEST(MapTest, BeginEndOnEmptyMap) {
  s21::map<int, std::string> empty_map;
  EXPECT_EQ(empty_map.begin(), empty_map.end());
}

TEST(MapTest, BracketOperator) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map[1] = "liza";
  std_map[1] = "liza";

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(std_map.size(), 1UL);

  EXPECT_EQ(map[1], "liza");
  EXPECT_EQ(std_map[1], "liza");

  map[2];
  std_map[2];

  EXPECT_EQ(map.size(), 2UL);
  EXPECT_EQ(std_map.size(), 2UL);

  EXPECT_EQ(map[2], "");
  EXPECT_EQ(std_map[2], "");
}

TEST(MapTest, AtOperator) {
  s21::map<int, std::string> map;
  std::map<int, std::string> std_map;

  map[1] = "liza";
  std_map[1] = "liza";
  try {
    std_map.at(1) = "liza_super";
    // std_map.at(2); // вызовет исключение std::out_of_range
  } catch (const std::out_of_range& e) {
    throw;
  }

  try {
    map.at(1) = "liza_super";
    // map.at(2); // вызовет исключение std::out_of_range
  } catch (const std::out_of_range& e) {
    throw;
  }

  EXPECT_EQ(map.size(), 1UL);
  EXPECT_EQ(std_map.size(), 1UL);

  EXPECT_EQ(map[1], "liza_super");
  EXPECT_EQ(std_map[1], "liza_super");

  map[2];
  std_map[2];

  EXPECT_EQ(map.size(), 2UL);
  EXPECT_EQ(std_map.size(), 2UL);

  EXPECT_EQ(map[2], "");
  EXPECT_EQ(std_map[2], "");
}

TEST(MapTest, InsertMany) {
  s21::map<int, std::string> map;

  auto pair1 = std::make_pair(1, "hello");
  auto pair2 = std::make_pair(2, "hi");
  auto pair3 = std::make_pair(3, "bye");

  auto results = map.insert_many(pair1, pair2, pair3);
  ASSERT_EQ(results.size(), 3UL);

  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }

  EXPECT_EQ(map[1], "hello");
  EXPECT_EQ(map[2], "hi");
  EXPECT_EQ(map[3], "bye");
}

TEST(MapTest, InsertManyDuplicates) {
  s21::map<int, std::string> map;

  auto pair1 = std::make_pair(1, "vova_clown");
  auto pair2 = std::make_pair(2, "hello");
  auto pair3 = std::make_pair(3, "hi");
  auto duplicate = std::make_pair(1, "vova_clown");

  auto results = map.insert_many(pair1, pair2, pair3, duplicate);
  ASSERT_EQ(results.size(), 4UL);

  for (size_t i = 0; i < results.size(); ++i) {
    if (i != 3) {
      EXPECT_TRUE(results[i].second);
    } else {
      EXPECT_FALSE(results[i].second);
    }
  }

  EXPECT_EQ(map[1], "vova_clown");
  EXPECT_EQ(map[2], "hello");
  EXPECT_EQ(map[3], "hi");
  EXPECT_EQ(map.size(), 3UL);
}

TEST(MapTest, InsertManyEmpty) {
  s21::map<int, std::string> customMap;
  auto result = customMap.insert_many();

  ASSERT_TRUE(result.empty());
  ASSERT_TRUE(customMap.empty());
}
