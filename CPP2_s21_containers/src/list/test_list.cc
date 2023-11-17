#include "gtest/gtest.h"
#include "s21_list.h"

TEST(ListTest, ConstructorSizeTest) {
  s21::list<int> myList(5);
  EXPECT_EQ(myList.size(), 5);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(myList.front(), 0);
    myList.pop_front();
  }
}

TEST(ListTest, CopyConstructorTest) {
  s21::list<int> original({1, 2, 3});
  s21::list<int> copy(original);

  EXPECT_EQ(copy.size(), original.size());
  while (!original.empty() && !copy.empty()) {
    EXPECT_EQ(copy.front(), original.front());
    original.pop_front();
    copy.pop_front();
  }
}

TEST(ListTest, MoveConstructorTest) {
  s21::list<int> original({1, 2, 3});
  s21::list<int> movedList(std::move(original));

  EXPECT_EQ(movedList.size(), 3);
  EXPECT_EQ(original.size(), 0);
  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(movedList.front(), i);
    movedList.pop_front();
  }
}

TEST(ListTest, InitializerListConstructorTest) {
  s21::list<int> myList({1, 2, 3});
  EXPECT_EQ(myList.size(), 3);
  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, DestructorTest) {
  s21::list<int>* dynamicList = new s21::list<int>(5);
  delete dynamicList;
}

TEST(ListTest, MoveAssignmentOperatorTest) {
  s21::list<int> original({1, 2, 3});
  s21::list<int> another({4, 5});
  another = std::move(original);

  EXPECT_EQ(another.size(), 3);
  EXPECT_EQ(original.size(), 0);
  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(another.front(), i);
    another.pop_front();
  }
}

TEST(ListTest, PushBackTest) {
  s21::list<int> myList;
  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  EXPECT_EQ(myList.size(), 3);
  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, PushFrontTest) {
  s21::list<int> myList;
  myList.push_front(1);
  myList.push_front(2);
  myList.push_front(3);

  EXPECT_EQ(myList.size(), 3);
  for (int i = 3; i >= 1; --i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, PopBackTest) {
  s21::list<int> myList({1, 2, 3});
  myList.pop_back();

  EXPECT_EQ(myList.size(), 2);
  for (int i = 1; i <= 2; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, PopBackEmptyListTest) {
  s21::list<int> myList;
  myList.pop_back();  // Should not crash

  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, PopFrontTest) {
  s21::list<int> myList({1, 2, 3});
  myList.pop_front();

  EXPECT_EQ(myList.size(), 2);
  for (int i = 2; i <= 3; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, PopFrontEmptyListTest) {
  s21::list<int> myList;
  myList.pop_front();  // Should not crash

  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, ClearTest) {
  s21::list<int> myList({1, 2, 3});
  myList.clear();

  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, BackTest) {
  s21::list<int> myList({1, 2, 3});

  EXPECT_EQ(myList.back(), 3);
}

TEST(ListTest, FrontTest) {
  s21::list<int> myList({1, 2, 3});

  EXPECT_EQ(myList.front(), 1);
}

TEST(ListTest, BackFrontExceptionTest) {
  s21::list<int> myList;

  EXPECT_THROW(myList.back(), std::out_of_range);
  EXPECT_THROW(myList.front(), std::out_of_range);
}

TEST(ListTest, EraseTest) {
  s21::list<int> myList({1, 2, 3});
  auto it = myList.begin();
  ++it;  // Pointing to 2

  myList.erase(it);
  EXPECT_EQ(myList.size(), 2);

  for (int i : {1, 3}) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, RemoveTest) {
  s21::list<int> myList({1, 2, 2, 3, 3, 3});
  myList.remove(2);
  myList.remove(3);

  EXPECT_EQ(myList.size(), 1);
  EXPECT_EQ(myList.front(), 1);
}

TEST(ListTest, AtTest) {
  s21::list<int> myList({1, 2, 3});
  auto it = myList.begin();
  ++it;

  EXPECT_EQ(myList.at(it), 2);
}

TEST(ListTest, AtExceptionTest) {
  s21::list<int> myList;
  auto it = myList.end();

  EXPECT_THROW(myList.at(it), std::out_of_range);
}

TEST(ListTest, SwapTest) {
  s21::list<int> list1({1, 2, 3});
  s21::list<int> list2({4, 5});

  list1.swap(list2);

  EXPECT_EQ(list1.size(), 2);
  EXPECT_EQ(list2.size(), 3);

  for (int i : {4, 5}) {
    EXPECT_EQ(list1.front(), i);
    list1.pop_front();
  }

  for (int i : {1, 2, 3}) {
    EXPECT_EQ(list2.front(), i);
    list2.pop_front();
  }
}

TEST(ListTest, MergeTest) {
  s21::list<int> list1({1, 3, 5});
  s21::list<int> list2({2, 4, 6});

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6);
  EXPECT_EQ(list2.size(), 0);
  for (int i = 1; i <= 6; ++i) {
    EXPECT_EQ(list1.front(), i);
    list1.pop_front();
  }
}

TEST(ListTest, ReverseTest) {
  s21::list<int> myList({1, 2, 3});
  myList.reverse();

  EXPECT_EQ(myList.size(), 3);
  for (int i = 3; i >= 1; --i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, UniqueTest) {
  s21::list<int> myList({1, 1, 2, 3, 3, 4});
  myList.unique();

  EXPECT_EQ(myList.size(), 4);
  for (int i = 1; i <= 4; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, SortTest) {
  s21::list<int> myList({3, 1, 2});
  myList.sort();

  EXPECT_EQ(myList.size(), 3);
  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, InsertTest) {
  s21::list<int> myList({1, 3});
  auto it = myList.begin();
  ++it;
  myList.insert(it, 2);

  EXPECT_EQ(myList.size(), 3);
  for (int i = 1; i <= 3; ++i) {
    EXPECT_EQ(myList.front(), i);
    myList.pop_front();
  }
}

TEST(ListTest, SpliceTest) {
  s21::list<int> myList1({1, 4});
  s21::list<int> myList2({2, 3});
  auto it = myList1.begin();
  ++it;
  auto const_it = s21::list<int>::const_iterator(it);
  myList1.splice(const_it, myList2);

  EXPECT_EQ(myList1.size(), 4);
  EXPECT_EQ(myList2.size(), 0);
  for (int i = 1; i <= 4; ++i) {
    EXPECT_EQ(myList1.front(), i);
    myList1.pop_front();
  }
}

TEST(ListTest, InsertMany) {
  s21::list<int> my_list;

  my_list.push_back(1);
  my_list.push_back(5);
  my_list.push_back(6);

  auto it = my_list.begin();
  ++it;
  auto const_it = s21::list<int>::const_iterator(it);
  my_list.insert_many(const_it, 2, 3, 4);

  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(my_list.back(), i);
    my_list.pop_back();
  }
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> my_list;

  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  my_list.insert_many_back(4, 5, 6);

  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(my_list.back(), i);
    my_list.pop_back();
  }
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> my_list;

  my_list.push_back(4);
  my_list.push_back(5);
  my_list.push_back(6);

  my_list.insert_many_front(1, 2, 3);

  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(my_list.back(), i);
    my_list.pop_back();
  }
}
