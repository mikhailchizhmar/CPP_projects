#include "s21_vector.h"

namespace s21 {

/* Vector Member functions */

template <typename T>
vector<T>::vector() : pdata(nullptr), sz(0), cap(0) {}

template <typename T>
vector<T>::vector(size_type n) : pdata(new value_type[n]), sz(n), cap(n) {
  for (std::size_t i = 0; i < sz; i++) {
    pdata[i] = T();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : pdata(new value_type[items.size()]), sz(items.size()), cap(items.size()) {
  std::copy(items.begin(), items.end(), pdata);
}

template <typename T>
vector<T>::vector(const vector &v)
    : pdata(new value_type[v.cap]), sz(v.sz), cap(v.cap) {
  std::copy(v.pdata, v.pdata + v.sz, pdata);
}

template <typename T>
vector<T>::vector(vector &&v) : pdata(v.pdata), sz(v.sz), cap(v.cap) {
  v.pdata = nullptr;
  v.sz = 0;
  v.cap = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] pdata;
  sz = 0;
  cap = 0;
  pdata = nullptr;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this == &v) {
    return *this;
  }

  delete[] pdata;
  pdata = v.pdata;
  sz = v.sz;
  cap = v.cap;

  v.pdata = nullptr;
  v.sz = 0;
  v.cap = 0;

  return *this;
}

/* Vector Element access */

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos < 0 || pos >= sz) {
    throw std::out_of_range("Index is out of range");
  }
  return *(pdata + pos);
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return *(pdata + pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return pdata[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return pdata[sz - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return pdata;
}

/* Vector Iterators */

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return pdata;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return pdata + sz;
}

/* Vector Capacity */

template <typename T>
bool vector<T>::empty() const {
  return sz == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return sz;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Capacity cannot be greater than maximum size");
  }
  if (size > cap) {
    value_type *new_data = new value_type[size];
    for (std::size_t i = 0; i < sz; i++) {
      new_data[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_data;
    cap = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return cap;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (cap > sz) {
    value_type *new_data = new value_type[sz];
    for (std::size_t i = 0; i < sz; i++) {
      new_data[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_data;
    cap = sz;
  }
}

/* Vector Modifiers */

template <typename T>
void vector<T>::clear() {
  delete[] pdata;
  pdata = new value_type[cap];
  sz = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();

  if (sz >= cap) reserve(cap == 0 ? 1 : cap * 2);

  iterator new_pos = begin() + index;
  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++sz;
  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - begin();
  iterator new_pos = begin() + index;
  for (iterator it = new_pos; it != end() - 1; ++it) {
    *it = *(it + 1);
  }
  --sz;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (sz >= cap) reserve(cap == 0 ? 1 : cap * 2);
  pdata[sz] = value;
  sz++;
}

template <typename T>
void vector<T>::pop_back() {
  if (sz > 0) sz--;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(pdata, other.pdata);
  std::swap(sz, other.sz);
  std::swap(cap, other.cap);
}

/* Bonus part */

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_type index = pos - begin();
  iterator new_pos = begin() + index;
  vector<value_type> temp = {args...};

  for (size_type i = 0; i < temp.size(); ++i) {
    new_pos = insert(new_pos, temp[i]);
    ++new_pos;
  }

  return new_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}

}  // namespace s21