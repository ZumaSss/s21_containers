#include "s21_core_tests.h"

#ifdef DEBUG
#include <iostream>
#endif

#include <algorithm>
#include <string>
#include <type_traits>
#include <vector>

#include "core/s21_vector.h"

template <typename T>
void checkBasicFieldEmpty(const s21::vector<T>& actual,
                          const std::vector<T>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_EQ(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T>
void checkBasicField(const s21::vector<T>& actual,
                     const std::vector<T>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T>
void checkBasicField(const s21::vector<T>& actual,
                     const s21::vector<T>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

/* NORMAL */

#define DEF_INT_VALS \
  { 1, 2, 3, 4, 5 }
#define DEF_DBL_VALS \
  { 1.42, 2.5, 0.003, 664.452, 1.0035 }
#define DEF_MOCK_VALS \
  { 1, 2, 44, 45 }
#define DEF_STR_VALS \
  { "hello", "world", "!" }

template <typename T>
void defaultInitAsContTest() {
  s21::IContainer* ct = new s21::vector<T>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_EMPTY_INIT_AS_CONT(suiteName)                                   \
  TEST(suiteName, uShortEmptyInitAsCont) {                                    \
    defaultInitAsContTest<unsigned short>();                                  \
  }                                                                           \
  TEST(suiteName, intEmptyInitAsCont) { defaultInitAsContTest<int>(); }       \
  TEST(suiteName, doubleEmptyInitAsCont) { defaultInitAsContTest<double>(); } \
  TEST(suiteName, MockClassEmptyInitAsCont) {                                 \
    defaultInitAsContTest<MockClass>();                                       \
  }                                                                           \
  TEST(suiteName, stringEmptyInitAsCont) {                                    \
    defaultInitAsContTest<std::string>();                                     \
  }                                                                           \
  TEST(suiteName, NoConstructClassEmptyInitAsCont) {                          \
    defaultInitAsContTest<NoConstructClass>();                                \
  }

TESTS_EMPTY_INIT_AS_CONT(s21Vector)

// --------------------------------------

template <typename T>
void defaultInitTest() {
  s21::vector<T> actual;
  std::vector<T> expected;

  checkBasicFieldEmpty(actual, expected);
}

#define TESTS_EMPTY_INIT(suiteName)                                       \
  TEST(suiteName, uShortEmptyInit) { defaultInitTest<unsigned short>(); } \
  TEST(suiteName, intEmptyInit) { defaultInitTest<int>(); }               \
  TEST(suiteName, doubleEmptyInit) { defaultInitTest<double>(); }         \
  TEST(suiteName, MockClassEmptyInit) { defaultInitTest<MockClass>(); }   \
  TEST(suiteName, stringEmptyInit) { defaultInitTest<std::string>(); }    \
  TEST(suiteName, NoConstructClassEmptyInit) {                            \
    defaultInitTest<NoConstructClass>();                                  \
  }

TESTS_EMPTY_INIT(s21Vector)

// --------------------------------------

template <typename T>
void sizeInitTest() {
  const std::size_t size = 100;

  s21::vector<T> actual(size);
  std::vector<T> expected(size);

  checkBasicField(actual, expected);
}

#define TESTS_SIZE_INIT(suiteName)                                    \
  TEST(suiteName, uShortSizeInit) { sizeInitTest<unsigned short>(); } \
  TEST(suiteName, intSizeInit) { sizeInitTest<int>(); }               \
  TEST(suiteName, doubleSizeInit) { sizeInitTest<double>(); }         \
  TEST(suiteName, MockClassSizeInit) { sizeInitTest<MockClass>(); }   \
  TEST(suiteName, stringSizeInit) { sizeInitTest<std::string>(); }

// #NOTE: NoConstructClass not compile as expected
// TEST(suiteName, NoConstructClassSizeInit) { sizeInitTest<NoConstructClass>();
// }

TESTS_SIZE_INIT(s21Vector)

// --------------------------------------

template <typename T>
void listInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_LIST_INIT(suiteName)                                             \
  TEST(suiteName, uShortListInit) {                                            \
    listInitTest<unsigned short>(DEF_INT_VALS);                                \
  }                                                                            \
  TEST(suiteName, intListInit) { listInitTest<int>(DEF_INT_VALS); }            \
  TEST(suiteName, doubleListInit) { listInitTest<double>(DEF_DBL_VALS); }      \
  TEST(suiteName, MockClassListInit) {                                         \
    listInitTest<MockClass>(DEF_MOCK_VALS);                                    \
  }                                                                            \
  TEST(suiteName, stringListInit) { listInitTest<std::string>(DEF_STR_VALS); } \
  TEST(suiteName, NoConstructClassListInit) {                                  \
    listInitTest<NoConstructClass>(DEF_INT_VALS);                              \
  }

TESTS_LIST_INIT(s21Vector)

// --------------------------------------

template <typename T>
void copyInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualCopy(actual);

  std::vector<T> expected(items);
  std::vector<T> expectedCopy(items);

  checkBasicField(actual, expected);
  checkBasicField(actualCopy, expectedCopy);

  EXPECT_TRUE(actual == actualCopy);
}

#define TESTS_COPY_INIT(suiteName)                                             \
  TEST(suiteName, uShortCopyInit) {                                            \
    copyInitTest<unsigned short>(DEF_INT_VALS);                                \
  }                                                                            \
  TEST(suiteName, intCopyInit) { copyInitTest<int>(DEF_INT_VALS); }            \
  TEST(suiteName, doubleCopyInit) { copyInitTest<double>(DEF_DBL_VALS); }      \
  TEST(suiteName, MockClassCopyInit) {                                         \
    copyInitTest<MockClass>(DEF_MOCK_VALS);                                    \
  }                                                                            \
  TEST(suiteName, stringCopyInit) { copyInitTest<std::string>(DEF_STR_VALS); } \
  TEST(suiteName, NoConstructClassCopyInit) {                                  \
    copyInitTest<NoConstructClass>(DEF_INT_VALS);                              \
  }

TESTS_COPY_INIT(s21Vector)

// --------------------------------------

template <typename T>
void moveInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualMove(std::move(actual));

  std::vector<T> expected(items);
  std::vector<T> expectedMove(std::move(expected));

  checkBasicField(actualMove, expectedMove);

  EXPECT_TRUE(actual != actualMove);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(actual.capacity(), 0);
  EXPECT_EQ(actual.data(), nullptr);

  EXPECT_EQ(expected.size(), 0);
  EXPECT_EQ(expected.capacity(), 0);
  EXPECT_EQ(expected.data(), nullptr);
}

#define TESTS_MOVE_INIT(suiteName)                                             \
  TEST(suiteName, uShortMoveInit) {                                            \
    moveInitTest<unsigned short>(DEF_INT_VALS);                                \
  }                                                                            \
  TEST(suiteName, intMoveInit) { moveInitTest<int>(DEF_INT_VALS); }            \
  TEST(suiteName, doubleMoveInit) { moveInitTest<double>(DEF_DBL_VALS); }      \
  TEST(suiteName, MockClassMoveInit) {                                         \
    moveInitTest<MockClass>(DEF_MOCK_VALS);                                    \
  }                                                                            \
  TEST(suiteName, stringMoveInit) { moveInitTest<std::string>(DEF_STR_VALS); } \
  TEST(suiteName, NoConstructClassMoveInit) {                                  \
    moveInitTest<NoConstructClass>(DEF_INT_VALS);                              \
  }

TESTS_MOVE_INIT(s21Vector)

// --------------------------------------

template <typename T>
void operatorCopyTest(const std::initializer_list<T>& items) {
  const std::size_t size = 1;

  s21::vector<T> actual(items);
  s21::vector<T> actualCopy(size);
  actualCopy = actual;

  std::vector<T> expected(items);
  std::vector<T> expectedCopy(size);
  expectedCopy = expected;

  checkBasicField(actualCopy, expectedCopy);

  EXPECT_TRUE(actual == actualCopy);
}

#define TESTS_OPERATOR_COPY(suiteName)                                      \
  TEST(suiteName, uShortOperatorCopy) {                                     \
    operatorCopyTest<unsigned short>(DEF_INT_VALS);                         \
  }                                                                         \
  TEST(suiteName, intOperatorCopy) { operatorCopyTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doubleOperatorCopy) {                                     \
    operatorCopyTest<double>(DEF_DBL_VALS);                                 \
  }                                                                         \
  TEST(suiteName, MockClassOperatorCopy) {                                  \
    operatorCopyTest<MockClass>(DEF_MOCK_VALS);                             \
  }                                                                         \
  TEST(suiteName, stringOperatorCopy) {                                     \
    operatorCopyTest<std::string>(DEF_STR_VALS);                            \
  }

TESTS_OPERATOR_COPY(s21Vector)

// --------------------------------------

template <typename T>
void operatorMoveTest(const std::initializer_list<T>& items) {
  const std::size_t size = 5;

  s21::vector<T> actual(items);
  s21::vector<T> actualMove(size);
  actualMove = std::move(actual);

  std::vector<T> expected(items);
  std::vector<T> expectedMove(size);
  expectedMove = std::move(expected);

  checkBasicField(actualMove, expectedMove);

  EXPECT_TRUE(actual != actualMove);
  EXPECT_TRUE(
      std::equal(actualMove.begin(), actualMove.end(), expectedMove.begin()));

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(actual.capacity(), 0);
  EXPECT_EQ(actual.data(), nullptr);

  EXPECT_EQ(expected.size(), 0);
  EXPECT_EQ(expected.capacity(), 0);
  EXPECT_EQ(expected.data(), nullptr);
}

#define TESTS_OPERATOR_MOVE(suiteName)                                      \
  TEST(suiteName, uShortOperatorMove) {                                     \
    operatorMoveTest<unsigned short>(DEF_INT_VALS);                         \
  }                                                                         \
  TEST(suiteName, intOperatorMove) { operatorMoveTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doubleOperatorMove) {                                     \
    operatorMoveTest<double>(DEF_DBL_VALS);                                 \
  }                                                                         \
  TEST(suiteName, MockClassOperatorMove) {                                  \
    operatorMoveTest<MockClass>(DEF_MOCK_VALS);                             \
  }                                                                         \
  TEST(suiteName, stringOperatorMove) {                                     \
    operatorMoveTest<std::string>(DEF_STR_VALS);                            \
  }

TESTS_OPERATOR_MOVE(s21Vector)

// --------------------------------------

template <typename T>
void clearTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  actual.clear();
  expected.clear();

  checkBasicField(actual, expected);
}

#define TESTS_CLEAR(suiteName)                                              \
  TEST(suiteName, uShortClear) { clearTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intClear) { clearTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleClear) { clearTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassClear) { clearTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringClear) { clearTest<std::string>(DEF_STR_VALS); }    \
  TEST(suiteName, NoConstructClassClear) {                                  \
    clearTest<NoConstructClass>(DEF_INT_VALS);                              \
  }

TESTS_CLEAR(s21Vector)

// --------------------------------------

template <typename T>
void beginTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(*actual.begin(), *expected.begin());
}

#define TESTS_BEGIN(suiteName)                                              \
  TEST(suiteName, uShortBegin) { beginTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intBegin) { beginTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleBegin) { beginTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassBegin) { beginTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringBegin) { beginTest<std::string>(DEF_STR_VALS); }

TESTS_BEGIN(s21Vector)

// --------------------------------------

template <typename T>
void endTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(&(*actual.end()), actual.data() + actual.size());
  EXPECT_EQ(&(*expected.end()), expected.data() + expected.size());
}

#define TESTS_END(suiteName)                                            \
  TEST(suiteName, uShortEnd) { endTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intEnd) { endTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleEnd) { endTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassEnd) { endTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringEnd) { endTest<std::string>(DEF_STR_VALS); }

TESTS_END(s21Vector)

// --------------------------------------

template <typename T>
void iteratorManualTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  auto itActual = actual.begin();
  auto itExpected = expected.begin();

  EXPECT_EQ(*itActual, *itExpected);

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    EXPECT_TRUE(itActual == itActual);
    EXPECT_FALSE(itActual != itActual);

    itActual++;
    itExpected++;

    EXPECT_EQ(*itActual, *itExpected);
  }

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    itActual--;
    itExpected--;

    EXPECT_EQ(*itActual, *itExpected);
  }
}

#define TESTS_ITERATOR_MANUAL(suiteName)              \
  TEST(suiteName, uShortIteratorManual) {             \
    iteratorManualTest<unsigned short>(DEF_INT_VALS); \
  }                                                   \
  TEST(suiteName, intIteratorManual) {                \
    iteratorManualTest<int>(DEF_INT_VALS);            \
  }                                                   \
  TEST(suiteName, doubleIteratorManual) {             \
    iteratorManualTest<double>(DEF_DBL_VALS);         \
  }                                                   \
  TEST(suiteName, MockClassIteratorManual) {          \
    iteratorManualTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                   \
  TEST(suiteName, stringIteratorManual) {             \
    iteratorManualTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_ITERATOR_MANUAL(s21Vector)

// --------------------------------------

template <typename T>
void iteratorForeachTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (auto i : actual) {
    // #DEFECT - std::is_same() not work
    // if (std::is_same<T, std::string>::value) {
    i = i * 2;
  }

  for (auto i : expected) {
    i = i * 2;
  }

  auto itActual = actual.begin();
  auto itExpected = expected.begin();

  EXPECT_EQ(*itActual, *itExpected);

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    itActual++;
    itExpected++;

    EXPECT_EQ(*itActual, *itExpected);
  }
}

#define TESTS_ITERATOR_FOREACH(suiteName)              \
  TEST(suiteName, uShortIteratorForeach) {             \
    iteratorForeachTest<unsigned short>(DEF_INT_VALS); \
  }                                                    \
  TEST(suiteName, intIteratorForeach) {                \
    iteratorForeachTest<int>(DEF_INT_VALS);            \
  }                                                    \
  TEST(suiteName, doubleIteratorForeach) {             \
    iteratorForeachTest<double>(DEF_DBL_VALS);         \
  }                                                    \
  TEST(suiteName, MockClassIteratorForeach) {          \
    iteratorForeachTest<MockClass>(DEF_MOCK_VALS);     \
  }

TESTS_ITERATOR_FOREACH(s21Vector)

// --------------------------------------

template <typename T>
void iteratorEqualTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualCopy(actual);

  EXPECT_EQ(actual.size(), actualCopy.size());
  EXPECT_EQ(actual.capacity(), actualCopy.capacity());
  EXPECT_NE(actual.data(), actualCopy.data());

  EXPECT_EQ(actual.empty(), actualCopy.empty());

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actualCopy.begin()));
}

#define TESTS_ITERATOR_EQUAL(suiteName)                                       \
  TEST(suiteName, uShortIteratorEqual) {                                      \
    iteratorEqualTest<unsigned short>(DEF_INT_VALS);                          \
  }                                                                           \
  TEST(suiteName, intIteratorEqual) { iteratorEqualTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doubleIteratorEqual) {                                      \
    iteratorEqualTest<double>(DEF_DBL_VALS);                                  \
  }                                                                           \
  TEST(suiteName, MockClassIteratorEqual) {                                   \
    iteratorEqualTest<MockClass>(DEF_MOCK_VALS);                              \
  }                                                                           \
  TEST(suiteName, stringIteratorEqual) {                                      \
    iteratorEqualTest<std::string>(DEF_STR_VALS);                             \
  }

TESTS_ITERATOR_EQUAL(s21Vector)

// --------------------------------------

template <typename T>
void swapTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  s21::vector<T> actualSwap;
  actualSwap.swap(actual);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(actual.capacity(), 0);
  EXPECT_EQ(actual.data(), nullptr);

  EXPECT_NE(actual.size(), actualSwap.size());
  EXPECT_NE(actual.capacity(), actualSwap.capacity());
  EXPECT_NE(actual.data(), actualSwap.data());

  EXPECT_NE(actual.empty(), actualSwap.empty());

  std::vector<T> expectedSwap;
  expectedSwap.swap(expected);

  EXPECT_EQ(expected.size(), 0);
  EXPECT_EQ(expected.capacity(), 0);
  EXPECT_EQ(expected.data(), nullptr);

  EXPECT_NE(expected.size(), expectedSwap.size());
  EXPECT_NE(expected.capacity(), expectedSwap.capacity());
  EXPECT_NE(expected.data(), expectedSwap.data());

  EXPECT_NE(expected.empty(), expectedSwap.empty());

  checkBasicFieldEmpty(actual, expected);

  EXPECT_EQ(actualSwap.size(), expectedSwap.size());
  EXPECT_EQ(actualSwap.capacity(), expectedSwap.capacity());
  EXPECT_NE(actualSwap.data(), expectedSwap.data());

  EXPECT_EQ(actualSwap.empty(), expectedSwap.empty());
}

#define TESTS_SWAP(suiteName)                                             \
  TEST(suiteName, uShortSwap) { swapTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intSwap) { swapTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleSwap) { swapTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassSwap) { swapTest<MockClass>(DEF_MOCK_VALS); }

TESTS_SWAP(s21Vector)

// --------------------------------------

template <typename T>
void atTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    EXPECT_EQ(actual.at(i), expected.at(i));
  }
}

#define TESTS_AT(suiteName)                                           \
  TEST(suiteName, uShortAt) { atTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intAt) { atTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleAt) { atTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassAt) { atTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringAt) { atTest<std::string>(DEF_STR_VALS); }

TESTS_AT(s21Vector)

// --------------------------------------

template <typename T>
void atChangeTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    actual.at(i) = actual.at(i) * 2;
    expected.at(i) = expected.at(i) * 2;
    EXPECT_EQ(actual.at(i), expected.at(i));
  }
}

#define TESTS_AT_CHANGE(suiteName)                                        \
  TEST(suiteName, uShortAtChange) {                                       \
    atChangeTest<unsigned short>(DEF_INT_VALS);                           \
  }                                                                       \
  TEST(suiteName, intAtChange) { atChangeTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleAtChange) { atChangeTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassAtChange) { atChangeTest<MockClass>(DEF_MOCK_VALS); }

TESTS_AT_CHANGE(s21Vector)

// --------------------------------------

template <typename T>
void constAtTest(const std::initializer_list<T>& items) {
  const s21::vector<T> actual(items);
  const std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    EXPECT_EQ(actual.at(i), expected.at(i));
  }
}

#define TESTS_CONST_AT(suiteName)                                              \
  TEST(suiteName, uShortConstAt) {                                             \
    constAtTest<unsigned short>(DEF_INT_VALS);                                 \
  }                                                                            \
  TEST(suiteName, intConstAt) { constAtTest<int>(DEF_INT_VALS); }              \
  TEST(suiteName, doubleConstAt) { constAtTest<double>(DEF_DBL_VALS); }        \
  TEST(suiteName, MockClassConstAt) { constAtTest<MockClass>(DEF_MOCK_VALS); } \
  TEST(suiteName, stringConstAt) { constAtTest<std::string>(DEF_STR_VALS); }

TESTS_CONST_AT(s21Vector)

// --------------------------------------

template <typename T>
void OperatorAtTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}

#define TESTS_OPEARTOR_AT(suiteName)                                          \
  TEST(suiteName, uShortOperatorAt) {                                         \
    OperatorAtTest<unsigned short>(DEF_INT_VALS);                             \
  }                                                                           \
  TEST(suiteName, intOperatorAt) { OperatorAtTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleOperatorAt) { OperatorAtTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassOperatorAt) {                                      \
    OperatorAtTest<MockClass>(DEF_MOCK_VALS);                                 \
  }                                                                           \
  TEST(suiteName, stringOperatorAt) {                                         \
    OperatorAtTest<std::string>(DEF_STR_VALS);                                \
  }

TESTS_OPEARTOR_AT(s21Vector)

// --------------------------------------

template <typename T>
void OperatorAtChangeTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    actual[i] = actual[i] * 2;
    expected[i] = expected[i] * 2;
    EXPECT_EQ(actual[i], expected[i]);
  }
}

#define TESTS_OPERATOR_AT_CHANGE(suiteName)             \
  TEST(suiteName, uShortOperatorAtChange) {             \
    OperatorAtChangeTest<unsigned short>(DEF_INT_VALS); \
  }                                                     \
  TEST(suiteName, intOperatorAtChange) {                \
    OperatorAtChangeTest<int>(DEF_INT_VALS);            \
  }                                                     \
  TEST(suiteName, doubleOperatorAtChange) {             \
    OperatorAtChangeTest<double>(DEF_DBL_VALS);         \
  }                                                     \
  TEST(suiteName, MockClassOperatorAtChange) {          \
    OperatorAtChangeTest<MockClass>(DEF_MOCK_VALS);     \
  }

TESTS_OPERATOR_AT_CHANGE(s21Vector)

// --------------------------------------

template <typename T>
void constOperatorAtTest(const std::initializer_list<T>& items) {
  const s21::vector<T> actual(items);
  const std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    EXPECT_EQ(actual[i], expected[i]);
  }
}

#define TESTS_CONST_OPERATOR_AT(suiteName)             \
  TEST(suiteName, uShortConstOperatorAt) {             \
    constOperatorAtTest<unsigned short>(DEF_INT_VALS); \
  }                                                    \
  TEST(suiteName, intConstOperatorAt) {                \
    constOperatorAtTest<int>(DEF_INT_VALS);            \
  }                                                    \
  TEST(suiteName, doubleConstOperatorAt) {             \
    constOperatorAtTest<double>(DEF_DBL_VALS);         \
  }                                                    \
  TEST(suiteName, MockClassConstOperatorAt) {          \
    constOperatorAtTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                    \
  TEST(suiteName, stringConstOperatorAt) {             \
    constOperatorAtTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_CONST_OPERATOR_AT(s21Vector)

// --------------------------------------

template <typename T>
void frontTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(actual.front(), expected.front());
}

#define TESTS_FRONT(suiteName)                                              \
  TEST(suiteName, uShortFront) { frontTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intFront) { frontTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleFront) { frontTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassFront) { frontTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringFront) { frontTest<std::string>(DEF_STR_VALS); }

TESTS_FRONT(s21Vector)

// --------------------------------------

template <typename T>
void backTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(actual.back(), expected.back());
}

#define TESTS_BACK(suiteName)                                             \
  TEST(suiteName, uShortBack) { backTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intBack) { backTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleBack) { backTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassBack) { backTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringBack) { backTest<std::string>(DEF_STR_VALS); }

TESTS_BACK(s21Vector)

// --------------------------------------

template <typename T>
void reserveTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  std::size_t newCapacity = 256;
  actual.reserve(newCapacity);
  expected.reserve(newCapacity);

  checkBasicField(actual, expected);

  EXPECT_EQ(actual.capacity(), newCapacity);
  EXPECT_EQ(expected.capacity(), newCapacity);

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }

  std::cout << "EXPECTED:" << std::endl;
  for (auto i : expected) {
    std::cout << i << std::endl;
  }
#endif

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  newCapacity = 1000;
  actual.reserve(newCapacity);
  expected.reserve(newCapacity);

  checkBasicField(actual, expected);

  EXPECT_EQ(actual.capacity(), newCapacity);
  EXPECT_EQ(expected.capacity(), newCapacity);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  newCapacity = 1;
  actual.reserve(newCapacity);
  expected.reserve(newCapacity);

  checkBasicField(actual, expected);

  EXPECT_NE(actual.capacity(), newCapacity);
  EXPECT_NE(expected.capacity(), newCapacity);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_RESERVE(suiteName)                                               \
  TEST(suiteName, uShortReserve) {                                             \
    reserveTest<unsigned short>(DEF_INT_VALS);                                 \
  }                                                                            \
  TEST(suiteName, intReserve) { reserveTest<int>(DEF_INT_VALS); }              \
  TEST(suiteName, doubleReserve) { reserveTest<double>(DEF_DBL_VALS); }        \
  TEST(suiteName, MockClassReserve) { reserveTest<MockClass>(DEF_MOCK_VALS); } \
  TEST(suiteName, stringReserve) { reserveTest<std::string>(DEF_STR_VALS); }   \
  TEST(suiteName, NoConstructClassReserve) {                                   \
    reserveTest<NoConstructClass>(DEF_INT_VALS);                               \
  }

TESTS_RESERVE(s21Vector)

// --------------------------------------

template <typename T>
void shrinkToFitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  actual.shrink_to_fit();
  expected.shrink_to_fit();

  checkBasicField(actual, expected);

  std::size_t newCapacity = 256;
  actual.reserve(newCapacity);
  expected.reserve(newCapacity);

  checkBasicField(actual, expected);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.shrink_to_fit();
  expected.shrink_to_fit();

  checkBasicField(actual, expected);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (auto i : items) {
    actual.push_back(i);
    expected.push_back(i);
  }

  newCapacity = 1000;
  actual.reserve(newCapacity);
  expected.reserve(newCapacity);

  checkBasicField(actual, expected);

  actual.shrink_to_fit();
  expected.shrink_to_fit();

  checkBasicField(actual, expected);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_SHRINK_TO_FIT(suiteName)                                    \
  TEST(suiteName, uShortShrinkToFit) {                                    \
    shrinkToFitTest<unsigned short>(DEF_INT_VALS);                        \
  }                                                                       \
  TEST(suiteName, intShrinkToFit) { shrinkToFitTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doubleShrinkToFit) {                                    \
    shrinkToFitTest<double>(DEF_DBL_VALS);                                \
  }                                                                       \
  TEST(suiteName, MockClassShrinkToFit) {                                 \
    shrinkToFitTest<MockClass>(DEF_MOCK_VALS);                            \
  }                                                                       \
  TEST(suiteName, stringShrinkToFit) {                                    \
    shrinkToFitTest<std::string>(DEF_STR_VALS);                           \
  }                                                                       \
  TEST(suiteName, NoConstructClassShrinkToFit) {                          \
    shrinkToFitTest<NoConstructClass>(DEF_INT_VALS);                      \
  }

TESTS_SHRINK_TO_FIT(s21Vector)

// --------------------------------------

template <typename T>
void pushBackTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (auto i : items) {
    actual.push_back(i);
    expected.push_back(i);
  }

  checkBasicField(actual, expected);

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_PUSH_BACK(suiteName)                                             \
  TEST(suiteName, uShortPushBack) {                                            \
    pushBackTest<unsigned short>(DEF_INT_VALS);                                \
  }                                                                            \
  TEST(suiteName, intPushBack) { pushBackTest<int>(DEF_INT_VALS); }            \
  TEST(suiteName, doublePushBack) { pushBackTest<double>(DEF_DBL_VALS); }      \
  TEST(suiteName, MockClassPushBack) {                                         \
    pushBackTest<MockClass>(DEF_MOCK_VALS);                                    \
  }                                                                            \
  TEST(suiteName, stringPushBack) { pushBackTest<std::string>(DEF_STR_VALS); } \
  TEST(suiteName, NoConstructClassPushBack) {                                  \
    pushBackTest<NoConstructClass>(DEF_INT_VALS);                              \
  }

TESTS_PUSH_BACK(s21Vector)

// --------------------------------------

template <typename T>
void pushBackEmptyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual;
  std::vector<T> expected;

  checkBasicFieldEmpty(actual, expected);

  for (auto i : items) {
    actual.push_back(i);
    expected.push_back(i);
  }

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_PUSH_BACK_EMPTY(suiteName)                                      \
  TEST(suiteName, uShortPushBackEmpty) {                                      \
    pushBackEmptyTest<unsigned short>(DEF_INT_VALS);                          \
  }                                                                           \
  TEST(suiteName, intPushBackEmpty) { pushBackEmptyTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doublePushBackEmpty) {                                      \
    pushBackEmptyTest<double>(DEF_DBL_VALS);                                  \
  }                                                                           \
  TEST(suiteName, MockClassPushBackEmpty) {                                   \
    pushBackEmptyTest<MockClass>(DEF_MOCK_VALS);                              \
  }                                                                           \
  TEST(suiteName, stringPushBackEmpty) {                                      \
    pushBackEmptyTest<std::string>(DEF_STR_VALS);                             \
  }                                                                           \
  TEST(suiteName, NoConstructClassPushBackEmpty) {                            \
    pushBackEmptyTest<NoConstructClass>(DEF_INT_VALS);                        \
  }

TESTS_PUSH_BACK_EMPTY(s21Vector)

// --------------------------------------

template <typename T>
void insertTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  auto actualIt = actual.insert(actual.begin() + 1, *items.begin());
  auto expectedIt = expected.insert(expected.begin() + 1, *items.begin());

  checkBasicField(actual, expected);

  EXPECT_TRUE(actualIt == (actual.begin() + 1));
  EXPECT_TRUE(expectedIt == (expected.begin() + 1));

  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.insert(actual.begin() + 3, *items.begin());
  expected.insert(expected.begin() + 3, *items.begin());

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.insert(actual.begin(), *items.begin());
  expected.insert(expected.begin(), *items.begin());

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  auto actualIt_2 = actual.insert(actual.end() - 1, *items.begin());
  auto expectedIt_2 = expected.insert(expected.end() - 1, *items.begin());

  EXPECT_TRUE(actualIt_2 == actual.end() - 2);
  EXPECT_TRUE(expectedIt_2 == expected.end() - 2);

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.insert(actual.end() - 3, *(items.end() - 1));
  expected.insert(expected.end() - 3, *(items.end() - 1));

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (std::size_t i = 0; i < 100; i++) {
    actual.insert(actual.end() - 3, *(items.end() - 1));
    expected.insert(expected.end() - 3, *(items.end() - 1));

    checkBasicField(actual, expected);
    EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
  }

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_INSERT(suiteName)                                               \
  TEST(suiteName, uShortInsert) { insertTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intInsert) { insertTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleInsert) { insertTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassInsert) { insertTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringInsert) { insertTest<std::string>(DEF_STR_VALS); }    \
  TEST(suiteName, NoConstructClassInsert) {                                   \
    insertTest<NoConstructClass>(DEF_INT_VALS);                               \
  }

TESTS_INSERT(s21Vector)

// --------------------------------------

template <typename T>
void insertEmptyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual;
  std::vector<T> expected;

  checkBasicFieldEmpty(actual, expected);

  actual.insert(actual.begin(), *items.begin());
  expected.insert(expected.begin(), *items.begin());

  actual.insert(actual.begin(), *items.begin());
  expected.insert(expected.begin(), *items.begin());

  for (std::size_t i = 0; i < 100; i++) {
    actual.insert(actual.begin() + 1, *(items.end() - 1));
    expected.insert(expected.begin() + 1, *(items.end() - 1));

    checkBasicField(actual, expected);
    EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
  }

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_INSERT_EMPTY(suiteName)                                     \
  TEST(suiteName, uShortInsertEmpty) {                                    \
    insertEmptyTest<unsigned short>(DEF_INT_VALS);                        \
  }                                                                       \
  TEST(suiteName, intInsertEmpty) { insertEmptyTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doubleInsertEmpty) {                                    \
    insertEmptyTest<double>(DEF_DBL_VALS);                                \
  }                                                                       \
  TEST(suiteName, MockClassInsertEmpty) {                                 \
    insertEmptyTest<MockClass>(DEF_MOCK_VALS);                            \
  }                                                                       \
  TEST(suiteName, stringInsertEmpty) {                                    \
    insertEmptyTest<std::string>(DEF_STR_VALS);                           \
  }                                                                       \
  TEST(suiteName, NoConstructClassInsertEmpty) {                          \
    insertEmptyTest<NoConstructClass>(DEF_INT_VALS);                      \
  }

TESTS_INSERT_EMPTY(s21Vector)

// --------------------------------------

template <typename T>
void insertManyBackTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);

  auto endIndex = actual.size();

  actual.insert_many_back(*items.begin(), *(items.begin() + 1),
                          *(items.begin() + 2));

  EXPECT_EQ(*items.begin(), actual[endIndex]);
  EXPECT_EQ(*(items.begin() + 1), actual[endIndex + 1]);
  EXPECT_EQ(*(items.begin() + 2), actual[endIndex + 2]);
}

#define TESTS_INSERT_MANY_BACK(suiteName)               \
  TEST(suiteName, uShortInsertManyBack) {               \
    insertManyBackTest<unsigned short>(DEF_INT_VALS);   \
  }                                                     \
  TEST(suiteName, intInsertManyBack) {                  \
    insertManyBackTest<int>(DEF_INT_VALS);              \
  }                                                     \
  TEST(suiteName, doubleInsertManyBack) {               \
    insertManyBackTest<double>(DEF_DBL_VALS);           \
  }                                                     \
  TEST(suiteName, MockClassInsertManyBack) {            \
    insertManyBackTest<MockClass>(DEF_MOCK_VALS);       \
  }                                                     \
  TEST(suiteName, stringInsertManyBack) {               \
    insertManyBackTest<std::string>(DEF_STR_VALS);      \
  }                                                     \
  TEST(suiteName, NoConstructClassInsertManyBack) {     \
    insertManyBackTest<NoConstructClass>(DEF_INT_VALS); \
  }

TESTS_INSERT_MANY_BACK(s21Vector)

// --------------------------------------

template <typename T>
void insertManyBackEmptyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual;

  auto endIndex = actual.size();

  actual.insert_many_back(*items.begin(), *(items.begin() + 1),
                          *(items.begin() + 2));

  EXPECT_EQ(*items.begin(), actual[endIndex]);
  EXPECT_EQ(*(items.begin() + 1), actual[endIndex + 1]);
  EXPECT_EQ(*(items.begin() + 2), actual[endIndex + 2]);
}

#define TESTS_INSERT_MANY_BACK_EMPTY(suiteName)              \
  TEST(suiteName, uShortInsertManyBackEmpty) {               \
    insertManyBackEmptyTest<unsigned short>(DEF_INT_VALS);   \
  }                                                          \
  TEST(suiteName, intInsertManyBackEmpty) {                  \
    insertManyBackEmptyTest<int>(DEF_INT_VALS);              \
  }                                                          \
  TEST(suiteName, doubleInsertManyBackEmpty) {               \
    insertManyBackEmptyTest<double>(DEF_DBL_VALS);           \
  }                                                          \
  TEST(suiteName, MockClassInsertManyBackEmpty) {            \
    insertManyBackEmptyTest<MockClass>(DEF_MOCK_VALS);       \
  }                                                          \
  TEST(suiteName, stringInsertManyBackEmpty) {               \
    insertManyBackEmptyTest<std::string>(DEF_STR_VALS);      \
  }                                                          \
  TEST(suiteName, NoConstructClassInsertManyBackEmpty) {     \
    insertManyBackEmptyTest<NoConstructClass>(DEF_INT_VALS); \
  }

TESTS_INSERT_MANY_BACK_EMPTY(s21Vector)

// --------------------------------------

template <typename T>
void insertManyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);

  std::size_t posIndex = 2;

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }
#endif

  actual.insert_many(actual.begin() + posIndex, *items.begin(),
                     *(items.begin() + 1), *(items.begin() + 2));

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }
#endif

  EXPECT_EQ(*items.begin(), actual[posIndex]);
  EXPECT_EQ(*(items.begin() + 1), actual[posIndex + 1]);
  EXPECT_EQ(*(items.begin() + 2), actual[posIndex + 2]);

  posIndex = 1;
  actual.insert_many(actual.begin() + posIndex, *items.begin());

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }
#endif

  EXPECT_EQ(*items.begin(), actual[posIndex]);

  actual.insert_many(actual.end() - 1, *(items.end() - 1), *(items.end() - 1));
  EXPECT_EQ(*(items.end() - 1), *(actual.end() - 1));
  EXPECT_EQ(*(items.end() - 1), *(actual.end() - 2));
}

#define TESTS_INSERT_MANY(suiteName)                                          \
  TEST(suiteName, uShortInsertMany) {                                         \
    insertManyTest<unsigned short>(DEF_INT_VALS);                             \
  }                                                                           \
  TEST(suiteName, intInsertMany) { insertManyTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleInsertMany) { insertManyTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassInsertMany) {                                      \
    insertManyTest<MockClass>(DEF_MOCK_VALS);                                 \
  }                                                                           \
  TEST(suiteName, stringInsertMany) {                                         \
    insertManyTest<std::string>(DEF_STR_VALS);                                \
  }                                                                           \
  TEST(suiteName, NoConstructClassInsertMany) {                               \
    insertManyTest<NoConstructClass>(DEF_INT_VALS);                           \
  }

TESTS_INSERT_MANY(s21Vector)

// --------------------------------------

template <typename T>
void insertManyEmptyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual;

  std::size_t posIndex = 0;

  actual.insert_many(actual.begin() + posIndex, *items.begin(),
                     *(items.begin() + 1), *(items.begin() + 2));

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }
#endif

  EXPECT_EQ(*items.begin(), actual[posIndex]);
  EXPECT_EQ(*(items.begin() + 1), actual[posIndex + 1]);
  EXPECT_EQ(*(items.begin() + 2), actual[posIndex + 2]);
}

#define TESTS_INSERT_MANY_EMPTY(suiteName)               \
  TEST(suiteName, uShortInsertManyEmpty) {               \
    insertManyEmptyTest<unsigned short>(DEF_INT_VALS);   \
  }                                                      \
  TEST(suiteName, intInsertManyEmpty) {                  \
    insertManyEmptyTest<int>(DEF_INT_VALS);              \
  }                                                      \
  TEST(suiteName, doubleInsertManyEmpty) {               \
    insertManyEmptyTest<double>(DEF_DBL_VALS);           \
  }                                                      \
  TEST(suiteName, MockClassInsertManyEmpty) {            \
    insertManyEmptyTest<MockClass>(DEF_MOCK_VALS);       \
  }                                                      \
  TEST(suiteName, stringInsertManyEmpty) {               \
    insertManyEmptyTest<std::string>(DEF_STR_VALS);      \
  }                                                      \
  TEST(suiteName, NoConstructClassInsertManyEmpty) {     \
    insertManyEmptyTest<NoConstructClass>(DEF_INT_VALS); \
  }

TESTS_INSERT_MANY_EMPTY(s21Vector)

// --------------------------------------

template <typename T>
void popBackTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  actual.pop_back();
  expected.pop_back();

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.push_back(*items.begin());
  expected.push_back(*items.begin());

  actual.pop_back();
  expected.pop_back();

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (auto i : items) {
    actual.push_back(i);
    expected.push_back(i);
  }

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (std::size_t i = 0; i < items.size(); i++) {
    actual.pop_back();
    expected.pop_back();
  }

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.pop_back();
  expected.pop_back();

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_POP_BACK(suiteName)                                              \
  TEST(suiteName, uShortPopBack) {                                             \
    popBackTest<unsigned short>(DEF_INT_VALS);                                 \
  }                                                                            \
  TEST(suiteName, intPopBack) { popBackTest<int>(DEF_INT_VALS); }              \
  TEST(suiteName, doublePopBack) { popBackTest<double>(DEF_DBL_VALS); }        \
  TEST(suiteName, MockClassPopBack) { popBackTest<MockClass>(DEF_MOCK_VALS); } \
  TEST(suiteName, stringPopBack) { popBackTest<std::string>(DEF_STR_VALS); }

TESTS_POP_BACK(s21Vector)

// --------------------------------------

template <typename T>
void eraseTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  actual.erase(actual.begin());
  expected.erase(expected.begin());

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }

  std::cout << "EXPECTED:" << std::endl;
  for (auto i : expected) {
    std::cout << i << std::endl;
  }
#endif

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  actual.push_back(*(items.end() - 2));
  expected.push_back(*(items.end() - 2));

  actual.erase(actual.begin() + 1);
  expected.erase(expected.begin() + 1);

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }

  std::cout << "EXPECTED:" << std::endl;
  for (auto i : expected) {
    std::cout << i << std::endl;
  }
#endif

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (auto i : items) {
    actual.push_back(i);
    expected.push_back(i);
  }

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }

  std::cout << "EXPECTED:" << std::endl;
  for (auto i : expected) {
    std::cout << i << std::endl;
  }
#endif

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (std::size_t i = 0; i < items.size(); i++) {
    actual.erase(actual.end() - 1);
    expected.erase(expected.end() - 1);
  }

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }

  std::cout << "EXPECTED:" << std::endl;
  for (auto i : expected) {
    std::cout << i << std::endl;
  }
#endif

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

  for (std::size_t i = 0; i < actual.size(); i++) {
    actual.erase(actual.begin());
    expected.erase(expected.begin());
  }

#ifdef DEBUG
  std::cout << "ACTUAL:" << std::endl;
  for (auto i : actual) {
    std::cout << i << std::endl;
  }

  std::cout << "EXPECTED:" << std::endl;
  for (auto i : expected) {
    std::cout << i << std::endl;
  }
#endif

  checkBasicField(actual, expected);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_ERASE(suiteName)                                              \
  TEST(suiteName, uShortErase) { eraseTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intErase) { eraseTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleErase) { eraseTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassErase) { eraseTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringErase) { eraseTest<std::string>(DEF_STR_VALS); }

TESTS_ERASE(s21Vector)

// --------------------------------------

/* EDGE */

template <typename T>
void operatorInitCopySelfTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  actual = actual;

  std::vector<T> expected(items);
  expected = expected;

  checkBasicField(actual, expected);

  EXPECT_TRUE(actual == actual);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));
}

#define TESTS_EDGE_OPERATOR_COPY_SELF_INIT(suiteName)       \
  TEST(suiteName, uShortOperatorCopyInitSelt) {             \
    operatorInitCopySelfTest<unsigned short>(DEF_INT_VALS); \
  }                                                         \
  TEST(suiteName, intOperatorCopyInitSelt) {                \
    operatorInitCopySelfTest<int>(DEF_INT_VALS);            \
  }                                                         \
  TEST(suiteName, doubleOperatorCopyInitSelt) {             \
    operatorInitCopySelfTest<double>(DEF_DBL_VALS);         \
  }                                                         \
  TEST(suiteName, MockClassOperatorCopyInitSelt) {          \
    operatorInitCopySelfTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                         \
  TEST(suiteName, stringOperatorCopyInitSelt) {             \
    operatorInitCopySelfTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_EDGE_OPERATOR_COPY_SELF_INIT(s21Vector)

// --------------------------------------

// #NOTE: std::vector does not check the case of self-assignment
template <typename T>
void operatorInitMoveSelfTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  actual = std::move(actual);

  EXPECT_TRUE(actual == actual);
}

#define TESTS_EDGE_OPERATOR_MOVE_SELF_INIT(suiteName)       \
  TEST(suiteName, uShortOperatorMoveSelfInit) {             \
    operatorInitMoveSelfTest<unsigned short>(DEF_INT_VALS); \
  }                                                         \
  TEST(suiteName, intOperatorMoveSelfInit) {                \
    operatorInitMoveSelfTest<int>(DEF_INT_VALS);            \
  }                                                         \
  TEST(suiteName, doubleOperatorMoveSelfInit) {             \
    operatorInitMoveSelfTest<double>(DEF_DBL_VALS);         \
  }                                                         \
  TEST(suiteName, MockClassOperatorMoveSelfInit) {          \
    operatorInitMoveSelfTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                         \
  TEST(suiteName, stringOperatorMoveSelfInit) {             \
    operatorInitMoveSelfTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_EDGE_OPERATOR_MOVE_SELF_INIT(s21Vector)

// --------------------------------------

// #NOTE: erase in empty std::vector is undefined behavior
template <typename T>
void eraseEmptyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual;
  s21::vector<T> actualInit = actual;

  checkBasicField(actual, actualInit);

  actual.erase(actual.begin());
  actualInit.erase(actualInit.begin());

  checkBasicField(actual, actualInit);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actualInit.begin()));

  actual.push_back(*(items.end() - 2));
  actualInit.push_back(*(items.end() - 2));

  actual.erase(actual.begin());
  actualInit.erase(actualInit.begin());

  checkBasicField(actual, actualInit);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actualInit.begin()));

  actual.erase(actual.end());
  actualInit.erase(actualInit.end());

  checkBasicField(actual, actualInit);
  EXPECT_TRUE(std::equal(actual.begin(), actual.end(), actualInit.begin()));
}

#define TESTS_EDGE_ERASE_EMPTY(suiteName)                                     \
  TEST(suiteName, uShortEraseEmpty) {                                         \
    eraseEmptyTest<unsigned short>(DEF_INT_VALS);                             \
  }                                                                           \
  TEST(suiteName, intEraseEmpty) { eraseEmptyTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleEraseEmpty) { eraseEmptyTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassEraseEmpty) {                                      \
    eraseEmptyTest<MockClass>(DEF_MOCK_VALS);                                 \
  }                                                                           \
  TEST(suiteName, stringEraseEmpty) {                                         \
    eraseEmptyTest<std::string>(DEF_STR_VALS);                                \
  }

TESTS_EDGE_ERASE_EMPTY(s21Vector)

// --------------------------------------

/* ANOMALY */

template <typename T>
void sizeErrorInitTest() {
  const std::size_t size = s21::vector<T>::max_size() + 1;

  EXPECT_THROW({ s21::vector<T> actual(size); }, std::length_error);
}

#define TESTS_ANOMALY_SIZE_ERROR_INIT(suiteName)                              \
  TEST(suiteName, uShortSizeErrorInit) {                                      \
    sizeErrorInitTest<unsigned short>();                                      \
  }                                                                           \
  TEST(suiteName, intSizeErrorInit) { sizeErrorInitTest<int>(); }             \
  TEST(suiteName, doubleSizeErrorInit) { sizeErrorInitTest<double>(); }       \
  TEST(suiteName, MockClassSizeErrorInit) { sizeErrorInitTest<MockClass>(); } \
  TEST(suiteName, stringSizeErrorInit) { sizeErrorInitTest<std::string>(); }

TESTS_ANOMALY_SIZE_ERROR_INIT(s21Vector)

// --------------------------------------

template <typename T>
void atOutOfRangeTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  std::size_t pos = actual.size();

  EXPECT_THROW({ actual.at(pos); }, std::out_of_range);

  EXPECT_THROW({ expected.at(pos); }, std::out_of_range);

  pos = actual.size() + 2;

  EXPECT_THROW({ actual.at(pos); }, std::out_of_range);

  EXPECT_THROW({ expected.at(pos); }, std::out_of_range);
}

#define TESTS_ANOMALY_AT_OUT_RANGE(suiteName)       \
  TEST(suiteName, uShortAnomalyAtOutRange) {        \
    atOutOfRangeTest<unsigned short>(DEF_INT_VALS); \
  }                                                 \
  TEST(suiteName, intAnomalyAtOutRange) {           \
    atOutOfRangeTest<int>(DEF_INT_VALS);            \
  }                                                 \
  TEST(suiteName, doubleAnomalyAtOutRange) {        \
    atOutOfRangeTest<double>(DEF_DBL_VALS);         \
  }                                                 \
  TEST(suiteName, MockClassAnomalyAtOutRange) {     \
    atOutOfRangeTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                 \
  TEST(suiteName, stringAnomalyAtOutRange) {        \
    atOutOfRangeTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_ANOMALY_AT_OUT_RANGE(s21Vector)

// --------------------------------------

template <typename T>
void constAtOutOfRangeTest(const std::initializer_list<T>& items) {
  const s21::vector<T> actual(items);
  const std::vector<T> expected(items);

  checkBasicField(actual, expected);

  std::size_t pos = actual.size();

  EXPECT_THROW({ actual.at(pos); }, std::out_of_range);

  EXPECT_THROW({ expected.at(pos); }, std::out_of_range);

  pos = actual.size() + 2;

  EXPECT_THROW({ actual.at(pos); }, std::out_of_range);

  EXPECT_THROW({ expected.at(pos); }, std::out_of_range);
}

#define TESTS_ANOMALY_CONST_AT_OUT_RANGE(suiteName)      \
  TEST(suiteName, uShortAnomalyConstAtOutRange) {        \
    constAtOutOfRangeTest<unsigned short>(DEF_INT_VALS); \
  }                                                      \
  TEST(suiteName, intAnomalyConstAtOutRange) {           \
    constAtOutOfRangeTest<int>(DEF_INT_VALS);            \
  }                                                      \
  TEST(suiteName, doubleAnomalyConstAtOutRange) {        \
    constAtOutOfRangeTest<double>(DEF_DBL_VALS);         \
  }                                                      \
  TEST(suiteName, MockClassAnomalyConstAtOutRange) {     \
    constAtOutOfRangeTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                      \
  TEST(suiteName, stringAnomalyConstAtOutRange) {        \
    constAtOutOfRangeTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_ANOMALY_CONST_AT_OUT_RANGE(s21Vector)

// --------------------------------------

// #NOTE: very big alloc ruined valgrind check
/*
template<typename T>
void reserveOutOfRangeTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);

  std::size_t size = s21::vector<T>::max_size() + 1;

  EXPECT_THROW({
    actual.reserve(size);
  }, std::length_error);
}

#define TESTS_ANOMALY_RESERVE_OUT_RANGE(suiteName) \
TEST(suiteName, uShortReserveOutOfRange) { reserveOutOfRangeTest<unsigned
short>(DEF_INT_VALS); } \
TEST(suiteName, intReserveOutOfRange) {
reserveOutOfRangeTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleReserveOutOfRange) {
reserveOutOfRangeTest<double>(DEF_DBL_VALS); } \

TESTS_ANOMALY_RESERVE_OUT_RANGE(s21Vector)

// --------------------------------------

template<typename T>
void pushBackOutOfRangeTest(const std::initializer_list<T>& items) {
  std::size_t size = s21::vector<T>::max_size();
  s21::vector<T> actual(size);

  EXPECT_THROW({
    actual.push_back(*items.begin());
  }, std::length_error);
}

#define TESTS_ANOMALY_PUSH_BACK_OUT_RANGE(suiteName) \
TEST(suiteName, uShortPushBackOutOfRange) { pushBackOutOfRangeTest<unsigned
short>(DEF_INT_VALS); } \
TEST(suiteName, intPushBackOutOfRange) {
pushBackOutOfRangeTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doublePushBackOutOfRange) {
pushBackOutOfRangeTest<double>(DEF_DBL_VALS); } \

TESTS_ANOMALY_PUSH_BACK_OUT_RANGE(s21Vector)
*/

// #NOTE: std::vector does not check empty when pop_back - UB
template <typename T>
void popBackEmptyTest() {
  s21::vector<T> actual;
  std::vector<T> expected;

  checkBasicFieldEmpty(actual, expected);

  EXPECT_THROW({ actual.pop_back(); }, std::out_of_range);
}

#define TESTS_ANOMALY_POP_BACK_EMPTY(suiteName)                               \
  TEST(suiteName, uShortPopBackEmpty) { popBackEmptyTest<unsigned short>(); } \
  TEST(suiteName, intPopBackEmpty) { popBackEmptyTest<int>(); }               \
  TEST(suiteName, doublePopBackEmpty) { popBackEmptyTest<double>(); }         \
  TEST(suiteName, MockClassPopBackEmpty) { popBackEmptyTest<MockClass>(); }   \
  TEST(suiteName, stringPopBackEmpty) { popBackEmptyTest<std::string>(); }

TESTS_ANOMALY_POP_BACK_EMPTY(s21Vector)

// --------------------------------------