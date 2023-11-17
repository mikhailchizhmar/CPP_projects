#include "s21_array.h"

namespace s21 {

/* Array Member functions */

template <typename T, std::size_t N>
array<T, N>::array() : sz(N) {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  std::copy(items.begin(), items.end(), elems);
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  std::copy(a.elems, a.elems + N, elems);
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) {
  std::move(a.elems, a.elems + N, elems);
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  std::move(a.elems, a.elems + N, elems);
  return *this;
}

/* Array Element access */

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos < 0 || pos >= N) {
    throw std::out_of_range("Index is out of range");
  }
  return elems[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return elems[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return elems[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return elems[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return elems;
}

/* Array Iterators */

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return elems;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return elems + sz;
}

/* Array Capacity */

template <typename T, std::size_t N>
bool array<T, N>::empty() const {
  return !sz;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return sz;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return sz;
}

/* Array Modifiers */

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap_ranges(begin(), end(), other.begin());
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(begin(), end(), value);
}

}  // namespace s21