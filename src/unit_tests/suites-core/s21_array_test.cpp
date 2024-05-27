#include "s21_core_tests.h"

#ifdef DEBUG
#include <iostream>
#endif

#include <algorithm>
#include <array>
#include <string>
#include <type_traits>

#include "core/s21_array.h"

template <typename T, std::size_t N>
void checkBasicFieldEmpty(const s21::array<T, N>& actual,
                          const std::array<T, N>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T, std::size_t N>
void checkBasicField(const s21::array<T, N>& actual,
                     const std::array<T, N>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T, std::size_t N>
void checkBasicField(const s21::array<T, N>& actual,
                     const s21::array<T, N>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

/* NORMAL */

#define DEF_INT_VALS \
  { 1, 2, 3, 4, 5 }
#define DEF_DBL_VALS \
  { 1.42, 2.5, 0.003, 664.452, 1.0035 }
#define DEF_MOCK_VALS \
  { 1, 2, 44, 45, 777 }
#define DEF_STR_VALS \
  { "hello", "world", "!", "Foo", "Bar" }

template <typename T>
void arrayDefaultInitTest() {
  s21::array<T, 5> actual;
  std::array<T, 5> expected;

  checkBasicField(actual, expected);
}

#define TESTS_EMPTY_INIT(suiteName)                                            \
  TEST(suiteName, uShortEmptyInit) { arrayDefaultInitTest<unsigned short>(); } \
  TEST(suiteName, intEmptyInit) { arrayDefaultInitTest<int>(); }               \
  TEST(suiteName, doubleEmptyInit) { arrayDefaultInitTest<double>(); }         \
  TEST(suiteName, MockClassEmptyInit) { arrayDefaultInitTest<MockClass>(); }   \
  TEST(suiteName, stringEmptyInit) { arrayDefaultInitTest<std::string>(); }

TESTS_EMPTY_INIT(s21Array)

// --------------------------------------

template <typename T>
void arrayCopyInitTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  s21::array<T, 5> actualCopy(actual);

  checkBasicField(actual, actualCopy);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actualCopy.begin()));
}

#define TESTS_COPY_INIT(suiteName)                                             \
  TEST(suiteName, uShortCopyInit) {                                            \
    arrayCopyInitTest<unsigned short>(DEF_INT_VALS);                           \
  }                                                                            \
  TEST(suiteName, intCopyInit) { arrayCopyInitTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleCopyInit) { arrayCopyInitTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassCopyInit) {                                         \
    arrayCopyInitTest<MockClass>(DEF_MOCK_VALS);                               \
  }                                                                            \
  TEST(suiteName, stringCopyInit) {                                            \
    arrayCopyInitTest<std::string>(DEF_STR_VALS);                              \
  }

TESTS_COPY_INIT(s21Array)

// --------------------------------------

template <typename T>
void arrayMoveInitTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  s21::array<T, 5> actualMove(std::move(actual));

  EXPECT_FALSE(std::equal(actual.begin(), actual.end(), actualMove.begin()));
}

#define TESTS_MOVE_INIT(suiteName)                \
  TEST(suiteName, MockClassMoveInit) {            \
    arrayMoveInitTest<MockClass>(DEF_MOCK_VALS);  \
  }                                               \
  TEST(suiteName, stringMoveInit) {               \
    arrayMoveInitTest<std::string>(DEF_STR_VALS); \
  }

TESTS_MOVE_INIT(s21Array)

// --------------------------------------

template <typename T>
void arrayOperatorCopyTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  s21::array<T, 5> actualCopy;
  actualCopy = actual;

  checkBasicField(actual, actualCopy);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actualCopy.begin()));
}

#define TESTS_OPERATOR_COPY(suiteName)                   \
  TEST(suiteName, uShortOperatorCopy) {                  \
    arrayOperatorCopyTest<unsigned short>(DEF_INT_VALS); \
  }                                                      \
  TEST(suiteName, intOperatorCopy) {                     \
    arrayOperatorCopyTest<int>(DEF_INT_VALS);            \
  }                                                      \
  TEST(suiteName, doubleOperatorCopy) {                  \
    arrayOperatorCopyTest<double>(DEF_DBL_VALS);         \
  }                                                      \
  TEST(suiteName, MockClassOperatorCopy) {               \
    arrayOperatorCopyTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                      \
  TEST(suiteName, stringOperatorCopy) {                  \
    arrayOperatorCopyTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_OPERATOR_COPY(s21Array)

// --------------------------------------

template <typename T>
void arrayOperatorMoveTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  s21::array<T, 5> actualMove;
  actualMove = std::move(actual);

  EXPECT_FALSE(std::equal(actual.begin(), actual.end(), actualMove.begin()));
}

#define TESTS_OPERATOR_MOVE(suiteName)                \
  TEST(suiteName, MockClassOperatorMove) {            \
    arrayOperatorMoveTest<MockClass>(DEF_MOCK_VALS);  \
  }                                                   \
  TEST(suiteName, stringOperatorMove) {               \
    arrayOperatorMoveTest<std::string>(DEF_STR_VALS); \
  }

TESTS_OPERATOR_MOVE(s21Array)

// --------------------------------------

template <typename T>
void arraySwapTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  s21::array<T, 5> actualSwap{9, 9, 9, 9, 9};
  actualSwap.swap(actual);

  EXPECT_FALSE(std::equal(actual.begin(), actual.end(), actualSwap.begin()));
}

#define TESTS_SWAP(suiteName)                                                  \
  TEST(suiteName, uShortSwap) { arraySwapTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intSwap) { arraySwapTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleSwap) { arraySwapTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassSwap) { arraySwapTest<MockClass>(DEF_MOCK_VALS); }

TESTS_SWAP(s21Array)

// --------------------------------------

template <typename T>
void arrayFrontTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);

  EXPECT_EQ(actual.front(), actual.front());
}

#define TESTS_FRONT(suiteName)                                           \
  TEST(suiteName, uShortFront) {                                         \
    arrayFrontTest<unsigned short>(DEF_INT_VALS);                        \
  }                                                                      \
  TEST(suiteName, intFront) { arrayFrontTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleFront) { arrayFrontTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassFront) {                                      \
    arrayFrontTest<MockClass>(DEF_MOCK_VALS);                            \
  }                                                                      \
  TEST(suiteName, stringFront) { arrayFrontTest<std::string>(DEF_STR_VALS); }

TESTS_FRONT(s21Array)

// --------------------------------------

template <typename T>
void arrayBackTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);

  EXPECT_EQ(actual.back(), actual.back());
}

#define TESTS_BACK(suiteName)                                                  \
  TEST(suiteName, uShortBack) { arrayBackTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intBack) { arrayBackTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleBack) { arrayBackTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassBack) { arrayBackTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringBack) { arrayBackTest<std::string>(DEF_STR_VALS); }

TESTS_BACK(s21Array)

/* EDGE */

template <typename T>
void arrayOperatorInitCopySelfTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  actual = actual;

  EXPECT_EQ(actual.size(), actual.size());
  EXPECT_EQ(actual.data(), actual.data());

  EXPECT_EQ(actual.empty(), actual.empty());

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actual.begin()));
}

#define TESTS_EDGE_OPERATOR_COPY_SELF_INIT(suiteName)            \
  TEST(suiteName, uShortOperatorCopyInitSelt) {                  \
    arrayOperatorInitCopySelfTest<unsigned short>(DEF_INT_VALS); \
  }                                                              \
  TEST(suiteName, intOperatorCopyInitSelt) {                     \
    arrayOperatorInitCopySelfTest<int>(DEF_INT_VALS);            \
  }                                                              \
  TEST(suiteName, doubleOperatorCopyInitSelt) {                  \
    arrayOperatorInitCopySelfTest<double>(DEF_DBL_VALS);         \
  }                                                              \
  TEST(suiteName, MockClassOperatorCopyInitSelt) {               \
    arrayOperatorInitCopySelfTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                              \
  TEST(suiteName, stringOperatorCopyInitSelt) {                  \
    arrayOperatorInitCopySelfTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_EDGE_OPERATOR_COPY_SELF_INIT(s21Array)

// --------------------------------------

// #NOTE: std::array does not check the case of self-assignment
template <typename T>
void arrayOperatorInitMoveSelfTest(const std::initializer_list<T>& items) {
  s21::array<T, 5> actual(items);
  actual = std::move(actual);

  EXPECT_EQ(actual.size(), actual.size());
  EXPECT_EQ(actual.data(), actual.data());

  EXPECT_EQ(actual.empty(), actual.empty());

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actual.begin()));
}

#define TESTS_EDGE_OPERATOR_MOVE_SELF_INIT(suiteName)            \
  TEST(suiteName, uShortOperatorMoveSelfInit) {                  \
    arrayOperatorInitMoveSelfTest<unsigned short>(DEF_INT_VALS); \
  }                                                              \
  TEST(suiteName, intOperatorMoveSelfInit) {                     \
    arrayOperatorInitMoveSelfTest<int>(DEF_INT_VALS);            \
  }                                                              \
  TEST(suiteName, doubleOperatorMoveSelfInit) {                  \
    arrayOperatorInitMoveSelfTest<double>(DEF_DBL_VALS);         \
  }                                                              \
  TEST(suiteName, MockClassOperatorMoveSelfInit) {               \
    arrayOperatorInitMoveSelfTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                              \
  TEST(suiteName, stringOperatorMoveSelfInit) {                  \
    arrayOperatorInitMoveSelfTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_EDGE_OPERATOR_MOVE_SELF_INIT(s21Array)

// --------------------------------------
