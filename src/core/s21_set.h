#ifndef SRC_CORE_S21_SET_H_
#define SRC_CORE_S21_SET_H_

#include <limits>
#include <type_traits>

#include "s21_container.h"
#include "s21_rbtree.h"
#include "s21_vector.h"

namespace s21 {

template <typename KeyT>
class set : public IContainer {
 public:
  class SetIterator;
  class SetConstIterator;

  using key_type = KeyT;
  using value_type = KeyT;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = set<key_type>::SetIterator;
  using const_iterator = set<key_type>::SetConstIterator;
  using typename IContainer::size_type;

 public:
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& other);
  set(set&& other) noexcept;
  ~set(){};

  set<key_type>& operator=(const set& other);
  set<key_type>& operator=(set&& other);

  bool operator==(const set<key_type>& other) const;
  bool operator!=(const set<key_type>& other) const;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const noexcept override { return btree_.isEmpty(); }
  size_type size() const noexcept override { return size_; }
  static size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);

  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  iterator find(const key_type& key);
  bool contains(const key_type& key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RBTree<KeyT, KeyT, false> btree_;
  size_type size_;

 private:
  void erase(value_type pos);
};

template <typename KeyT>
class set<KeyT>::SetIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = KeyT;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  using Node = typename RBTree<KeyT, KeyT, false>::Node;

 public:
  SetIterator() = default;
  SetIterator(Node* ptr, RBTree<KeyT, KeyT, false>* it_btree)
      : ptr_(ptr), it_btree_(it_btree) {}

  bool operator==(const SetIterator& other) { return ptr_ == other.ptr_; }
  bool operator!=(const SetIterator& other) { return !(*this == other); }

  SetIterator& operator++() {
    ptr_ = RBT_increment(ptr_);
    return *this;
  }

  SetIterator operator++(int) {
    SetIterator temp = *this;
    ++*this;
    return temp;
  }

  SetIterator& operator--() {
    ptr_ = RBT_decrement(ptr_);
    return *this;
  }

  SetIterator operator--(int) {
    SetIterator temp = *this;
    --*this;
    return temp;
  }

  reference operator*() { return ptr_->val_.second; }

 private:
  Node* ptr_ = nullptr;
  RBTree<KeyT, KeyT, false>* it_btree_ = nullptr;

  Node* RBT_increment(Node* ptr);
  Node* RBT_decrement(Node* ptr);
};

template <typename KeyT>
class set<KeyT>::SetConstIterator : public set<KeyT>::SetIterator {
 public:
  using value_type = KeyT;
  using const_reference = const value_type&;

 public:
  SetConstIterator(SetIterator other) : SetIterator(other) {}
  const_reference operator*() { return SetIterator::operator*(); }
};

template <typename key_type>
typename set<key_type>::iterator set<key_type>::find(const key_type& key) {
  typename RBTree<key_type, key_type, false>::Node* temp = btree_.search(key);
  return (!temp) ? end() : set<key_type>::iterator(temp, &btree_);
}

template <typename key_type>
typename RBTree<key_type, key_type, false>::Node*
set<key_type>::SetIterator::RBT_increment(
    typename RBTree<key_type, key_type, false>::Node* ptr) {
  if (!it_btree_->isNil(ptr->right_)) {
    ptr = ptr->right_;
    while (!it_btree_->isNil(ptr->left_)) ptr = ptr->left_;
  } else {
    typename RBTree<key_type, key_type, false>::Node* parent = ptr->parent_;
    while (ptr == parent->right_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->right_ != parent) ptr = parent;
  }
  return ptr;
}

template <typename key_type>
typename RBTree<key_type, key_type, false>::Node*
set<key_type>::SetIterator::RBT_decrement(
    typename RBTree<key_type, key_type, false>::Node* ptr) {
  if (!it_btree_->isNil(ptr->left_)) {
    ptr = ptr->left_;
    while (!it_btree_->isNil(ptr->right_)) ptr = ptr->right_;
  } else {
    typename RBTree<key_type, key_type, false>::Node* parent = ptr->parent_;
    while (ptr == parent->left_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->left_ != parent) ptr = parent;
  }
  return ptr;
}

template <typename key_type>
bool set<key_type>::operator==(const set<key_type>& other) const {
  if (this == &other) return true;
  if (size() != other.size()) return false;

  return (std::equal(begin(), end(), other.begin()));
}

template <typename key_type>
bool set<key_type>::operator!=(const set<key_type>& other) const {
  return !(*this == other);
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename RBTree<key_type, key_type, false>::Node) / 4294967296;
}

template <typename key_type>
set<key_type>::set() : btree_(), size_(0) {}

template <typename key_type>
set<key_type>::set(std::initializer_list<value_type> const& items)
    : btree_(), size_(0) {
  for (const_reference p : items)
    if (btree_.insert(std::make_pair(p, p)).second) size_++;
}

template <typename key_type>
set<key_type>::set(const set& other) : btree_(), size_(other.size_) {
  for (auto it : other) this->btree_.insert(std::make_pair(it, it));
}

template <typename key_type>
set<key_type>::set(set&& other) noexcept
    : btree_(other.btree_), size_(other.size_) {
  if (this != &other) {
    other.btree_.makeNullRoot();
    other.size_ = 0;
  }
}

template <typename key_type>
set<key_type>& set<key_type>::operator=(const set& other) {
  size_ = other.size_;
  for (auto it : other) this->btree_.insert(std::make_pair(it, it));

  return *this;
}

template <typename key_type>
set<key_type>& set<key_type>::operator=(set&& other) {
  if (this == &other) return *this;
  set<key_type> temp = std::move(*this);
  btree_ = other.btree_;
  size_ = other.size_;

  other.btree_.makeNullRoot();
  other.size_ = 0;

  return *this;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::begin() {
  set<key_type>::iterator it(btree_.getMin(), &btree_);
  return it;
}

template <typename key_type>
typename set<key_type>::const_iterator set<key_type>::begin() const {
  SetIterator it(btree_.getMin(),
                 const_cast<RBTree<key_type, key_type, false>*>(&btree_));
  return SetConstIterator(it);
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::end() {
  set<key_type>::iterator it(btree_.getMax(), &btree_);
  return it;
}

template <typename key_type>
typename set<key_type>::const_iterator set<key_type>::end() const {
  SetIterator it(btree_.getMax(),
                 const_cast<RBTree<key_type, key_type, false>*>(&btree_));
  return SetConstIterator(it);
}

template <typename key_type>
void set<key_type>::clear() {
  btree_.clear();
  size_ = 0;
}

template <typename key_type>
std::pair<typename set<key_type>::iterator, bool> set<key_type>::insert(
    const value_type& value) {
  std::pair<typename RBTree<key_type, key_type, false>::Node*, bool> temp =
      btree_.insert(std::make_pair(value, value));
  if (temp.second) size_++;
  return std::make_pair(set<key_type>::iterator(temp.first, &btree_),
                        temp.second);
}

template <typename key_type>
void set<key_type>::erase(iterator pos) {
  btree_.remove(*pos);
  size_--;
}

template <typename key_type>
void set<key_type>::erase(value_type pos) {
  btree_.remove(pos);
  size_--;
}

template <typename key_type>
void set<key_type>::swap(set& other) {
  btree_.swapOtherRoot(other.btree_);
  std::swap(size_, other.size_);
}

template <typename key_type>
void set<key_type>::merge(set& other) {
  set<key_type>::iterator itTemp;
  vector<key_type> buff;
  for (set<key_type>::iterator it = other.begin(); it != other.end(); ++it) {
    if (insert(*it).second) {
      buff.push_back(*it);
    }
  }
  for (auto it : buff) other.erase(it);
}

template <typename key_type>
bool set<key_type>::contains(const key_type& key) {
  return (btree_.search(key) == nullptr) ? false : true;
}

template <typename key_type>
template <typename... Args>
vector<std::pair<typename set<key_type>::iterator, bool>>
set<key_type>::insert_many(Args&&... args) {
  vector<std::pair<set<key_type>::iterator, bool>> res;
  for (auto it : {args...}) res.push_back(insert(it));
  return res;
}
}  // namespace s21

#endif  // SRC_CORE_S21_SET_H_