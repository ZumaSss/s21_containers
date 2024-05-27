#ifndef SRC_CORE_S21_CONTAINER_H_
#define SRC_CORE_S21_CONTAINER_H_

#include <cstddef>

namespace s21 {

/*
  The class IContainer serves as an interface for data containers.
  It defines a set of methods that any subclass representing a container must
  implement.

  Interface:
  - Interface in object-oriented programming defines a set
    of methods that must be implemented by subclasses.
    It serves as a contract describing the behavior of the class.

  Iterators:
  - Iterators are used to traverse the elements of a container.
    They provide a way to sequentially access the elements of a collection
    and can be used for reading or modifying the values of elements.

  Virtual methods:
  - Virtual methods are defined using the virtual keyword and can be overridden
  in subclass. They enable polymorphism, allowing to call methods from the base
  class for objects of subclass.

  Method descriptions:
  - size(): returns the number of elements in the container.

  - max_size(): returns the maximum possible number of elements in the
  container.

  - empty(): returns true if the container is empty, otherwise false.

  - insert(const_iterator pos, const T& value):
    inserts the element value at the position specified by the iterator pos.

  - clear(): removes all elements from the container.

  - erase(const T& value): removes the element value from the container.

  - swap(IContainer& other) noexcept:
    swaps the contents of the container with another container.

  - begin():
    returns an iterator pointing to the first element of the container.

  - end():
    returns an iterator pointing to the position past the last element of the
  container.

  - operator=(): assignment operators for copying and moving the container.
*/

class IContainer {
 public:
  using size_type = std::size_t;

  virtual ~IContainer() {}

  virtual size_type size() const noexcept = 0;
  virtual bool empty() const noexcept = 0;
};

}  // namespace s21

#endif  // SRC_S21_CONTAINER_H_