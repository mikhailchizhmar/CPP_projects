#include "s21_queue.h"

namespace s21 {

template <typename T, typename Container>
queue<T, Container>::queue() : container_() {}

template <typename T, typename Container>
queue<T, Container>::queue(std::initializer_list<value_type> const &items)
    : container_(items) {}

template <typename T, typename Container>
queue<T, Container>::queue(const queue &q) : container_(q.container_) {}

template <typename T, typename Container>
queue<T, Container>::queue(queue &&q) : container_(std::move(q.container_)) {}

template <typename T, typename Container>
queue<T, Container>::~queue() {}

template <typename T, typename Container>
queue<T, Container> &queue<T, Container>::operator=(queue &&q) {
  if (this != &q) {
    this->container_ = std::move(q.container_);
  }
  return *this;
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::front() {
  return container_.front();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::back() {
  return container_.back();
}

template <typename T, typename Container>
bool queue<T, Container>::empty() {
  return container_.empty();
}

template <typename T, typename Container>
typename queue<T, Container>::size_type queue<T, Container>::size_() {
  return container_.size();
}

template <typename T, typename Container>
void queue<T, Container>::push(const_reference value) {
  this->container_.push_back(value);
}

template <typename T, typename Container>
void queue<T, Container>::pop() {
  this->container_.pop_front();
}

template <typename T, typename Container>
void queue<T, Container>::swap(queue &other) {
  this->container_.swap(other.container_);
}

template <typename T, typename Container>
template <typename... Args>
void s21::queue<T, Container>::insert_many_back(Args &&...args) {
  container_.insert_many_back(std::forward<Args>(args)...);
}

}  // namespace s21
