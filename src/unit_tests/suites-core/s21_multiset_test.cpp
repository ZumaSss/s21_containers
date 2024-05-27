#include "core/s21_multiset.h"

#include <set>

#include "s21_core_tests.h"

#define DEF_INT_KEYS \
  { 1, 2, 3, 4, 8, 3, 4, 4 }
#define DEF_DBL_KEYS \
  { 4.35, 2.977, 873.23, 6.875, 9.6534, 6.875, 2.977, 2.977 }
#define DEF_MOCK_KEYS \
  { 1, 4, 44, 45, 88, 44, 1, 1 }
#define DEF_STR_KEYS \
  { "hello", "world", "!", "mock", "multiset", "!", "!", "world" }

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

#define INT_KEY_DUPLICATE 4
#define DBL_KEY_DUPLICATE 2.977
#define MOCK_KEY_DUPLICATE 1
#define STR_KEY_DUPLICATE "!"

template <typename key_type>
void multiCheckFields(const s21::multiset<key_type>& s21_multiset,
                      const std::multiset<key_type>& std_multiset) {
  auto std_it = std_multiset.begin();
  for (auto s21_it : s21_multiset) {
    EXPECT_EQ(s21_it, *std_it);

    ++std_it;
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

template <typename key_type>
void multiCheckFieldsEmpty(const s21::multiset<key_type>& s21_multiset,
                           const std::multiset<key_type>& std_multiset) {
  auto std_it = std_multiset.begin();
  for (auto s21_it : s21_multiset) {
    EXPECT_EQ(s21_it, *std_it);

    ++std_it;
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------

template <typename key_type>
void multiConstructorDefaultAsCont() {
  s21::IContainer* ct = new s21::multiset<key_type>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_CONSTRUCTOR_INIT_AS_CONT(suiteName)                          \
  TEST(suiteName, intInitAsCont) { multiConstructorDefaultAsCont<int>(); } \
  TEST(suiteName, doubleInitAsCont) {                                      \
    multiConstructorDefaultAsCont<double>();                               \
  }                                                                        \
  TEST(suiteName, mockClassInitAsCont) {                                   \
    multiConstructorDefaultAsCont<MockClass>();                            \
  }                                                                        \
  TEST(suiteName, stringInitAsCont) {                                      \
    multiConstructorDefaultAsCont<std::string>();                          \
  }

TESTS_CONSTRUCTOR_INIT_AS_CONT(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiConstructorDefault() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  multiCheckFieldsEmpty(s21_multiset, std_multiset);
}

#define TESTS_DEFAULT_CONSTRUCTOR_INIT(suiteName)                             \
  TEST(suiteName, intDefInit) { multiConstructorDefault<int>(); }             \
  TEST(suiteName, doubleDefInit) { multiConstructorDefault<double>(); }       \
  TEST(suiteName, mockClassDefInit) { multiConstructorDefault<MockClass>(); } \
  TEST(suiteName, stringDefInit) { multiConstructorDefault<std::string>(); }

TESTS_DEFAULT_CONSTRUCTOR_INIT(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiConstructorInitList(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  multiCheckFields(s21_multiset, std_multiset);
}

#define TESTS_CONSTRUCTOR_INIT_LIST(suiteName)           \
  TEST(suiteName, intInitList) {                         \
    multiConstructorInitList<int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleInitList) {                      \
    multiConstructorInitList<double>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassInitList) {                   \
    multiConstructorInitList<MockClass>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringInitList) {                      \
    multiConstructorInitList<std::string>(DEF_STR_KEYS); \
  }

TESTS_CONSTRUCTOR_INIT_LIST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiConstructorCopyEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_copy(s21_multiset);
  std::multiset<key_type> std_map_copy(std_multiset);

  multiCheckFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY_EMPTY(suiteName)                             \
  TEST(suiteName, intCopyEmpty) { multiConstructorCopyEmpty<int>(); }       \
  TEST(suiteName, doubleCopyEmpty) { multiConstructorCopyEmpty<double>(); } \
  TEST(suiteName, mockClassCopyEmpty) {                                     \
    multiConstructorCopyEmpty<MockClass>();                                 \
  }                                                                         \
  TEST(suiteName, stringCopyEmpty) { multiConstructorCopyEmpty<std::string>(); }

TESTS_CONSTRUCTOR_COPY_EMPTY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiConstructorCopy(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_copy(s21_multiset);
  std::multiset<key_type> std_map_copy(std_multiset);

  multiCheckFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY(suiteName)                                     \
  TEST(suiteName, intCopy) { multiConstructorCopy<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleCopy) { multiConstructorCopy<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassCopy) {                                            \
    multiConstructorCopy<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                           \
  TEST(suiteName, stringCopy) {                                               \
    multiConstructorCopy<std::string>(DEF_STR_KEYS);                          \
  }

TESTS_CONSTRUCTOR_COPY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiConstructorMoveEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_move(std::move(s21_multiset));
  std::multiset<key_type> std_map_move(std::move(std_multiset));

  multiCheckFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE_EMPTY(suiteName)                             \
  TEST(suiteName, intMoveEmpty) { multiConstructorMoveEmpty<int>(); }       \
  TEST(suiteName, doubleMoveEmpty) { multiConstructorMoveEmpty<double>(); } \
  TEST(suiteName, mockClassMoveEmpty) {                                     \
    multiConstructorMoveEmpty<MockClass>();                                 \
  }                                                                         \
  TEST(suiteName, stringMoveEmpty) { multiConstructorMoveEmpty<std::string>(); }

TESTS_CONSTRUCTOR_MOVE_EMPTY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiConstructorMove(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_move(std::move(s21_multiset));
  std::multiset<key_type> std_map_move(std::move(std_multiset));

  multiCheckFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE(suiteName)                                     \
  TEST(suiteName, intMove) { multiConstructorMove<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleMove) { multiConstructorMove<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassMove) {                                            \
    multiConstructorMove<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                           \
  TEST(suiteName, stringMove) {                                               \
    multiConstructorMove<std::string>(DEF_STR_KEYS);                          \
  }

TESTS_CONSTRUCTOR_MOVE(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiOperatorCopyEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_copy = s21_multiset;
  std::multiset<key_type> std_map_copy = std_multiset;

  multiCheckFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY_EMPTY(suiteName)                               \
  TEST(suiteName, intOperatorCopyEmpty) { multiOperatorCopyEmpty<int>(); } \
  TEST(suiteName, doubleOperatorCopyEmpty) {                               \
    multiOperatorCopyEmpty<double>();                                      \
  }                                                                        \
  TEST(suiteName, mockClassOperatorCopyEmpty) {                            \
    multiOperatorCopyEmpty<MockClass>();                                   \
  }                                                                        \
  TEST(suiteName, stringOperatorCopyEmpty) {                               \
    multiOperatorCopyEmpty<std::string>();                                 \
  }

TESTS_OPERATOR_COPY_EMPTY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiOperatorCopy(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_copy = s21_multiset;
  std::multiset<key_type> std_map_copy = std_multiset;

  multiCheckFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY(suiteName)                                       \
  TEST(suiteName, intOperatorCopy) { multiOperatorCopy<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleOperatorCopy) {                                      \
    multiOperatorCopy<double>(DEF_DBL_KEYS);                                 \
  }                                                                          \
  TEST(suiteName, mockClassOperatorCopy) {                                   \
    multiOperatorCopy<MockClass>(DEF_MOCK_KEYS);                             \
  }                                                                          \
  TEST(suiteName, stringOperatorCopy) {                                      \
    multiOperatorCopy<std::string>(DEF_STR_KEYS);                            \
  }

TESTS_OPERATOR_COPY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiOperatorMoveEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_move = std::move(s21_multiset);
  std::multiset<key_type> std_map_move = std::move(std_multiset);

  multiCheckFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE_EMPTY(suiteName)                               \
  TEST(suiteName, intOperatorMoveEmpty) { multiOperatorMoveEmpty<int>(); } \
  TEST(suiteName, doubleOperatorMoveEmpty) {                               \
    multiOperatorMoveEmpty<double>();                                      \
  }                                                                        \
  TEST(suiteName, mockClassOperatorMoveEmpty) {                            \
    multiOperatorMoveEmpty<MockClass>();                                   \
  }                                                                        \
  TEST(suiteName, stringOperatorMoveEmptye) {                              \
    multiOperatorMoveEmpty<std::string>();                                 \
  }

TESTS_OPERATOR_MOVE_EMPTY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiOperatorMove(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_move = std::move(s21_multiset);
  std::multiset<key_type> std_map_move = std::move(std_multiset);

  multiCheckFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE(suiteName)                                       \
  TEST(suiteName, intOperatorMove) { multiOperatorMove<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleOperatorMove) {                                      \
    multiOperatorMove<double>(DEF_DBL_KEYS);                                 \
  }                                                                          \
  TEST(suiteName, mockClassOperatorMove) {                                   \
    multiOperatorMove<MockClass>(DEF_MOCK_KEYS);                             \
  }                                                                          \
  TEST(suiteName, stringOperatorMove) {                                      \
    multiOperatorMove<std::string>(DEF_STR_KEYS);                            \
  }

TESTS_OPERATOR_MOVE(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodEmpty(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_map_empty.empty(), std_map_empty.empty());
}

#define TESTS_EMPTY(suiteName)                                             \
  TEST(suiteName, intEmpty) { multiMethodEmpty<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleEmpty) { multiMethodEmpty<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassEmpty) {                                        \
    multiMethodEmpty<MockClass>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringEmpty) { multiMethodEmpty<std::string>(DEF_STR_KEYS); }

TESTS_EMPTY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodSize(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_map_empty.size(), std_map_empty.size());
}

#define TESTS_SIZE(suiteName)                                            \
  TEST(suiteName, intSize) { multiMethodSize<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleSize) { multiMethodSize<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassSize) {                                       \
    multiMethodSize<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                      \
  TEST(suiteName, stringSize) { multiMethodSize<std::string>(DEF_STR_KEYS); }

TESTS_SIZE(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodSwap(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  s21::multiset<key_type> s21_map_empty;

  std::multiset<key_type> std_multiset(items);

  multiCheckFields(s21_multiset, std_multiset);
  s21_map_empty.swap(s21_multiset);
  multiCheckFields(s21_map_empty, std_multiset);
}

#define TESTS_SWAP(suiteName)                                            \
  TEST(suiteName, intSwap) { multiMethodSwap<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleSwap) { multiMethodSwap<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassSwap) {                                       \
    multiMethodSwap<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                      \
  TEST(suiteName, stringSwap) { multiMethodSwap<std::string>(DEF_STR_KEYS); }

TESTS_SWAP(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodMergeWithDublicates(
    const std::initializer_list<key_type>& items,
    const std::initializer_list<key_type>& itemsDublicates) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_dublicate(itemsDublicates);
  std::multiset<key_type> std_map_dublicate(itemsDublicates);

  multiCheckFields(s21_multiset, std_multiset);
  multiCheckFields(s21_map_dublicate, std_map_dublicate);

  s21_multiset.merge(s21_map_dublicate);
  std_multiset.merge(std_map_dublicate);

  multiCheckFields(s21_multiset, std_multiset);
}

#define TESTS_MERGE_WITH_DUBLICATES(suiteName)                                 \
  TEST(suiteName, intMergeWithDublicates) {                                    \
    multiMethodMergeWithDublicates<int>(DEF_INT_KEYS, DEF_INT_KEYS_DUBLICATE); \
  }                                                                            \
  TEST(suiteName, doubleMergeWithDublicates) {                                 \
    multiMethodMergeWithDublicates<double>(DEF_DBL_KEYS,                       \
                                           DEF_DBL_KEYS_DUBLICATE);            \
  }                                                                            \
  TEST(suiteName, mockClassMergeWithDublicates) {                              \
    multiMethodMergeWithDublicates<MockClass>(DEF_MOCK_KEYS,                   \
                                              DEF_MOCK_KEYS_DUBLICATE);        \
  }                                                                            \
  TEST(suiteName, stringMergeWithDublicates) {                                 \
    multiMethodMergeWithDublicates<std::string>(DEF_STR_KEYS,                  \
                                                DEF_STR_KEYS_DUBLICATE);       \
  }

TESTS_MERGE_WITH_DUBLICATES(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodMergeWithNoDublicates(
    const std::initializer_list<key_type>& items,
    const std::initializer_list<key_type>& itemsNoDublicates) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_no_dublicate(itemsNoDublicates);
  std::multiset<key_type> std_map_no_dublicate(itemsNoDublicates);

  multiCheckFields(s21_multiset, std_multiset);
  multiCheckFields(s21_map_no_dublicate, std_map_no_dublicate);

  s21_multiset.merge(s21_map_no_dublicate);
  std_multiset.merge(std_map_no_dublicate);

  multiCheckFields(s21_multiset, std_multiset);
}

#define TESTS_MERGE_WITH_NO_DUBLICATES(suiteName)                             \
  TEST(suiteName, intMergeWithNoDublicates) {                                 \
    multiMethodMergeWithNoDublicates<int>(DEF_INT_KEYS,                       \
                                          DEF_INT_KEYS_NO_DUBLICATE);         \
  }                                                                           \
  TEST(suiteName, doubleMergeWithNoDublicates) {                              \
    multiMethodMergeWithNoDublicates<double>(DEF_DBL_KEYS,                    \
                                             DEF_DBL_KEYS_NO_DUBLICATE);      \
  }                                                                           \
  TEST(suiteName, mockClassMergeWithNoDublicates) {                           \
    multiMethodMergeWithNoDublicates<MockClass>(DEF_MOCK_KEYS,                \
                                                DEF_MOCK_KEYS_NO_DUBLICATE);  \
  }                                                                           \
  TEST(suiteName, stringMergeWithNoDublicates) {                              \
    multiMethodMergeWithNoDublicates<std::string>(DEF_STR_KEYS,               \
                                                  DEF_STR_KEYS_NO_DUBLICATE); \
  }

TESTS_MERGE_WITH_NO_DUBLICATES(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodClear(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  s21_multiset.clear();
  std_multiset.clear();

  s21_map_empty.clear();
  std_map_empty.clear();

  multiCheckFields(s21_multiset, std_multiset);
  multiCheckFields(s21_map_empty, std_map_empty);
}

#define TESTS_CLEAR(suiteName)                                             \
  TEST(suiteName, intClear) { multiMethodClear<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleClear) { multiMethodClear<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassClear) {                                        \
    multiMethodClear<MockClass>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringClear) { multiMethodClear<std::string>(DEF_STR_KEYS); }

TESTS_CLEAR(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodBegin(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  typename s21::multiset<key_type>::iterator it1 = s21_map_empty.begin();
  typename std::multiset<key_type>::iterator it2 = std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end(), it2 == std_map_empty.end());

  typename s21::multiset<key_type>::iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it4 = std_multiset.begin();

  EXPECT_EQ(it3 != s21_multiset.end(), it4 != std_multiset.end());
  EXPECT_EQ(*it3, *it4);
}

#define TESTS_BEGIN(suiteName)                                             \
  TEST(suiteName, intBegin) { multiMethodBegin<int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleBegin) { multiMethodBegin<double>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassBegin) {                                        \
    multiMethodBegin<MockClass>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringBegin) { multiMethodBegin<std::string>(DEF_STR_KEYS); }

TESTS_BEGIN(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodBeginConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  typename s21::multiset<key_type>::const_iterator it1 = s21_map_empty.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end(), it2 == std_map_empty.end());

  typename s21::multiset<key_type>::const_iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it4 = std_multiset.begin();

  EXPECT_EQ(it3 != s21_multiset.end(), it4 != std_multiset.end());
  EXPECT_EQ(*it3, *it4);
}

#define TESTS_BEGIN_CONST(suiteName)                                           \
  TEST(suiteName, intBeginConst) { multiMethodBeginConst<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleBeginConst) {                                          \
    multiMethodBeginConst<double>(DEF_DBL_KEYS);                               \
  }                                                                            \
  TEST(suiteName, mockClassBeginConst) {                                       \
    multiMethodBeginConst<MockClass>(DEF_MOCK_KEYS);                           \
  }                                                                            \
  TEST(suiteName, stringBeginConst) {                                          \
    multiMethodBeginConst<std::string>(DEF_STR_KEYS);                          \
  }

TESTS_BEGIN_CONST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorPlus(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_PLUS(suiteName)                  \
  TEST(suiteName, intIteratorPlus) {                    \
    multiMethodIteratorPlus<int>(DEF_INT_KEYS);         \
  }                                                     \
  TEST(suiteName, doubleIteratorPlus) {                 \
    multiMethodIteratorPlus<double>(DEF_DBL_KEYS);      \
  }                                                     \
  TEST(suiteName, mockClassIteratorPlus) {              \
    multiMethodIteratorPlus<MockClass>(DEF_MOCK_KEYS);  \
  }                                                     \
  TEST(suiteName, stringIteratorPlus) {                 \
    multiMethodIteratorPlus<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_PLUS(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorMinus(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  --it1;
  --it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_MINUS(suiteName)                  \
  TEST(suiteName, intIteratorMinus) {                    \
    multiMethodIteratorMinus<int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorMinus) {                 \
    multiMethodIteratorMinus<double>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorMinus) {              \
    multiMethodIteratorMinus<MockClass>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorMinus) {                 \
    multiMethodIteratorMinus<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_MINUS(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorAssignment(
    const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::iterator it3 = it1;
  typename std::multiset<key_type>::iterator it4 = it2;

  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*it2, *it4);
}

#define TESTS_ITERATOR_ASSIGNMENT(suiteName)                  \
  TEST(suiteName, intIteratorAssignment) {                    \
    multiMethodIteratorAssignment<int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorAssignment) {                 \
    multiMethodIteratorAssignment<double>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorAssignment) {              \
    multiMethodIteratorAssignment<MockClass>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorAssignment) {                 \
    multiMethodIteratorAssignment<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_ASSIGNMENT(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorEqual(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it4 = std_multiset.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL(suiteName)                  \
  TEST(suiteName, intIteratorEqual) {                    \
    multiMethodIteratorEqual<int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorEqual) {                 \
    multiMethodIteratorEqual<double>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorEqual) {              \
    multiMethodIteratorEqual<MockClass>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorEqual) {                 \
    multiMethodIteratorEqual<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_EQUAL(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorNotEqual(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  EXPECT_EQ(it1 != s21_multiset.end(), it2 != std_multiset.end());
}

#define TESTS_ITERATOR_NOT_EQUAL(suiteName)                 \
  TEST(suiteName, intIteratorNotEqual) {                    \
    multiMethodIteratorNotEqual<int>(DEF_INT_KEYS);         \
  }                                                         \
  TEST(suiteName, doubleIteratorNotEqual) {                 \
    multiMethodIteratorNotEqual<double>(DEF_DBL_KEYS);      \
  }                                                         \
  TEST(suiteName, mockClassIteratorNotEqual) {              \
    multiMethodIteratorNotEqual<MockClass>(DEF_MOCK_KEYS);  \
  }                                                         \
  TEST(suiteName, stringIteratorNotEqual) {                 \
    multiMethodIteratorNotEqual<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_NOT_EQUAL(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorPlusConst(
    const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_PLUS_CONST(suiteName)                 \
  TEST(suiteName, intIteratorPlusConst) {                    \
    multiMethodIteratorPlusConst<int>(DEF_INT_KEYS);         \
  }                                                          \
  TEST(suiteName, doubleIteratorPlusConst) {                 \
    multiMethodIteratorPlusConst<double>(DEF_DBL_KEYS);      \
  }                                                          \
  TEST(suiteName, mockClassIteratorPlusConst) {              \
    multiMethodIteratorPlusConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                          \
  TEST(suiteName, stringIteratorPlusConst) {                 \
    multiMethodIteratorPlusConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_PLUS_CONST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorMinusConst(
    const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  --it1;
  --it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_MINUS_CONST(suiteName)                 \
  TEST(suiteName, intIteratorMinusConst) {                    \
    multiMethodIteratorMinusConst<int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorMinusConst) {                 \
    multiMethodIteratorMinusConst<double>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorMinusConst) {              \
    multiMethodIteratorMinusConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorMinusConst) {                 \
    multiMethodIteratorMinusConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_MINUS_CONST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorAssignmentConst(
    const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::const_iterator it3 = it1;
  typename std::multiset<key_type>::const_iterator it4 = it2;

  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*it2, *it4);
}

#define TESTS_ITERATOR_ASSIGNMENT_CONST(suiteName)                 \
  TEST(suiteName, intIteratorAssignmentConst) {                    \
    multiMethodIteratorAssignmentConst<int>(DEF_INT_KEYS);         \
  }                                                                \
  TEST(suiteName, doubleIteratorAssignmentConst) {                 \
    multiMethodIteratorAssignmentConst<double>(DEF_DBL_KEYS);      \
  }                                                                \
  TEST(suiteName, mockClassIteratorAssignmentConst) {              \
    multiMethodIteratorAssignmentConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                                \
  TEST(suiteName, stringIteratorAssignmentConst) {                 \
    multiMethodIteratorAssignmentConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_ASSIGNMENT_CONST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorEqualConst(
    const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::const_iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it4 = std_multiset.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL_CONST(suiteName)                 \
  TEST(suiteName, intIteratorEqualConst) {                    \
    multiMethodIteratorEqualConst<int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorEqualConst) {                 \
    multiMethodIteratorEqualConst<double>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorEqualConst) {              \
    multiMethodIteratorEqualConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorEqualConst) {                 \
    multiMethodIteratorEqualConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_EQUAL_CONST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodIteratorNotEqualConst(
    const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  EXPECT_EQ(it1 != s21_multiset.end(), it2 != std_multiset.end());
}

#define TESTS_ITERATOR_NOT_EQUAL_CONST(suiteName)                \
  TEST(suiteName, intIteratorNotEqualConst) {                    \
    multiMethodIteratorNotEqualConst<int>(DEF_INT_KEYS);         \
  }                                                              \
  TEST(suiteName, doubleIteratorNotEqualConst) {                 \
    multiMethodIteratorNotEqualConst<double>(DEF_DBL_KEYS);      \
  }                                                              \
  TEST(suiteName, mockClassIteratorNotEqualConst) {              \
    multiMethodIteratorNotEqualConst<MockClass>(DEF_MOCK_KEYS);  \
  }                                                              \
  TEST(suiteName, stringIteratorNotEqualConst) {                 \
    multiMethodIteratorNotEqualConst<std::string>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_NOT_EQUAL_CONST(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodInsertNoDuplicate(const std::initializer_list<key_type>& items,
                                  const key_type& key) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.insert(key);
  typename std::multiset<key_type>::iterator it2 = std_multiset.insert(key);

  multiCheckFields(s21_multiset, std_multiset);

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_INSERT_NO_DUPLICATE(suiteName)                          \
  TEST(suiteName, intInsertNoDuplicate) {                             \
    multiMethodInsertNoDuplicate<int>(DEF_INT_KEYS, INT_KEY);         \
  }                                                                   \
  TEST(suiteName, doubleInsertNoDuplicate) {                          \
    multiMethodInsertNoDuplicate<double>(DEF_DBL_KEYS, DBL_KEY);      \
  }                                                                   \
  TEST(suiteName, mockClassInsertNoDuplicate) {                       \
    multiMethodInsertNoDuplicate<MockClass>(DEF_MOCK_KEYS, MOCK_KEY); \
  }                                                                   \
  TEST(suiteName, stringInsertNoDuplicate) {                          \
    multiMethodInsertNoDuplicate<std::string>(DEF_STR_KEYS, STR_KEY); \
  }

TESTS_INSERT_NO_DUPLICATE(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodInsertDuplicate(const std::initializer_list<key_type>& items,
                                const key_type& key) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.insert(key);
  typename std::multiset<key_type>::iterator it2 = std_multiset.insert(key);

  multiCheckFields(s21_multiset, std_multiset);

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_INSERT_DUPLICATE(suiteName)                                     \
  TEST(suiteName, intInsertDuplicate) {                                       \
    multiMethodInsertDuplicate<int>(DEF_INT_KEYS, INT_KEY_DUPLICATE);         \
  }                                                                           \
  TEST(suiteName, doubleInsertDuplicate) {                                    \
    multiMethodInsertDuplicate<double>(DEF_DBL_KEYS, DBL_KEY_DUPLICATE);      \
  }                                                                           \
  TEST(suiteName, mockClassInsertDuplicate) {                                 \
    multiMethodInsertDuplicate<MockClass>(DEF_MOCK_KEYS, MOCK_KEY_DUPLICATE); \
  }                                                                           \
  TEST(suiteName, stringInsertDuplicate) {                                    \
    multiMethodInsertDuplicate<std::string>(DEF_STR_KEYS, STR_KEY_DUPLICATE); \
  }

TESTS_INSERT_DUPLICATE(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodErase(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21_multiset.erase(s21_multiset.begin());
  std_multiset.erase(std_multiset.begin());

  multiCheckFields(s21_multiset, std_multiset);

  s21_multiset.erase(s21_multiset.begin());
  std_multiset.erase(std_multiset.begin());

  multiCheckFields(s21_multiset, std_multiset);
}

#define TESTS_ERASE(suiteName)                                             \
  TEST(suiteName, intMethodErase) { multiMethodErase<int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleMethodErase) {                                     \
    multiMethodErase<double>(DEF_DBL_KEYS);                                \
  }                                                                        \
  TEST(suiteName, mockClassMethodErase) {                                  \
    multiMethodErase<MockClass>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringMethodErase) {                                     \
    multiMethodErase<std::string>(DEF_STR_KEYS);                           \
  }

TESTS_ERASE(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodContains(const std::initializer_list<key_type>& items,
                         const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);

  ASSERT_FALSE(s21_multiset.contains(key));
  ASSERT_TRUE(s21_multiset.contains(key_duplicate));
}

#define TESTS_CONTAINS(suiteName)                                          \
  TEST(suiteName, intMethodContains) {                                     \
    multiMethodContains<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);    \
  }                                                                        \
  TEST(suiteName, doubleMethodContains) {                                  \
    multiMethodContains<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); \
  }                                                                        \
  TEST(suiteName, mockClassMethodContains) {                               \
    multiMethodContains<MockClass>(DEF_MOCK_KEYS, MOCK_KEY,                \
                                   MOCK_KEY_DUPLICATE);                    \
  }                                                                        \
  TEST(suiteName, stringMethodContains) {                                  \
    multiMethodContains<std::string>(DEF_STR_KEYS, STR_KEY,                \
                                     STR_KEY_DUPLICATE);                   \
  }

TESTS_CONTAINS(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodInsertMany(
    const std::initializer_list<key_type>& items,
    const std::initializer_list<key_type>& insert_items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21_multiset.insert_many(*insert_items.begin(), *(insert_items.begin() + 1),
                           *(insert_items.begin() + 2));
  std_multiset.insert(*insert_items.begin());
  std_multiset.insert(*(insert_items.begin() + 1));
  std_multiset.insert(*(insert_items.begin() + 2));

  multiCheckFields(s21_multiset, std_multiset);
}

#define TESTS_INSERT_MANY(suiteName)                                        \
  TEST(suiteName, intMethodInsertMany) {                                    \
    multiMethodInsertMany<int>(DEF_INT_KEYS, DEF_INT_KEYS_NO_DUBLICATE);    \
  }                                                                         \
  TEST(suiteName, doubleMethodInsertMany) {                                 \
    multiMethodInsertMany<double>(DEF_DBL_KEYS, DEF_DBL_KEYS_NO_DUBLICATE); \
  }                                                                         \
  TEST(suiteName, mockClassMethodInsertMany) {                              \
    multiMethodInsertMany<MockClass>(DEF_MOCK_KEYS,                         \
                                     DEF_MOCK_KEYS_NO_DUBLICATE);           \
  }                                                                         \
  TEST(suiteName, stringMethodInsertMany) {                                 \
    multiMethodInsertMany<std::string>(DEF_STR_KEYS,                        \
                                       DEF_STR_KEYS_NO_DUBLICATE);          \
  }

TESTS_INSERT_MANY(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodFind(const std::initializer_list<key_type>& items,
                     const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.find(key) == s21_multiset.end(),
            std_multiset.find(key) == std_multiset.end());

  EXPECT_EQ(*(s21_multiset.find(key_duplicate)),
            *(std_multiset.find(key_duplicate)));
}

#define TESTS_FIND(suiteName)                                                \
  TEST(suiteName, intMethodFind) {                                           \
    multiMethodFind<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);          \
  }                                                                          \
  TEST(suiteName, doubleMethodFind) {                                        \
    multiMethodFind<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE);       \
  }                                                                          \
  TEST(suiteName, mockClassMethodFind) {                                     \
    multiMethodFind<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); \
  }                                                                          \
  TEST(suiteName, stringMethodFind) {                                        \
    multiMethodFind<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE);  \
  }

TESTS_FIND(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodCount(const std::initializer_list<key_type>& items,
                      const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.count(key) == 0, std_multiset.count(key) == 0);

  EXPECT_EQ(s21_multiset.count(key_duplicate),
            std_multiset.count(key_duplicate));
}

#define TESTS_COUNT(suiteName)                                                \
  TEST(suiteName, intMethodCount) {                                           \
    multiMethodCount<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);          \
  }                                                                           \
  TEST(suiteName, doubleMethodCount) {                                        \
    multiMethodCount<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE);       \
  }                                                                           \
  TEST(suiteName, mockClassMethodCount) {                                     \
    multiMethodCount<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); \
  }                                                                           \
  TEST(suiteName, stringMethodCount) {                                        \
    multiMethodCount<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE);  \
  }

TESTS_COUNT(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodLowerBound(const std::initializer_list<key_type>& items,
                           const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.lower_bound(key) == s21_multiset.end(),
            std_multiset.lower_bound(key) == std_multiset.end());

  EXPECT_EQ(*(s21_multiset.lower_bound(key_duplicate)--),
            *(std_multiset.lower_bound(key_duplicate)--));
}

#define TESTS_LOWER_BOUND(suiteName)                                         \
  TEST(suiteName, intMethodLowerBound) {                                     \
    multiMethodLowerBound<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);    \
  }                                                                          \
  TEST(suiteName, doubleMethodLowerBound) {                                  \
    multiMethodLowerBound<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); \
  }                                                                          \
  TEST(suiteName, mockClassMethodLowerBound) {                               \
    multiMethodLowerBound<MockClass>(DEF_MOCK_KEYS, MOCK_KEY,                \
                                     MOCK_KEY_DUPLICATE);                    \
  }                                                                          \
  TEST(suiteName, stringMethodLowerBound) {                                  \
    multiMethodLowerBound<std::string>(DEF_STR_KEYS, STR_KEY,                \
                                       STR_KEY_DUPLICATE);                   \
  }

TESTS_LOWER_BOUND(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodUpperBound(const std::initializer_list<key_type>& items,
                           const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.upper_bound(key) == s21_multiset.end(),
            std_multiset.upper_bound(key) == std_multiset.end());

  EXPECT_EQ(*(s21_multiset.upper_bound(key_duplicate)++),
            *(std_multiset.upper_bound(key_duplicate)++));
}

#define TESTS_UPPER_BOUND(suiteName)                                         \
  TEST(suiteName, intMethodUpperBound) {                                     \
    multiMethodUpperBound<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);    \
  }                                                                          \
  TEST(suiteName, doubleMethodUpperBound) {                                  \
    multiMethodUpperBound<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); \
  }                                                                          \
  TEST(suiteName, mockClassMethodUpperBound) {                               \
    multiMethodUpperBound<MockClass>(DEF_MOCK_KEYS, MOCK_KEY,                \
                                     MOCK_KEY_DUPLICATE);                    \
  }                                                                          \
  TEST(suiteName, stringMethodUpperBound) {                                  \
    multiMethodUpperBound<std::string>(DEF_STR_KEYS, STR_KEY,                \
                                       STR_KEY_DUPLICATE);                   \
  }

TESTS_UPPER_BOUND(s21Multiset)

// -------------------------------------------------

template <typename key_type>
void multiMethodEqualRange(const std::initializer_list<key_type>& items,
                           const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);

  EXPECT_TRUE(s21_multiset.equal_range(key).first ==
              s21_multiset.lower_bound(key));
  EXPECT_TRUE(s21_multiset.equal_range(key).second ==
              s21_multiset.upper_bound(key));

  EXPECT_TRUE(s21_multiset.equal_range(key_duplicate).first ==
              s21_multiset.lower_bound(key_duplicate));
  EXPECT_TRUE(s21_multiset.equal_range(key_duplicate).second ==
              s21_multiset.upper_bound(key_duplicate));
}

#define TESTS_EQUAL_RANGE(suiteName)                                         \
  TEST(suiteName, intMethodEqualRange) {                                     \
    multiMethodEqualRange<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);    \
  }                                                                          \
  TEST(suiteName, doubleMethodEqualRange) {                                  \
    multiMethodEqualRange<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); \
  }                                                                          \
  TEST(suiteName, mockClassMethodEqualRange) {                               \
    multiMethodEqualRange<MockClass>(DEF_MOCK_KEYS, MOCK_KEY,                \
                                     MOCK_KEY_DUPLICATE);                    \
  }                                                                          \
  TEST(suiteName, stringMethodEqualRange) {                                  \
    multiMethodEqualRange<std::string>(DEF_STR_KEYS, STR_KEY,                \
                                       STR_KEY_DUPLICATE);                   \
  }

TESTS_EQUAL_RANGE(s21Multiset)

// -------------------------------------------------

#define TEST_ROUNDS 3000

template <typename key_type>
void multiBigLineTree(int rounds) {
  s21::multiset<key_type> actual;
  std::multiset<key_type> expected;

  srand(static_cast<int>((std::size_t)&actual));

  for (int i = 0; i < rounds; i++) {
    actual.insert(i);
    expected.insert(i);
  }

  multiCheckFields(actual, expected);
}

#define TESTS_BIG_LINE_TREE(suiteName) \
  TEST(suiteName, intBigLineTree) { multiBigLineTree<int>(TEST_ROUNDS); }

TESTS_BIG_LINE_TREE(s21Multiset)

// -------------------------------------------------

double multiGetRandMultiset(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

template <typename key_type>
void multiBigRandomTree(int rMin, int rMax, int rounds) {
  s21::multiset<key_type> actual;
  std::multiset<key_type> expected;

  srand(static_cast<int>((std::size_t)&actual));

  for (int i = 0; i < rounds; i++) {
    auto val = multiGetRandMultiset(rMin, rMax);
    actual.insert(val);
    expected.insert(val);
  }

  multiCheckFields(actual, expected);
}

#define TEST_RAND_MIN -10000
#define TEST_RAND_MAX 10000
#define TEST_RAND_ROUNDS 1000

#define TESTS_BIG_RANDOM_TREE(suiteName)                                     \
  TEST(suiteName, intBigRandomTree) {                                        \
    multiBigRandomTree<int>(TEST_RAND_MIN, TEST_RAND_MAX, TEST_RAND_ROUNDS); \
  }                                                                          \
  TEST(suiteName, doubleBigRandomTree) {                                     \
    multiBigRandomTree<double>(TEST_RAND_MIN, TEST_RAND_MAX,                 \
                               TEST_RAND_ROUNDS);                            \
  }

TESTS_BIG_RANDOM_TREE(s21Multiset)