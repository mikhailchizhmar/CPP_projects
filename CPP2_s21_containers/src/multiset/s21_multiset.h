#ifndef CPP2_S21_CONTAINERS_1_S21_MULTISET_H
#define CPP2_S21_CONTAINERS_1_S21_MULTISET_H

#include "../avl_tree/s21_avl_tree.h"
#include "../map/s21_map.h"

namespace s21 {
template <typename Key>
class multiset : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename BinaryTree<Key, Key>::Iterator;
  using const_iterator = typename BinaryTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  multiset() : BinaryTree<key_type, key_type>(){};
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &other) : BinaryTree<key_type, key_type>(other){};
  multiset(multiset &&other) noexcept
      : BinaryTree<key_type, key_type>(std::move(other)){};
  ~multiset() = default;

  iterator insert(const value_type &value);
  void merge(multiset &other);
  size_type count(const key_type &key) const;
  iterator lower_bound(const Key &key);
  Node<key_type, value_type> *lower_bound_recursive(
      Node<key_type, key_type> *node, const key_type &key);
  iterator upper_bound(const Key &key);
  Node<key_type, value_type> *upper_bound_recursive(
      Node<key_type, key_type> *node, const key_type &key);
  std::pair<iterator, iterator> equal_range(const Key &key);

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  Node<key_type, key_type> *insert(Node<key_type, key_type> *node,
                                   const key_type &key,
                                   const value_type &value);
  size_type countRecursive(Node<key_type, key_type> *node,
                           const key_type &key) const;
  void merge(Node<key_type, key_type> *&into, Node<key_type, key_type> *from);
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  // CPP2_S21_CONTAINERS_1_S21_MULTISET_H
