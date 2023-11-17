#include "s21_multiset.h"

namespace s21 {

template <typename key_type>
multiset<key_type>::multiset(const std::initializer_list<value_type> &items) {
  for (const value_type &item : items) {
    this->insert(item);
  }
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::insert(
    const value_type &value) {
  this->root = insert(this->root, value, value);
  return iterator(this->root);
}

template <typename key_type>
Node<typename multiset<key_type>::key_type,
     typename multiset<key_type>::value_type>
    *multiset<key_type>::insert(Node<key_type, key_type> *node,
                                const key_type &key, const value_type &value) {
  if (node == nullptr) {
    return new Node<key_type, key_type>(key, value);
  }
  if (key <= node->key) {
    node->left = insert(node->left, key, value);
  } else {
    node->right = insert(node->right, key, value);
  }
  return this->Balance(node);
}

template <typename key_type>
void multiset<key_type>::merge(multiset &other) {
  merge(this->root, other.root);
  other.root = nullptr;
  other.clear();
}

template <typename key_type>
void multiset<key_type>::merge(Node<key_type, key_type> *&into,
                               Node<key_type, key_type> *from) {
  if (from == nullptr) {
    return;
  }

  Node<key_type, key_type> *left_subtree = from->left;
  Node<key_type, key_type> *right_subtree = from->right;

  from->left = nullptr;
  from->right = nullptr;

  this->insert(from->key);

  delete from;

  merge(into, left_subtree);
  merge(into, right_subtree);
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type &key) const {
  return countRecursive(this->root, key);
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::countRecursive(
    Node<key_type, key_type> *node, const key_type &key) const {
  if (node == nullptr) {
    return 0;
  }

  size_type count = 0;

  if (key == node->key) {
    count++;
  }

  if (key <= node->key) {
    count += countRecursive(node->left, key);
  }

  count += countRecursive(node->right, key);

  return count;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type &key) {
  return lower_bound_recursive(this->root, key);
}

template <typename key_type>
Node<typename multiset<key_type>::key_type,
     typename multiset<key_type>::value_type> *
s21::multiset<key_type>::lower_bound_recursive(Node<key_type, key_type> *node,
                                               const key_type &key) {
  if (node == nullptr) {
    return nullptr;
  }
  if (key == node->key) {
    return node;
  }
  if (key < node->key) {
    Node<key_type, key_type> *tempNode = lower_bound_recursive(node->left, key);
    return (tempNode != nullptr) ? tempNode : node;
  } else {
    return lower_bound_recursive(node->right, key);
  }
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type &key) {
  return upper_bound_recursive(this->root, key);
}

template <typename key_type>
Node<typename multiset<key_type>::key_type,
     typename multiset<key_type>::value_type> *
s21::multiset<key_type>::upper_bound_recursive(Node<key_type, key_type> *node,
                                               const key_type &key) {
  if (node == nullptr) {
    return nullptr;
  }
  if (key < node->key) {
    Node<key_type, key_type> *tempNode = upper_bound_recursive(node->left, key);
    return (tempNode != nullptr) ? tempNode : node;
  } else {
    return upper_bound_recursive(node->right, key);
  }
}

template <typename key_type>
std::pair<typename multiset<key_type>::iterator,
          typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type &key) {
  auto lower = lower_bound(key);
  auto upper = upper_bound(key);
  auto result = std::make_pair(lower, upper);
  return result;
}

template <typename Key>
template <class... Args>
vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  vector<std::pair<typename multiset<Key>::iterator, bool>> results;
  (...,
   results.push_back(std::make_pair(insert(std::forward<Args>(args)), true)));

  return results;
}

}  // namespace s21
