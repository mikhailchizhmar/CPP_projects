#ifndef CPP2_S21_CONTAINERS_SRC_BST_H_
#define CPP2_S21_CONTAINERS_SRC_BST_H_

#include <iostream>
#include <limits>

#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key, typename T>
struct Node {
  Key key;
  T value;
  Node *left;
  Node *right;
  Node *parent;
  int height;

  Node(Key key, T value)
      : key(key),
        value(value),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        height(1) {}
};

template <typename Key, typename T>
class BinaryTree {
 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    friend class BinaryTree;
    Iterator() {}
    Iterator(Node<key_type, value_type> *node,
             Node<key_type, value_type> *past_node = nullptr)
        : it_node(node), it_past_node(past_node) {}

    iterator operator++(int);
    iterator &operator++();
    iterator &operator--();
    iterator operator--(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    const_reference operator*();
    reference second();

   private:
    Node<key_type, value_type> *it_node;
    Node<key_type, value_type> *it_past_node;
  };

  class ConstIterator {
   public:
    friend class BinaryTree;
    ConstIterator(const Node<key_type, value_type> *node,
                  const Node<key_type, value_type> *past_node = nullptr)
        : it_node(node), it_past_node(past_node) {}

    ConstIterator operator++(int) const;
    ConstIterator &operator++() const;
    ConstIterator &operator--() const;
    ConstIterator operator--(int) const;
    bool operator==(const ConstIterator &other) const;
    bool operator!=(const ConstIterator &other) const;
    reference operator*();

   private:
    const Node<key_type, value_type> *it_node;
    const Node<key_type, value_type> *it_past_node;
  };

  BinaryTree();
  BinaryTree(
      std::initializer_list<std::pair<key_type, value_type>> const &items);
  BinaryTree(const key_type &key, const value_type &value);
  BinaryTree(const BinaryTree &other);
  BinaryTree(BinaryTree &&other) noexcept;
  ~BinaryTree();

  BinaryTree &operator=(BinaryTree &&other);

  std::pair<typename BinaryTree<key_type, value_type>::iterator, bool> insert(
      const value_type &value);
  std::pair<iterator, bool> insert(
      const std::pair<key_type, value_type> &value);
  iterator find(const key_type &key);
  iterator find(Node<key_type, value_type> *node, const key_type &key);
  bool contains(const key_type &key);
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void erase(iterator pos);
  bool erase(const key_type &key);
  void swap(BinaryTree &other);
  void merge(BinaryTree &other);
  void clear();

  iterator begin();
  iterator end();

  int Height();
  int BalanceFactor();
  Node<key_type, value_type> *RightRotate();
  Node<key_type, value_type> *LeftRotate();
  Node<key_type, value_type> *Balance();
  bool IsBalanced();

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 protected:
  Node<key_type, value_type> *root;
  Node<key_type, value_type> *Balance(Node<key_type, value_type> *node);

 private:
  Node<key_type, value_type> *insert(Node<key_type, value_type> *node,
                                     const key_type &key,
                                     const value_type &value, bool &inserted);
  Node<key_type, value_type> *remove(Node<key_type, value_type> *node,
                                     const key_type &key);
  void clear(Node<key_type, value_type> *node);
  void merge(Node<key_type, value_type> *&into,
             Node<key_type, value_type> *&from, BinaryTree &other);
  size_type size(Node<key_type, value_type> *node) const;
  int Height(Node<key_type, value_type> *node);
  int BalanceFactor(Node<key_type, value_type> *node);
  Node<key_type, value_type> *RightRotate(Node<key_type, value_type> *node);
  Node<key_type, value_type> *LeftRotate(Node<key_type, value_type> *node);
  int UpdateHeight(Node<key_type, value_type> *node);
  bool IsBalanced(Node<key_type, value_type> *node);
  Node<key_type, value_type> *GetMin(Node<key_type, value_type> *node);
  Node<key_type, value_type> *copy(Node<key_type, value_type> *other_node);
  key_type GetRootKey();
  key_type GetLeftChildKey();
  key_type GetRightChildKey();
};

}  // namespace s21

#include "s21_avl_tree.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_BST_H_
