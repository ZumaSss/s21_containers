#ifndef SRC_CORE_S21_RBTREE_H_
#define SRC_CORE_S21_RBTREE_H_

#include <algorithm>
#include <iostream>

namespace s21 {
template <typename KeyT, typename ValT, bool multi_type>
class RBTree {
 private:
  enum class NodeColor { BLACK, RED };

 public:
  struct Node {
    Node* left_;
    Node* right_;
    Node* parent_;
    NodeColor color_ = NodeColor::BLACK;
    std::pair<const KeyT, ValT> val_;

    Node() : left_(nullptr), right_(nullptr), parent_(nullptr) {}
    Node(std::pair<const KeyT, ValT> pair, Node* node)
        : left_(node),
          right_(node),
          parent_(node),
          color_(NodeColor::RED),
          val_(pair) {}
  };

 private:
  Node* nil_ = new Node();
  Node* root_;

 public:
  RBTree() : root_(nil_) {}
  RBTree(std::pair<const KeyT, ValT> pair) : root_(new Node(pair, nil_)) {}
  ~RBTree();

  bool isNil(Node* node) const { return node == nil_; }
  bool isEmpty() const { return root_ == nil_; }

  std::pair<Node*, bool> insert(const std::pair<const KeyT, ValT>& pair);
  std::pair<Node*, bool> insert(const KeyT& key);
  std::pair<Node*, bool> insert(const KeyT& key, const ValT& obj);
  void remove(const KeyT& key) { removeNode(key); }

  Node* search(const KeyT& key) const { return search(root_, key); }
  Node* getMin() const;
  Node* getMax() const;

  Node* getMin(Node* node) const;
  Node* getMax(Node* node) const;

  void makeNullRoot();
  void clear();
  void printTree() { printTree(root_); }
  void swapOtherRoot(RBTree& other);

 private:
  std::pair<Node*, bool> insertNode(const KeyT& key, const ValT& obj);
  void balanceInsert(Node* newNode);
  void removeNode(const KeyT& key);
  void balanceRemove(Node* node);
  void rightRotate(Node* node);
  void leftRotate(Node* node);

  Node* search(Node* node, const KeyT& key) const;
  Node* getChildOrMock(Node* node);
  int getChildrenCount(Node* node);
  void transplateNode(Node* dest, Node* src);

  void swap(Node* a, Node* b);
  void swapValue(Node* dest, Node* src);

  void printTree(Node* node);
  void deleteTree(Node* node);
};

template <typename KeyT, typename ValT, bool multi_type>
std::pair<typename RBTree<KeyT, ValT, multi_type>::Node*, bool>
RBTree<KeyT, ValT, multi_type>::insert(const KeyT& key, const ValT& obj) {
  return insertNode(key, obj);
}

template <typename KeyT, typename ValT, bool multi_type>
std::pair<typename RBTree<KeyT, ValT, multi_type>::Node*, bool>
RBTree<KeyT, ValT, multi_type>::insert(const KeyT& key) {
  ValT defaultValue = ValT();
  return insertNode(key, defaultValue);
}

template <typename KeyT, typename ValT, bool multi_type>
std::pair<typename RBTree<KeyT, ValT, multi_type>::Node*, bool>
RBTree<KeyT, ValT, multi_type>::insert(
    const std::pair<const KeyT, ValT>& pair) {
  return insertNode(pair.first, pair.second);
}

template <typename KeyT, typename ValT, bool multi_type>
typename RBTree<KeyT, ValT, multi_type>::Node*
RBTree<KeyT, ValT, multi_type>::getChildOrMock(
    typename RBTree<KeyT, ValT, multi_type>::Node* node) {
  return isNil(node->left_) ? node->right_ : node->left_;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::makeNullRoot() {
  root_ = nullptr;
  nil_ = nullptr;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::swapOtherRoot(
    RBTree<KeyT, ValT, multi_type>& other) {
  std::swap(root_, other.root_);
  std::swap(nil_, other.nil_);
}

template <typename KeyT, typename ValT, bool multi_type>
RBTree<KeyT, ValT, multi_type>::~RBTree() {
  deleteTree(root_);
  delete nil_;
}

template <typename KeyT, typename ValT, bool multi_type>
std::pair<typename RBTree<KeyT, ValT, multi_type>::Node*, bool>
RBTree<KeyT, ValT, multi_type>::insertNode(const KeyT& key, const ValT& value) {
  Node* checkNode = search(key);
  if (checkNode != nullptr && (!multi_type))
    return std::make_pair(checkNode, false);

  Node* currentNode = root_;
  Node* parent = nil_;
  while (!isNil(currentNode)) {
    parent = currentNode;
    (key < currentNode->val_.first) ? currentNode = currentNode->left_
                                    : currentNode = currentNode->right_;
  }
  Node* newNode = new Node(std::make_pair(key, value), nil_);
  newNode->parent_ = parent;
  if (parent == nil_)
    root_ = newNode;
  else if (key < parent->val_.first)
    parent->left_ = newNode;
  else
    parent->right_ = newNode;
  balanceInsert(newNode);
  return std::make_pair(newNode, true);
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::balanceInsert(Node* newNode) {
  Node* uncle;
  while (newNode->parent_->color_ == NodeColor::RED) {
    if (newNode->parent_ == newNode->parent_->parent_->left_) {
      uncle = newNode->parent_->parent_->right_;
      if (uncle->color_ == NodeColor::RED) {
        newNode->parent_->color_ = NodeColor::BLACK;
        uncle->color_ = NodeColor::BLACK;
        newNode->parent_->parent_->color_ = NodeColor::RED;
        newNode = newNode->parent_->parent_;
      } else {
        if (newNode == newNode->parent_->right_) {
          leftRotate(newNode->parent_);

          newNode->color_ = NodeColor::BLACK;
          newNode->parent_->color_ = NodeColor::RED;
          rightRotate(newNode->parent_);
          newNode = newNode->parent_;
        } else {
          newNode->parent_->color_ = NodeColor::BLACK;
          newNode->parent_->parent_->color_ = NodeColor::RED;
          rightRotate(newNode->parent_->parent_);
        }
      }
    } else {
      uncle = newNode->parent_->parent_->left_;
      if (uncle->color_ == NodeColor::RED) {
        newNode->parent_->color_ = NodeColor::BLACK;
        uncle->color_ = NodeColor::BLACK;
        newNode->parent_->parent_->color_ = NodeColor::RED;
        newNode = newNode->parent_->parent_;
      } else {
        if (newNode == newNode->parent_->left_) {
          rightRotate(newNode->parent_);

          newNode->color_ = NodeColor::BLACK;
          newNode->parent_->color_ = NodeColor::RED;
          leftRotate(newNode->parent_);
          newNode = newNode->parent_;
        } else {
          newNode->parent_->color_ = NodeColor::BLACK;
          newNode->parent_->parent_->color_ = NodeColor::RED;
          leftRotate(newNode->parent_->parent_);
        }
      }
    }
  }
  root_->color_ = NodeColor::BLACK;
}

template <typename KeyT, typename ValT, bool multi_type>
typename RBTree<KeyT, ValT, multi_type>::Node*
RBTree<KeyT, ValT, multi_type>::search(Node* node, const KeyT& key) const {
  if (isNil(node)) return nullptr;

  if (node->val_.first == key) {
    if (!multi_type)
      return node;
    else
      return (node->left_->val_.first == key) ? search(node->left_, key) : node;
  }

  return (key < node->val_.first) ? search(node->left_, key)
                                  : search(node->right_, key);
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::printTree(Node* node) {
  if (isNil(node)) return;

  printTree(node->left_);
  std::cout << node->val_.first << ' ';
  printTree(node->right_);
}

template <typename KeyT, typename ValT, bool multi_type>
int RBTree<KeyT, ValT, multi_type>::getChildrenCount(Node* node) {
  int count = 0;
  if (!isNil(node->left_)) count++;
  if (!isNil(node->right_)) count++;
  return count;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::transplateNode(Node* dest, Node* src) {
  if (dest == root_)
    root_ = src;
  else if (dest == dest->parent_->left_)
    dest->parent_->left_ = src;
  else
    dest->parent_->right_ = src;
  src->parent_ = dest->parent_;
  delete dest;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::swapValue(Node* dest, Node* src) {
  Node* temp = new Node(src->val_, nil_);
  temp->color_ = dest->color_;

  temp->left_ = dest->left_;
  temp->right_ = dest->right_;
  temp->parent_ = dest->parent_;

  dest->left_->parent_ = temp;
  dest->right_->parent_ = temp;
  if (dest != root_) {
    if (dest == dest->parent_->left_)
      dest->parent_->left_ = temp;
    else
      dest->parent_->right_ = temp;
  } else
    root_ = temp;

  delete dest;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::removeNode(const KeyT& key) {
  Node* nodeToDelete = search(key);
  if (nodeToDelete == nullptr) return;

  NodeColor removedNodeColor = nodeToDelete->color_;
  Node* child;

  if (getChildrenCount(nodeToDelete) < 2) {
    child = getChildOrMock(nodeToDelete);
    transplateNode(nodeToDelete, child);
  } else {
    Node* minNode = getMin(nodeToDelete->right_);
    swapValue(nodeToDelete, minNode);
    removedNodeColor = minNode->color_;
    child = getChildOrMock(minNode);
    transplateNode(minNode, child);
  }
  if (removedNodeColor == NodeColor::BLACK) balanceRemove(child);
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::balanceRemove(Node* node) {
  while (node != root_ && node->color_ == NodeColor::BLACK) {
    Node* brother;
    if (node == node->parent_->left_) {
      brother = node->parent_->right_;
      if (brother->color_ == NodeColor::RED) {
        brother->color_ = NodeColor::BLACK;
        node->parent_->color_ = NodeColor::RED;
        leftRotate(node->parent_);
        brother = node->parent_->right_;
      }
      if (brother->left_->color_ == NodeColor::BLACK &&
          brother->right_->color_ == NodeColor::BLACK) {
        brother->color_ = NodeColor::RED;
        node = node->parent_;
      } else {
        if (brother->right_->color_ == NodeColor::BLACK) {
          brother->left_->color_ = NodeColor::BLACK;
          brother->color_ = NodeColor::RED;
          rightRotate(brother);
          node->parent_ = brother->parent_->parent_;
          brother = node->parent_->right_;
        }
        brother->color_ = node->parent_->color_;
        node->parent_->color_ = NodeColor::BLACK;
        brother->right_->color_ = NodeColor::BLACK;
        leftRotate(node->parent_);
        node = root_;
      }
    } else {
      brother = node->parent_->left_;
      if (brother->color_ == NodeColor::RED) {
        brother->color_ = NodeColor::BLACK;
        node->parent_->color_ = NodeColor::RED;
        rightRotate(node->parent_);
        brother = node->parent_->left_;
      }
      if (brother->left_->color_ == NodeColor::BLACK &&
          brother->right_->color_ == NodeColor::BLACK) {
        brother->color_ = NodeColor::RED;
        node = node->parent_;
      } else {
        if (brother->left_->color_ == NodeColor::BLACK) {
          brother->right_->color_ = NodeColor::BLACK;
          brother->color_ = NodeColor::RED;
          leftRotate(brother);
          node->parent_ = brother->parent_->parent_;
          brother = node->parent_->left_;
        }
        brother->color_ = node->parent_->color_;
        node->parent_->color_ = NodeColor::BLACK;
        brother->left_->color_ = NodeColor::BLACK;
        rightRotate(node->parent_);
        node = root_;
      }
    }
  }
  node->color_ = NodeColor::BLACK;
}

template <typename KeyT, typename ValT, bool multi_type>
typename RBTree<KeyT, ValT, multi_type>::Node*
RBTree<KeyT, ValT, multi_type>::getMin(Node* node) const {
  if (isNil(node)) return nullptr;

  if (isNil(node->left_)) return node;
  return getMin(node->left_);
}

template <typename KeyT, typename ValT, bool multi_type>
typename RBTree<KeyT, ValT, multi_type>::Node*
RBTree<KeyT, ValT, multi_type>::getMin() const {
  if (isNil(root_) || isNil(root_->left_)) return root_;

  Node* temp = root_->left_;
  while (!isNil(temp->left_)) temp = temp->left_;

  return temp;
}

template <typename KeyT, typename ValT, bool multi_type>
typename RBTree<KeyT, ValT, multi_type>::Node*
RBTree<KeyT, ValT, multi_type>::getMax(Node* node) const {
  if (isNil(node)) return nullptr;

  if (isNil(node->right_)) return node;
  return getMax(node->right_);
}

template <typename KeyT, typename ValT, bool multi_type>
typename RBTree<KeyT, ValT, multi_type>::Node*
RBTree<KeyT, ValT, multi_type>::getMax() const {
  if (isNil(root_)) return nil_;

  Node* temp = root_;
  while (!isNil(temp->right_)) temp = temp->right_;

  return temp->right_;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::deleteTree(Node* node) {
  if (isNil(node)) return;

  deleteTree(node->left_);
  deleteTree(node->right_);
  delete node;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::swap(Node* a, Node* b) {
  if (b == a->left_) {
    Node* aRight = a->right_;
    Node* bLeft = b->left_;
    a->right_ = b->right_;
    b->right_ = aRight;

    b->left_ = a;
    a->left_ = bLeft;

    if (!isNil(a->parent_)) {
      if (a == a->parent_->left_)
        a->parent_->left_ = b;
      else
        a->parent_->right_ = b;
      b->parent_ = a->parent_;
    } else
      b->parent_ = nil_;
    a->parent_ = b;

    if (!isNil(b->right_)) b->right_->parent_ = b;

    if (!isNil(a->right_)) a->right_->parent_ = a;

    if (!isNil(a->left_)) a->left_->parent_ = a;
  } else {
    Node* aLeft = a->left_;
    Node* bRight = b->right_;
    a->left_ = b->left_;
    b->left_ = aLeft;

    b->right_ = a;
    a->right_ = bRight;

    if (!isNil(a->parent_)) {
      if (a == a->parent_->left_)
        a->parent_->left_ = b;
      else
        a->parent_->right_ = b;
      b->parent_ = a->parent_;
    } else
      b->parent_ = nil_;
    a->parent_ = b;

    if (!isNil(b->left_)) b->left_->parent_ = b;

    if (!isNil(a->left_)) a->left_->parent_ = a;

    if (!isNil(a->right_)) a->right_->parent_ = a;
  }

  if (a == root_) root_ = b;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::rightRotate(Node* node) {
  swap(node, node->left_);
  Node* temp = node->parent_->right_;
  node->parent_->right_ = node->parent_->left_;
  node->parent_->left_ = node->parent_->right_->left_;
  node->parent_->right_->left_ = node->parent_->right_->right_;
  node->parent_->right_->right_ = temp;

  node->parent_->left_->parent_ = node->parent_;
  if (!isNil(node->parent_->right_->right_->parent_))
    node->parent_->right_->right_->parent_ = node->parent_->right_;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::leftRotate(Node* node) {
  swap(node, node->right_);
  Node* temp = node->parent_->left_;
  node->parent_->left_ = node->parent_->right_;
  node->parent_->right_ = node->parent_->left_->right_;
  node->parent_->left_->right_ = node->parent_->left_->left_;
  node->parent_->left_->left_ = temp;

  node->parent_->right_->parent_ = node->parent_;
  if (!isNil(node->parent_->left_->left_->parent_))
    node->parent_->left_->left_->parent_ = node->parent_->left_;
}

template <typename KeyT, typename ValT, bool multi_type>
void RBTree<KeyT, ValT, multi_type>::clear() {
  deleteTree(root_);
  root_ = nil_;
}
}  // namespace s21

#endif  // SRC_CORE_S21_RBTREE_H_