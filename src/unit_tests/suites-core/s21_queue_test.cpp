#include "core/s21_queue.h"

#include <algorithm>
#include <queue>
#include <string>
#include <type_traits>

#include "s21_core_tests.h"

template <typename T>
void checkBasicField(const s21::queue<T>& actual,
                     const std::queue<T>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T>
void checkBasicField(const s21::queue<T>& actual,
                     const s21::queue<T>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.empty(), expected.empty());
}

template <typename T>
void checkDataEQ(s21::queue<T> actual, std::queue<T> expected) {
  while (!actual.empty()) {
    EXPECT_EQ(actual.size(), expected.size());
    EXPECT_EQ(actual.empty(), expected.empty());

    EXPECT_EQ(actual.front(), expected.front());
    actual.pop();
    expected.pop();
  }
}

template <typename T>
void checkDataEQ(s21::queue<T> actual, s21::queue<T> expected) {
  while (!actual.empty()) {
    EXPECT_EQ(actual.size(), expected.size());
    EXPECT_EQ(actual.empty(), expected.empty());

    EXPECT_EQ(actual.front(), expected.front());
    actual.pop();
    expected.pop();
  }
}

template <typename T>
void checkDataNE(s21::queue<T> actual, std::queue<T> expected) {
  while (!actual.empty()) {
    EXPECT_NE(actual.front(), expected.front());
    actual.pop();
    expected.pop();
  }
}

template <typename T>
void checkDataNE(s21::queue<T> actual, s21::queue<T> expected) {
  while (!actual.empty()) {
    EXPECT_NE(actual.front(), expected.front());
    actual.pop();
    expected.pop();
  }
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
void queueDefaultInitAsContTest() {
  s21::IContainer* ct = new s21::queue<T>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_EMPTY_INIT_AS_CONT(suiteName)                                  \
  TEST(suiteName, uShortEmptyInitAsCont) {                                   \
    queueDefaultInitAsContTest<unsigned short>();                            \
  }                                                                          \
  TEST(suiteName, intEmptyInitAsCont) { queueDefaultInitAsContTest<int>(); } \
  TEST(suiteName, doubleEmptyInitAsCont) {                                   \
    queueDefaultInitAsContTest<double>();                                    \
  }                                                                          \
  TEST(suiteName, MockClassEmptyInitAsCont) {                                \
    queueDefaultInitAsContTest<MockClass>();                                 \
  }                                                                          \
  TEST(suiteName, stringEmptyInitAsCont) {                                   \
    queueDefaultInitAsContTest<std::string>();                               \
  }                                                                          \
  TEST(suiteName, NoConstructClassEmptyInitAsCont) {                         \
    queueDefaultInitAsContTest<NoConstructClass>();                          \
  }

TESTS_EMPTY_INIT_AS_CONT(s21Queue)

// --------------------------------------

template <typename T>
void queueDefaultInitTest() {
  s21::queue<T> actual;
  std::queue<T> expected;

  checkBasicField(actual, expected);
}

#define TESTS_EMPTY_INIT(suiteName)                                            \
  TEST(suiteName, uShortEmptyInit) { queueDefaultInitTest<unsigned short>(); } \
  TEST(suiteName, intEmptyInit) { queueDefaultInitTest<int>(); }               \
  TEST(suiteName, doubleEmptyInit) { queueDefaultInitTest<double>(); }         \
  TEST(suiteName, MockClassEmptyInit) { queueDefaultInitTest<MockClass>(); }   \
  TEST(suiteName, stringEmptyInit) { queueDefaultInitTest<std::string>(); }    \
  TEST(suiteName, NoConstructClassEmptyInit) {                                 \
    queueDefaultInitTest<NoConstructClass>();                                  \
  }

TESTS_EMPTY_INIT(s21Queue)

// --------------------------------------

template <typename T>
void queueListInitTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  std::queue<T> expected(items);

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);
}

#define TESTS_LIST_INIT(suiteName)                                             \
  TEST(suiteName, uShortListInit) {                                            \
    queueListInitTest<unsigned short>(DEF_INT_VALS);                           \
  }                                                                            \
  TEST(suiteName, intListInit) { queueListInitTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleListInit) { queueListInitTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassListInit) {                                         \
    queueListInitTest<MockClass>(DEF_MOCK_VALS);                               \
  }                                                                            \
  TEST(suiteName, stringListInit) {                                            \
    queueListInitTest<std::string>(DEF_STR_VALS);                              \
  }                                                                            \
  TEST(suiteName, NoConstructClassListInit) {                                  \
    queueListInitTest<NoConstructClass>(DEF_INT_VALS);                         \
  }

TESTS_LIST_INIT(s21Queue)

// --------------------------------------

template <typename T>
void queueCopyInitTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  s21::queue<T> actualCopy(actual);

  std::queue<T> expected(items);
  std::queue<T> expectedCopy(items);

  checkBasicField(actual, expected);
  checkBasicField(actualCopy, expectedCopy);

  checkDataEQ(actual, actualCopy);
  checkDataEQ(actual, expectedCopy);
  checkDataEQ(actual, expected);
}

#define TESTS_COPY_INIT(suiteName)                                             \
  TEST(suiteName, uShortCopyInit) {                                            \
    queueCopyInitTest<unsigned short>(DEF_INT_VALS);                           \
  }                                                                            \
  TEST(suiteName, intCopyInit) { queueCopyInitTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleCopyInit) { queueCopyInitTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassCopyInit) {                                         \
    queueCopyInitTest<MockClass>(DEF_MOCK_VALS);                               \
  }                                                                            \
  TEST(suiteName, stringCopyInit) {                                            \
    queueCopyInitTest<std::string>(DEF_STR_VALS);                              \
  }                                                                            \
  TEST(suiteName, NoConstructClassCopyInit) {                                  \
    queueCopyInitTest<NoConstructClass>(DEF_INT_VALS);                         \
  }

TESTS_COPY_INIT(s21Queue)

// --------------------------------------

template <typename T>
void queueMoveInitTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  s21::queue<T> actualMove(std::move(actual));

  std::queue<T> expected(items);
  std::queue<T> expectedMove(std::move(expected));

  checkBasicField(actualMove, expectedMove);

  checkDataNE(actual, actualMove);
  checkDataEQ(actualMove, expectedMove);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(expected.size(), 0);
}

#define TESTS_MOVE_INIT(suiteName)                                             \
  TEST(suiteName, uShortMoveInit) {                                            \
    queueMoveInitTest<unsigned short>(DEF_INT_VALS);                           \
  }                                                                            \
  TEST(suiteName, intMoveInit) { queueMoveInitTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleMoveInit) { queueMoveInitTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassMoveInit) {                                         \
    queueMoveInitTest<MockClass>(DEF_MOCK_VALS);                               \
  }                                                                            \
  TEST(suiteName, stringMoveInit) {                                            \
    queueMoveInitTest<std::string>(DEF_STR_VALS);                              \
  }                                                                            \
  TEST(suiteName, NoConstructClassMoveInit) {                                  \
    queueMoveInitTest<NoConstructClass>(DEF_INT_VALS);                         \
  }

TESTS_MOVE_INIT(s21Queue)

// --------------------------------------

template <typename T>
void queueOperatorCopyTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  s21::queue<T> actualCopy;
  actualCopy = actual;

  std::queue<T> expected(items);
  std::queue<T> expectedCopy;
  expectedCopy = expected;

  checkBasicField(actual, actualCopy);
  checkDataEQ(actual, actualCopy);

  checkBasicField(actualCopy, expectedCopy);
  checkDataEQ(actualCopy, expectedCopy);
}

#define TESTS_OPERATOR_COPY(suiteName)                   \
  TEST(suiteName, uShortOperatorCopy) {                  \
    queueOperatorCopyTest<unsigned short>(DEF_INT_VALS); \
  }                                                      \
  TEST(suiteName, intOperatorCopy) {                     \
    queueOperatorCopyTest<int>(DEF_INT_VALS);            \
  }                                                      \
  TEST(suiteName, doubleOperatorCopy) {                  \
    queueOperatorCopyTest<double>(DEF_DBL_VALS);         \
  }                                                      \
  TEST(suiteName, MockClassOperatorCopy) {               \
    queueOperatorCopyTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                      \
  TEST(suiteName, stringOperatorCopy) {                  \
    queueOperatorCopyTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_OPERATOR_COPY(s21Queue)

// --------------------------------------

template <typename T>
void queueOperatorMoveTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  s21::queue<T> actualMove;
  actualMove = std::move(actual);

  std::queue<T> expected(items);
  std::queue<T> expectedMove;
  expectedMove = std::move(expected);

  checkBasicField(actualMove, expectedMove);

  checkDataNE(actual, actualMove);
  checkDataEQ(actualMove, expectedMove);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(expected.size(), 0);
}

#define TESTS_OPERATOR_MOVE(suiteName)                   \
  TEST(suiteName, uShortOperatorMove) {                  \
    queueOperatorMoveTest<unsigned short>(DEF_INT_VALS); \
  }                                                      \
  TEST(suiteName, intOperatorMove) {                     \
    queueOperatorMoveTest<int>(DEF_INT_VALS);            \
  }                                                      \
  TEST(suiteName, doubleOperatorMove) {                  \
    queueOperatorMoveTest<double>(DEF_DBL_VALS);         \
  }                                                      \
  TEST(suiteName, MockClassOperatorMove) {               \
    queueOperatorMoveTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                      \
  TEST(suiteName, stringOperatorMove) {                  \
    queueOperatorMoveTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_OPERATOR_MOVE(s21Queue)

// --------------------------------------

template <typename T>
void queueSwapTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  std::queue<T> expected(items);

  checkBasicField(actual, expected);

  s21::queue<T> actualSwap;
  actualSwap.swap(actual);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_NE(actual.size(), actualSwap.size());
  EXPECT_NE(actual.empty(), actualSwap.empty());

  std::queue<T> expectedSwap;
  expectedSwap.swap(expected);

  EXPECT_EQ(expected.size(), 0);
  EXPECT_NE(expected.size(), expectedSwap.size());
  EXPECT_NE(expected.empty(), expectedSwap.empty());

  checkBasicField(actual, expected);
  checkDataEQ(actualSwap, expectedSwap);
}

#define TESTS_SWAP(suiteName)                                                  \
  TEST(suiteName, uShortSwap) { queueSwapTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intSwap) { queueSwapTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleSwap) { queueSwapTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassSwap) { queueSwapTest<MockClass>(DEF_MOCK_VALS); }

TESTS_SWAP(s21Queue)

// --------------------------------------

template <typename T>
void queueFrontTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  std::queue<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(actual.front(), expected.front());
}

#define TESTS_FRONT(suiteName)                                           \
  TEST(suiteName, uShortFront) {                                         \
    queueFrontTest<unsigned short>(DEF_INT_VALS);                        \
  }                                                                      \
  TEST(suiteName, intFront) { queueFrontTest<int>(DEF_INT_VALS); }       \
  TEST(suiteName, doubleFront) { queueFrontTest<double>(DEF_DBL_VALS); } \
  TEST(suiteName, MockClassFront) {                                      \
    queueFrontTest<MockClass>(DEF_MOCK_VALS);                            \
  }                                                                      \
  TEST(suiteName, stringFront) { queueFrontTest<std::string>(DEF_STR_VALS); }

TESTS_FRONT(s21Queue)

// --------------------------------------

template <typename T>
void queueBackTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  std::queue<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(actual.back(), expected.back());
}

#define TESTS_BACK(suiteName)                                                  \
  TEST(suiteName, uShortBack) { queueBackTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intBack) { queueBackTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doubleBack) { queueBackTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassBack) { queueBackTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringBack) { queueBackTest<std::string>(DEF_STR_VALS); }

TESTS_BACK(s21Queue)

// --------------------------------------

template <typename T>
void queuePushTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  std::queue<T> expected(items);

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  for (auto i : items) {
    actual.push(i);
    expected.push(i);
  }

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);
}

#define TESTS_PUSH(suiteName)                                                  \
  TEST(suiteName, uShortPush) { queuePushTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intPush) { queuePushTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doublePush) { queuePushTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassPush) { queuePushTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringPush) { queuePushTest<std::string>(DEF_STR_VALS); }    \
  TEST(suiteName, NoConstructClassPush) {                                      \
    queuePushTest<NoConstructClass>(DEF_INT_VALS);                             \
  }

TESTS_PUSH(s21Queue)

// --------------------------------------

template <typename T>
void queuePushEmptyTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual;
  std::queue<T> expected;

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  for (auto i : items) {
    actual.push(i);
    expected.push(i);
  }

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);
}

#define TESTS_PUSH_EMPTY(suiteName)                                        \
  TEST(suiteName, uShortPushEmpty) {                                       \
    queuePushEmptyTest<unsigned short>(DEF_INT_VALS);                      \
  }                                                                        \
  TEST(suiteName, intPushEmpty) { queuePushEmptyTest<int>(DEF_INT_VALS); } \
  TEST(suiteName, doublePushEmpty) {                                       \
    queuePushEmptyTest<double>(DEF_DBL_VALS);                              \
  }                                                                        \
  TEST(suiteName, MockClassPushEmpty) {                                    \
    queuePushEmptyTest<MockClass>(DEF_MOCK_VALS);                          \
  }                                                                        \
  TEST(suiteName, stringPushEmpty) {                                       \
    queuePushEmptyTest<std::string>(DEF_STR_VALS);                         \
  }                                                                        \
  TEST(suiteName, NoConstructClassPushEmpty) {                             \
    queuePushEmptyTest<NoConstructClass>(DEF_INT_VALS);                    \
  }

TESTS_PUSH_EMPTY(s21Queue)

// --------------------------------------

template <typename T>
void queueInsertManyqueueBackTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  s21::queue<T> actualPush(items);

  actualPush.push(*items.begin());
  actualPush.push(*(items.begin() + 1));
  actualPush.push(*(items.begin() + 2));

  actual.insert_many_back(*items.begin(), *(items.begin() + 1),
                          *(items.begin() + 2));

  checkBasicField(actual, actualPush);
  checkDataEQ(actual, actualPush);
}

#define TESTS_INSERT_MANY_BACK(suiteName)                         \
  TEST(suiteName, uShortInsertManyBack) {                         \
    queueInsertManyqueueBackTest<unsigned short>(DEF_INT_VALS);   \
  }                                                               \
  TEST(suiteName, intInsertManyBack) {                            \
    queueInsertManyqueueBackTest<int>(DEF_INT_VALS);              \
  }                                                               \
  TEST(suiteName, doubleInsertManyBack) {                         \
    queueInsertManyqueueBackTest<double>(DEF_DBL_VALS);           \
  }                                                               \
  TEST(suiteName, MockClassInsertManyBack) {                      \
    queueInsertManyqueueBackTest<MockClass>(DEF_MOCK_VALS);       \
  }                                                               \
  TEST(suiteName, stringInsertManyBack) {                         \
    queueInsertManyqueueBackTest<std::string>(DEF_STR_VALS);      \
  }                                                               \
  TEST(suiteName, NoConstructClassInsertManyBack) {               \
    queueInsertManyqueueBackTest<NoConstructClass>(DEF_INT_VALS); \
  }

TESTS_INSERT_MANY_BACK(s21Queue)

// --------------------------------------

template <typename T>
void queueInsertManyBackEmptyTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual;
  s21::queue<T> actualPush;

  actualPush.push(*items.begin());
  actualPush.push(*(items.begin() + 1));
  actualPush.push(*(items.begin() + 2));

  actual.insert_many_back(*items.begin(), *(items.begin() + 1),
                          *(items.begin() + 2));

  checkBasicField(actual, actualPush);
  checkDataEQ(actual, actualPush);
}

#define TESTS_INSERT_MANY_BACK_EMPTY(suiteName)                   \
  TEST(suiteName, uShortInsertManyBackEmpty) {                    \
    queueInsertManyBackEmptyTest<unsigned short>(DEF_INT_VALS);   \
  }                                                               \
  TEST(suiteName, intInsertManyBackEmpty) {                       \
    queueInsertManyBackEmptyTest<int>(DEF_INT_VALS);              \
  }                                                               \
  TEST(suiteName, doubleInsertManyBackEmpty) {                    \
    queueInsertManyBackEmptyTest<double>(DEF_DBL_VALS);           \
  }                                                               \
  TEST(suiteName, MockClassInsertManyBackEmpty) {                 \
    queueInsertManyBackEmptyTest<MockClass>(DEF_MOCK_VALS);       \
  }                                                               \
  TEST(suiteName, stringInsertManyBackEmpty) {                    \
    queueInsertManyBackEmptyTest<std::string>(DEF_STR_VALS);      \
  }                                                               \
  TEST(suiteName, NoConstructClassInsertManyBackEmpty) {          \
    queueInsertManyBackEmptyTest<NoConstructClass>(DEF_INT_VALS); \
  }

TESTS_INSERT_MANY_BACK_EMPTY(s21Queue)

// --------------------------------------

template <typename T>
void queuePopTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  std::queue<T> expected(items);

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  actual.pop();
  expected.pop();

  EXPECT_EQ(actual.front(), expected.front());
  EXPECT_EQ(actual.back(), expected.back());

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  actual.push(*items.begin());
  expected.push(*items.begin());

  EXPECT_EQ(actual.front(), expected.front());
  EXPECT_EQ(actual.back(), expected.back());

  actual.pop();
  expected.pop();

  EXPECT_EQ(actual.front(), expected.front());
  EXPECT_EQ(actual.back(), expected.back());

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  for (auto i : items) {
    actual.push(i);
    expected.push(i);

    EXPECT_EQ(actual.front(), expected.front());
    EXPECT_EQ(actual.back(), expected.back());
  }

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  for (std::size_t i = 0; i < items.size(); i++) {
    actual.pop();
    expected.pop();

    EXPECT_EQ(actual.front(), expected.front());
    EXPECT_EQ(actual.back(), expected.back());
  }

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);

  actual.pop();
  expected.pop();

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);
}

#define TESTS_POP(suiteName)                                                 \
  TEST(suiteName, uShortPop) { queuePopTest<unsigned short>(DEF_INT_VALS); } \
  TEST(suiteName, intPop) { queuePopTest<int>(DEF_INT_VALS); }               \
  TEST(suiteName, doublePop) { queuePopTest<double>(DEF_DBL_VALS); }         \
  TEST(suiteName, MockClassPop) { queuePopTest<MockClass>(DEF_MOCK_VALS); }  \
  TEST(suiteName, stringPop) { queuePopTest<std::string>(DEF_STR_VALS); }

TESTS_POP(s21Queue)

// --------------------------------------

/* EDGE */

template <typename T>
void queueOperatorInitCopySelfTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  actual = actual;

  std::queue<T> expected(items);
  expected = expected;

  checkBasicField(actual, expected);
  checkDataEQ(actual, expected);
}

#define TESTS_EDGE_OPERATOR_COPY_SELF_INIT(suiteName)            \
  TEST(suiteName, uShortOperatorCopyInitSelt) {                  \
    queueOperatorInitCopySelfTest<unsigned short>(DEF_INT_VALS); \
  }                                                              \
  TEST(suiteName, intOperatorCopyInitSelt) {                     \
    queueOperatorInitCopySelfTest<int>(DEF_INT_VALS);            \
  }                                                              \
  TEST(suiteName, doubleOperatorCopyInitSelt) {                  \
    queueOperatorInitCopySelfTest<double>(DEF_DBL_VALS);         \
  }                                                              \
  TEST(suiteName, MockClassOperatorCopyInitSelt) {               \
    queueOperatorInitCopySelfTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                              \
  TEST(suiteName, stringOperatorCopyInitSelt) {                  \
    queueOperatorInitCopySelfTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_EDGE_OPERATOR_COPY_SELF_INIT(s21Queue)

// --------------------------------------

// #NOTE: std::vector does not check the case of self-assignment
template <typename T>
void queueOperatorInitMoveSelfTest(const std::initializer_list<T>& items) {
  s21::queue<T> actual(items);
  actual = std::move(actual);

  checkBasicField(actual, actual);
  checkDataEQ(actual, actual);
}

#define TESTS_EDGE_OPERATOR_MOVE_SELF_INIT(suiteName)            \
  TEST(suiteName, uShortOperatorMoveSelfInit) {                  \
    queueOperatorInitMoveSelfTest<unsigned short>(DEF_INT_VALS); \
  }                                                              \
  TEST(suiteName, intOperatorMoveSelfInit) {                     \
    queueOperatorInitMoveSelfTest<int>(DEF_INT_VALS);            \
  }                                                              \
  TEST(suiteName, doubleOperatorMoveSelfInit) {                  \
    queueOperatorInitMoveSelfTest<double>(DEF_DBL_VALS);         \
  }                                                              \
  TEST(suiteName, MockClassOperatorMoveSelfInit) {               \
    queueOperatorInitMoveSelfTest<MockClass>(DEF_MOCK_VALS);     \
  }                                                              \
  TEST(suiteName, stringOperatorMoveSelfInit) {                  \
    queueOperatorInitMoveSelfTest<std::string>(DEF_STR_VALS);    \
  }

TESTS_EDGE_OPERATOR_MOVE_SELF_INIT(s21Queue)

// --------------------------------------

/* ANOMALY */

// #NOTE: std::queue does not check empty when pop - UB
template <typename T>
void queuePopEmptyTest() {
  s21::queue<T> actual;
  std::queue<T> expected;

  checkBasicField(actual, expected);

  EXPECT_THROW({ actual.pop(); }, std::out_of_range);
}

#define TESTS_ANOMALY_POP_EMPTY(suiteName)                                 \
  TEST(suiteName, uShortPopEmpty) { queuePopEmptyTest<unsigned short>(); } \
  TEST(suiteName, intPopEmpty) { queuePopEmptyTest<int>(); }               \
  TEST(suiteName, doublePopEmpty) { queuePopEmptyTest<double>(); }         \
  TEST(suiteName, MockClassPopEmpty) { queuePopEmptyTest<MockClass>(); }   \
  TEST(suiteName, stringPopEmpty) { queuePopEmptyTest<std::string>(); }

TESTS_ANOMALY_POP_EMPTY(s21Queue)

// --------------------------------------