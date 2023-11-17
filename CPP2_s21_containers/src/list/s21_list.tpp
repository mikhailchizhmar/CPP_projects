#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename value_type>
list<value_type>::list(const list& other)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (Node* node = other.head_; node; node = node->next) {
    push_back(node->data);
  }
}

template <typename value_type>
list<value_type>::list(list&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> il)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto& elem : il) {
    push_back(elem);
  }
}

template <typename T>
list<T>::~list() {
  Node* current = head_;
  while (current) {
    Node* toDelete = current;
    current = current->next;
    delete toDelete;
  }
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& l) noexcept {
  if (this == &l) {
    return *this;
  }

  clear();

  head_ = l.head_;
  tail_ = l.tail_;
  size_ = l.size_;

  l.head_ = nullptr;
  l.tail_ = nullptr;
  l.size_ = 0;

  return *this;
}

template <typename value_type>
void list<value_type>::push_back(const value_type& data) {
  Node* newNode = new Node(data);
  if (tail_) {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  } else {
    head_ = tail_ = newNode;
  }
  ++size_;
}

template <typename value_type>
void list<value_type>::push_front(const value_type& data) {
  Node* newNode = new Node(data);
  if (head_) {
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
  } else {
    head_ = tail_ = newNode;
  }
  ++size_;
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (!head_) return;
  Node* toDelete = tail_;
  if (tail_->prev) {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  } else {
    head_ = tail_ = nullptr;
  }
  delete toDelete;
  --size_;
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (!tail_) return;
  Node* toDelete = head_;
  if (head_->next) {
    head_ = head_->next;
    head_->prev = nullptr;
  } else {
    head_ = tail_ = nullptr;
  }
  delete toDelete;
  --size_;
}

template <typename value_type>
void list<value_type>::clear() {
  Node* current = tail_;
  while (current) {
    Node* toDelete = current;
    current = current->prev;
    delete toDelete;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename value_type>
const value_type& list<value_type>::back() const {
  if (!tail_) {
    throw std::out_of_range("list is empty");
  }
  return tail_->data;
}

template <typename value_type>
const value_type& list<value_type>::front() const {
  if (!head_) {
    throw std::out_of_range("list is empty");
  }
  return head_->data;
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (pos.get_current() == nullptr) return;
  Node* toDelete = pos.get_current();

  if (toDelete->next) {
    toDelete->next->prev = toDelete->prev;
  } else {
    tail_ = toDelete->prev;
  }

  if (toDelete->prev) {
    toDelete->prev->next = toDelete->next;
  } else {
    head_ = toDelete->next;
  }

  delete toDelete;
  --size_;
}

template <typename value_type>
void list<value_type>::remove(const_reference value) {
  Node* current = head_;
  while (current) {
    if (current->data == value) {
      Node* toDelete = current;
      current = current->next;

      if (toDelete->prev) {
        toDelete->prev->next = toDelete->next;
      } else {
        head_ = toDelete->next;
      }

      if (toDelete->next) {
        toDelete->next->prev = toDelete->prev;
      } else {
        tail_ = toDelete->prev;
      }

      delete toDelete;
      --size_;
    } else {
      current = current->next;
    }
  }
}

template <typename value_type>
typename list<value_type>::reference list<value_type>::at(iterator pos) {
  if (pos.get_current() == nullptr) {
    throw std::out_of_range("Iterator points to nullptr");
  }

  return pos.get_current()->data;
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list<T>& other) {
  Node* first1 = head_;
  Node* first2 = other.head_;

  Node dummy;
  Node* last = &dummy;

  while (first1 && first2) {
    if (first1->data < first2->data) {
      last->next = first1;
      first1 = first1->next;
    } else {
      last->next = first2;
      first2 = first2->next;
    }
    last = last->next;
  }

  if (first1) {
    last->next = first1;
  } else {
    last->next = first2;
  }

  head_ = dummy.next;
  while (last->next) {
    last = last->next;
  }
  tail_ = last;

  size_ += other.size_;
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() {
  Node* current = head_;
  Node* prev = nullptr;
  Node* next = nullptr;

  while (current) {
    next = current->next;
    current->next = prev;
    current->prev = next;
    prev = current;
    current = next;
  }

  std::swap(head_, tail_);
}

template <typename T>
void list<T>::unique() {
  if (!head_ || !head_->next) {
    return;
  }

  Node* current = head_;
  while (current && current->next) {
    if (current->data == current->next->data) {
      Node* toDelete = current->next;
      current->next = current->next->next;

      if (current->next) {
        current->next->prev = current;
      } else {
        tail_ = current;
      }

      delete toDelete;
      --size_;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;

  Node* current = head_;
  while (current) {
    Node* next = current->next;
    while (next) {
      if (current->data > next->data) {
        std::swap(current->data, next->data);
      }
      next = next->next;
    }
    current = current->next;
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* current = pos.get_current();
  if (current == head_) {
    push_front(value);
    return iterator(head_);
  } else {
    Node* newNode = new Node(value);
    newNode->next = current;
    newNode->prev = current->prev;
    if (current->prev) {
      current->prev->next = newNode;
    }
    current->prev = newNode;
    ++size_;
    return iterator(newNode);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  Node* current = pos.get_current();
  Node* other_head = other.head_;
  Node* other_tail = other.tail_;

  if (!other_head) return;

  if (!head_) {
    head_ = other_head;
    tail_ = other_tail;
  } else {
    if (current == head_) {
      other_tail->next = head_;
      head_->prev = other_tail;
      head_ = other_head;
    } else {
      Node* prevnode = current->prev;
      prevnode->next = other_head;
      other_head->prev = prevnode;
      other_tail->next = current;
      current->prev = other_tail;
    }
  }

  size_ += other.size_;

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  const size_type n = sizeof...(args);
  value_type arr[] = {std::forward<Args>(args)...};
  Node* cur_node = pos.get_current();

  for (size_type i = 0; i < n; ++i) {
    iterator new_pos = insert(iterator(cur_node), arr[i]);
    cur_node = new_pos.get_current()->next;
  }

  return iterator(cur_node);
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args&&... args) {
  const size_type n = sizeof...(args);
  value_type arr[] = {std::forward<Args>(args)...};

  for (size_type i = 0; i < n; ++i) {
    push_back(arr[i]);
  }
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args&&... args) {
  const size_type n = sizeof...(args);
  value_type arr[] = {std::forward<Args>(args)...};

  for (size_type i = n; i > 0; --i) {
    push_front(arr[i - 1]);
  }
}

}  // namespace s21
