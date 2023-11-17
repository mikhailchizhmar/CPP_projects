#include <set>

#include "gtest/gtest.h"
#include "s21_set.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> set;

  ASSERT_EQ(set.size(), 0UL);
  ASSERT_TRUE(set.empty());

  std::set<int> setStd;

  ASSERT_EQ(setStd.size(), 0UL);
  ASSERT_TRUE(setStd.empty());
}

TEST(SetTest, InitializerListConstructor) {
  std::set<int> setStd{100, 200, 300};

  ASSERT_TRUE(setStd.count(100));
  ASSERT_TRUE(setStd.count(200));
  ASSERT_TRUE(setStd.count(300));
  ASSERT_FALSE(setStd.empty());
}

TEST(SetTest, InitializerListConstructorEmpty) {
  std::set<int> setStd{};

  ASSERT_FALSE(setStd.count(100));
  ASSERT_TRUE(setStd.empty());
}

TEST(SetTest, InitializerListConstructorUnique) {
  s21::set<int> set = {1, 1, 2, 3, 4, 5, 5, 6};

  ASSERT_TRUE(set.contains(1));
  ASSERT_TRUE(set.contains(2));
  ASSERT_TRUE(set.contains(3));
  ASSERT_TRUE(set.contains(4));
  ASSERT_TRUE(set.contains(5));
  ASSERT_FALSE(set.contains(7));
  ASSERT_EQ(set.size(), 6UL);

  std::set<int> setStd = {1, 1, 2, 3, 4, 5, 5, 6};

  ASSERT_TRUE(setStd.count(1));
  ASSERT_TRUE(setStd.count(2));
  ASSERT_TRUE(setStd.count(3));
  ASSERT_TRUE(setStd.count(4));
  ASSERT_TRUE(setStd.count(5));
  ASSERT_FALSE(setStd.count(7));
  ASSERT_EQ(setStd.size(), 6UL);
}

TEST(SetTest, CopyConstructor) {
  std::set<int> setStd = {1, 2, 3, 4, 5};
  std::set<int> newSetStd(setStd);

  ASSERT_EQ(setStd.size(), newSetStd.size());
  for (const int &item : setStd) {
    ASSERT_TRUE(newSetStd.count(item));
  }

  s21::set<int> set = {1, 2, 3, 4, 5};
  s21::set<int> newSet(set);

  ASSERT_EQ(set.size(), newSet.size());
  for (const int &item : set) {
    ASSERT_TRUE(newSet.contains(item));
  }

  for (int n : newSet) {
    ASSERT_TRUE(newSet.contains(n));
  }
}

TEST(SetTest, MoveConstructor) {
  std::set<int> setStd = {1, 2, 3, 4, 5};
  std::set<int> newSetStd(std::move(setStd));

  ASSERT_EQ(setStd.size(), 0UL);
  ASSERT_EQ(newSetStd.size(), 5UL);
  for (int i = 1; i <= 5; ++i) {
    ASSERT_TRUE(newSetStd.count(i));
  }

  s21::set<int> set = {1, 2, 3, 4, 5};
  s21::set<int> newSet(std::move(set));

  ASSERT_EQ(set.size(), 0UL);
  ASSERT_EQ(newSet.size(), 5UL);
  for (int i = 1; i <= 5; ++i) {
    ASSERT_TRUE(newSet.contains(i));
  }
}

TEST(SetTest, MoveOperator) {
  std::set<int> setStd = {1, 2, 3, 4, 5};

  std::set<int> setStdNew = std::move(setStd);

  ASSERT_TRUE(setStdNew.count(1));
  ASSERT_TRUE(setStdNew.count(2));
  ASSERT_TRUE(setStd.empty());

  s21::set<int> set = {1, 2, 3, 4, 5};

  s21::set<int> setNew = std::move(set);

  ASSERT_TRUE(setNew.contains(1));
  ASSERT_TRUE(setNew.contains(2));
  ASSERT_TRUE(set.empty());
}

TEST(SetTest, MoveOperatorSecond) {
  std::set<char> setStd = {'A', 'B'};
  ASSERT_TRUE(setStd.count('A'));
  setStd = std::set{'C', 'D'};
  ASSERT_TRUE(setStd.count('C'));
  ASSERT_FALSE(setStd.count('A'));
  ASSERT_FALSE(setStd.empty());

  s21::set<char> set = {'A', 'B'};
  ASSERT_TRUE(set.contains('A'));
  set = s21::set{'C', 'D'};
  ASSERT_TRUE(set.contains('C'));
  ASSERT_FALSE(set.contains('A'));
  ASSERT_FALSE(set.empty());
}

TEST(SetTest, IteratorBeginEnd) {
  std::set<char> setStd = {1, 2, 3};

  auto it_beginStd = setStd.begin();
  auto it_endStd = setStd.end();

  EXPECT_EQ(*it_beginStd, 1);
  EXPECT_EQ(it_endStd, setStd.end());

  s21::set<char> set = {1, 2, 3};

  auto it_begin = set.begin();
  auto it_end = set.end();

  EXPECT_EQ(*it_begin, 1);
  EXPECT_EQ(it_end, set.end());
}

TEST(SetTest, BeginEndEmpty) {
  std::set<int> emptySetStd;
  ASSERT_EQ(emptySetStd.begin(), emptySetStd.end());

  s21::set<int> emptySet;
  ASSERT_EQ(emptySet.begin(), emptySet.end());
}

TEST(SetTest, InsertUniqueElements) {
  s21::set<int> set;
  auto [it, inserted] = set.insert(1);

  ASSERT_TRUE(inserted);
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(set.size(), 1UL);

  ASSERT_TRUE(set.contains(1));
}

TEST(SetTest, InsertDuplicateElements) {
  s21::set<int> set = {2, 4, 6};

  auto [it, inserted] = set.insert(4);

  ASSERT_FALSE(inserted);
  ASSERT_EQ(*it, 4);
  ASSERT_EQ(set.size(), 3UL);

  ASSERT_TRUE(set.contains(2));
  ASSERT_TRUE(set.contains(4));
  ASSERT_TRUE(set.contains(6));
}

TEST(SetTest, MaxSizeTest) {
  std::set<int> setStd = {};
  size_t resultStd = setStd.max_size();
  EXPECT_GE(resultStd, setStd.size());

  s21::set<int> set = {};
  size_t result = set.max_size();
  EXPECT_GE(result, set.size());
}

TEST(SetTest, InsertAfterClear) {
  s21::set<int> set = {1, 2, 3};
  set.clear();

  auto [it, inserted] = set.insert(4);

  ASSERT_TRUE(inserted);
  ASSERT_EQ(*it, 4);
  ASSERT_EQ(set.size(), 1UL);
}

TEST(SetTest, InsertManyVal) {
  s21::set<int> set;

  for (int i = 0; i < 5; ++i) {
    auto [it, inserted] = set.insert(i);

    ASSERT_TRUE(inserted);
    ASSERT_EQ(*it, i);
  }

  ASSERT_EQ(set.size(), 5UL);
}

TEST(SetTest, EraseByIterator) {
  s21::set<int> set = {1, 3, 5};
  auto it = set.find(3);

  ASSERT_NE(it, set.end());

  set.erase(it);
  ASSERT_EQ(set.find(3), set.end());
  ASSERT_EQ(set.size(), 2UL);
  ASSERT_NE(set.find(1), set.end());
  ASSERT_NE(set.find(5), set.end());
}

TEST(SetTest, EraseNonExistent) {
  s21::set<int> set = {1, 3, 5};
  size_t numErased = set.erase(4);

  ASSERT_EQ(numErased, 0UL);
  ASSERT_EQ(set.size(), 3UL);
}

TEST(SetTest, EraseManyVal) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  set.erase(set.find(2));
  set.erase(set.find(4));

  ASSERT_EQ(set.find(2), set.end());
  ASSERT_EQ(set.find(4), set.end());

  ASSERT_EQ(set.size(), 3UL);

  ASSERT_NE(set.find(1), set.end());
  ASSERT_NE(set.find(3), set.end());
  ASSERT_NE(set.find(5), set.end());
}

TEST(SetTest, Contains) {
  s21::set<int> set;
  set.insert(5);
  ASSERT_TRUE(set.contains(5));
  ASSERT_FALSE(set.contains(6));
}

TEST(SetTest, Find) {
  s21::set<int> set;
  set.insert(5);
  auto it = set.find(5);
  ASSERT_NE(it, set.end());
  ASSERT_EQ(*it, 5);
}

TEST(SetTest, Swap) {
  s21::set<int> set;
  set.insert(5);
  s21::set<int> newSet;
  newSet.insert(6);
  set.swap(newSet);
  ASSERT_TRUE(set.contains(6));
}

TEST(SetTest, SwapWithEmpty) {
  s21::set<int> set = {1, 2, 3};
  s21::set<int> emptySet;

  set.swap(emptySet);

  ASSERT_TRUE(set.empty());
  ASSERT_EQ(emptySet.size(), 3UL);
  ASSERT_TRUE(emptySet.contains(1));
  ASSERT_TRUE(emptySet.contains(2));
  ASSERT_TRUE(emptySet.contains(3));
}

TEST(SetTest, SwapManyVal) {
  s21::set<int> set1;
  s21::set<int> set2;

  for (int i = 0; i < 20; ++i) {
    set1.insert(i);
  }

  for (int i = 20; i < 30; ++i) {
    set2.insert(i);
  }

  set1.swap(set2);

  for (int i = 0; i < 20; ++i) {
    ASSERT_FALSE(set1.contains(i));
    ASSERT_TRUE(set2.contains(i));
  }

  for (int i = 20; i < 30; ++i) {
    ASSERT_FALSE(set2.contains(i));
    ASSERT_TRUE(set1.contains(i));
  }
}

TEST(SetTest, SwapSelfSwap) {
  s21::set<int> set = {1, 2, 3, 4, 5};
  set.swap(set);

  ASSERT_EQ(set.size(), 5UL);
  ASSERT_TRUE(set.contains(1));
  ASSERT_TRUE(set.contains(2));
  ASSERT_TRUE(set.contains(3));
  ASSERT_TRUE(set.contains(4));
  ASSERT_TRUE(set.contains(5));
}

TEST(SetTest, ClearAndFind) {
  s21::set<int> set;
  set.insert(5);
  set.insert(6);
  set.clear();
  ASSERT_FALSE(set.contains(6));
  ASSERT_EQ(set.size(), 0UL);
}

TEST(SetTest, MergeWithDuplicates) {
  s21::set<char> p{'C', 'B', 'B', 'A'};
  s21::set<char> q{'E', 'D', 'E', 'C'};

  p.merge(q);

  ASSERT_EQ(p.size(), 5UL);
  ASSERT_TRUE(p.contains('C'));
  ASSERT_TRUE(p.contains('D'));
  ASSERT_TRUE(p.contains('B'));
  ASSERT_TRUE(p.contains('E'));
  ASSERT_TRUE(q.contains('C'));

  ASSERT_EQ(q.size(), 1UL);
}

TEST(SetTest, MergeEmptySets) {
  s21::set<int> set1;
  s21::set<int> set2;
  set1.merge(set2);

  ASSERT_TRUE(set1.empty());
  ASSERT_TRUE(set2.empty());
}

TEST(SetTest, MergeIntoEmptySet) {
  s21::set<int> set1;
  s21::set<int> set2 = {1, 2, 3};

  set1.merge(set2);

  ASSERT_EQ(set1.size(), 3UL);
  ASSERT_TRUE(set2.empty());
}

TEST(SetTest, MergeFromEmptySet) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2;

  set1.merge(set2);

  ASSERT_EQ(set1.size(), 3UL);
  ASSERT_TRUE(set2.empty());
}

TEST(SetTest, MergeAll) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5, 6};

  set1.merge(set2);

  ASSERT_EQ(set1.size(), 6UL);
  ASSERT_EQ(set2.size(), 0UL);
  ASSERT_TRUE(set1.contains(1));
  ASSERT_TRUE(set1.contains(2));
  ASSERT_TRUE(set1.contains(3));
  ASSERT_TRUE(set1.contains(4));
  ASSERT_TRUE(set1.contains(5));
  ASSERT_TRUE(set1.contains(6));
}

TEST(SetTest, MergeSelf) {
  s21::set<int> set = {1, 2, 3};
  set.merge(set);

  ASSERT_EQ(set.size(), 3UL);
}

TEST(SetTest, InsertMany) {
  s21::set<int> set;
  std::set<int> stdSet;

  auto result = set.insert_many(3, 1, 4, 1, 5, 9);

  std::vector<std::pair<std::set<int>::iterator, bool>> stdResults;
  stdResults.push_back(stdSet.insert(3));
  stdResults.push_back(stdSet.insert(1));
  stdResults.push_back(stdSet.insert(4));
  stdResults.push_back(stdSet.insert(1));
  stdResults.push_back(stdSet.insert(5));
  stdResults.push_back(stdSet.insert(9));

  ASSERT_EQ(set.size(), stdSet.size());
  ASSERT_EQ(result.size(), stdResults.size());

  for (size_t i = 0; i < stdResults.size(); ++i) {
    ASSERT_EQ(result[i].second, stdResults[i].second);

    if (result[i].second) {
      ASSERT_EQ(*result[i].first, *stdResults[i].first);
    }
  }

  for (const auto &elem : stdSet) {
    ASSERT_TRUE(set.contains(elem));
  }
}

TEST(SetTest, InsertManyEmpty) {
  s21::set<int> set;
  auto result = set.insert_many();

  ASSERT_TRUE(result.empty());
  ASSERT_TRUE(set.empty());
}

TEST(SetTest, InsertManyDuplicates) {
  s21::set<int> set;

  auto result = set.insert_many(1, 1, 1, 2, 2);

  ASSERT_EQ(set.size(), 2UL);
  ASSERT_EQ(result.size(), 5UL);

  ASSERT_TRUE(result[0].second);
  ASSERT_FALSE(result[1].second);
  ASSERT_FALSE(result[2].second);
  ASSERT_TRUE(result[3].second);
  ASSERT_FALSE(result[4].second);
}
