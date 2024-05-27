#ifndef SRC_CORE_S21_MAP_H_
#define SRC_CORE_S21_MAP_H_

#include <limits>
#include <type_traits>

#include "s21_container.h"
#include "s21_rbtree.h"
#include "s21_vector.h"

namespace s21 {

template <typename KeyT, typename ValT>
class map : public IContainer {
 public:
  class MapIterator;
  class MapConstIterator;

  using key_type = KeyT;
  using mapped_type = ValT;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = map<key_type, mapped_type>::MapIterator;
  using const_iterator = map<key_type, mapped_type>::MapConstIterator;
  using typename IContainer::size_type;

 public:
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& other);
  map(map&& other) noexcept;
  ~map(){};

  map<key_type, mapped_type>& operator=(const map& other);
  map<key_type, mapped_type>& operator=(map&& other);
  mapped_type& at(const key_type& key);
  mapped_type& at(const key_type& key) const;
  mapped_type& operator[](const key_type& key);

  bool operator==(const map<key_type, mapped_type>& other) const;
  bool operator!=(const map<key_type, mapped_type>& other) const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const noexcept override { return btree_.isEmpty(); }
  size_type size() const noexcept override { return size_; }
  static size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);

  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const key_type& key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RBTree<KeyT, ValT, false> btree_;
  size_type size_;

 private:
  void erase(value_type pos);
};

template <typename KeyT, typename ValT>
class map<KeyT, ValT>::MapIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = std::pair<const KeyT, ValT>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  using Node = typename RBTree<KeyT, ValT, false>::Node;

 public:
  MapIterator() = default;
  MapIterator(typename RBTree<KeyT, ValT, false>::Node* ptr,
              RBTree<KeyT, ValT, false>* it_btree)
      : ptr_(ptr), it_btree_(it_btree) {}

  bool operator==(const MapIterator& other) { return ptr_ == other.ptr_; }
  bool operator!=(const MapIterator& other) { return !(*this == other); }

  MapIterator& operator++() {
    ptr_ = RBT_increment(ptr_);
    return *this;
  }

  MapIterator operator++(int) {
    MapIterator temp = *this;
    ++*this;
    return temp;
  }

  MapIterator& operator--() {
    ptr_ = RBT_decrement(ptr_);
    return *this;
  }

  MapIterator operator--(int) {
    MapIterator temp = *this;
    --*this;
    return temp;
  }

  reference operator*() { return ptr_->val_; }

 private:
  typename RBTree<KeyT, ValT, false>::Node* ptr_ = nullptr;
  RBTree<KeyT, ValT, false>* it_btree_ = nullptr;

  Node* RBT_increment(Node* ptr);
  Node* RBT_decrement(Node* ptr);
};

template <typename KeyT, typename ValT>
class map<KeyT, ValT>::MapConstIterator : public map<KeyT, ValT>::MapIterator {
 public:
  using value_type = std::pair<const KeyT, ValT>;
  using const_reference = const value_type&;

 public:
  MapConstIterator(MapIterator other) : MapIterator(other) {}
  const_reference operator*() { return MapIterator::operator*(); }
};

template <typename key_type, typename mapped_type>
typename RBTree<key_type, mapped_type, false>::Node*
map<key_type, mapped_type>::MapIterator::RBT_increment(
    typename RBTree<key_type, mapped_type, false>::Node* ptr) {
  if (!it_btree_->isNil(ptr->right_)) {
    ptr = ptr->right_;
    while (!it_btree_->isNil(ptr->left_)) ptr = ptr->left_;
  } else {
    typename RBTree<key_type, mapped_type, false>::Node* parent = ptr->parent_;
    while (ptr == parent->right_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->right_ != parent) ptr = parent;
  }
  return ptr;
}

template <typename key_type, typename mapped_type>
typename RBTree<key_type, mapped_type, false>::Node*
map<key_type, mapped_type>::MapIterator::RBT_decrement(
    typename RBTree<key_type, mapped_type, false>::Node* ptr) {
  if (!it_btree_->isNil(ptr->left_)) {
    ptr = ptr->left_;
    while (!it_btree_->isNil(ptr->right_)) ptr = ptr->right_;
  } else {
    typename RBTree<key_type, mapped_type, false>::Node* parent = ptr->parent_;
    while (ptr == parent->left_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->left_ != parent) ptr = parent;
  }
  return ptr;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::operator==(
    const map<key_type, mapped_type>& other) const {
  if (this == &other) return true;
  if (size() != other.size()) return false;

  return (std::equal(begin(), end(), other.begin()));
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::operator!=(
    const map<key_type, mapped_type>& other) const {
  return !(*this == other);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename RBTree<key_type, mapped_type, false>::Node) /
         4294967296;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() : btree_(), size_(0) {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const& items)
    : btree_(), size_(0) {
  for (const_reference p : items)
    if (btree_.insert(p).second) size_++;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map& other)
    : btree_(), size_(other.size_) {
  for (auto it : other) this->btree_.insert(it);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map&& other) noexcept
    : btree_(other.btree_), size_(other.size_) {
  if (this != &other) {
    other.btree_.makeNullRoot();
    other.size_ = 0;
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(
    const map& other) {
  size_ = other.size_;
  for (auto it : other) this->btree_.insert(it);

  return *this;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(map&& other) {
  if (this == &other) return *this;
  map<key_type, mapped_type> temp = std::move(*this);
  btree_ = other.btree_;
  size_ = other.size_;

  other.btree_.makeNullRoot();
  other.size_ = 0;

  return *this;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
  typename RBTree<key_type, mapped_type, false>::Node* temp =
      btree_.search(key);
  if (temp == nullptr)
    throw std::out_of_range("Element with the current key was not found!");
  else
    return temp->val_.second;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) const {
  typename RBTree<key_type, mapped_type, false>::Node* temp =
      btree_.search(key);
  if (temp == nullptr)
    throw std::out_of_range("Element with the current key was not found!");
  else
    return temp->val_.second;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::operator[](const key_type& key) {
  std::pair<typename RBTree<key_type, mapped_type, false>::Node*, bool> temp =
      btree_.insert(key);
  if (temp.second) size_++;
  return temp.first->val_.second;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  map<key_type, mapped_type>::iterator it(btree_.getMin(), &btree_);
  return it;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::begin() const {
  MapIterator it(btree_.getMin(),
                 const_cast<RBTree<key_type, mapped_type, false>*>(&btree_));
  return MapConstIterator(it);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  map<key_type, mapped_type>::iterator it(btree_.getMax(), &btree_);
  return it;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::end() const {
  MapIterator it(btree_.getMax(),
                 const_cast<RBTree<key_type, mapped_type, false>*>(&btree_));
  return MapConstIterator(it);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  btree_.clear();
  size_ = 0;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type& value) {
  std::pair<typename RBTree<key_type, mapped_type, false>::Node*, bool> temp =
      btree_.insert(value);
  if (temp.second) size_++;
  return std::make_pair(
      map<key_type, mapped_type>::iterator(temp.first, &btree_), temp.second);
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  std::pair<typename RBTree<key_type, mapped_type, false>::Node*, bool> temp =
      btree_.insert(key, obj);
  if (temp.second) size_++;
  return std::make_pair(
      map<key_type, mapped_type>::iterator(temp.first, &btree_), temp.second);
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  std::pair<typename RBTree<key_type, mapped_type, false>::Node*, bool> temp =
      btree_.insert(key, obj);
  if (temp.second)
    size_++;
  else
    temp.first->val_.second = obj;
  return std::make_pair(
      map<key_type, mapped_type>::iterator(temp.first, &btree_), temp.second);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  btree_.remove((*pos).first);
  size_--;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(value_type pos) {
  btree_.remove(pos.first);
  size_--;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
  btree_.swapOtherRoot(other.btree_);
  std::swap(size_, other.size_);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  map<key_type, mapped_type>::iterator itTemp;
  vector<std::pair<const key_type, mapped_type>> buff;
  for (map<key_type, mapped_type>::iterator it = other.begin();
       it != other.end(); ++it) {
    if (insert(*it).second) {
      buff.push_back(*it);
    }
  }
  for (auto it : buff) other.erase(it);
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) {
  return (btree_.search(key) == nullptr) ? false : true;
}

template <typename key_type, typename mapped_type>
template <typename... Args>
vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
map<key_type, mapped_type>::insert_many(Args&&... args) {
  vector<std::pair<map<key_type, mapped_type>::iterator, bool>> res;
  for (auto it : {args...}) res.push_back(insert(it));
  return res;
}
}  // namespace s21

#endif  // SRC_CORE_S21_MAP_H_