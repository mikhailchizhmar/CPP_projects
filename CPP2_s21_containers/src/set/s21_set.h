#ifndef CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_

#include "../avl_tree/s21_avl_tree.h"

namespace s21 {

template <typename Key>
class set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename BinaryTree<Key, Key>::Iterator;
  using const_iterator = typename BinaryTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  set() : BinaryTree<key_type, key_type>(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : BinaryTree<key_type, key_type>(other){};
  set(set &&other) noexcept
      : BinaryTree<key_type, key_type>(std::move(other)){};
  set &operator=(set &&other) noexcept;
  ~set() = default;
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_SET_S21_SET_H_