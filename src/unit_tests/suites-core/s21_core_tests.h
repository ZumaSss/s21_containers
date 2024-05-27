#ifndef SRC_UNIT_S21_MATRIX_CORE_TEST_H_
#define SRC_UNIT_S21_MATRIX_CORE_TEST_H_

#include <gtest/gtest.h>

#include "../../s21_containers.h"
#include "../../s21_containersplus.h"

#define LOOP_TESTS_QUANTITY 50

class MockClass {
 public:
  MockClass() : data_(new int[size_]), subData_(42) {
    for (int i = 0; i < size_; i++) {
      data_[i] = i * 2;
    }
  }

  MockClass(int subData) : data_(new int[size_]), subData_(subData) {
    for (int i = 0; i < size_; i++) {
      data_[i] = i * 2;
    }
  }

  MockClass(const MockClass& other)
      : size_(other.size_), data_(new int[size_]), subData_(other.subData_) {
    for (int i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }

  MockClass(MockClass&& other) noexcept
      : size_(other.size_), data_(other.data_), subData_(other.subData_) {
    other.data_ = nullptr;
    other.subData_ = 0;
  }

  ~MockClass() {
    if (data_ != nullptr) delete[] data_;
    data_ = nullptr;
  }

  MockClass& operator=(const MockClass& other) {
    if (this != &other) {
      if (data_ != nullptr) delete[] data_;
      data_ = new int[other.size_];
      for (int i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
      subData_ = other.subData_;
    }
    return *this;
  }

  MockClass& operator=(MockClass&& other) noexcept {
    if (this != &other) {
      if (data_ != nullptr) delete[] data_;
      data_ = other.data_;
      subData_ = other.subData_;
      other.data_ = nullptr;
      other.subData_ = 0;
    }
    return *this;
  }

  bool operator==(const MockClass& other) const noexcept {
    if (subData_ != other.subData_) return false;
    for (int i = 0; i < size_; i++) {
      if (data_[i] != other.data_[i]) return false;
    }
    return true;
  }

  bool operator!=(const MockClass& other) const noexcept {
    return !(*this == other);
  }

  bool operator<(const MockClass& other) const noexcept {
    if (subData_ != other.subData_) return subData_ < other.subData_;
    for (int i = 0; i < size_; i++) {
      if (data_[i] != other.data_[i]) return data_[i] < other.data_[i];
    }
    return false;
  }

  bool operator>(const MockClass& other) const noexcept {
    if (subData_ != other.subData_) return subData_ > other.subData_;
    for (int i = 0; i < size_; i++) {
      if (data_[i] != other.data_[i]) return data_[i] > other.data_[i];
    }
    return false;
  }

  bool operator>=(const MockClass& other) const noexcept {
    return !(*this < other);
  }

  bool operator<=(const MockClass& other) const noexcept {
    return !(*this > other);
  }

  MockClass& operator*(const int mult) noexcept {
    subData_ *= mult;

    for (int i = 0; i < size_; i++) {
      data_[i] *= mult;
    }

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const MockClass& obj) {
    os << "Size: " << obj.size_ << ", "
       << "Subdata: " << obj.subData_ << std::endl;
    os << "Data: " << std::endl;
    for (int i = 0; i < obj.size_; i++) {
      os << "[" << i << "] = " << obj.data_[i] << std::endl;
    }

    return os;
  }

 private:
  const int size_ = 10;
  int* data_;
  int subData_;
};

class NoConstructClass {
 public:
  NoConstructClass(int val) : val_{val} {};

  bool operator==(const NoConstructClass& other) const noexcept {
    return val_ == other.val_;
  }

  bool operator!=(const NoConstructClass& other) const noexcept {
    return !(*this == other);
  }

  NoConstructClass& operator*(const int mult) noexcept {
    val_ *= mult;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const NoConstructClass& obj) {
    os << "Val: " << obj.val_ << std::endl;
    return os;
  }

 private:
  NoConstructClass() = delete;
  int val_ = 5;
};

#endif  // SRC_UNIT_S21_MATRIX_CORE_TEST_H_