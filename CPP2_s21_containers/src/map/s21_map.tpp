#include "s21_map.h"

namespace s21 {
template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const &items) {
  for (const auto &item : items) {
    this->insert(item);
  }
}

template <typename key_type, typename mapped_type>
mapped_type &map<key_type, mapped_type>::operator[](const key_type &key) {
  auto it = this->find(key);
  if (it == this->end()) {
    auto pr = this->insert(std::make_pair(key, mapped_type()));
    it = pr.first;
  }
  return it.second();
}

template <typename key_type, typename mapped_type>
mapped_type &map<key_type, mapped_type>::at(const key_type &key) {
  auto it = this->find(key);
  if (it == this->end()) {
    throw std::out_of_range("map::at");
  }
  return it.second();
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type &key,
                                             const mapped_type &value) {
  auto it = this->find(key);

  if (it != this->end()) {
    it.second() = value;
    return std::make_pair(iterator(it), false);
  }

  auto result = this->insert(std::make_pair(key, value));
  return std::make_pair(iterator(result.first), true);
}

}  // namespace s21
