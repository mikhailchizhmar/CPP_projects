#ifndef CPP2_S21_CONTAINERS_1_LIST_H
#define CPP2_S21_CONTAINERS_1_LIST_H

#include <cstdio>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

 private:
  struct Node {
    value_type data;
    Node* prev;
    Node* next;
    Node() : data(value_type()), prev(nullptr), next(nullptr) {}
    explicit Node(const_reference data)
        : data(data), prev(nullptr), next(nullptr) {}
  };
  Node* head_;
  Node* tail_;
  size_type size_;

 public:
  list() : head_(nullptr), tail_(nullptr), size_(0) {}
  explicit list(size_type n);
  list(std::initializer_list<value_type> il);
  list(const list& other);
  list(list&& other) noexcept;
  ~list();
  list& operator=(list&& l) noexcept;

  const_reference front() const;
  const_reference back() const;

  bool empty() { return size_ == 0; }
  size_type size() { return size_; }
  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

  void clear();
  void push_back(const_reference data);
  void pop_back();
  void push_front(const_reference data);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void reverse();
  void unique();
  void sort();
  void remove(const_reference value);

  template <typename value_type>
  class ListIterator {
   private:
    Node* current;

   public:
    explicit ListIterator(Node* current) : current(current) {}
    ListIterator() { current = nullptr; }
    virtual const T& operator*() const { return current->data; }
    virtual T& operator*() { return current->data; }

    ListIterator& operator++() {
      if (current) {
        current = current->next;
      }
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ListIterator& operator--() {
      if (current) {
        current = current->prev;
      }
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const ListIterator& other) const {
      return current == other.current;
    }

    bool operator!=(const ListIterator& other) const { return *this != other; }

    Node* get_current() { return this->current; }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    explicit ListConstIterator(ListIterator<T> other)
        : ListIterator<T>(other) {}
    const T& operator*() const override { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(nullptr); }
  const_iterator begin() const { return const_iterator(head_); }
  const_iterator end() const { return const_iterator(nullptr); }

  iterator insert(iterator pos, const_reference value);
  void splice(const_iterator pos, list& other);

  reference at(iterator pos);
  void erase(iterator pos);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_1_LIST_H