#include <set>

#include "gtest/gtest.h"
#include "s21_multiset.h"

// constructors
TEST(MultiSetTest, DefaultConstructor) {
  s21::multiset<int> multiset;
  ASSERT_EQ(multiset.size(), 0UL);
  ASSERT_TRUE(multiset.empty());

  std::multiset<int> multisetStd;
  ASSERT_EQ(multisetStd.size(), 0UL);
  ASSERT_TRUE(multisetStd.empty());
}

TEST(MultiSetTest, InitializerConstructor) {
  s21::multiset<int> multiset = {100, 200, 300, 100};
  ASSERT_EQ(multiset.size(), 4UL);
  ASSERT_FALSE(multiset.empty());

  std::multiset<int> multisetStd = {100, 200, 300, 100};
  ASSERT_EQ(multisetStd.size(), 4UL);
  ASSERT_TRUE(multisetStd.count(100));
  ASSERT_TRUE(multisetStd.count(200));
  ASSERT_TRUE(multisetStd.count(300));
  ASSERT_FALSE(multisetStd.empty());
}

TEST(MultiSetTest, CopyConstructor) {
  s21::multiset<int> multiset = {100, 200, 300, 100, 100};
  s21::multiset<int> multisetCopy(multiset);

  ASSERT_EQ(multisetCopy.size(), 5UL);
  ASSERT_TRUE(multisetCopy.count(100));
  ASSERT_TRUE(multisetCopy.count(200));
  ASSERT_TRUE(multisetCopy.count(300));
  ASSERT_FALSE(multisetCopy.empty());

  std::multiset<int> multisetStd = {100, 200, 300, 100, 100};
  std::multiset<int> multisetStdCopy(multisetStd);

  ASSERT_EQ(multisetStdCopy.size(), 5UL);
  ASSERT_TRUE(multisetStdCopy.count(100));
  ASSERT_TRUE(multisetStdCopy.count(200));
  ASSERT_TRUE(multisetStdCopy.count(300));
  ASSERT_FALSE(multisetStdCopy.empty());
}

TEST(MultiSetTest, MoveConstructor) {
  s21::multiset<int> multiset = {100, 200, 300, 100};
  s21::multiset<int> multisetMove(std::move(multiset));

  ASSERT_EQ(multisetMove.size(), 4UL);
  ASSERT_TRUE(multisetMove.count(100));
  ASSERT_TRUE(multisetMove.count(200));
  ASSERT_TRUE(multisetMove.count(300));
  ASSERT_FALSE(multisetMove.empty());

  std::multiset<int> multisetStd = {100, 200, 300, 100};
  std::multiset<int> multisetStdMove(std::move(multisetStd));

  ASSERT_EQ(multisetStdMove.size(), 4UL);
  ASSERT_TRUE(multisetStdMove.count(100));
  ASSERT_TRUE(multisetStdMove.count(200));
  ASSERT_TRUE(multisetStdMove.count(300));
  ASSERT_FALSE(multisetStdMove.empty());
}

// begin, end
TEST(MultiSetTest, BeginAndEnd) {
  s21::multiset<int> multiset;
  multiset.insert(100);
  multiset.insert(200);
  multiset.insert(300);

  std::multiset<int> multisetStd;
  multisetStd.insert(100);
  multisetStd.insert(200);
  multisetStd.insert(300);

  auto itBegin = multiset.begin();
  auto itStdBegin = multisetStd.begin();
  ASSERT_EQ(*itBegin, *itStdBegin);

  auto itEnd = multiset.end();
  auto itStdEnd = multisetStd.end();
  ASSERT_TRUE(itEnd == multiset.end());
  ASSERT_TRUE(itStdEnd == multisetStd.end());
}

// clear, insert, erase, swap, merge
TEST(MultiSetTest, Clear) {
  s21::multiset<int> multiset = {100, 200, 300, 100};
  ASSERT_EQ(multiset.size(), 4UL);
  ASSERT_FALSE(multiset.empty());

  multiset.clear();

  ASSERT_EQ(multiset.size(), 0UL);
  ASSERT_TRUE(multiset.empty());

  std::multiset<int> multisetStd = {100, 200, 300, 100};
  ASSERT_EQ(multisetStd.size(), 4UL);
  ASSERT_FALSE(multisetStd.empty());

  multisetStd.clear();

  ASSERT_EQ(multisetStd.size(), 0UL);
  ASSERT_TRUE(multisetStd.empty());
}

TEST(MultiSetTest, InsertMethodComparisonWithStdMultiset) {
  s21::multiset<int> multiset;
  std::multiset<int> multisetStd;

  for (int i = 1; i <= 100; ++i) {
    multiset.insert(i);
    multisetStd.insert(i);
  }

  ASSERT_EQ(multiset.size(), multisetStd.size());

  for (int i = 1; i <= 100; ++i) {
    ASSERT_TRUE(multiset.count(i) > 0);
    ASSERT_TRUE(multisetStd.count(i) > 0);

    ASSERT_EQ(multiset.count(i), multisetStd.count(i));
  }
}

TEST(MultiSetTest, InsertDuplicates) {
  s21::multiset<int> multiset;
  std::multiset<int> multisetStd;

  multiset.insert(42);
  multiset.insert(42);
  multiset.insert(42);
  multisetStd.insert(42);
  multisetStd.insert(42);
  multisetStd.insert(42);

  ASSERT_EQ(multiset.size(), multisetStd.size());

  ASSERT_EQ(multiset.count(42), 3U);
  ASSERT_EQ(multisetStd.count(42), 3U);
}

TEST(MultiSetTest, EraseMethodEmpty) {
  s21::multiset<int> multiset;
  ASSERT_EQ(multiset.size(), 0U);

  s21::multiset<int>::iterator it = multiset.begin();
  ASSERT_NO_THROW(multiset.erase(it));
  ASSERT_EQ(multiset.size(), 0U);
}

TEST(MultiSetTest, EraseSingle) {
  s21::multiset<int> multiset = {42};
  ASSERT_EQ(multiset.size(), 1U);

  s21::multiset<int>::iterator it = multiset.begin();
  multiset.erase(it);
  ASSERT_EQ(multiset.size(), 0U);
  ASSERT_TRUE(multiset.empty());

  std::multiset<int> multisetStd = {42};
  ASSERT_EQ(multisetStd.size(), 1U);

  std::multiset<int>::iterator itStd = multisetStd.begin();
  multisetStd.erase(itStd);
  ASSERT_EQ(multisetStd.size(), 0U);
  ASSERT_TRUE(multisetStd.empty());
}

TEST(MultiSetTest, EraseManyVal) {
  s21::multiset<int> multiset = {2, 3, 2, 6, 4};
  ASSERT_EQ(multiset.size(), 5U);

  s21::multiset<int>::iterator it = multiset.begin();
  multiset.erase(it);
  ASSERT_EQ(multiset.size(), 4U);

  it = multiset.begin();
  multiset.erase(it);
  ASSERT_EQ(multiset.size(), 3U);

  std::multiset<int> multisetStd = {2, 3, 2, 6, 4};
  ASSERT_EQ(multisetStd.size(), 5U);

  std::multiset<int>::iterator StdIt = multisetStd.begin();
  multisetStd.erase(StdIt);
  ASSERT_EQ(multisetStd.size(), 4U);

  StdIt = multisetStd.begin();
  multisetStd.erase(StdIt);
  ASSERT_EQ(multisetStd.size(), 3U);
}

TEST(MultiSetTest, Swap) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {4, 5, 6};

  std::multiset<int> multisetStd1 = {1, 2, 3};
  std::multiset<int> multisetStd2 = {4, 5, 6};

  multiset1.swap(multiset2);
  multisetStd1.swap(multisetStd2);

  ASSERT_EQ(multiset1.size(), 3U);
  ASSERT_EQ(multiset2.size(), 3U);
  ASSERT_EQ(multisetStd1.size(), 3U);
  ASSERT_EQ(multisetStd2.size(), 3U);

  ASSERT_TRUE(multiset1.find(4) != multiset1.end());
  ASSERT_TRUE(multiset1.find(5) != multiset1.end());
  ASSERT_TRUE(multiset1.find(6) != multiset1.end());
  ASSERT_TRUE(multiset2.find(1) != multiset2.end());
  ASSERT_TRUE(multiset2.find(2) != multiset2.end());
  ASSERT_TRUE(multiset2.find(3) != multiset2.end());

  ASSERT_TRUE(multisetStd1.find(4) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(5) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(6) != multisetStd1.end());
  ASSERT_TRUE(multisetStd2.find(1) != multisetStd2.end());
  ASSERT_TRUE(multisetStd2.find(2) != multisetStd2.end());
  ASSERT_TRUE(multisetStd2.find(3) != multisetStd2.end());
}

TEST(MultiSetTest, SwapEmpty) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2;

  std::multiset<int> multisetStd1 = {1, 2, 3};
  std::multiset<int> multisetStd2;

  multiset1.swap(multiset2);
  multisetStd1.swap(multisetStd2);

  ASSERT_EQ(multiset1.size(), 0U);
  ASSERT_EQ(multiset2.size(), 3U);
  ASSERT_EQ(multisetStd1.size(), 0U);
  ASSERT_EQ(multisetStd2.size(), 3U);

  ASSERT_TRUE(multiset1.empty());
  ASSERT_TRUE(multiset2.count(1));
  ASSERT_TRUE(multiset2.count(2));
  ASSERT_TRUE(multiset2.count(3));

  ASSERT_TRUE(multisetStd1.empty());
  ASSERT_TRUE(multisetStd2.count(1));
  ASSERT_TRUE(multisetStd2.count(2));
  ASSERT_TRUE(multisetStd2.count(3));
}

TEST(MultiSetTest, MergeEmpty) {
  s21::multiset<int> multiset1;
  s21::multiset<int> multiset2;

  std::multiset<int> multisetStd1;
  std::multiset<int> multisetStd2;

  multiset1.merge(multiset2);
  multisetStd1.merge(multisetStd2);

  ASSERT_EQ(multiset1.size(), 0U);
  ASSERT_EQ(multiset2.size(), 0U);
  ASSERT_EQ(multisetStd1.size(), 0U);
  ASSERT_EQ(multisetStd2.size(), 0U);
}

TEST(MultiSetTest, MergeNonEmptyWithEmpty) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2;

  std::multiset<int> multisetStd1 = {1, 2, 3};
  std::multiset<int> multisetStd2;

  multiset1.merge(multiset2);
  multisetStd1.merge(multisetStd2);

  ASSERT_EQ(multiset1.size(), 3U);
  ASSERT_EQ(multiset2.size(), 0U);
  ASSERT_EQ(multisetStd1.size(), 3U);
  ASSERT_EQ(multisetStd2.size(), 0U);

  ASSERT_TRUE(multiset1.find(1) != multiset1.end());
  ASSERT_TRUE(multiset1.find(2) != multiset1.end());
  ASSERT_TRUE(multiset1.find(3) != multiset1.end());

  ASSERT_TRUE(multisetStd1.find(1) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(2) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(3) != multisetStd1.end());
}

TEST(MultiSetTest, Merge) {
  s21::multiset<int> multiset1 = {1, 2, 3};
  s21::multiset<int> multiset2 = {4, 5, 6};

  std::multiset<int> multisetStd1 = {1, 2, 3};
  std::multiset<int> multisetStd2 = {4, 5, 6};

  multiset1.merge(multiset2);
  multisetStd1.merge(multisetStd2);

  ASSERT_EQ(multiset1.size(), 6U);
  ASSERT_EQ(multiset2.size(), 0U);
  ASSERT_EQ(multisetStd1.size(), 6U);
  ASSERT_EQ(multisetStd2.size(), 0U);

  ASSERT_TRUE(multiset1.find(1) != multiset1.end());
  ASSERT_TRUE(multiset1.find(2) != multiset1.end());
  ASSERT_TRUE(multiset1.find(3) != multiset1.end());
  ASSERT_TRUE(multiset1.find(4) != multiset1.end());
  ASSERT_TRUE(multiset1.find(5) != multiset1.end());
  ASSERT_TRUE(multiset1.find(6) != multiset1.end());

  ASSERT_TRUE(multisetStd1.find(1) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(2) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(3) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(4) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(5) != multisetStd1.end());
  ASSERT_TRUE(multisetStd1.find(6) != multisetStd1.end());
}

TEST(MultiSetTest, MergeWithDuplicates) {
  s21::multiset<int> multiset1 = {1, 2, 2, 3};
  s21::multiset<int> multiset2 = {2, 3, 4, 5};

  std::multiset<int> multisetStd1 = {1, 2, 2, 3};
  std::multiset<int> multisetStd2 = {2, 3, 4, 5};

  multiset1.merge(multiset2);
  multisetStd1.merge(multisetStd2);

  ASSERT_EQ(multiset1.size(), 8U);
  ASSERT_EQ(multiset2.size(), 0U);
  ASSERT_EQ(multisetStd1.size(), 8U);
  ASSERT_EQ(multisetStd2.size(), 0U);

  ASSERT_EQ(multiset1.count(1), 1U);
  ASSERT_EQ(multiset1.count(2), 3U);
  ASSERT_EQ(multiset1.count(3), 2U);
  ASSERT_EQ(multiset1.count(4), 1U);
  ASSERT_EQ(multiset1.count(5), 1U);

  ASSERT_EQ(multisetStd1.count(1), 1U);
  ASSERT_EQ(multisetStd1.count(2), 3U);
  ASSERT_EQ(multisetStd1.count(3), 2U);
  ASSERT_EQ(multisetStd1.count(4), 1U);
  ASSERT_EQ(multisetStd1.count(5), 1U);
}

TEST(MultiSetTest, MergeManyDuplicates) {
  s21::multiset<int> multiset1 = {5, 5, 5, 5, 5, 3, 3, 3, 1, 1};
  s21::multiset<int> multiset2 = {5, 5, 4, 4, 4, 4, 3, 2, 2, 2};

  std::multiset<int> multisetStd1 = {5, 5, 5, 5, 5, 3, 3, 3, 1, 1};
  std::multiset<int> multisetStd2 = {5, 5, 4, 4, 4, 4, 3, 2, 2, 2};

  multiset1.merge(multiset2);
  multisetStd1.merge(multisetStd2);

  ASSERT_EQ(multiset1.size(), 20U);
  ASSERT_EQ(multiset2.size(), 0U);
  ASSERT_EQ(multisetStd1.size(), 20U);
  ASSERT_EQ(multisetStd2.size(), 0U);

  ASSERT_EQ(multiset1.count(1), 2U);
  ASSERT_EQ(multiset1.count(2), 3U);
  ASSERT_EQ(multiset1.count(3), 4U);
  ASSERT_EQ(multiset1.count(4), 4U);
  ASSERT_EQ(multiset1.count(5), 7U);

  ASSERT_EQ(multisetStd1.count(1), 2U);
  ASSERT_EQ(multisetStd1.count(2), 3U);
  ASSERT_EQ(multisetStd1.count(3), 4U);
  ASSERT_EQ(multisetStd1.count(4), 4U);
  ASSERT_EQ(multisetStd1.count(5), 7U);
}

// multiset lookup
TEST(MultiSetTest, CountEmpty) {
  s21::multiset<int> multiset;
  std::multiset<int> multisetStd;

  ASSERT_EQ(multiset.count(1), 0U);
  ASSERT_EQ(multisetStd.count(1), 0U);
}

TEST(MultiSetTest, CountSingle) {
  s21::multiset<int> multiset = {1};
  std::multiset<int> multisetStd = {1};

  ASSERT_EQ(multiset.count(1), 1U);
  ASSERT_EQ(multisetStd.count(1), 1U);

  ASSERT_EQ(multiset.count(2), 0U);
  ASSERT_EQ(multisetStd.count(2), 0U);
}

TEST(MultiSetTest, CountManuVal) {
  s21::multiset<int> multiset = {1, 1, 1, 2, 4};
  std::multiset<int> multisetStd = {1, 1, 1, 2, 4};

  ASSERT_EQ(multiset.count(1), 3U);
  ASSERT_EQ(multisetStd.count(1), 3U);

  ASSERT_EQ(multiset.count(2), 1U);
  ASSERT_EQ(multisetStd.count(2), 1U);

  ASSERT_EQ(multiset.count(5), 0U);
  ASSERT_EQ(multisetStd.count(5), 0U);
}

TEST(MultiSetTest, CountDuplicates) {
  s21::multiset<int> multiset = {2, 2, 2, 2, 2};
  std::multiset<int> multisetStd = {2, 2, 2, 2, 2};

  ASSERT_EQ(multiset.count(2), 5U);
  ASSERT_EQ(multisetStd.count(2), 5U);

  ASSERT_EQ(multiset.count(1), 0U);
  ASSERT_EQ(multisetStd.count(1), 0U);
}

TEST(MultiSetTest, FindInEmpty) {
  s21::multiset<int> multiet;
  std::multiset<int> stdSet;

  auto element = multiet.find(5);
  auto stdElement = stdSet.find(5);

  ASSERT_EQ(element, multiet.end());
  ASSERT_EQ(stdElement, stdSet.end());
}

TEST(MultiSetTest, Find) {
  s21::multiset<int> multiset = {1, 2, 3, 4, 5, 2, 3};
  std::multiset<int> multisetStd = {1, 2, 3, 4, 5, 2, 3};

  auto element = multiset.find(3);
  auto elementStd = multisetStd.find(3);

  ASSERT_NE(element, multiset.end());
  ASSERT_NE(elementStd, multisetStd.end());
  ASSERT_EQ(*element, *elementStd);

  element = multiset.find(10);
  elementStd = multisetStd.find(10);

  ASSERT_EQ(element, multiset.end());
  ASSERT_EQ(elementStd, multisetStd.end());

  element = multiset.find(2);
  elementStd = multisetStd.find(2);

  ASSERT_NE(element, multiset.end());
  ASSERT_NE(elementStd, multisetStd.end());
  ASSERT_EQ(*element, *elementStd);

  element = multiset.find(5);
  elementStd = multisetStd.find(5);

  ASSERT_NE(element, multiset.end());
  ASSERT_NE(elementStd, multisetStd.end());
  ASSERT_EQ(*element, *elementStd);
}

TEST(MultiSetTest, Contains) {
  s21::multiset<int> multiset = {1, 2, 3, 4, 5, 2, 3};
  std::multiset<int> multisetStd = {1, 2, 3, 4, 5, 2, 3};

  ASSERT_TRUE(multiset.contains(3));
  ASSERT_EQ(multiset.count(3), 2U);
  ASSERT_EQ(multisetStd.count(3), 2U);

  ASSERT_FALSE(multiset.contains(100));
  ASSERT_TRUE(multiset.contains(2));
}

TEST(MultiSetTest, ContainsEmpty) {
  s21::multiset<int> multiset;
  std::multiset<int> multisetStd;

  ASSERT_FALSE(multiset.contains(5));
  ASSERT_FALSE(multisetStd.count(5) > 0);
}

TEST(MultiSetTest, UpperLowerBound) {
  s21::multiset<int> multiset = {1, 2, 3, 4, 4, 4, 7};
  std::multiset<int> multisetStd = {1, 2, 3, 4, 4, 4, 7};

  auto lb = multiset.lower_bound(3);
  auto ub = multiset.upper_bound(3);
  ASSERT_EQ(lb.second(), 3);
  ASSERT_EQ(*ub, 4);

  auto lbStd = multisetStd.lower_bound(3);
  auto ubStd = multisetStd.upper_bound(3);
  ASSERT_EQ(*lbStd, 3);
  ASSERT_EQ(*ubStd, 4);
}

TEST(MultiSetTest, LowerBound) {
  s21::multiset<int> multiset = {5, 5, 10, 15};
  std::multiset<int> multisetStd = {5, 5, 10, 15};

  auto it = multiset.lower_bound(5);
  auto stdIt = multisetStd.lower_bound(5);
  ASSERT_EQ(*it, *stdIt);

  it = multiset.lower_bound(6);
  stdIt = multisetStd.lower_bound(6);
  ASSERT_EQ(*it, 10);
  ASSERT_EQ(*stdIt, 10);

  it = multiset.lower_bound(0);
  stdIt = multisetStd.lower_bound(0);
  ASSERT_NE(it, multiset.end());
  ASSERT_EQ(*it, 5);
  ASSERT_EQ(*stdIt, 5);

  it = multiset.lower_bound(20);
  stdIt = multisetStd.lower_bound(20);
  ASSERT_EQ(it, multiset.end());
  ASSERT_EQ(stdIt, multisetStd.end());
}

TEST(MultiSetTest, UpperBound) {
  s21::multiset<int> multiset = {5, 5, 10, 15};
  std::multiset<int> multisetStd = {5, 5, 10, 15};

  auto it = multiset.upper_bound(5);
  auto stdIt = multisetStd.upper_bound(5);
  ASSERT_EQ(*it, *stdIt);

  it = multiset.upper_bound(6);
  stdIt = multisetStd.upper_bound(6);
  ASSERT_EQ(*it, *stdIt);

  it = multiset.upper_bound(0);
  stdIt = multisetStd.upper_bound(0);
  ASSERT_EQ(it, multiset.begin());
  ASSERT_EQ(stdIt, multisetStd.begin());

  it = multiset.upper_bound(20);
  stdIt = multisetStd.upper_bound(20);
  ASSERT_EQ(it, multiset.end());
  ASSERT_EQ(stdIt, multisetStd.end());
}

TEST(MultiSetTest, EqualRange) {
  std::multiset<int> multisetStd = {1, 2, 3, 4, 4, 4, 7};

  auto rangeStd = multisetStd.equal_range(4);
  ASSERT_EQ(*rangeStd.first, 4);
  ASSERT_EQ(*rangeStd.second, 7);

  s21::multiset<int> multiset = {1, 2, 3, 4, 4, 4, 7};

  auto range = multiset.equal_range(4);
  ASSERT_EQ(*range.first, 4);
  ASSERT_EQ(*range.second, 7);
}

TEST(MultiSetTest, InsertMany) {
  s21::multiset<int> multiset;
  std::multiset<int> multisetStd;

  auto results = multiset.insert_many(5, 3, 8, 3, 5);
  multisetStd.insert({5, 3, 8, 3, 5});

  ASSERT_EQ(multiset.size(), 5UL);
  ASSERT_EQ(multisetStd.size(), multiset.size());

  for (int element : {3, 5, 8}) {
    ASSERT_EQ(multiset.count(element), multisetStd.count(element));
  }
}

TEST(MultiSetTest, InsertManyEmpty) {
  s21::multiset<int> multiset;
  auto result = multiset.insert_many();

  ASSERT_TRUE(result.empty());
  ASSERT_TRUE(multiset.empty());
}

TEST(MultiSetTest, InsertManyDuplicates) {
  s21::multiset<int> multiset;

  auto result = multiset.insert_many(1, 1, 1, 2, 2);

  ASSERT_EQ(multiset.size(), 5UL);
  ASSERT_EQ(result.size(), 5UL);

  for (const auto& res : result) {
    ASSERT_TRUE(res.second);
  }
}
