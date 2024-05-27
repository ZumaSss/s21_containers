#include "core/s21_stack.h"

#include <stack>

#include "s21_core_tests.h"

#define DEF_STR_VALS \
  { "hello", "world", "!" }

TEST(s21_stack_suite, init_empty_stack) {
  std::stack<NoConstructClass> std_stack;
  s21::stack<NoConstructClass> s21_stack;
  ASSERT_EQ(std_stack.empty(), s21_stack.empty());
  ASSERT_EQ(std_stack.size(), s21_stack.size());

  std::stack<std::string> std_stack_str;
  s21::stack<std::string> s21_stack_str;
  ASSERT_EQ(std_stack_str.empty(), s21_stack_str.empty());
  ASSERT_EQ(std_stack_str.size(), s21_stack_str.size());
}

TEST(s21_stack_suite, empty_stack_pop) {
  s21::stack<int> s21_stack;
  EXPECT_THROW(s21_stack.pop(), std::out_of_range);
}

TEST(s21_stack_suite, init_list_stack00) {
  s21::stack<int> s21_stack{21, 42, 84};
  int list_data[] = {21, 42, 84};
  int i = 2;
  while (!s21_stack.empty()) {
    ASSERT_EQ(list_data[i], s21_stack.top());
    s21_stack.pop();
    --i;
  }
  ASSERT_EQ(s21_stack.empty(), true);
  ASSERT_EQ(s21_stack.size(), 0);
}

TEST(s21_stack_suite, init_list_stack01) {
  s21::stack<std::string> s21_stack{"hello", "world", "!"};
  std::string list_data[] = {"hello", "world", "!"};
  int i = 2;
  while (!s21_stack.empty()) {
    ASSERT_EQ(list_data[i], s21_stack.top());
    s21_stack.pop();
    --i;
  }
  ASSERT_EQ(s21_stack.empty(), true);
  ASSERT_EQ(s21_stack.size(), 0);
}

TEST(s21_stack_suite, push_stack00) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  std_stack.push(21);
  s21_stack.push(21);

  ASSERT_EQ(std_stack.top(), s21_stack.top());

  std_stack.push(42);
  s21_stack.push(42);

  ASSERT_EQ(std_stack.top(), s21_stack.top());
}

TEST(s21_stack_suite, push_stack01) {
  std::stack<std::string> std_stack;
  s21::stack<std::string> s21_stack;

  std_stack.push("hello");
  s21_stack.push("hello");

  ASSERT_EQ(std_stack.top(), s21_stack.top());

  std_stack.push("world");
  s21_stack.push("world");

  ASSERT_EQ(std_stack.top(), s21_stack.top());
}

TEST(s21_stack_suite, empty_swap00) {
  s21::stack<int> s21_this;
  s21::stack<int> s21_other{21, 42, 84};

  s21_this.swap(s21_other);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), true);

  ASSERT_EQ(s21_this.size(), 3);
  ASSERT_EQ(s21_other.size(), 0);
}

TEST(s21_stack_suite, empty_swap01) {
  s21::stack<std::string> s21_this;
  s21::stack<std::string> s21_other{"hello", "world", "!"};

  s21_this.swap(s21_other);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), true);

  ASSERT_EQ(s21_this.size(), 3);
  ASSERT_EQ(s21_other.size(), 0);
}

TEST(s21_stack_suite, non_empty_swap00) {
  s21::stack<int> s21_this{21, 42};
  s21::stack<int> s21_other{84, 96, 77, 31, 55};

  s21_this.swap(s21_other);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), false);

  ASSERT_EQ(s21_this.size(), 5);
  ASSERT_EQ(s21_other.size(), 2);

  ASSERT_EQ(s21_this.top(), 55);
  ASSERT_EQ(s21_other.top(), 42);
}

TEST(s21_stack_suite, non_empty_swap01) {
  s21::stack<std::string> s21_this{"hello", "world"};
  s21::stack<std::string> s21_other{"asta", "la", "vista", "baby", "!"};

  s21_this.swap(s21_other);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), false);

  ASSERT_EQ(s21_this.size(), 5);
  ASSERT_EQ(s21_other.size(), 2);

  ASSERT_EQ(s21_this.top(), "!");
  ASSERT_EQ(s21_other.top(), "world");
}

TEST(s21_stack_suite, move_constructor00) {
  s21::stack<int> s21_this;
  s21::stack<int> s21_other{21, 42, 84};
  s21_this = std::move(s21_other);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), true);

  ASSERT_EQ(s21_this.size(), 3);
  ASSERT_EQ(s21_other.size(), 0);
}

TEST(s21_stack_suite, move_constructor01) {
  s21::stack<int> s21_this{21, 42, 84};
  s21_this = std::move(s21_this);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_this.size(), 3);
}

TEST(s21_stack_suite, move_constructor02) {
  s21::stack<std::string> s21_this;
  s21::stack<std::string> s21_other{"hello", "world", "!"};
  s21_this = std::move(s21_other);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), true);

  ASSERT_EQ(s21_this.size(), 3);
  ASSERT_EQ(s21_other.size(), 0);
}

TEST(s21_stack_suite, move_constructor03) {
  s21::stack<std::string> s21_this{"hello", "world", "!"};
  s21_this = std::move(s21_this);

  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_this.size(), 3);
}

TEST(s21_stack_suite, insert_many_top00) {
  s21::stack<int> s21_stack{21, 42, 84};
  s21_stack.insert_many_front(33, 42, 11);

  ASSERT_EQ(s21_stack.empty(), false);
  ASSERT_EQ(s21_stack.size(), 6);
  ASSERT_EQ(s21_stack.top(), 11);
}

TEST(s21_stack_suite, insert_many_top01) {
  s21::stack<std::string> s21_stack{"hello", "world"};
  s21_stack.insert_many_front("asta", "la", "vista", "baby");

  ASSERT_EQ(s21_stack.empty(), false);
  ASSERT_EQ(s21_stack.size(), 6);
  ASSERT_EQ(s21_stack.top(), "baby");
}