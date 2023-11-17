#include "s21_set.h"

namespace s21 {
template <typename key_type>
set<key_type>::set(const std::initializer_list<value_type> &items) {
  for (const value_type &item : items) {
    this->insert(item);
  }
}

template <typename key_type>
set<key_type> &set<key_type>::operator=(set &&other) noexcept {
  if (this != &other) {
    BinaryTree<key_type, key_type>::operator=(std::move(other));
  }
  return *this;
}

}  // namespace s21
