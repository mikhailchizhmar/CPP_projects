#include "s21_stack.h"

namespace s21 {

template <class T, class Container>
stack<T, Container>::stack() : container_() {}

template <class T, class Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : container_(items) {}

template <class T, class Container>
stack<T, Container>::stack(const stack &s) : container_(s.container_) {}

template <class T, class Container>
stack<T, Container>::stack(stack &&s) : container_(std::move(s.container_)) {}

template <class T, class Container>
stack<T, Container>::~stack() {}

template <class T, class Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&s) {
  this->container_ = std::move(s.container_);
  return *this;
}

template <class T, class Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() {
  return container_.back();
}

template <class T, class Container>
bool stack<T, Container>::empty() {
  return container_.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type stack<T, Container>::size() {
  return container_.size();
}

template <class T, class Container>
void stack<T, Container>::push(const_reference value) {
  this->container_.push_back(value);
}

template <class T, class Container>
void stack<T, Container>::pop() {
  this->container_.pop_back();
}

template <class T, class Container>
void stack<T, Container>::swap(stack &other) {
  this->container_.swap(other.container_);
}

template <typename T, typename Container>
template <typename... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  container_.insert_many_back(std::forward<Args>(args)...);
}

}  // namespace s21
