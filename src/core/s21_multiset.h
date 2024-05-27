#ifndef SRC_CORE_S21_MULTISET_H_
#define SRC_CORE_S21_MULTISET_H_

#include <limits>
#include <type_traits>

#include "s21_container.h"
#include "s21_rbtree.h"
#include "s21_vector.h"

namespace s21 {

template <typename KeyT>
class multiset : public IContainer {
 public:
  class MultisetIterator;
  class MultisetConstIterator;

  using key_type = KeyT;
  using value_type = KeyT;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = multiset<key_type>::MultisetIterator;
  using const_iterator = multiset<key_type>::MultisetConstIterator;
  using typename IContainer::size_type;

 public:
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other) noexcept;
  ~multiset(){};

  multiset<key_type>& operator=(const multiset& other);
  multiset<key_type>& operator=(multiset&& other);

  bool operator==(const multiset<key_type>& other) const;
  bool operator!=(const multiset<key_type>& other) const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const noexcept override { return btree_.isEmpty(); }
  size_type size() const noexcept override { return size_; }
  static size_type max_size();

  void clear();
  iterator insert(const value_type& value);

  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);
  iterator find(const key_type& key);
  bool contains(const key_type& key);

  size_type count(const key_type& key);
  iterator lower_bound(const key_type& key);
  iterator upper_bound(const key_type& key);
  std::pair<iterator, iterator> equal_range(const key_type& key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RBTree<KeyT, KeyT, true> btree_;
  size_type size_;

 private:
  void erase(value_type pos);
};

template <typename key_type>
std::pair<typename multiset<key_type>::iterator,
          typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type& key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type& key) {
  iterator res = end();
  for (iterator it = begin(); it != end(); ++it) {
    if (*it > key) {
      res = it;
      break;
    }
  }
  return res;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type& key) {
  iterator res = end();
  for (iterator it = begin(); it != end(); ++it) {
    if (*it >= key) {
      res = it;
      break;
    }
  }
  return res;
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type& key) {
  size_type res = 0;
  if (iterator it = find(key); it != end()) {
    while (*it == key) {
      ++res;
      ++it;
    }
  }
  return res;
}

template <typename KeyT>
class multiset<KeyT>::MultisetIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = KeyT;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  using Node = typename RBTree<KeyT, KeyT, true>::Node;

 public:
  MultisetIterator() = default;
  MultisetIterator(Node* ptr, RBTree<KeyT, KeyT, true>* it_btree)
      : ptr_(ptr), it_btree_(it_btree) {}

  bool operator==(const MultisetIterator& other) { return ptr_ == other.ptr_; }
  bool operator!=(const MultisetIterator& other) { return !(*this == other); }

  MultisetIterator& operator++() {
    ptr_ = RBT_increment(ptr_);
    return *this;
  }

  MultisetIterator operator++(int) {
    MultisetIterator temp = *this;
    ++*this;
    return temp;
  }

  MultisetIterator& operator--() {
    ptr_ = RBT_decrement(ptr_);
    return *this;
  }

  MultisetIterator operator--(int) {
    MultisetIterator temp = *this;
    --*this;
    return temp;
  }

  reference operator*() { return ptr_->val_.second; }

 private:
  Node* ptr_ = nullptr;
  RBTree<KeyT, KeyT, true>* it_btree_ = nullptr;

  Node* RBT_increment(Node* ptr);
  Node* RBT_decrement(Node* ptr);
};

template <typename KeyT>
class multiset<KeyT>::MultisetConstIterator
    : public multiset<KeyT>::MultisetIterator {
 public:
  using value_type = KeyT;
  using const_reference = const value_type&;

 public:
  MultisetConstIterator(MultisetIterator other) : MultisetIterator(other) {}
  const_reference operator*() { return MultisetIterator::operator*(); }
};

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::find(
    const key_type& key) {
  typename RBTree<key_type, key_type, true>::Node* temp = btree_.search(key);
  return (!temp) ? end() : multiset<key_type>::iterator(temp, &btree_);
}

template <typename key_type>
typename RBTree<key_type, key_type, true>::Node*
multiset<key_type>::MultisetIterator::RBT_increment(
    typename RBTree<key_type, key_type, true>::Node* ptr) {
  if (!it_btree_->isNil(ptr->right_)) {
    ptr = ptr->right_;
    while (!it_btree_->isNil(ptr->left_)) ptr = ptr->left_;
  } else {
    typename RBTree<key_type, key_type, true>::Node* parent = ptr->parent_;
    while (ptr == parent->right_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->right_ != parent) ptr = parent;
  }
  return ptr;
}

template <typename key_type>
typename RBTree<key_type, key_type, true>::Node*
multiset<key_type>::MultisetIterator::RBT_decrement(
    typename RBTree<key_type, key_type, true>::Node* ptr) {
  if (!it_btree_->isNil(ptr->left_)) {
    ptr = ptr->left_;
    while (!it_btree_->isNil(ptr->right_)) ptr = ptr->right_;
  } else {
    typename RBTree<key_type, key_type, true>::Node* parent = ptr->parent_;
    while (ptr == parent->left_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->left_ != parent) ptr = parent;
  }
  return ptr;
}

template <typename key_type>
bool multiset<key_type>::operator==(const multiset<key_type>& other) const {
  if (this == &other) return true;
  if (size() != other.size()) return false;

  return (std::equal(begin(), end(), other.begin()));
}

template <typename key_type>
bool multiset<key_type>::operator!=(const multiset<key_type>& other) const {
  return !(*this == other);
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename RBTree<key_type, key_type, true>::Node) / 4294967296;
}

template <typename key_type>
multiset<key_type>::multiset() : btree_(), size_(0) {}

template <typename key_type>
multiset<key_type>::multiset(std::initializer_list<value_type> const& items)
    : btree_(), size_(0) {
  for (const_reference p : items)
    if (btree_.insert(std::make_pair(p, p)).second) size_++;
}

template <typename key_type>
multiset<key_type>::multiset(const multiset& other)
    : btree_(), size_(other.size_) {
  for (auto it : other) this->btree_.insert(std::make_pair(it, it));
}

template <typename key_type>
multiset<key_type>::multiset(multiset&& other) noexcept
    : btree_(other.btree_), size_(other.size_) {
  if (this != &other) {
    other.btree_.makeNullRoot();
    other.size_ = 0;
  }
}

template <typename key_type>
multiset<key_type>& multiset<key_type>::operator=(const multiset& other) {
  size_ = other.size_;
  for (auto it : other) this->btree_.insert(std::make_pair(it, it));

  return *this;
}

template <typename key_type>
multiset<key_type>& multiset<key_type>::operator=(multiset&& other) {
  if (this == &other) return *this;
  multiset<key_type> temp = std::move(*this);
  btree_ = other.btree_;
  size_ = other.size_;

  other.btree_.makeNullRoot();
  other.size_ = 0;

  return *this;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::begin() {
  multiset<key_type>::iterator it(btree_.getMin(), &btree_);
  return it;
}

template <typename key_type>
typename multiset<key_type>::const_iterator multiset<key_type>::begin() const {
  MultisetIterator it(btree_.getMin(),
                      const_cast<RBTree<key_type, key_type, true>*>(&btree_));
  return MultisetConstIterator(it);
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::end() {
  multiset<key_type>::iterator it(btree_.getMax(), &btree_);
  return it;
}

template <typename key_type>
typename multiset<key_type>::const_iterator multiset<key_type>::end() const {
  MultisetIterator it(btree_.getMax(),
                      const_cast<RBTree<key_type, key_type, true>*>(&btree_));
  return MultisetConstIterator(it);
}

template <typename key_type>
void multiset<key_type>::clear() {
  btree_.clear();
  size_ = 0;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::insert(
    const value_type& value) {
  std::pair<typename RBTree<key_type, key_type, true>::Node*, bool> temp =
      btree_.insert(std::make_pair(value, value));
  if (temp.second) size_++;
  return multiset<key_type>::iterator(temp.first, &btree_);
}

template <typename key_type>
void multiset<key_type>::erase(iterator pos) {
  btree_.remove(*pos);
  size_--;
}

template <typename key_type>
void multiset<key_type>::erase(value_type pos) {
  btree_.remove(pos);
  size_--;
}

template <typename key_type>
void multiset<key_type>::swap(multiset& other) {
  btree_.swapOtherRoot(other.btree_);
  std::swap(size_, other.size_);
}

template <typename key_type>
void multiset<key_type>::merge(multiset& other) {
  multiset<key_type>::iterator itTemp;
  for (auto it : other) {
    insert(it);
  }
  other.clear();
}

template <typename key_type>
bool multiset<key_type>::contains(const key_type& key) {
  return (btree_.search(key) == nullptr) ? false : true;
}

template <typename key_type>
template <typename... Args>
vector<std::pair<typename multiset<key_type>::iterator, bool>>
multiset<key_type>::insert_many(Args&&... args) {
  vector<std::pair<multiset<key_type>::iterator, bool>> res;
  for (auto it : {args...}) res.push_back(std::make_pair(insert(it), true));
  return res;
}
}  // namespace s21

#endif  // SRC_CORE_S21_MULTISET_H_