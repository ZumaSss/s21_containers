#include "core/s21_map.h"

#include <map>

#include "s21_core_tests.h"

#define DEF_INT_KEYS                          \
  {                                           \
    {1, 2}, {2, 4}, {3, 69}, {4, 4}, { 8, 6 } \
  }
#define DEF_DBL_KEYS                                                   \
  {                                                                    \
    {4.35, 321}, {2.977, 12}, {873.23, 6}, {6.875, 69}, { 9.6534, 98 } \
  }
#define DEF_MOCK_KEYS                              \
  {                                                \
    {1, 542}, {4, 5}, {44, 69}, {45, 6}, { 88, 4 } \
  }
#define DEF_STR_KEYS                                                 \
  {                                                                  \
    {"hello", 2}, {"world", 4}, {"!", 69}, {"mock", 6}, { "set", 4 } \
  }

#define DEF_INT_KEYS_DUBLICATE                \
  {                                           \
    {6, 2}, {2, 4}, {3, 5}, {8, 6}, { 10, 0 } \
  }
#define DEF_DBL_KEYS_DUBLICATE                                         \
  {                                                                    \
    {5.41, 321}, {2.977, 12}, {873.23, 6}, {6.875, 0}, { 123.123, 98 } \
  }
#define DEF_MOCK_KEYS_DUBLICATE                     \
  {                                                 \
    {1, 542}, {9, 5}, {10, 3}, {45, 6}, { 10, 123 } \
  }
#define DEF_STR_KEYS_DUBLICATE                                          \
  {                                                                     \
    {"hello", 2}, {"test", 4}, {"!!!", 8}, {"this", 2}, { "mock", 564 } \
  }

#define DEF_INT_KEYS_NO_DUBLICATE                 \
  {                                               \
    {6, 2}, {5, 4}, {10, 5}, {9, 432}, { 11, 32 } \
  }
#define DEF_DBL_KEYS_NO_DUBLICATE                                      \
  {                                                                    \
    {7.523, 321}, {234.4, 12}, {1.001, 6}, {1.002, 7}, { 124.124, 99 } \
  }
#define DEF_MOCK_KEYS_NO_DUBLICATE                    \
  {                                                   \
    {98, 542}, {9, 5}, {10, 3}, {11, 6}, { 90, 4123 } \
  }
#define DEF_STR_KEYS_NO_DUBLICATE                                   \
  {                                                                 \
    {"this", 2}, {"is", 4}, {"test", 8}, {"or", 3}, { "not", 1234 } \
  }

#define INT_PAIR std::make_pair(69, 69)
#define DBL_PAIR std::make_pair(69.69, 69)
#define MOCK_PAIR std::make_pair(69, 69)
#define STR_PAIR std::make_pair("69", 69)

#define INT_PAIR_DUPLICATE std::make_pair(3, 69)
#define DBL_PAIR_DUPLICATE std::make_pair(6.875, 69)
#define MOCK_PAIR_DUPLICATE std::make_pair(44, 69)
#define STR_PAIR_DUPLICATE std::make_pair("!", 69)

#define INT_KEY 69
#define DBL_KEY 69.69
#define MOCK_KEY 69
#define STR_KEY "69"

#define INT_KEY_DUPLICATE 3
#define DBL_KEY_DUPLICATE 6.875
#define MOCK_KEY_DUPLICATE 44
#define STR_KEY_DUPLICATE "!"

#define INT_OBJ 69
#define DBL_OBJ 69
#define MOCK_OBJ 69
#define STR_OBJ 69

template <typename key_type, typename mapped_type>
void checkFields(const s21::map<key_type, mapped_type>& s21_map,
                 const std::map<key_type, mapped_type>& std_map) {
  auto std_it = std_map.begin();
  for (auto s21_it : s21_map) {
    EXPECT_EQ(s21_it.first, (*std_it).first);
    EXPECT_EQ(s21_it.second, (*std_it).second);

    ++std_it;
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
}

template <typename key_type, typename mapped_type>
void checkFieldsEmpty(const s21::map<key_type, mapped_type>& s21_map,
                      const std::map<key_type, mapped_type>& std_map) {
  auto std_it = std_map.begin();
  for (auto s21_it : s21_map) {
    EXPECT_EQ(s21_it.first, (*std_it).first);
    EXPECT_EQ(s21_it.second, (*std_it).second);

    ++std_it;
  }
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorDefaultAsCont() {
  s21::IContainer* ct = new s21::map<key_type, mapped_type>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_CONSTRUCTOR_INIT_AS_CONT(suiteName)                          \
  TEST(suiteName, intInitAsCont) { constructorDefaultAsCont<int, int>(); } \
  TEST(suiteName, doubleInitAsCont) {                                      \
    constructorDefaultAsCont<double, int>();                               \
  }                                                                        \
  TEST(suiteName, mockClassInitAsCont) {                                   \
    constructorDefaultAsCont<MockClass, int>();                            \
  }                                                                        \
  TEST(suiteName, stringInitAsCont) {                                      \
    constructorDefaultAsCont<std::string, int>();                          \
  }

TESTS_CONSTRUCTOR_INIT_AS_CONT(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorDefault() {
  s21::map<key_type, mapped_type> s21_map;
  std::map<key_type, mapped_type> std_map;

  checkFieldsEmpty(s21_map, std_map);
}

#define TESTS_DEFAULT_CONSTRUCTOR_INIT(suiteName)                             \
  TEST(suiteName, intDefInit) { constructorDefault<int, int>(); }             \
  TEST(suiteName, doubleDefInit) { constructorDefault<double, int>(); }       \
  TEST(suiteName, mockClassDefInit) { constructorDefault<MockClass, int>(); } \
  TEST(suiteName, stringDefInit) { constructorDefault<std::string, int>(); }

TESTS_DEFAULT_CONSTRUCTOR_INIT(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorInitList(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  checkFields(s21_map, std_map);
}

#define TESTS_CONSTRUCTOR_INIT_LIST(suiteName)           \
  TEST(suiteName, intInitList) {                         \
    constructorInitList<int, int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleInitList) {                      \
    constructorInitList<double, int>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassInitList) {                   \
    constructorInitList<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringInitList) {                      \
    constructorInitList<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_CONSTRUCTOR_INIT_LIST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorCopyEmpty() {
  s21::map<key_type, mapped_type> s21_map;
  std::map<key_type, mapped_type> std_map;

  s21::map<key_type, mapped_type> s21_map_copy(s21_map);
  std::map<key_type, mapped_type> std_map_copy(std_map);

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY_EMPTY(suiteName)                             \
  TEST(suiteName, intCopyEmpty) { constructorCopyEmpty<int, int>(); }       \
  TEST(suiteName, doubleCopyEmpty) { constructorCopyEmpty<double, int>(); } \
  TEST(suiteName, mockClassCopyEmpty) {                                     \
    constructorCopyEmpty<MockClass, int>();                                 \
  }                                                                         \
  TEST(suiteName, stringCopyEmpty) { constructorCopyEmpty<std::string, int>(); }

TESTS_CONSTRUCTOR_COPY_EMPTY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorCopy(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_copy(s21_map);
  std::map<key_type, mapped_type> std_map_copy(std_map);

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY(suiteName)                                     \
  TEST(suiteName, intCopy) { constructorCopy<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleCopy) { constructorCopy<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassCopy) {                                            \
    constructorCopy<MockClass, int>(DEF_MOCK_KEYS);                           \
  }                                                                           \
  TEST(suiteName, stringCopy) {                                               \
    constructorCopy<std::string, int>(DEF_STR_KEYS);                          \
  }

TESTS_CONSTRUCTOR_COPY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorMoveEmpty() {
  s21::map<key_type, mapped_type> s21_map;
  std::map<key_type, mapped_type> std_map;

  s21::map<key_type, mapped_type> s21_map_move(std::move(s21_map));
  std::map<key_type, mapped_type> std_map_move(std::move(std_map));

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE_EMPTY(suiteName)                             \
  TEST(suiteName, intMoveEmpty) { constructorMoveEmpty<int, int>(); }       \
  TEST(suiteName, doubleMoveEmpty) { constructorMoveEmpty<double, int>(); } \
  TEST(suiteName, mockClassMoveEmpty) {                                     \
    constructorMoveEmpty<MockClass, int>();                                 \
  }                                                                         \
  TEST(suiteName, stringMoveEmpty) { constructorMoveEmpty<std::string, int>(); }

TESTS_CONSTRUCTOR_MOVE_EMPTY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void constructorMove(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_move(std::move(s21_map));
  std::map<key_type, mapped_type> std_map_move(std::move(std_map));

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE(suiteName)                                     \
  TEST(suiteName, intMove) { constructorMove<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleMove) { constructorMove<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassMove) {                                            \
    constructorMove<MockClass, int>(DEF_MOCK_KEYS);                           \
  }                                                                           \
  TEST(suiteName, stringMove) {                                               \
    constructorMove<std::string, int>(DEF_STR_KEYS);                          \
  }

TESTS_CONSTRUCTOR_MOVE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void operatorCopyEmpty() {
  s21::map<key_type, mapped_type> s21_map;
  std::map<key_type, mapped_type> std_map;

  s21::map<key_type, mapped_type> s21_map_copy = s21_map;
  std::map<key_type, mapped_type> std_map_copy = std_map;

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY_EMPTY(suiteName)                               \
  TEST(suiteName, intOperatorCopyEmpty) { operatorCopyEmpty<int, int>(); } \
  TEST(suiteName, doubleOperatorCopyEmpty) {                               \
    operatorCopyEmpty<double, int>();                                      \
  }                                                                        \
  TEST(suiteName, mockClassOperatorCopyEmpty) {                            \
    operatorCopyEmpty<MockClass, int>();                                   \
  }                                                                        \
  TEST(suiteName, stringOperatorCopyEmpty) {                               \
    operatorCopyEmpty<std::string, int>();                                 \
  }

TESTS_OPERATOR_COPY_EMPTY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void operatorCopy(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_copy = s21_map;
  std::map<key_type, mapped_type> std_map_copy = std_map;

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY(suiteName)                                       \
  TEST(suiteName, intOperatorCopy) { operatorCopy<int, int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleOperatorCopy) {                                      \
    operatorCopy<double, int>(DEF_DBL_KEYS);                                 \
  }                                                                          \
  TEST(suiteName, mockClassOperatorCopy) {                                   \
    operatorCopy<MockClass, int>(DEF_MOCK_KEYS);                             \
  }                                                                          \
  TEST(suiteName, stringOperatorCopy) {                                      \
    operatorCopy<std::string, int>(DEF_STR_KEYS);                            \
  }

TESTS_OPERATOR_COPY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void operatorMoveEmpty() {
  s21::map<key_type, mapped_type> s21_map;
  std::map<key_type, mapped_type> std_map;

  s21::map<key_type, mapped_type> s21_map_move = std::move(s21_map);
  std::map<key_type, mapped_type> std_map_move = std::move(std_map);

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE_EMPTY(suiteName)                               \
  TEST(suiteName, intOperatorMoveEmpty) { operatorMoveEmpty<int, int>(); } \
  TEST(suiteName, doubleOperatorMoveEmpty) {                               \
    operatorMoveEmpty<double, int>();                                      \
  }                                                                        \
  TEST(suiteName, mockClassOperatorMoveEmpty) {                            \
    operatorMoveEmpty<MockClass, int>();                                   \
  }                                                                        \
  TEST(suiteName, stringOperatorMoveEmptye) {                              \
    operatorMoveEmpty<std::string, int>();                                 \
  }

TESTS_OPERATOR_MOVE_EMPTY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void operatorMove(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_move = std::move(s21_map);
  std::map<key_type, mapped_type> std_map_move = std::move(std_map);

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE(suiteName)                                       \
  TEST(suiteName, intOperatorMove) { operatorMove<int, int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleOperatorMove) {                                      \
    operatorMove<double, int>(DEF_DBL_KEYS);                                 \
  }                                                                          \
  TEST(suiteName, mockClassOperatorMove) {                                   \
    operatorMove<MockClass, int>(DEF_MOCK_KEYS);                             \
  }                                                                          \
  TEST(suiteName, stringOperatorMove) {                                      \
    operatorMove<std::string, int>(DEF_STR_KEYS);                            \
  }

TESTS_OPERATOR_MOVE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodEmpty(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_empty;
  std::map<key_type, mapped_type> std_map_empty;

  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map_empty.empty(), std_map_empty.empty());
}

#define TESTS_EMPTY(suiteName)                                             \
  TEST(suiteName, intEmpty) { methodEmpty<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleEmpty) { methodEmpty<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassEmpty) {                                        \
    methodEmpty<MockClass, int>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringEmpty) { methodEmpty<std::string, int>(DEF_STR_KEYS); }

TESTS_EMPTY(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodSize(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_empty;
  std::map<key_type, mapped_type> std_map_empty;

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_empty.size(), std_map_empty.size());
}

#define TESTS_SIZE(suiteName)                                             \
  TEST(suiteName, intSize) { methodEmpty<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleSize) { methodEmpty<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassSize) {                                        \
    methodEmpty<MockClass, int>(DEF_MOCK_KEYS);                           \
  }                                                                       \
  TEST(suiteName, stringSize) { methodEmpty<std::string, int>(DEF_STR_KEYS); }

TESTS_SIZE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodSwap(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  s21::map<key_type, mapped_type> s21_map_empty;

  std::map<key_type, mapped_type> std_map(items);

  checkFields(s21_map, std_map);
  s21_map_empty.swap(s21_map);
  checkFields(s21_map_empty, std_map);
}

#define TESTS_SWAP(suiteName)                                            \
  TEST(suiteName, intSwap) { methodSwap<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleSwap) { methodSwap<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassSwap) {                                       \
    methodSwap<MockClass, int>(DEF_MOCK_KEYS);                           \
  }                                                                      \
  TEST(suiteName, stringSwap) { methodSwap<std::string, int>(DEF_STR_KEYS); }

TESTS_SWAP(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodMergeWithDublicates(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        itemsDublicates) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_dublicate(itemsDublicates);
  std::map<key_type, mapped_type> std_map_dublicate(itemsDublicates);

  checkFields(s21_map, std_map);
  checkFields(s21_map_dublicate, std_map_dublicate);

  s21_map.merge(s21_map_dublicate);
  std_map.merge(std_map_dublicate);

  checkFields(s21_map, std_map);
}

#define TESTS_MERGE_WITH_DUBLICATES(suiteName)                                 \
  TEST(suiteName, intMergeWithDublicates) {                                    \
    methodMergeWithDublicates<int, int>(DEF_INT_KEYS, DEF_INT_KEYS_DUBLICATE); \
  }                                                                            \
  TEST(suiteName, doubleMergeWithDublicates) {                                 \
    methodMergeWithDublicates<double, int>(DEF_DBL_KEYS,                       \
                                           DEF_DBL_KEYS_DUBLICATE);            \
  }                                                                            \
  TEST(suiteName, mockClassMergeWithDublicates) {                              \
    methodMergeWithDublicates<MockClass, int>(DEF_MOCK_KEYS,                   \
                                              DEF_MOCK_KEYS_DUBLICATE);        \
  }                                                                            \
  TEST(suiteName, stringMergeWithDublicates) {                                 \
    methodMergeWithDublicates<std::string, int>(DEF_STR_KEYS,                  \
                                                DEF_STR_KEYS_DUBLICATE);       \
  }

TESTS_MERGE_WITH_DUBLICATES(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodMergeWithNoDublicates(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        itemsNoDublicates) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_no_dublicate(itemsNoDublicates);
  std::map<key_type, mapped_type> std_map_no_dublicate(itemsNoDublicates);

  checkFields(s21_map, std_map);
  checkFields(s21_map_no_dublicate, std_map_no_dublicate);

  s21_map.merge(s21_map_no_dublicate);
  std_map.merge(std_map_no_dublicate);

  checkFields(s21_map, std_map);
}

#define TESTS_MERGE_WITH_NO_DUBLICATES(suiteName)                             \
  TEST(suiteName, intMergeWithNoDublicates) {                                 \
    methodMergeWithNoDublicates<int, int>(DEF_INT_KEYS,                       \
                                          DEF_INT_KEYS_NO_DUBLICATE);         \
  }                                                                           \
  TEST(suiteName, doubleMergeWithNoDublicates) {                              \
    methodMergeWithNoDublicates<double, int>(DEF_DBL_KEYS,                    \
                                             DEF_DBL_KEYS_NO_DUBLICATE);      \
  }                                                                           \
  TEST(suiteName, mockClassMergeWithNoDublicates) {                           \
    methodMergeWithNoDublicates<MockClass, int>(DEF_MOCK_KEYS,                \
                                                DEF_MOCK_KEYS_NO_DUBLICATE);  \
  }                                                                           \
  TEST(suiteName, stringMergeWithNoDublicates) {                              \
    methodMergeWithNoDublicates<std::string, int>(DEF_STR_KEYS,               \
                                                  DEF_STR_KEYS_NO_DUBLICATE); \
  }

TESTS_MERGE_WITH_NO_DUBLICATES(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodClear(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_empty;
  std::map<key_type, mapped_type> std_map_empty;

  s21_map.clear();
  std_map.clear();

  s21_map_empty.clear();
  std_map_empty.clear();

  checkFields(s21_map, std_map);
  checkFields(s21_map_empty, std_map_empty);
}

#define TESTS_CLEAR(suiteName)                                             \
  TEST(suiteName, intClear) { methodClear<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleClear) { methodClear<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassClear) {                                        \
    methodClear<MockClass, int>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringClear) { methodClear<std::string, int>(DEF_STR_KEYS); }

TESTS_CLEAR(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodBegin(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_empty;
  std::map<key_type, mapped_type> std_map_empty;

  typename s21::map<key_type, mapped_type>::iterator it1 =
      s21_map_empty.begin();
  typename std::map<key_type, mapped_type>::iterator it2 =
      std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end(), it2 == std_map_empty.end());

  typename s21::map<key_type, mapped_type>::iterator it3 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it4 = std_map.begin();

  EXPECT_EQ(it3 != s21_map.end(), it4 != std_map.end());
  EXPECT_EQ((*it3).second, (*it4).second);
}

#define TESTS_BEGIN(suiteName)                                             \
  TEST(suiteName, intBegin) { methodBegin<int, int>(DEF_INT_KEYS); }       \
  TEST(suiteName, doubleBegin) { methodBegin<double, int>(DEF_DBL_KEYS); } \
  TEST(suiteName, mockClassBegin) {                                        \
    methodBegin<MockClass, int>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringBegin) { methodBegin<std::string, int>(DEF_STR_KEYS); }

TESTS_BEGIN(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodBeginConst(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21::map<key_type, mapped_type> s21_map_empty;
  std::map<key_type, mapped_type> std_map_empty;

  typename s21::map<key_type, mapped_type>::const_iterator it1 =
      s21_map_empty.begin();
  typename std::map<key_type, mapped_type>::const_iterator it2 =
      std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end(), it2 == std_map_empty.end());

  typename s21::map<key_type, mapped_type>::const_iterator it3 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it4 =
      std_map.begin();

  EXPECT_EQ(it3 != s21_map.end(), it4 != std_map.end());
  EXPECT_EQ((*it3).second, (*it4).second);
}

#define TESTS_BEGIN_CONST(suiteName)                                           \
  TEST(suiteName, intBeginConst) { methodBeginConst<int, int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleBeginConst) {                                          \
    methodBeginConst<double, int>(DEF_DBL_KEYS);                               \
  }                                                                            \
  TEST(suiteName, mockClassBeginConst) {                                       \
    methodBeginConst<MockClass, int>(DEF_MOCK_KEYS);                           \
  }                                                                            \
  TEST(suiteName, stringBeginConst) {                                          \
    methodBeginConst<std::string, int>(DEF_STR_KEYS);                          \
  }

TESTS_BEGIN_CONST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorPlus(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::iterator it1 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it2 = std_map.begin();

  ++it1;
  ++it2;

  EXPECT_EQ((*it1).second, (*it2).second);

  ++it1;
  ++it2;

  EXPECT_EQ((*it1).second, (*it2).second);
}

#define TESTS_ITERATOR_PLUS(suiteName)                  \
  TEST(suiteName, intIteratorPlus) {                    \
    methodIteratorPlus<int, int>(DEF_INT_KEYS);         \
  }                                                     \
  TEST(suiteName, doubleIteratorPlus) {                 \
    methodIteratorPlus<double, int>(DEF_DBL_KEYS);      \
  }                                                     \
  TEST(suiteName, mockClassIteratorPlus) {              \
    methodIteratorPlus<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                     \
  TEST(suiteName, stringIteratorPlus) {                 \
    methodIteratorPlus<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_PLUS(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorMinus(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::iterator it1 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it2 = std_map.begin();

  ++it1;
  ++it2;

  EXPECT_EQ((*it1).second, (*it2).second);

  --it1;
  --it2;

  EXPECT_EQ((*it1).second, (*it2).second);
}

#define TESTS_ITERATOR_MINUS(suiteName)                  \
  TEST(suiteName, intIteratorMinus) {                    \
    methodIteratorMinus<int, int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorMinus) {                 \
    methodIteratorMinus<double, int>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorMinus) {              \
    methodIteratorMinus<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorMinus) {                 \
    methodIteratorMinus<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_MINUS(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorAssignment(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::iterator it1 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it2 = std_map.begin();

  typename s21::map<key_type, mapped_type>::iterator it3 = it1;
  typename std::map<key_type, mapped_type>::iterator it4 = it2;

  EXPECT_EQ((*it1).second, (*it3).second);
  EXPECT_EQ((*it2).second, (*it4).second);
}

#define TESTS_ITERATOR_ASSIGNMENT(suiteName)                  \
  TEST(suiteName, intIteratorAssignment) {                    \
    methodIteratorAssignment<int, int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorAssignment) {                 \
    methodIteratorAssignment<double, int>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorAssignment) {              \
    methodIteratorAssignment<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorAssignment) {                 \
    methodIteratorAssignment<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_ASSIGNMENT(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorEqual(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::iterator it1 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it2 = std_map.begin();

  typename s21::map<key_type, mapped_type>::iterator it3 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it4 = std_map.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL(suiteName)                  \
  TEST(suiteName, intIteratorEqual) {                    \
    methodIteratorEqual<int, int>(DEF_INT_KEYS);         \
  }                                                      \
  TEST(suiteName, doubleIteratorEqual) {                 \
    methodIteratorEqual<double, int>(DEF_DBL_KEYS);      \
  }                                                      \
  TEST(suiteName, mockClassIteratorEqual) {              \
    methodIteratorEqual<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                      \
  TEST(suiteName, stringIteratorEqual) {                 \
    methodIteratorEqual<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_EQUAL(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorNotEqual(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::iterator it1 = s21_map.begin();
  typename std::map<key_type, mapped_type>::iterator it2 = std_map.begin();

  EXPECT_EQ(it1 != s21_map.end(), it2 != std_map.end());
}

#define TESTS_ITERATOR_NOT_EQUAL(suiteName)                 \
  TEST(suiteName, intIteratorNotEqual) {                    \
    methodIteratorNotEqual<int, int>(DEF_INT_KEYS);         \
  }                                                         \
  TEST(suiteName, doubleIteratorNotEqual) {                 \
    methodIteratorNotEqual<double, int>(DEF_DBL_KEYS);      \
  }                                                         \
  TEST(suiteName, mockClassIteratorNotEqual) {              \
    methodIteratorNotEqual<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                         \
  TEST(suiteName, stringIteratorNotEqual) {                 \
    methodIteratorNotEqual<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_NOT_EQUAL(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorPlusConst(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::const_iterator it1 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it2 =
      std_map.begin();

  ++it1;
  ++it2;

  EXPECT_EQ((*it1).second, (*it2).second);

  ++it1;
  ++it2;

  EXPECT_EQ((*it1).second, (*it2).second);
}

#define TESTS_ITERATOR_PLUS_CONST(suiteName)                 \
  TEST(suiteName, intIteratorPlusConst) {                    \
    methodIteratorPlusConst<int, int>(DEF_INT_KEYS);         \
  }                                                          \
  TEST(suiteName, doubleIteratorPlusConst) {                 \
    methodIteratorPlusConst<double, int>(DEF_DBL_KEYS);      \
  }                                                          \
  TEST(suiteName, mockClassIteratorPlusConst) {              \
    methodIteratorPlusConst<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                          \
  TEST(suiteName, stringIteratorPlusConst) {                 \
    methodIteratorPlusConst<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_PLUS_CONST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorMinusConst(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::const_iterator it1 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it2 =
      std_map.begin();

  ++it1;
  ++it2;

  EXPECT_EQ((*it1).second, (*it2).second);

  --it1;
  --it2;

  EXPECT_EQ((*it1).second, (*it2).second);
}

#define TESTS_ITERATOR_MINUS_CONST(suiteName)                 \
  TEST(suiteName, intIteratorMinusConst) {                    \
    methodIteratorMinusConst<int, int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorMinusConst) {                 \
    methodIteratorMinusConst<double, int>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorMinusConst) {              \
    methodIteratorMinusConst<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorMinusConst) {                 \
    methodIteratorMinusConst<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_MINUS_CONST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorAssignmentConst(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::const_iterator it1 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it2 =
      std_map.begin();

  typename s21::map<key_type, mapped_type>::const_iterator it3 = it1;
  typename std::map<key_type, mapped_type>::const_iterator it4 = it2;

  EXPECT_EQ((*it1).second, (*it3).second);
  EXPECT_EQ((*it2).second, (*it4).second);
}

#define TESTS_ITERATOR_ASSIGNMENT_CONST(suiteName)                 \
  TEST(suiteName, intIteratorAssignmentConst) {                    \
    methodIteratorAssignmentConst<int, int>(DEF_INT_KEYS);         \
  }                                                                \
  TEST(suiteName, doubleIteratorAssignmentConst) {                 \
    methodIteratorAssignmentConst<double, int>(DEF_DBL_KEYS);      \
  }                                                                \
  TEST(suiteName, mockClassIteratorAssignmentConst) {              \
    methodIteratorAssignmentConst<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                                \
  TEST(suiteName, stringIteratorAssignmentConst) {                 \
    methodIteratorAssignmentConst<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_ASSIGNMENT_CONST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorEqualConst(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::const_iterator it1 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it2 =
      std_map.begin();

  typename s21::map<key_type, mapped_type>::const_iterator it3 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it4 =
      std_map.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL_CONST(suiteName)                 \
  TEST(suiteName, intIteratorEqualConst) {                    \
    methodIteratorEqualConst<int, int>(DEF_INT_KEYS);         \
  }                                                           \
  TEST(suiteName, doubleIteratorEqualConst) {                 \
    methodIteratorEqualConst<double, int>(DEF_DBL_KEYS);      \
  }                                                           \
  TEST(suiteName, mockClassIteratorEqualConst) {              \
    methodIteratorEqualConst<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                           \
  TEST(suiteName, stringIteratorEqualConst) {                 \
    methodIteratorEqualConst<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_EQUAL_CONST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodIteratorNotEqualConst(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  typename s21::map<key_type, mapped_type>::const_iterator it1 =
      s21_map.begin();
  typename std::map<key_type, mapped_type>::const_iterator it2 =
      std_map.begin();

  EXPECT_EQ(it1 != s21_map.end(), it2 != std_map.end());
}

#define TESTS_ITERATOR_NOT_EQUAL_CONST(suiteName)                \
  TEST(suiteName, intIteratorNotEqualConst) {                    \
    methodIteratorNotEqualConst<int, int>(DEF_INT_KEYS);         \
  }                                                              \
  TEST(suiteName, doubleIteratorNotEqualConst) {                 \
    methodIteratorNotEqualConst<double, int>(DEF_DBL_KEYS);      \
  }                                                              \
  TEST(suiteName, mockClassIteratorNotEqualConst) {              \
    methodIteratorNotEqualConst<MockClass, int>(DEF_MOCK_KEYS);  \
  }                                                              \
  TEST(suiteName, stringIteratorNotEqualConst) {                 \
    methodIteratorNotEqualConst<std::string, int>(DEF_STR_KEYS); \
  }

TESTS_ITERATOR_NOT_EQUAL_CONST(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertNoDuplicate(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const std::pair<key_type, mapped_type>& pair) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool> it1 =
      s21_map.insert(pair);
  std::pair<typename std::map<key_type, mapped_type>::iterator, bool> it2 =
      std_map.insert(pair);

  checkFields(s21_map, std_map);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ((*(it1.first)).second, (*(it2.first)).second);
}

#define TESTS_INSERT_NO_DUPLICATE(suiteName)                           \
  TEST(suiteName, intInsertNoDuplicate) {                              \
    methodInsertNoDuplicate<int, int>(DEF_INT_KEYS, INT_PAIR);         \
  }                                                                    \
  TEST(suiteName, doubleInsertNoDuplicate) {                           \
    methodInsertNoDuplicate<double, int>(DEF_DBL_KEYS, DBL_PAIR);      \
  }                                                                    \
  TEST(suiteName, mockClassInsertNoDuplicate) {                        \
    methodInsertNoDuplicate<MockClass, int>(DEF_MOCK_KEYS, MOCK_PAIR); \
  }                                                                    \
  TEST(suiteName, stringInsertNoDuplicate) {                           \
    methodInsertNoDuplicate<std::string, int>(DEF_STR_KEYS, STR_PAIR); \
  }

TESTS_INSERT_NO_DUPLICATE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertDuplicate(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const std::pair<key_type, mapped_type>& pair) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool> it1 =
      s21_map.insert(pair);
  std::pair<typename std::map<key_type, mapped_type>::iterator, bool> it2 =
      std_map.insert(pair);

  checkFields(s21_map, std_map);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ((*(it1.first)).second, (*(it2.first)).second);
}

#define TESTS_INSERT_DUPLICATE(suiteName)                                      \
  TEST(suiteName, intInsertDuplicate) {                                        \
    methodInsertDuplicate<int, int>(DEF_INT_KEYS, INT_PAIR_DUPLICATE);         \
  }                                                                            \
  TEST(suiteName, doubleInsertDuplicate) {                                     \
    methodInsertDuplicate<double, int>(DEF_DBL_KEYS, DBL_PAIR_DUPLICATE);      \
  }                                                                            \
  TEST(suiteName, mockClassInsertDuplicate) {                                  \
    methodInsertDuplicate<MockClass, int>(DEF_MOCK_KEYS, MOCK_PAIR_DUPLICATE); \
  }                                                                            \
  TEST(suiteName, stringInsertDuplicate) {                                     \
    methodInsertDuplicate<std::string, int>(DEF_STR_KEYS, STR_PAIR_DUPLICATE); \
  }

TESTS_INSERT_DUPLICATE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertKeyNoDuplicate(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const key_type& key, const mapped_type& obj,
    const std::pair<key_type, mapped_type>& pair) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool> it1 =
      s21_map.insert(key, obj);
  std::pair<typename std::map<key_type, mapped_type>::iterator, bool> it2 =
      std_map.insert(pair);

  checkFields(s21_map, std_map);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ((*(it1.first)).second, (*(it2.first)).second);
}

#define TESTS_INSERT_KEY_NO_DUPLICATE(suiteName)                            \
  TEST(suiteName, intInsertKeyNoDuplicate) {                                \
    methodInsertKeyNoDuplicate<int, int>(DEF_INT_KEYS, INT_KEY, INT_OBJ,    \
                                         INT_PAIR);                         \
  }                                                                         \
  TEST(suiteName, doubleInsertKeyNoDuplicate) {                             \
    methodInsertKeyNoDuplicate<double, int>(DEF_DBL_KEYS, DBL_KEY, DBL_OBJ, \
                                            DBL_PAIR);                      \
  }                                                                         \
  TEST(suiteName, mockClassInsertKeyNoDuplicate) {                          \
    methodInsertKeyNoDuplicate<MockClass, int>(DEF_MOCK_KEYS, MOCK_KEY,     \
                                               MOCK_OBJ, MOCK_PAIR);        \
  }                                                                         \
  TEST(suiteName, stringInsertKeyNoDuplicate) {                             \
    methodInsertKeyNoDuplicate<std::string, int>(DEF_STR_KEYS, STR_KEY,     \
                                                 STR_OBJ, STR_PAIR);        \
  }

TESTS_INSERT_KEY_NO_DUPLICATE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertKeyDuplicate(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const key_type& key, const mapped_type& obj,
    const std::pair<key_type, mapped_type>& pair) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool> it1 =
      s21_map.insert(key, obj);
  std::pair<typename std::map<key_type, mapped_type>::iterator, bool> it2 =
      std_map.insert(pair);

  checkFields(s21_map, std_map);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ((*(it1.first)).second, (*(it2.first)).second);
}

#define TESTS_INSERT_KEY_DUPLICATE(suiteName)                              \
  TEST(suiteName, intInsertKeyDuplicate) {                                 \
    methodInsertKeyDuplicate<int, int>(DEF_INT_KEYS, INT_KEY_DUPLICATE,    \
                                       INT_OBJ, INT_PAIR_DUPLICATE);       \
  }                                                                        \
  TEST(suiteName, doubleInsertKeyDuplicate) {                              \
    methodInsertKeyDuplicate<double, int>(DEF_DBL_KEYS, DBL_KEY_DUPLICATE, \
                                          DBL_OBJ, DBL_PAIR_DUPLICATE);    \
  }                                                                        \
  TEST(suiteName, mockClassInsertKeyDuplicate) {                           \
    methodInsertKeyDuplicate<MockClass, int>(                              \
        DEF_MOCK_KEYS, MOCK_KEY_DUPLICATE, MOCK_OBJ, MOCK_PAIR_DUPLICATE); \
  }                                                                        \
  TEST(suiteName, stringInsertKeyDuplicate) {                              \
    methodInsertKeyDuplicate<std::string, int>(                            \
        DEF_STR_KEYS, STR_KEY_DUPLICATE, STR_OBJ, STR_PAIR_DUPLICATE);     \
  }

TESTS_INSERT_KEY_DUPLICATE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertOrAssignNoDuplicate(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const key_type& key, const mapped_type& obj,
    const std::pair<key_type, mapped_type>& pair) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool> it1 =
      s21_map.insert_or_assign(key, obj);
  std::pair<typename std::map<key_type, mapped_type>::iterator, bool> it2 =
      std_map.insert(pair);

  checkFields(s21_map, std_map);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ((*(it1.first)).second, (*(it2.first)).second);
}

#define TESTS_INSERT_OR_ASSIGN_NO_DUPLICATE(suiteName)                        \
  TEST(suiteName, intInsertOrAssignNoDuplicate) {                             \
    methodInsertOrAssignNoDuplicate<int, int>(DEF_INT_KEYS, INT_KEY, INT_OBJ, \
                                              INT_PAIR);                      \
  }                                                                           \
  TEST(suiteName, doubleInsertOrAssignNoDuplicate) {                          \
    methodInsertOrAssignNoDuplicate<double, int>(DEF_DBL_KEYS, DBL_KEY,       \
                                                 DBL_OBJ, DBL_PAIR);          \
  }                                                                           \
  TEST(suiteName, mockClassInsertOrAssignNoDuplicate) {                       \
    methodInsertOrAssignNoDuplicate<MockClass, int>(DEF_MOCK_KEYS, MOCK_KEY,  \
                                                    MOCK_OBJ, MOCK_PAIR);     \
  }                                                                           \
  TEST(suiteName, stringInsertOrAssignNoDuplicate) {                          \
    methodInsertOrAssignNoDuplicate<std::string, int>(DEF_STR_KEYS, STR_KEY,  \
                                                      STR_OBJ, STR_PAIR);     \
  }

TESTS_INSERT_OR_ASSIGN_NO_DUPLICATE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertOrAssignDuplicate(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const key_type& key, const mapped_type& obj,
    const std::pair<key_type, mapped_type>& pair) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  std::pair<typename s21::map<key_type, mapped_type>::iterator, bool> it1 =
      s21_map.insert_or_assign(key, obj);
  std::pair<typename std::map<key_type, mapped_type>::iterator, bool> it2 =
      std_map.insert(pair);

  checkFields(s21_map, std_map);

  EXPECT_EQ(it1.second, it2.second);
  EXPECT_EQ((*(it1.first)).second, (*(it2.first)).second);
}

#define TESTS_INSERT_OR_ASSIGN_DUPLICATE(suiteName)                          \
  TEST(suiteName, intInsertOrAssignDuplicate) {                              \
    methodInsertOrAssignDuplicate<int, int>(DEF_INT_KEYS, INT_KEY_DUPLICATE, \
                                            INT_OBJ, INT_PAIR_DUPLICATE);    \
  }                                                                          \
  TEST(suiteName, doubleInsertOrAssignDuplicate) {                           \
    methodInsertOrAssignDuplicate<double, int>(                              \
        DEF_DBL_KEYS, DBL_KEY_DUPLICATE, DBL_OBJ, DBL_PAIR_DUPLICATE);       \
  }                                                                          \
  TEST(suiteName, mockClassInsertOrAssignDuplicate) {                        \
    methodInsertOrAssignDuplicate<MockClass, int>(                           \
        DEF_MOCK_KEYS, MOCK_KEY_DUPLICATE, MOCK_OBJ, MOCK_PAIR_DUPLICATE);   \
  }                                                                          \
  TEST(suiteName, stringInsertOrAssignDuplicate) {                           \
    methodInsertOrAssignDuplicate<std::string, int>(                         \
        DEF_STR_KEYS, STR_KEY_DUPLICATE, STR_OBJ, STR_PAIR_DUPLICATE);       \
  }

TESTS_INSERT_OR_ASSIGN_DUPLICATE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodAt(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const key_type& key) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  EXPECT_EQ(s21_map.at(key), std_map.at(key));
}

#define TESTS_AT(suiteName)                                      \
  TEST(suiteName, intMethodAt) {                                 \
    methodAt<int, int>(DEF_INT_KEYS, INT_KEY_DUPLICATE);         \
  }                                                              \
  TEST(suiteName, doubleMethodAt) {                              \
    methodAt<double, int>(DEF_DBL_KEYS, DBL_KEY_DUPLICATE);      \
  }                                                              \
  TEST(suiteName, mockClassMethodAt) {                           \
    methodAt<MockClass, int>(DEF_MOCK_KEYS, MOCK_KEY_DUPLICATE); \
  }                                                              \
  TEST(suiteName, stringMethodAt) {                              \
    methodAt<std::string, int>(DEF_STR_KEYS, STR_KEY_DUPLICATE); \
  }

TESTS_AT(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodErase(
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21_map.erase(s21_map.begin());
  std_map.erase(std_map.begin());

  checkFields(s21_map, std_map);

  s21_map.erase(s21_map.begin());
  std_map.erase(std_map.begin());

  checkFields(s21_map, std_map);
}

#define TESTS_ERASE(suiteName)                                             \
  TEST(suiteName, intMethodErase) { methodErase<int, int>(DEF_INT_KEYS); } \
  TEST(suiteName, doubleMethodErase) {                                     \
    methodErase<double, int>(DEF_DBL_KEYS);                                \
  }                                                                        \
  TEST(suiteName, mockClassMethodErase) {                                  \
    methodErase<MockClass, int>(DEF_MOCK_KEYS);                            \
  }                                                                        \
  TEST(suiteName, stringMethodErase) {                                     \
    methodErase<std::string, int>(DEF_STR_KEYS);                           \
  }

TESTS_ERASE(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodContains(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const key_type& key, const key_type& key_duplicate) {
  s21::map<key_type, mapped_type> s21_map(items);

  ASSERT_FALSE(s21_map.contains(key));
  ASSERT_TRUE(s21_map.contains(key_duplicate));
}

#define TESTS_CONTAINS(suiteName)                                          \
  TEST(suiteName, intMethodContains) {                                     \
    methodContains<int, int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE);    \
  }                                                                        \
  TEST(suiteName, doubleMethodContains) {                                  \
    methodContains<double, int>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); \
  }                                                                        \
  TEST(suiteName, mockClassMethodContains) {                               \
    methodContains<MockClass, int>(DEF_MOCK_KEYS, MOCK_KEY,                \
                                   MOCK_KEY_DUPLICATE);                    \
  }                                                                        \
  TEST(suiteName, stringMethodContains) {                                  \
    methodContains<std::string, int>(DEF_STR_KEYS, STR_KEY,                \
                                     STR_KEY_DUPLICATE);                   \
  }

TESTS_CONTAINS(s21Map)

// -------------------------------------------------

template <typename key_type, typename mapped_type>
void methodInsertMany(
    const std::initializer_list<std::pair<const key_type, mapped_type>>& items,
    const std::initializer_list<std::pair<const key_type, mapped_type>>&
        insert_items) {
  s21::map<key_type, mapped_type> s21_map(items);
  std::map<key_type, mapped_type> std_map(items);

  s21_map.insert_many(*insert_items.begin(), *(insert_items.begin() + 1),
                      *(insert_items.begin() + 2));
  std_map.insert(*insert_items.begin());
  std_map.insert(*(insert_items.begin() + 1));
  std_map.insert(*(insert_items.begin() + 2));

  checkFields(s21_map, std_map);
}

#define TESTS_INSERT_MANY(suiteName)                                        \
  TEST(suiteName, intMethodInsertMany) {                                    \
    methodInsertMany<int, int>(DEF_INT_KEYS, DEF_INT_KEYS_NO_DUBLICATE);    \
  }                                                                         \
  TEST(suiteName, doubleMethodInsertMany) {                                 \
    methodInsertMany<double, int>(DEF_DBL_KEYS, DEF_DBL_KEYS_NO_DUBLICATE); \
  }                                                                         \
  TEST(suiteName, mockClassMethodInsertMany) {                              \
    methodInsertMany<MockClass, int>(DEF_MOCK_KEYS,                         \
                                     DEF_MOCK_KEYS_NO_DUBLICATE);           \
  }                                                                         \
  TEST(suiteName, stringMethodInsertMany) {                                 \
    methodInsertMany<std::string, int>(DEF_STR_KEYS,                        \
                                       DEF_STR_KEYS_NO_DUBLICATE);          \
  }

TESTS_INSERT_MANY(s21Map)
