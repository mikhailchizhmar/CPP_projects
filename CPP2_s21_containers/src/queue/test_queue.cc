#include "gtest/gtest.h"
#include "s21_queue.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> original = {1, 2, 3};
  s21::queue<int> copy(original);

  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.front(), 1);
  EXPECT_EQ(copy.back(), 3);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> original = {1, 2, 3};
  s21::queue<int> moved(std::move(original));

  EXPECT_FALSE(moved.empty());
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(QueueTest, Destructor) {
  s21::queue<int>* ptr = new s21::queue<int>({1, 2, 3});
  delete ptr;
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> original = {1, 2, 3};
  s21::queue<int> assigned;
  assigned = std::move(original);

  EXPECT_FALSE(assigned.empty());
  EXPECT_EQ(assigned.front(), 1);
  EXPECT_EQ(assigned.back(), 3);

  // original теперь должен быть пустым
  EXPECT_TRUE(original.empty());
}

TEST(QueueTest, MoveAssignmentOperator_SelfAssignment) {
  s21::queue<int> q = {1, 2, 3};
  q = std::move(q);  // Самоприсваивание

  // Должно оставаться неизменным
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, FrontMethod) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.front(), 1);
}

TEST(QueueTest, BackMethod) {
  s21::queue<int> q = {1, 2, 3};
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, EmptyMethod) {
  s21::queue<int> empty_q;
  s21::queue<int> non_empty_q = {1, 2, 3};

  EXPECT_TRUE(empty_q.empty());
  EXPECT_FALSE(non_empty_q.empty());
}

TEST(QueueTest, SizeMethod) {
  s21::queue<int> q;
  EXPECT_EQ(q.size_(), 0);

  q.push(1);
  EXPECT_EQ(q.size_(), 1);

  q.push(2);
  EXPECT_EQ(q.size_(), 2);

  q.pop();
  EXPECT_EQ(q.size_(), 1);
}

TEST(QueueTest, PushMethod) {
  s21::queue<int> q;
  q.push(1);

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 1);
}

TEST(QueueTest, PopMethod) {
  s21::queue<int> q = {1, 2, 3};
  q.pop();

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.size_(), 2);
}

TEST(QueueTest, SwapMethod) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5, 6};

  q1.swap(q2);

  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q1.back(), 6);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, InsertManyBack) {
  s21::queue<int> my_queue;

  my_queue.push(1);
  my_queue.push(2);
  my_queue.push(3);

  my_queue.insert_many_back(4, 5, 6);

  for (int i = 1; i < 7; ++i) {
    EXPECT_EQ(my_queue.front(), i);
    my_queue.pop();
  }
}
