#include "s21_avl_tree.h"

namespace s21 {

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree() : root(nullptr) {}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(
    std::initializer_list<std::pair<key_type, value_type>> const &items) {
  root = nullptr;
  for (const auto &item : items) {
    insert(item);
  }
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(const key_type &key,
                                             const value_type &value) {
  root = nullptr;
  bool inserted;
  root = insert(root, key, value, inserted);
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(
    const BinaryTree<key_type, value_type> &other) {
  if (other.root) {
    root = copy(other.root);
  } else {
    root = nullptr;
  }
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::BinaryTree(
    BinaryTree<key_type, value_type> &&other) noexcept {
  if (&other != this) {
    root = other.root;
    other.root = nullptr;
  }
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type>::~BinaryTree() {
  clear();
}

template <typename key_type, typename value_type>
BinaryTree<key_type, value_type> &BinaryTree<key_type, value_type>::operator=(
    BinaryTree<key_type, value_type> &&other) {
  if (&other != this) {
    clear(root);
    root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::clear() {
  clear(root);
  root = nullptr;
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::clear(Node<key_type, value_type> *node) {
  if (node) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename key_type, typename value_type>
std::pair<typename BinaryTree<key_type, value_type>::iterator, bool>
BinaryTree<key_type, value_type>::insert(const value_type &value) {
  bool inserted = false;
  root = insert(root, value, value, inserted);
  return {find(value), inserted};
}

template <typename key_type, typename value_type>
std::pair<typename BinaryTree<key_type, value_type>::iterator, bool>
BinaryTree<key_type, value_type>::insert(
    const std::pair<key_type, value_type> &value) {
  bool inserted = false;
  root = insert(root, value.first, value.second, inserted);
  return {find(value.first), inserted};
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::insert(
    Node<key_type, value_type> *node, const key_type &key,
    const value_type &value, bool &inserted) {
  if (node == nullptr) {
    inserted = true;
    return new Node<key_type, value_type>(key, value);
  }

  if (key < node->key) {
    node->left = insert(node->left, key, value, inserted);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value, inserted);
  } else {
    inserted = false;
  }

  return Balance(node);
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::find(const key_type &key) {
  return find(root, key);
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::find(Node<key_type, value_type> *node,
                                       const key_type &key) {
  if (node == nullptr) {
    return Iterator(nullptr);
  }

  if (key < node->key) {
    return find(node->left, key);
  } else if (key > node->key) {
    return find(node->right, key);
  } else {
    return iterator(node);
  }
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::contains(const key_type &key) {
  iterator it = find(key);
  return it != iterator(nullptr);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::erase(const key_type &key) {
  if (contains(key)) {
    root = remove(root, key);
    return true;
  }
  return false;
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::erase(iterator pos) {
  if (pos != end()) {
    root = remove(root, pos.it_node->key);
  }
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::remove(
    Node<key_type, value_type> *node, const key_type &key) {
  if (node == nullptr) return node;

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    } else if (node->left == nullptr) {
      Node<key_type, value_type> *temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      Node<key_type, value_type> *temp = node->left;
      delete node;
      return temp;
    } else {
      Node<key_type, value_type> *temp = GetMin(node->right);
      node->key = temp->key;
      node->value = temp->value;
      node->right = remove(node->right, temp->key);
    }
  }
  UpdateHeight(node);
  return Balance(node);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::empty() const {
  return root == nullptr;
}

template <typename key_type, typename value_type>
size_t BinaryTree<key_type, value_type>::size() const {
  return size(root);
}

template <typename key_type, typename value_type>
size_t BinaryTree<key_type, value_type>::size(
    Node<key_type, value_type> *node) const {
  if (node == nullptr) {
    return 0;
  } else {
    return size(node->left) + size(node->right) + 1;
  }
}

template <typename key_type, typename value_type>
size_t BinaryTree<key_type, value_type>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::swap(BinaryTree &other) {
  std::swap(root, other.root);
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::merge(BinaryTree &other) {
  merge(this->root, other.root, other);
}

template <typename key_type, typename value_type>
void BinaryTree<key_type, value_type>::merge(Node<key_type, value_type> *&into,
                                             Node<key_type, value_type> *&from,
                                             BinaryTree &other) {
  if (from == nullptr) {
    return;
  }

  if (!this->contains(from->key)) {
    bool inserted = false;
    into = insert(into, from->key, from->value, inserted);

    if (inserted) {
      Node<key_type, value_type> *left_from = from->left;
      Node<key_type, value_type> *right_from = from->right;

      merge(into, left_from, other);
      merge(into, right_from, other);

      if (other.contains(from->key)) {
        other.erase(from->key);
      }
    }
  } else {
    merge(into, from->left, other);
    merge(into, from->right, other);
  }
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::copy(
    Node<key_type, value_type> *other_node) {
  if (other_node == nullptr) {
    return nullptr;
  }

  Node<key_type, value_type> *new_node =
      new Node<key_type, value_type>(other_node->key, other_node->value);
  new_node->left = copy(other_node->left);
  new_node->right = copy(other_node->right);

  return new_node;
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::GetMin(
    Node<key_type, value_type> *node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename key_type, typename value_type>
typename BinaryTree<key_type, value_type>::iterator
BinaryTree<key_type, value_type>::begin() {
  Node<key_type, value_type> *minNode = GetMin(root);

  if (minNode == nullptr) {
    return this->end();
  }

  return iterator(minNode);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::iterator BinaryTree<Key, Value>::end() {
  return iterator(nullptr);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::iterator::operator==(
    const iterator &other) const {
  return it_node == other.it_node && it_past_node == other.it_past_node;
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::iterator::operator!=(
    const iterator &other) const {
  return !(*this == other);
}

template <typename Key, typename T>
typename s21::BinaryTree<Key, T>::iterator
s21::BinaryTree<Key, T>::iterator::operator++(int) {
  iterator temp = *this;
  ++(*this);
  return temp;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::Iterator &
BinaryTree<Key, T>::Iterator::operator++() {
  if (it_node == nullptr) {
    return *this;
  }

  if (it_node->right != nullptr) {
    it_node = it_node->right;
    while (it_node->left != nullptr) {
      it_node = it_node->left;
    }
  } else {
    Node<key_type, value_type> *parent = it_node->parent;
    while (parent != nullptr && it_node == parent->right) {
      it_node = parent;
      parent = parent->parent;
    }
    it_node = parent;
  }

  return *this;
}

template <typename key_type, typename value_type>
const value_type &BinaryTree<key_type, value_type>::iterator::operator*() {
  static value_type sentinel;
  return (it_node != nullptr) ? it_node->value : sentinel;
}

template <typename key_type, typename value_type>
value_type &BinaryTree<key_type, value_type>::iterator::second() {
  static value_type sentinel;
  return (it_node != nullptr) ? it_node->value : sentinel;
}

template <typename key_type, typename value_type>
key_type BinaryTree<key_type, value_type>::GetRootKey() {
  return root->key;
}
template <typename key_type, typename value_type>
key_type BinaryTree<key_type, value_type>::GetLeftChildKey() {
  return root->left->key;
}
template <typename key_type, typename value_type>
key_type BinaryTree<key_type, value_type>::GetRightChildKey() {
  return root->right->key;
}

// Balancing
template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::UpdateHeight(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return 0;
  int leftHeight = UpdateHeight(node->left);
  int rightHeight = UpdateHeight(node->right);
  node->height = 1 + std::max(leftHeight, rightHeight);
  return node->height;
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::Height() {
  return Height(root);
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::Height(Node<key_type, value_type> *node) {
  if (node == nullptr) return 0;
  return 1 + std::max(Height(node->left), Height(node->right));
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::BalanceFactor() {
  return BalanceFactor(root);
}

template <typename key_type, typename value_type>
int BinaryTree<key_type, value_type>::BalanceFactor(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return 0;
  return Height(node->left) - Height(node->right);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::RightRotate() {
  return RightRotate(root);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::RightRotate(
    Node<key_type, value_type> *node) {
  if (node == nullptr || node->left == nullptr) {
    return node;
  }
  Node<key_type, value_type> *left = node->left;
  Node<key_type, value_type> *left_right = left->right;

  left->right = node;
  node->left = left_right;

  return left;
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::LeftRotate() {
  return LeftRotate(root);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::LeftRotate(
    Node<key_type, value_type> *node) {
  if (node == nullptr || node->right == nullptr) {
    return node;
  }
  Node<key_type, value_type> *right = node->right;
  Node<key_type, value_type> *right_left = right->left;

  right->left = node;
  node->right = right_left;

  return right;
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::Balance() {
  return Balance(root);
}

template <typename key_type, typename value_type>
Node<key_type, value_type> *BinaryTree<key_type, value_type>::Balance(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return node;

  node->left = Balance(node->left);
  node->right = Balance(node->right);

  int bf = BalanceFactor(node);

  if (bf < -1) {
    if (BalanceFactor(node->right) <= 0) {
      return LeftRotate(node);
    } else {
      node->right = RightRotate(node->right);
      return LeftRotate(node);
    }
  }

  if (bf > 1) {
    if (BalanceFactor(node->left) >= 0) {
      return RightRotate(node);
    } else {
      node->left = LeftRotate(node->left);
      return RightRotate(node);
    }
  }

  return node;
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::IsBalanced() {
  return IsBalanced(root);
}

template <typename key_type, typename value_type>
bool BinaryTree<key_type, value_type>::IsBalanced(
    Node<key_type, value_type> *node) {
  if (node == nullptr) return true;

  int leftHeight = Height(node->left);
  int rightHeight = Height(node->right);

  return abs(leftHeight - rightHeight) <= 1 && IsBalanced(node->left) &&
         IsBalanced(node->right);
}

template <typename Key, typename T>
template <class... Args>
vector<std::pair<typename BinaryTree<Key, T>::iterator, bool>>
BinaryTree<Key, T>::insert_many(Args &&...args) {
  vector<std::pair<typename BinaryTree<Key, T>::iterator, bool>> results;
  (..., results.push_back(insert(std::forward<Args>(args))));

  return results;
}

}  // namespace s21
