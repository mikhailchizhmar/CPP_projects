#include "gtest/gtest.h"
#include "s21_avl_tree.h"

namespace s21 {

template <typename Key, typename T>
class BinaryTreeTest : public ::testing::Test {
 protected:
  BinaryTree<Key, T>* tree;
  BinaryTree<Key, T>* tree2;

  BinaryTreeTest() {
    tree = new BinaryTree<Key, T>();
    tree2 = new BinaryTree<Key, T>();
  }

  ~BinaryTreeTest() override {
    delete tree;
    delete tree2;
  }
};

using IntTree = BinaryTreeTest<int, int>;

TEST(BinaryTreeTest, DefaultConstructor) {
  BinaryTree<int, int> tree;
  ASSERT_TRUE(tree.empty());
}

TEST_F(IntTree, InitializerListConstructor) {
  BinaryTree<int, int> tree{(std::make_pair(2, 200))};

  ASSERT_TRUE(tree.contains(2));
  ASSERT_FALSE(tree.contains(200));
  ASSERT_FALSE(tree.empty());
}

TEST_F(IntTree, InitializerListConstructorEmpty) {
  BinaryTree<int, int> tree{};

  ASSERT_FALSE(tree.contains(100));
  ASSERT_TRUE(tree.empty());
}

TEST(BinaryTreeTest, ParamConstructor) {
  BinaryTree<int, int> tree(1, 100);
  ASSERT_FALSE(tree.empty());
  auto it_begin = tree.begin();
  EXPECT_EQ(*it_begin, 100);
  ASSERT_TRUE(tree.contains(1));
}

TEST_F(IntTree, CopyConstructor) {
  std::pair<int, int> value(1, 100);
  tree->insert(value);
  BinaryTree<int, int> newTree(*tree);
  ASSERT_TRUE(newTree.contains(1));
}

TEST_F(IntTree, MoveConstructor) {
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(2, 200));

  BinaryTree<int, int> newTree(std::move(*tree));

  ASSERT_TRUE(newTree.contains(1));
  ASSERT_TRUE(newTree.contains(2));
  ASSERT_TRUE(tree->empty());
}

TEST_F(IntTree, MoveOperator) {
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(2, 200));

  BinaryTree<int, int> newTree = std::move(*tree);

  ASSERT_TRUE(newTree.contains(1));
  ASSERT_TRUE(newTree.contains(2));
  ASSERT_TRUE(tree->empty());
}

TEST_F(IntTree, MoveOperatorSecond) {
  tree->insert('A');
  tree->insert('B');

  BinaryTree<int, int> tree = BinaryTree{1, 2};
  ASSERT_TRUE(tree.contains(1));
  ASSERT_FALSE(tree.contains('A'));
  ASSERT_FALSE(tree.empty());
}

TEST_F(IntTree, IncrementEndIterator) {
  tree->insert(std::make_pair(1, 100));
  auto it = tree->end();
  ASSERT_EQ(++it, nullptr);
}

TEST_F(IntTree, IncrementOnEmptyTree) {
  auto it = tree->begin();
  ASSERT_EQ(it, tree->end());
  ASSERT_EQ(++it, nullptr);
}

TEST_F(IntTree, IncrementEnd) {
  tree->insert(std::make_pair(1, 1));
  tree->insert(std::make_pair(0, 0));
  tree->insert(std::make_pair(2, 2));

  auto it = tree->find(2);
  ASSERT_NE(it, tree->end());
  ++it;
  ASSERT_EQ(it, tree->end());
}

TEST_F(IntTree, IncrementManyVal) {
  tree->insert(std::make_pair(3, 1));
  tree->insert(std::make_pair(2, -1));
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(4, 300));
  tree->insert(std::make_pair(5, 500));

  auto it = tree->find(4);
  ASSERT_EQ(*it, 300);

  ++it;
  ASSERT_TRUE(tree->IsBalanced());

  ASSERT_EQ(*it, 500);
}

TEST_F(IntTree, PostIncrementEndIterator) {
  tree->insert(std::make_pair(1, 100));
  auto it = tree->begin();
  auto post = it++;

  ASSERT_TRUE(post != tree->end());
  ASSERT_EQ(*post, 100);
  ASSERT_TRUE(it == tree->end());
}

TEST_F(IntTree, PostIncrementOnEmpty) {
  auto it = tree->begin();
  ASSERT_EQ(++it, nullptr);
}

TEST_F(IntTree, PostIncrementManyVal) {
  tree->insert(std::make_pair(3, 1));
  tree->insert(std::make_pair(2, -1));
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(4, 300));
  tree->insert(std::make_pair(5, 500));

  auto it = tree->begin();
  int oldValue = *it;

  auto post = it++;
  ASSERT_EQ(*post, oldValue);
}

TEST_F(IntTree, InsertIntoEmptyTree) {
  std::pair<int, int> value(1, 100);
  auto result = tree->insert(value);
  ASSERT_TRUE(result.second);
  ASSERT_TRUE(tree->contains(1));
}

TEST_F(IntTree, InsertNewKey) {
  std::pair<int, int> value1(1, 100);
  auto result1 = tree->insert(value1);
  ASSERT_TRUE(result1.second);

  std::pair<int, int> value2(2, 200);
  auto result2 = tree->insert(value2);
  ASSERT_TRUE(result2.second);

  ASSERT_TRUE(tree->contains(1));
  ASSERT_TRUE(tree->contains(2));
}

TEST_F(IntTree, InsertExistingKey) {
  std::pair<int, int> value1(1, 100);
  auto result1 = tree->insert(value1);
  ASSERT_TRUE(result1.second);

  std::pair<int, int> value2(1, 200);
  auto result2 = tree->insert(value2);
  ASSERT_FALSE(result2.second);
  ASSERT_TRUE(tree->contains(1));
}

TEST_F(IntTree, DestructorTest) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);

  tree->insert(value1);
  tree->insert(value2);

  ASSERT_TRUE(tree != nullptr);

  delete tree;
  tree = nullptr;

  ASSERT_TRUE(tree == nullptr);
}

TEST_F(IntTree, EraseExistingKey) {
  std::pair<int, int> value1(1, 100);
  tree->insert(value1);

  tree->erase(1);
  ASSERT_FALSE(tree->contains(1));
}

TEST_F(IntTree, EraseNonExistingKey) {
  std::pair<int, int> value1(1, 100);
  tree->insert(value1);

  tree->erase(2);
  ASSERT_FALSE(tree->contains(2));
}

TEST_F(IntTree, EraseAllKeys) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);
  std::pair<int, int> value3(3, 300);

  tree->insert(value1);
  tree->insert(value2);
  tree->insert(value3);

  tree->erase(1);
  tree->erase(2);
  tree->erase(3);

  ASSERT_FALSE(tree->contains(1));
  ASSERT_FALSE(tree->contains(2));
  ASSERT_FALSE(tree->contains(3));
}

TEST_F(IntTree, IteratorBeginEnd) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);
  std::pair<int, int> value3(3, 300);

  tree->insert(value1);
  tree->insert(value2);
  tree->insert(value3);

  auto it_begin = tree->begin();
  auto it_end = tree->end();

  EXPECT_EQ(*it_begin, 100);
  EXPECT_EQ(it_end, tree->end());
}

TEST_F(IntTree, BeginEndEmpty) {
  BinaryTree<int, int> emptyTree;
  ASSERT_EQ(emptyTree.begin(), emptyTree.end());
}

TEST_F(IntTree, BeginEnd) {
  std::pair<int, int> value1(1, 100);

  tree->insert(value1);

  auto it_begin = tree->begin();
  auto it_end = tree->end();

  ASSERT_EQ(*it_begin, 100);
  ASSERT_EQ(it_end, nullptr);
}

TEST_F(IntTree, BeginEnd2) {
  std::pair<int, int> value1(2, 200);
  std::pair<int, int> value2(1, 100);
  std::pair<int, int> value3(3, 300);

  tree->insert(value1);
  tree->insert(value2);
  tree->insert(value3);

  auto it_begin = tree->begin();
  auto it_end = tree->end();

  ASSERT_NE(*it_begin, 200);
  ASSERT_EQ(it_end, nullptr);
}

TEST_F(IntTree, EmptyTree) { ASSERT_TRUE(tree->empty()); }

TEST_F(IntTree, NonEmpty) {
  std::pair<int, int> value(1, 100);
  tree->insert(value);
  ASSERT_FALSE(tree->empty());
}

TEST_F(IntTree, EmptyAfterClear) {
  std::pair<int, int> value(1, 100);
  tree->insert(value);
  tree->clear();
  ASSERT_TRUE(tree->empty());
}

TEST_F(IntTree, SizeOfEmpty) { ASSERT_EQ(static_cast<int>(tree->size()), 0); }

TEST_F(IntTree, SizeAfterInsert) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);
  std::pair<int, int> value3(3, 300);

  tree->insert(value1);
  tree->insert(value2);
  tree->insert(value3);

  ASSERT_EQ(static_cast<int>(tree->size()), 3);
}

TEST_F(IntTree, SizeAfterInsertAndErase) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);

  tree->insert(value1);
  tree->insert(value2);

  tree->erase(1);

  ASSERT_EQ(static_cast<int>(tree->size()), 1);
}

TEST_F(IntTree, MaxSizeTest) {
  size_t expected =
      std::numeric_limits<typename BinaryTree<int, int>::size_type>::max();
  size_t result = tree->max_size();
  EXPECT_EQ(expected, result);
}

TEST_F(IntTree, ContainsEmpty) {
  bool result = tree->contains(1);
  EXPECT_FALSE(result);
}

TEST_F(IntTree, ContainsExisting) {
  int key = 1;
  int value = 100;
  tree->insert(std::make_pair(key, value));
  bool result = tree->contains(key);
  EXPECT_TRUE(result);
}

TEST_F(IntTree, ContainsNonexistent) {
  int key = 1;
  int value = 100;
  tree->insert(std::make_pair(key, value));
  bool result = tree->contains(2);
  EXPECT_FALSE(result);
}

TEST_F(IntTree, SwapTest) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);
  tree->insert(value1);
  tree->insert(value2);

  std::pair<int, int> value3(3, 300);
  std::pair<int, int> value4(4, 400);
  tree2->insert(value3);
  tree2->insert(value4);

  tree->swap(*tree2);

  ASSERT_TRUE(tree->contains(3));
  ASSERT_TRUE(tree->contains(4));

  ASSERT_TRUE(tree2->contains(1));
  ASSERT_TRUE(tree2->contains(2));
}

TEST_F(IntTree, SwapEmpty) {
  tree->swap(*tree2);
  ASSERT_TRUE(tree->empty());
  ASSERT_TRUE(tree2->empty());
}

TEST_F(IntTree, SwapOneEmpty) {
  std::pair<int, int> value(1, 100);
  tree->insert(value);
  tree->swap(*tree2);

  ASSERT_TRUE(tree->empty());
  ASSERT_TRUE(tree2->contains(1));
}

TEST_F(IntTree, SwapTheSame) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);
  tree->insert(value1);
  tree->insert(value2);
  tree2->insert(value1);
  tree2->insert(value2);

  tree->swap(*tree2);

  ASSERT_TRUE(tree2->contains(1));
  ASSERT_TRUE(tree2->contains(2));
}

TEST_F(IntTree, MergeEmpty) {
  tree->merge(*tree2);

  ASSERT_TRUE(tree->empty());
  ASSERT_EQ(static_cast<int>(tree2->size()), 0);
}

TEST_F(IntTree, MergeNonEmpty) {
  std::pair<int, int> value1(1, 100);
  tree2->insert(value1);

  tree->merge(*tree2);

  ASSERT_EQ(static_cast<int>(tree->size()), 1);
  ASSERT_TRUE(tree->contains(1));
  ASSERT_EQ(static_cast<int>(tree2->size()), 0);
}

TEST_F(IntTree, MergeTwoNonEmpty) {
  std::pair<int, int> value1(1, 100);
  std::pair<int, int> value2(2, 200);
  tree->insert(value1);
  tree2->insert(value2);

  tree->merge(*tree2);

  ASSERT_EQ(static_cast<int>(tree->size()), 2);
  ASSERT_TRUE(tree->contains(1));
  ASSERT_TRUE(tree->contains(2));
  ASSERT_EQ(static_cast<int>(tree2->size()), 0);
}

TEST_F(IntTree, MergeTrees) {
  tree->insert(std::make_pair(3, 300));
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(2, 200));

  tree2->insert(std::make_pair(6, 600));
  tree2->insert(std::make_pair(4, 400));
  tree2->insert(std::make_pair(5, 500));

  ASSERT_TRUE(tree->contains(1));
  ASSERT_TRUE(tree2->contains(4));

  tree->merge(*tree2);

  ASSERT_TRUE(tree->contains(1));
  ASSERT_TRUE(tree->contains(2));
  ASSERT_TRUE(tree->contains(3));
  ASSERT_TRUE(tree->contains(4));
  ASSERT_TRUE(tree->contains(5));
  ASSERT_TRUE(tree->contains(6));

  ASSERT_TRUE(tree2->empty());
  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, HeightTest) {
  ASSERT_EQ(tree->Height(), 0);

  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(2, 200));
  tree->insert(std::make_pair(3, 300));

  ASSERT_EQ(tree->Height(), 2);
}

TEST_F(IntTree, BalanceFactorTest) {
  ASSERT_EQ(tree->BalanceFactor(), 0);
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(2, 200));

  ASSERT_EQ(tree->BalanceFactor(), -1);
}

TEST_F(IntTree, IsBalancedTest) {
  tree->insert(std::make_pair(2, 300));
  tree->insert(std::make_pair(3, 200));
  tree->insert(std::make_pair(1, 100));

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest) {
  tree->insert(std::make_pair(3, 300));
  tree->insert(std::make_pair(2, 200));
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(5, 500));
  tree->insert(std::make_pair(7, 700));
  tree->insert(std::make_pair(9, 900));

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_InsertAscending) {
  for (int i = 1; i <= 100; ++i) {
    tree->insert(std::make_pair(i, i * 100));
  }

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_InsertDescending) {
  for (int i = 100; i >= 1; --i) {
    tree->insert(std::make_pair(i, i * 100));
  }

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_InsertRandom) {
  std::srand(std::time(nullptr));
  for (int i = 0; i < 100; ++i) {
    int key = std::rand() % 100 + 1;
    tree->insert(std::make_pair(key, key * 100));
  }

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_InsertValue) {
  for (int i = 1; i <= 100; ++i) {
    tree->insert(i * 100);
  }

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_DeleteValue) {
  for (int i = 1; i <= 100; ++i) {
    tree->insert(i * 100);
  }

  for (int i = 1; i <= 20; ++i) {
    tree->erase(i * 100);
  }

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_DeleteValu2) {
  tree->insert(10);
  tree->insert(5);
  tree->insert(15);
  tree->insert(33);
  tree->insert(40);
  tree->insert(45);

  tree->erase(15);
  tree->erase(5);

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_DeleteWithIterator) {
  tree->insert(std::make_pair(1, 100));
  tree->insert(std::make_pair(2, 200));
  tree->insert(std::make_pair(3, 300));
  tree->insert(std::make_pair(4, 400));
  tree->insert(std::make_pair(5, 500));
  tree->insert(std::make_pair(6, 600));
  tree->insert(std::make_pair(7, 7));

  BinaryTree<int, int>::iterator it3 = tree->find(6);
  tree->erase(it3);
  ASSERT_FALSE(tree->contains(6));

  BinaryTree<int, int>::iterator it4 = tree->find(5);
  tree->erase(it4);
  ASSERT_FALSE(tree->contains(5));

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, BalanceTest_DeletetRandom) {
  std::srand(std::time(nullptr));
  for (int i = 0; i < 100; ++i) {
    int key = std::rand() % 100 + 1;
    tree->erase(key * 100);
    tree->erase(key * 88);
    tree->erase(key * 45);
    tree->erase(key * 13);
  }

  ASSERT_TRUE(tree->IsBalanced());
}

TEST_F(IntTree, InsertMany) {
  std::pair<int, int> data1 = std::make_pair(1, 100);
  std::pair<int, int> data2 = std::make_pair(2, 200);
  std::pair<int, int> data3 = std::make_pair(3, 300);

  auto results = tree->insert_many(data1, data2, data3);

  ASSERT_EQ(results.size(), 3UL);

  for (const auto& result : results) {
    ASSERT_TRUE(result.second);
  }

  ASSERT_TRUE(tree->contains(1));
  ASSERT_TRUE(tree->contains(2));
  ASSERT_TRUE(tree->contains(3));

  ASSERT_EQ(tree->find(1).second(), 100);
  ASSERT_EQ(tree->find(2).second(), 200);
  ASSERT_EQ(tree->find(3).second(), 300);
}

}  // namespace s21
