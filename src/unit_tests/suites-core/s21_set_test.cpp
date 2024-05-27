#include "core/s21_set.h"

#include <set>

#include "s21_core_tests.h"

#define DEF_INT_KEYS \
  { 1, 2, 3, 4, 8 }
#define DEF_DBL_KEYS \
  { 4.35, 2.977, 873.23, 6.875, 9.6534 }
#define DEF_MOCK_KEYS \
  { 1, 4, 44, 45, 88 }
#define DEF_STR_KEYS \
  { "hello", "world", "!", "mock", "set" }

#define DEF_INT_KEYS_DUBLICATE \
  { 6, 2, 3, 8, 10 }
#define DEF_DBL_KEYS_DUBLICATE \
  { 5.41, 2.977, 873.23, 6.875, 123.123 }
#define DEF_MOCK_KEYS_DUBLICATE \
  { 1, 9, 10, 45, 10 }
#define DEF_STR_KEYS_DUBLICATE \
  { "hello", "test", "!!!", "this", "mock" }

#define DEF_INT_KEYS_NO_DUBLICATE \
  { 6, 5, 10, 9, 11 }
#define DEF_DBL_KEYS_NO_DUBLICATE \
  { 7.523, 234.4, 1.001, 1.002, 124.124 }
#define DEF_MOCK_KEYS_NO_DUBLICATE \
  { 98, 9, 10, 11, 90 }
#define DEF_STR_KEYS_NO_DUBLICATE \
  { "this", "is", "test", "or", "not" }

#define INT_KEY 69
#define DBL_KEY 69.69
#define MOCK_KEY 69
#define STR_KEY "69"

#define INT_KEY_DUPLICATE 3
#define DBL_KEY_DUPLICATE 6.875
#define MOCK_KEY_DUPLICATE 44
#define STR_KEY_DUPLICATE "!"

template <typename key_type>
void checkFields(const s21::set<key_type>& s21_set,
                 const std::set<key_type>& std_set) {
  auto std_it = std_set.begin();
  for (auto s21_it : s21_set) {
    EXPECT_EQ(s21_it, *std_it);

    ++std_it;
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
}

template <typename key_type>
void checkFieldsEmpty(const s21::set<key_type>& s21_set,
                      const std::set<key_type>& std_set) {
  auto std_it = std_set.begin();
  for (auto s21_it : s21_set) {
    EXPECT_EQ(s21_it, *std_it);

    ++std_it;
  }
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------

template <typename key_type>
void constructorDefaultAsCont() {
  s21::IContainer* ct = new s21::set<key_type>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_CONSTRUCTOR_INIT_AS_CONT(suiteName)                           \
  TEST(suiteName, intInitAsCont) { constructorDefaultAsCont<int>(); }       \
  TEST(suiteName, doubleInitAsCont) { constructorDefaultAsCont<double>(); } \
  TEST(suiteName, mockClassInitAsCont) {                                    \
    constructorDefaultAsCont<MockClass>();                                  \
  }                                                                         \
  TEST(suiteName, stringInitAsCont) { constructorDefaultAsCont<std::string>(); }

TESTS_CONSTRUCTOR_INIT_AS_CONT(s21Set)

// -------------------------------------------------

template <typename key_type>
void constructorDefault() {
  s21::set<key_type> s21_set;
  std::set<key_type> std_set;

  checkFieldsEmpty(s21_set, std_set);
}

#define TESTS_DEFAULT_CONSTRUCTOR_INIT(suiteName)                        \
  TEST(suiteName, intDefInit) { constructorDefault<int>(); }             \
  TEST(suiteName, doubleDefInit) { constructorDefault<double>(); }       \
  TEST(suiteName, mockClassDefInit) { constructorDefault<MockClass>(); } \
  TEST(suiteName, stringDefInit) { constructorDefault<std::string>(); }

TESTS_DEFAULT_CONSTRUCTOR_INIT(s21Set)

// -------------------------------------------------

template <typename key_type>
void constructorInitList(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  checkFields(s21_set, std_set);
}

#define TESTS_CONSTRUCTOR_INIT_LIST(suiteName)                             \
  TEST(suiteName, intInitList) { constructorInitList<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleInitList) {                                        \
    constructorInitList<double>(DEF_DBL_KEYS);                             \
  }                                                                        \
  TEST(suiteName, mockClassInitList) {                                     \
    constructorInitList<MockClass>(DEF_MOCK_KEYS);                         \
  }                                                                        \
  TEST(suiteName, stringInitList) {                                        \
    constructorInitList<std::string>(DEF_STR_KEYS);                        \
  }

TESTS_CONSTRUCTOR_INIT_LIST(s21Set)

// -------------------------------------------------

template <typename key_type>
void constructorCopyEmpty() {
  s21::set<key_type> s21_set;
  std::set<key_type> std_set;

  s21::set<key_type> s21_map_copy(s21_set);
  std::set<key_type> std_map_copy(std_set);

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY_EMPTY(suiteName)                              \
  TEST(suiteName, intCopyEmpty) { constructorCopyEmpty<int>(); }             \
  TEST(suiteName, doubleCopyEmpty) { constructorCopyEmpty<double>(); }       \
  TEST(suiteName, mockClassCopyEmpty) { constructorCopyEmpty<MockClass>(); } \
  TEST(suiteName, stringCopyEmpty) { constructorCopyEmpty<std::string>(); }

TESTS_CONSTRUCTOR_COPY_EMPTY(s21Set)

// -------------------------------------------------

template <typename key_type>
void constructorCopy(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_copy(s21_set);
  std::set<key_type> std_map_copy(std_set);

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY(suiteName)                                \
  TEST(suiteName, intCopy) { constructorCopy<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleCopy) { constructorCopy<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassCopy) {                                       \
    constructorCopy<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                      \
  TEST(suiteName, stringCopy) { constructorCopy<std::string>(DEF_STR_KEYS); }

TESTS_CONSTRUCTOR_COPY(s21Set)

// -------------------------------------------------

template <typename key_type>
void constructorMoveEmpty() {
  s21::set<key_type> s21_set;
  std::set<key_type> std_set;

  s21::set<key_type> s21_map_move(std::move(s21_set));
  std::set<key_type> std_map_move(std::move(std_set));

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE_EMPTY(suiteName)                              \
  TEST(suiteName, intMoveEmpty) { constructorMoveEmpty<int>(); }             \
  TEST(suiteName, doubleMoveEmpty) { constructorMoveEmpty<double>(); }       \
  TEST(suiteName, mockClassMoveEmpty) { constructorMoveEmpty<MockClass>(); } \
  TEST(suiteName, stringMoveEmpty) { constructorMoveEmpty<std::string>(); }

TESTS_CONSTRUCTOR_MOVE_EMPTY(s21Set)

// -------------------------------------------------

template <typename key_type>
void constructorMove(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_move(std::move(s21_set));
  std::set<key_type> std_map_move(std::move(std_set));

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE(suiteName)                                \
  TEST(suiteName, intMove) { constructorMove<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleMove) { constructorMove<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassMove) {                                       \
    constructorMove<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                      \
  TEST(suiteName, stringMove) { constructorMove<std::string>(DEF_STR_KEYS); }

TESTS_CONSTRUCTOR_MOVE(s21Set)

// -------------------------------------------------

template <typename key_type>
void operatorCopyEmpty() {
  s21::set<key_type> s21_set;
  std::set<key_type> std_set;

  s21::set<key_type> s21_map_copy = s21_set;
  std::set<key_type> std_map_copy = std_set;

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY_EMPTY(suiteName)                                \
  TEST(suiteName, intOperatorCopyEmpty) { operatorCopyEmpty<int>(); }       \
  TEST(suiteName, doubleOperatorCopyEmpty) { operatorCopyEmpty<double>(); } \
  TEST(suiteName, mockClassOperatorCopyEmpty) {                             \
    operatorCopyEmpty<MockClass>();                                         \
  }                                                                         \
  TEST(suiteName, stringOperatorCopyEmpty) { operatorCopyEmpty<std::string>(); }

TESTS_OPERATOR_COPY_EMPTY(s21Set)

// -------------------------------------------------

template <typename key_type>
void operatorCopy(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_copy = s21_set;
  std::set<key_type> std_map_copy = std_set;

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY(suiteName)                                        \
  TEST(suiteName, intOperatorCopy) { operatorCopy<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleOperatorCopy) { operatorCopy<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassOperatorCopy) {                                    \
    operatorCopy<MockClass>(DEF_MOCK_KEYS);                                   \
  }                                                                           \
  TEST(suiteName, stringOperatorCopy) {                                       \
    operatorCopy<std::string>(DEF_STR_KEYS);                                  \
  }

TESTS_OPERATOR_COPY(s21Set)

// -------------------------------------------------

template <typename key_type>
void operatorMoveEmpty() {
  s21::set<key_type> s21_set;
  std::set<key_type> std_set;

  s21::set<key_type> s21_map_move = std::move(s21_set);
  std::set<key_type> std_map_move = std::move(std_set);

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE_EMPTY(suiteName)                                \
  TEST(suiteName, intOperatorMoveEmpty) { operatorMoveEmpty<int>(); }       \
  TEST(suiteName, doubleOperatorMoveEmpty) { operatorMoveEmpty<double>(); } \
  TEST(suiteName, mockClassOperatorMoveEmpty) {                             \
    operatorMoveEmpty<MockClass>();                                         \
  }                                                                         \
  TEST(suiteName, stringOperatorMoveEmptye) {                               \
    operatorMoveEmpty<std::string>();                                       \
  }

TESTS_OPERATOR_MOVE_EMPTY(s21Set)

// -------------------------------------------------

template <typename key_type>
void operatorMove(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_move = std::move(s21_set);
  std::set<key_type> std_map_move = std::move(std_set);

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE(suiteName)                                        \
  TEST(suiteName, intOperatorMove) { operatorMove<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleOperatorMove) { operatorMove<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassOperatorMove) {                                    \
    operatorMove<MockClass>(DEF_MOCK_KEYS);                                   \
  }                                                                           \
  TEST(suiteName, stringOperatorMove) {                                       \
    operatorMove<std::string>(DEF_STR_KEYS);                                  \
  }

TESTS_OPERATOR_MOVE(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodEmpty(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_empty;
  std::set<key_type> std_map_empty;

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_map_empty.empty(), std_map_empty.empty());
}

#define TESTS_EMPTY(suiteName)                                               \
  TEST(suiteName, intEmpty) { methodEmpty<int>(DEF_INT_KEYS); }              \
  TEST(suiteName, doubleEmpty) { methodEmpty<double>(DEF_DBL_KEYS); }        \
  TEST(suiteName, mockClassEmpty) { methodEmpty<MockClass>(DEF_MOCK_KEYS); } \
  TEST(suiteName, stringEmpty) { methodEmpty<std::string>(DEF_STR_KEYS); }

TESTS_EMPTY(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodSize(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_empty;
  std::set<key_type> std_map_empty;

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_map_empty.size(), std_map_empty.size());
}

#define TESTS_SIZE(suiteName)                                               \
  TEST(suiteName, intSize) { methodEmpty<int>(DEF_INT_KEYS); }              \
  TEST(suiteName, doubleSize) { methodEmpty<double>(DEF_DBL_KEYS); }        \
  TEST(suiteName, mockClassSize) { methodEmpty<MockClass>(DEF_MOCK_KEYS); } \
  TEST(suiteName, stringSize) { methodEmpty<std::string>(DEF_STR_KEYS); }

TESTS_SIZE(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodSwap(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  s21::set<key_type> s21_map_empty;

  std::set<key_type> std_set(items);

  checkFields(s21_set, std_set);
  s21_map_empty.swap(s21_set);
  checkFields(s21_map_empty, std_set);
}

#define TESTS_SWAP(suiteName)                                              \
  TEST(suiteName, intSwap) { methodSwap<int>(DEF_INT_KEYS); }              \
  TEST(suiteName, doubleSwap) { methodSwap<double>(DEF_DBL_KEYS); }        \
  TEST(suiteName, mockClassSwap) { methodSwap<MockClass>(DEF_MOCK_KEYS); } \
  TEST(suiteName, stringSwap) { methodSwap<std::string>(DEF_STR_KEYS); }

TESTS_SWAP(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodMergeWithDublicates(
    const std::initializer_list<key_type>& items,
    const std::initializer_list<key_type>& itemsDublicates) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_dublicate(itemsDublicates);
  std::set<key_type> std_map_dublicate(itemsDublicates);

  checkFields(s21_set, std_set);
  checkFields(s21_map_dublicate, std_map_dublicate);

  s21_set.merge(s21_map_dublicate);
  std_set.merge(std_map_dublicate);

  checkFields(s21_set, std_set);
}

#define TESTS_MERGE_WITH_DUBLICATES(suiteName)                               \
  TEST(suiteName, intMergeWithDublicates) {                                  \
    methodMergeWithDublicates<int>(DEF_INT_KEYS, DEF_INT_KEYS_DUBLICATE);    \
  }                                                                          \
  TEST(suiteName, doubleMergeWithDublicates) {                               \
    methodMergeWithDublicates<double>(DEF_DBL_KEYS, DEF_DBL_KEYS_DUBLICATE); \
  }                                                                          \
  TEST(suiteName, mockClassMergeWithDublicates) {                            \
    methodMergeWithDublicates<MockClass>(DEF_MOCK_KEYS,                      \
                                         DEF_MOCK_KEYS_DUBLICATE);           \
  }                                                                          \
  TEST(suiteName, stringMergeWithDublicates) {                               \
    methodMergeWithDublicates<std::string>(DEF_STR_KEYS,                     \
                                           DEF_STR_KEYS_DUBLICATE);          \
  }

TESTS_MERGE_WITH_DUBLICATES(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodMergeWithNoDublicates(
    const std::initializer_list<key_type>& items,
    const std::initializer_list<key_type>& itemsNoDublicates) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_no_dublicate(itemsNoDublicates);
  std::set<key_type> std_map_no_dublicate(itemsNoDublicates);

  checkFields(s21_set, std_set);
  checkFields(s21_map_no_dublicate, std_map_no_dublicate);

  s21_set.merge(s21_map_no_dublicate);
  std_set.merge(std_map_no_dublicate);

  checkFields(s21_set, std_set);
}

#define TESTS_MERGE_WITH_NO_DUBLICATES(suiteName)                              \
  TEST(suiteName, intMergeWithNoDublicates) {                                  \
    methodMergeWithNoDublicates<int>(DEF_INT_KEYS, DEF_INT_KEYS_NO_DUBLICATE); \
  }                                                                            \
  TEST(suiteName, doubleMergeWithNoDublicates) {                               \
    methodMergeWithNoDublicates<double>(DEF_DBL_KEYS,                          \
                                        DEF_DBL_KEYS_NO_DUBLICATE);            \
  }                                                                            \
  TEST(suiteName, mockClassMergeWithNoDublicates) {                            \
    methodMergeWithNoDublicates<MockClass>(DEF_MOCK_KEYS,                      \
                                           DEF_MOCK_KEYS_NO_DUBLICATE);        \
  }                                                                            \
  TEST(suiteName, stringMergeWithNoDublicates) {                               \
    methodMergeWithNoDublicates<std::string>(DEF_STR_KEYS,                     \
                                             DEF_STR_KEYS_NO_DUBLICATE);       \
  }

TESTS_MERGE_WITH_NO_DUBLICATES(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodClear(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_empty;
  std::set<key_type> std_map_empty;

  s21_set.clear();
  std_set.clear();

  s21_map_empty.clear();
  std_map_empty.clear();

  checkFields(s21_set, std_set);
  checkFields(s21_map_empty, std_map_empty);
}

#define TESTS_CLEAR(suiteName)                                               \
  TEST(suiteName, intClear) { methodClear<int>(DEF_INT_KEYS); }              \
  TEST(suiteName, doubleClear) { methodClear<double>(DEF_DBL_KEYS); }        \
  TEST(suiteName, mockClassClear) { methodClear<MockClass>(DEF_MOCK_KEYS); } \
  TEST(suiteName, stringClear) { methodClear<std::string>(DEF_STR_KEYS); }

TESTS_CLEAR(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodBegin(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_empty;
  std::set<key_type> std_map_empty;

  typename s21::set<key_type>::iterator it1 = s21_map_empty.begin();
  typename std::set<key_type>::iterator it2 = std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end(), it2 == std_map_empty.end());

  typename s21::set<key_type>::iterator it3 = s21_set.begin();
  typename std::set<key_type>::iterator it4 = std_set.begin();

  EXPECT_EQ(it3 != s21_set.end(), it4 != std_set.end());
  EXPECT_EQ(*it3, *it4);
}

#define TESTS_BEGIN(suiteName)                                               \
  TEST(suiteName, intBegin) { methodBegin<int>(DEF_INT_KEYS); }              \
  TEST(suiteName, doubleBegin) { methodBegin<double>(DEF_DBL_KEYS); }        \
  TEST(suiteName, mockClassBegin) { methodBegin<MockClass>(DEF_MOCK_KEYS); } \
  TEST(suiteName, stringBegin) { methodBegin<std::string>(DEF_STR_KEYS); }

TESTS_BEGIN(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodBeginConst(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21::set<key_type> s21_map_empty;
  std::set<key_type> std_map_empty;

  typename s21::set<key_type>::const_iterator it1 = s21_map_empty.begin();
  typename std::set<key_type>::const_iterator it2 = std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end(), it2 == std_map_empty.end());

  typename s21::set<key_type>::const_iterator it3 = s21_set.begin();
  typename std::set<key_type>::const_iterator it4 = std_set.begin();

  EXPECT_EQ(it3 != s21_set.end(), it4 != std_set.end());
  EXPECT_EQ(*it3, *it4);
}

#define TESTS_BEGIN_CONST(suiteName)                                      \
  TEST(suiteName, intBeginConst) { methodBeginConst<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleBeginConst) {                                     \
    methodBeginConst<double>(DEF_DBL_KEYS);                               \
  }                                                                       \
  TEST(suiteName, mockClassBeginConst) {                                  \
    methodBeginConst<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                       \
  TEST(suiteName, stringBeginConst) {                                     \
    methodBeginConst<std::string>(DEF_STR_KEYS);                          \
  }

TESTS_BEGIN_CONST(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorPlus(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::iterator it1 = s21_set.begin();
  typename std::set<key_type>::iterator it2 = std_set.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_PLUS(suiteName)                                        \
  TEST(suiteName, intIteratorPlus) { methodIteratorPlus<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleIteratorPlus) {                                       \
    methodIteratorPlus<double>(DEF_DBL_KEYS);                                 \
  }                                                                           \
  TEST(suiteName, mockClassIteratorPlus) {                                    \
    methodIteratorPlus<MockClass>(DEF_MOCK_KEYS);                             \
  }                                                                           \
  TEST(suiteName, stringIteratorPlus) {                                       \
    methodIteratorPlus<std::string>(DEF_STR_KEYS);                            \
  }

TESTS_ITERATOR_PLUS(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorMinus(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::iterator it1 = s21_set.begin();
  typename std::set<key_type>::iterator it2 = std_set.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  --it1;
  --it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_MINUS(suiteName)             \
  TEST(suiteName, intIteratorMinus) {               \
    methodIteratorMinus<int>(DEF_INT_KEYS);         \
  }                                                 \
  TEST(suiteName, doubleIteratorMinus) {            \
    methodIteratorMinus<double>(DEF_DBL_KEYS);      \
  }                                                 \
  TEST(suiteName, mockClassIteratorMinus) {         \
    methodIteratorMinus<MockClass>(DEF_MOCK_KEYS);  \
  }                                                 \
  TEST(suiteName, stringIteratorMinus) {            \
    methodIteratorMinus<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_MINUS(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorAssignment(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::iterator it1 = s21_set.begin();
  typename std::set<key_type>::iterator it2 = std_set.begin();

  typename s21::set<key_type>::iterator it3 = it1;
  typename std::set<key_type>::iterator it4 = it2;

  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*it2, *it4);
}

#define TESTS_ITERATOR_ASSIGNMENT(suiteName)             \
  TEST(suiteName, intIteratorAssignment) {               \
    methodIteratorAssignment<int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorAssignment) {            \
    methodIteratorAssignment<double>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorAssignment) {         \
    methodIteratorAssignment<MockClass>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorAssignment) {            \
    methodIteratorAssignment<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_ASSIGNMENT(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorEqual(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::iterator it1 = s21_set.begin();
  typename std::set<key_type>::iterator it2 = std_set.begin();

  typename s21::set<key_type>::iterator it3 = s21_set.begin();
  typename std::set<key_type>::iterator it4 = std_set.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL(suiteName)             \
  TEST(suiteName, intIteratorEqual) {               \
    methodIteratorEqual<int>(DEF_INT_KEYS);         \
  }                                                 \
  TEST(suiteName, doubleIteratorEqual) {            \
    methodIteratorEqual<double>(DEF_DBL_KEYS);      \
  }                                                 \
  TEST(suiteName, mockClassIteratorEqual) {         \
    methodIteratorEqual<MockClass>(DEF_MOCK_KEYS);  \
  }                                                 \
  TEST(suiteName, stringIteratorEqual) {            \
    methodIteratorEqual<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_EQUAL(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorNotEqual(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::iterator it1 = s21_set.begin();
  typename std::set<key_type>::iterator it2 = std_set.begin();

  EXPECT_EQ(it1 != s21_set.end(), it2 != std_set.end());
}

#define TESTS_ITERATOR_NOT_EQUAL(suiteName)            \
  TEST(suiteName, intIteratorNotEqual) {               \
    methodIteratorNotEqual<int>(DEF_INT_KEYS);         \
  }                                                    \
  TEST(suiteName, doubleIteratorNotEqual) {            \
    methodIteratorNotEqual<double>(DEF_DBL_KEYS);      \
  }                                                    \
  TEST(suiteName, mockClassIteratorNotEqual) {         \
    methodIteratorNotEqual<MockClass>(DEF_MOCK_KEYS);  \
  }                                                    \
  TEST(suiteName, stringIteratorNotEqual) {            \
    methodIteratorNotEqual<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_NOT_EQUAL(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorPlusConst(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::const_iterator it1 = s21_set.begin();
  typename std::set<key_type>::const_iterator it2 = std_set.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_PLUS_CONST(suiteName)            \
  TEST(suiteName, intIteratorPlusConst) {               \
    methodIteratorPlusConst<int>(DEF_INT_KEYS);         \
  }                                                     \
  TEST(suiteName, doubleIteratorPlusConst) {            \
    methodIteratorPlusConst<double>(DEF_DBL_KEYS);      \
  }                                                     \
  TEST(suiteName, mockClassIteratorPlusConst) {         \
    methodIteratorPlusConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                     \
  TEST(suiteName, stringIteratorPlusConst) {            \
    methodIteratorPlusConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_PLUS_CONST(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorMinusConst(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::const_iterator it1 = s21_set.begin();
  typename std::set<key_type>::const_iterator it2 = std_set.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  --it1;
  --it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_MINUS_CONST(suiteName)            \
  TEST(suiteName, intIteratorMinusConst) {               \
    methodIteratorMinusConst<int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorMinusConst) {            \
    methodIteratorMinusConst<double>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorMinusConst) {         \
    methodIteratorMinusConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorMinusConst) {            \
    methodIteratorMinusConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_MINUS_CONST(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorAssignmentConst(
    const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::const_iterator it1 = s21_set.begin();
  typename std::set<key_type>::const_iterator it2 = std_set.begin();

  typename s21::set<key_type>::const_iterator it3 = it1;
  typename std::set<key_type>::const_iterator it4 = it2;

  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*it2, *it4);
}

#define TESTS_ITERATOR_ASSIGNMENT_CONST(suiteName)            \
  TEST(suiteName, intIteratorAssignmentConst) {               \
    methodIteratorAssignmentConst<int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorAssignmentConst) {            \
    methodIteratorAssignmentConst<double>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorAssignmentConst) {         \
    methodIteratorAssignmentConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorAssignmentConst) {            \
    methodIteratorAssignmentConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_ASSIGNMENT_CONST(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorEqualConst(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::const_iterator it1 = s21_set.begin();
  typename std::set<key_type>::const_iterator it2 = std_set.begin();

  typename s21::set<key_type>::const_iterator it3 = s21_set.begin();
  typename std::set<key_type>::const_iterator it4 = std_set.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL_CONST(suiteName)            \
  TEST(suiteName, intIteratorEqualConst) {               \
    methodIteratorEqualConst<int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorEqualConst) {            \
    methodIteratorEqualConst<double>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorEqualConst) {         \
    methodIteratorEqualConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorEqualConst) {            \
    methodIteratorEqualConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_EQUAL_CONST(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodIteratorNotEqualConst(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  typename s21::set<key_type>::const_iterator it1 = s21_set.begin();
  typename std::set<key_type>::const_iterator it2 = std_set.begin();

  EXPECT_EQ(it1 != s21_set.end(), it2 != std_set.end());
}

#define TESTS_ITERATOR_NOT_EQUAL_CONST(suiteName)           \
  TEST(suiteName, intIteratorNotEqualConst) {               \
    methodIteratorNotEqualConst<int>(DEF_INT_KEYS);         \
  }                                                         \
  TEST(suiteName, doubleIteratorNotEqualConst) {            \
    methodIteratorNotEqualConst<double>(DEF_DBL_KEYS);      \
  }                                                         \
  TEST(suiteName, mockClassIteratorNotEqualConst) {         \
    methodIteratorNotEqualConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                         \
  TEST(suiteName, stringIteratorNotEqualConst) {            \
    methodIteratorNotEqualConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_NOT_EQUAL_CONST(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodInsertNoDuplicate(const std::initializer_list<key_type>& items,
                             const key_type& key) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  std::pair<typename s21::set<key_type>::iterator, bool> it1 =
      s21_set.insert(key);
  std::pair<typename std::set<key_type>::iterator, bool> it2 =
      std_set.insert(key);

  checkFields(s21_set, std_set);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ(*(it1.first), *(it2.first));
}

#define TESTS_INSERT_NO_DUPLICATE(suiteName)                     \
  TEST(suiteName, intInsertNoDuplicate) {                        \
    methodInsertNoDuplicate<int>(DEF_INT_KEYS, INT_KEY);         \
  }                                                              \
  TEST(suiteName, doubleInsertNoDuplicate) {                     \
    methodInsertNoDuplicate<double>(DEF_DBL_KEYS, DBL_KEY);      \
  }                                                              \
  TEST(suiteName, mockClassInsertNoDuplicate) {                  \
    methodInsertNoDuplicate<MockClass>(DEF_MOCK_KEYS, MOCK_KEY); \
  }                                                              \
  TEST(suiteName, stringInsertNoDuplicate) {                     \
    methodInsertNoDuplicate<std::string>(DEF_STR_KEYS, STR_KEY); \
  }

TESTS_INSERT_NO_DUPLICATE(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodInsertDuplicate(const std::initializer_list<key_type>& items,
                           const key_type& key) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  std::pair<typename s21::set<key_type>::iterator, bool> it1 =
      s21_set.insert(key);
  std::pair<typename std::set<key_type>::iterator, bool> it2 =
      std_set.insert(key);

  checkFields(s21_set, std_set);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ(*(it1.first), *(it2.first));
}

#define TESTS_INSERT_DUPLICATE(suiteName)                                \
  TEST(suiteName, intInsertDuplicate) {                                  \
    methodInsertDuplicate<int>(DEF_INT_KEYS, INT_KEY_DUPLICATE);         \
  }                                                                      \
  TEST(suiteName, doubleInsertDuplicate) {                               \
    methodInsertDuplicate<double>(DEF_DBL_KEYS, DBL_KEY_DUPLICATE);      \
  }                                                                      \
  TEST(suiteName, mockClassInsertDuplicate) {                            \
    methodInsertDuplicate<MockClass>(DEF_MOCK_KEYS, MOCK_KEY_DUPLICATE); \
  }                                                                      \
  TEST(suiteName, stringInsertDuplicate) {                               \
    methodInsertDuplicate<std::string>(DEF_STR_KEYS, STR_KEY_DUPLICATE); \
  }

TESTS_INSERT_DUPLICATE(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodErase(const std::initializer_list<key_type>& items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21_set.erase(s21_set.begin());
  std_set.erase(std_set.begin());

  checkFields(s21_set, std_set);

  s21_set.erase(s21_set.begin());
  std_set.erase(std_set.begin());

  checkFields(s21_set, std_set);
}

#define TESTS_ERASE(suiteName)                                              \
  TEST(suiteName, intMethodErase) { methodErase<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleMethodErase) { methodErase<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassMethodErase) {                                   \
    methodErase<MockClass>(DEF_MOCK_KEYS);                                  \
  }                                                                         \
  TEST(suiteName, stringMethodErase) { methodErase<std::string>(DEF_STR_KEYS); }

TESTS_ERASE(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodContains(const std::initializer_list<key_type>& items,
                    const key_type& key, const key_type& key_duplicate) {
  s21::set<key_type> s21_set(items);

  ASSERT_FALSE(s21_set.contains(key));
  ASSERT_TRUE(s21_set.contains(key_duplicate));
}

#define TESTS_CONTAINS(suiteName)                                           \
  TEST(suiteName, intMethodContains) {                                      \
    methodContains<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);          \
  }                                                                         \
  TEST(suiteName, doubleMethodContains) {                                   \
    methodContains<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE);       \
  }                                                                         \
  TEST(suiteName, mockClassMethodContains) {                                \
    methodContains<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); \
  }                                                                         \
  TEST(suiteName, stringMethodContains) {                                   \
    methodContains<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE);  \
  }

TESTS_CONTAINS(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodInsertMany(const std::initializer_list<key_type>& items,
                      const std::initializer_list<key_type>& insert_items) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  s21_set.insert_many(*insert_items.begin(), *(insert_items.begin() + 1),
                      *(insert_items.begin() + 2));
  std_set.insert(*insert_items.begin());
  std_set.insert(*(insert_items.begin() + 1));
  std_set.insert(*(insert_items.begin() + 2));

  checkFields(s21_set, std_set);
}

#define TESTS_INSERT_MANY(suiteName)                                        \
  TEST(suiteName, intMethodInsertMany) {                                    \
    methodInsertMany<int>(DEF_INT_KEYS, DEF_INT_KEYS_NO_DUBLICATE);         \
  }                                                                         \
  TEST(suiteName, doubleMethodInsertMany) {                                 \
    methodInsertMany<double>(DEF_DBL_KEYS, DEF_DBL_KEYS_NO_DUBLICATE);      \
  }                                                                         \
  TEST(suiteName, mockClassMethodInsertMany) {                              \
    methodInsertMany<MockClass>(DEF_MOCK_KEYS, DEF_MOCK_KEYS_NO_DUBLICATE); \
  }                                                                         \
  TEST(suiteName, stringMethodInsertMany) {                                 \
    methodInsertMany<std::string>(DEF_STR_KEYS, DEF_STR_KEYS_NO_DUBLICATE); \
  }

TESTS_INSERT_MANY(s21Set)

// -------------------------------------------------

template <typename key_type>
void methodFind(const std::initializer_list<key_type>& items,
                const key_type& key, const key_type& key_duplicate) {
  s21::set<key_type> s21_set(items);
  std::set<key_type> std_set(items);

  EXPECT_EQ(s21_set.find(key) == s21_set.end(),
            std_set.find(key) == std_set.end());

  EXPECT_EQ(*(s21_set.find(key_duplicate)), *(std_set.find(key_duplicate)));
}

#define TESTS_FIND(suiteName)                                           \
  TEST(suiteName, intMethodFind) {                                      \
    methodFind<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);          \
  }                                                                     \
  TEST(suiteName, doubleMethodFind) {                                   \
    methodFind<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE);       \
  }                                                                     \
  TEST(suiteName, mockClassMethodFind) {                                \
    methodFind<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); \
  }                                                                     \
  TEST(suiteName, stringMethodFind) {                                   \
    methodFind<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE);  \
  }

TESTS_FIND(s21Set)

#define TEST_ROUNDS 3000

template <typename key_type>
void bigLineTree(int rounds) {
  s21::set<key_type> actual;
  std::set<key_type> expected;

  srand(static_cast<int>((std::size_t)&actual));

  for (int i = 0; i < rounds; i++) {
    actual.insert(i);
    expected.insert(i);
  }

  checkFields(actual, expected);
}

#define TESTS_BIG_LINE_TREE(suiteName) \
  TEST(suiteName, intBigLineTree) { bigLineTree<int>(TEST_ROUNDS); }

TESTS_BIG_LINE_TREE(s21Set)

double GetRandSet(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

template <typename key_type>
void bigRandomTree(int rMin, int rMax, int rounds) {
  s21::set<key_type> actual;
  std::set<key_type> expected;

  srand(static_cast<int>((std::size_t)&actual));

  for (int i = 0; i < rounds; i++) {
    auto val = GetRandSet(rMin, rMax);
    actual.insert(val);
    expected.insert(val);
  }

  checkFields(actual, expected);
}

#define TEST_RAND_MIN -10000
#define TEST_RAND_MAX 10000
#define TEST_RAND_ROUNDS 1000

#define TESTS_BIG_RANDOM_TREE(suiteName)                                   \
  TEST(suiteName, intBigRandomTree) {                                      \
    bigRandomTree<int>(TEST_RAND_MIN, TEST_RAND_MAX, TEST_RAND_ROUNDS);    \
  }                                                                        \
  TEST(suiteName, doubleBigRandomTree) {                                   \
    bigRandomTree<double>(TEST_RAND_MIN, TEST_RAND_MAX, TEST_RAND_ROUNDS); \
  }

TESTS_BIG_RANDOM_TREE(s21Set)