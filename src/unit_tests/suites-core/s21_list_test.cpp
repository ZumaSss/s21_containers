#include "core/s21_list.h"

#include <list>

#include "s21_core_tests.h"

static void list_check_data(const s21::list<int>& s21_list,
                            const std::list<int>& std_list) {
  auto std_iter = std_list.begin();
  for (auto iter = s21_list.begin(); iter != s21_list.end(); ++iter) {
    ASSERT_EQ(*std_iter, *iter);
    ++std_iter;
  }

  std_iter = --std_list.end();
  for (auto iter = --s21_list.end(); iter != s21_list.end(); --iter) {
    ASSERT_EQ(*std_iter, *iter);
    --std_iter;
  }
}

TEST(s21_list_suite, init_empty_list) {
  std::list<NoConstructClass> std_list;
  s21::list<NoConstructClass> s21_list;
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
}

TEST(s21_list_suite, init_empty_n_list) {
  std::list<int> std_list(5);
  s21::list<int> s21_list(5);
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
}

TEST(s21_list_suite, copy_empty_list) {
  s21::list<int> s21_list_this;
  s21::list<int> s21_list_other(s21_list_this);
  s21::list<int> s21_list_another = s21_list_this;

  ASSERT_EQ(s21_list_this.size(), s21_list_other.size());
  ASSERT_EQ(s21_list_this.size(), s21_list_another.size());
}

TEST(s21_list_suite, copy_list) {
  s21::list<int> s21_list_this = {21, 42, 84, 77};
  s21::list<int> s21_list_other(s21_list_this);
  s21::list<int> s21_list_another = s21_list_this;

  ASSERT_EQ(s21_list_this.size(), s21_list_other.size());
  ASSERT_EQ(s21_list_this.size(), s21_list_another.size());

  s21::list<int>::const_iterator iter_this = s21_list_this.begin();
  s21::list<int>::const_iterator iter_other = s21_list_other.begin();
  s21::list<int>::const_iterator iter_another = s21_list_another.begin();

  for (std::size_t i = 0; i < s21_list_this.size(); ++i) {
    ASSERT_EQ(*iter_this, *iter_other);
    ASSERT_EQ(*iter_this, *iter_another);
    ++iter_this;
    ++iter_other;
    ++iter_another;
  }
}

TEST(s21_list_suite, move_list) {
  s21::list<std::string> s21_src_list = {"Hello", "World"};
  std::list<std::string> std_src_list = {"Hello", "World"};
  s21::list<std::string> s21_dst_list = std::move(s21_src_list);
  std::list<std::string> std_dst_list = std::move(std_src_list);

  ASSERT_EQ(std_src_list.size(), s21_src_list.size());
  ASSERT_EQ(std_dst_list.size(), s21_dst_list.size());

  s21::list<std::string>::iterator s21_iter = s21_dst_list.begin();
  auto std_iter = std_dst_list.begin();

  for (std::size_t i = 0; i < s21_dst_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    ++s21_iter;
    ++std_iter;
  }
}

TEST(s21_list_suite, basic_operations) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, push_back_01) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.push_back(21);
  std_list.push_back(21);

  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, push_back_02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  s21_list.push_back(168);
  std_list.push_back(168);

  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, push_front_01) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.push_front(21);
  std_list.push_front(21);

  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.size(), s21_list.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(s21_list_suite, push_front_02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  s21_list.push_front(168);
  std_list.push_front(168);

  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.size(), s21_list.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(s21_list_suite, empty_list_exceptions) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.pop_back(), std::out_of_range);
  EXPECT_THROW(empty_list.pop_front(), std::out_of_range);
  EXPECT_THROW(empty_list.front(), std::out_of_range);
  EXPECT_THROW(empty_list.back(), std::out_of_range);
}

TEST(s21_list_suite, oversize_list_exceptions) {
  s21::list<int> max_size_counter;
  std::size_t size_cap = max_size_counter.max_size() + 1;
  EXPECT_THROW(s21::list<int> s21_list(size_cap), std::length_error);
}

TEST(s21_list_suite, pop_back00) {
  s21::list<int> s21_list = {21, 42, 84, 77};
  std::list<int> std_list = {21, 42, 84, 77};

  std_list.pop_back();
  s21_list.pop_back();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, pop_back01) {
  s21::list<int> s21_list = {21};
  std::list<int> std_list = {21};

  std_list.pop_back();
  s21_list.pop_back();

  ASSERT_EQ(std_list.size(), s21_list.size());

  s21_list.push_back(42);
  std_list.push_back(42);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, pop_front00) {
  s21::list<int> s21_list = {21, 42, 84, 77};
  std::list<int> std_list = {21, 42, 84, 77};

  std_list.pop_front();
  s21_list.pop_front();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, pop_front01) {
  s21::list<int> s21_list = {21};
  std::list<int> std_list = {21};

  std_list.pop_front();
  s21_list.pop_front();

  ASSERT_EQ(std_list.size(), s21_list.size());

  s21_list.push_front(42);
  std_list.push_front(42);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, erase01) {
  s21::list<int> s21_list = {21};
  std::list<int> std_list = {21};

  auto s21_iter = s21_list.erase(s21_list.begin());
  auto std_iter = std_list.erase(std_list.begin());

  ASSERT_EQ((std_iter == std_list.end()), (s21_iter == s21_list.end()));
  ASSERT_EQ(std_list.size(), s21_list.size());
}

TEST(s21_list_suite, erase02) {
  s21::list<int> s21_list = {21, 42};
  std::list<int> std_list = {21, 42};

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();
  ++s21_iter;
  ++std_iter;

  auto s21_res_iter = s21_list.erase(s21_iter);
  auto std_res_iter = std_list.erase(std_iter);

  ASSERT_EQ((std_res_iter == std_list.end()), (s21_res_iter == s21_list.end()));
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(*(std_list.begin()), *(s21_list.begin()));
}

TEST(s21_list_suite, erase03) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();
  ++s21_iter;
  ++std_iter;

  auto s21_res_iter = s21_list.erase(s21_iter);
  auto std_res_iter = std_list.erase(std_iter);

  ASSERT_EQ(*std_res_iter, *s21_res_iter);
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(*(std_list.begin()), *(s21_list.begin()));
}

TEST(s21_list_suite, iterator_clockwise01) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    ++s21_iter;
    ++std_iter;
  }
}

TEST(s21_list_suite, iterator_clockwise02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(s21_list_suite, iterator_counterclockwise01) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.end();
  auto std_iter = std_list.end();
  s21_iter--;
  std_iter--;
  ASSERT_EQ(*std_iter, *s21_iter);

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter--;
    std_iter--;
  }
}

TEST(s21_list_suite, iterator_counterclockwise02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.end();
  auto std_iter = std_list.end();
  --s21_iter;
  --std_iter;
  ASSERT_EQ(*std_iter, *s21_iter);

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    --s21_iter;
    --std_iter;
  }
}

TEST(s21_list_suite, iterator_circular_behavior) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.end();
  auto std_iter = std_list.end();
  s21_iter++;
  std_iter++;
  ASSERT_EQ(*std_iter, *s21_iter);
}

TEST(s21_list_suite, iterator_compare) {
  s21::list<int> s21_list = {21, 42, 84};

  auto s21_iter_begin = s21_list.begin();
  auto s21_iter_end = s21_list.end();

  ASSERT_TRUE(s21_iter_begin != s21_iter_end);

  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    --s21_iter_end;
  }

  ASSERT_TRUE(s21_iter_begin == s21_iter_end);
}

TEST(s21_list_suite, max_size) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(std_list.max_size(), s21_list.max_size());
}

TEST(s21_list_suite, swap_empty) {
  s21::list<int> s21_list;
  s21::list<int> s21_list_other = {15, 25, 35};

  std::list<int> std_list;
  std::list<int> std_list_other = {15, 25, 35};

  s21_list.swap(s21_list_other);
  std_list.swap(std_list_other);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list_other.size(), s21_list_other.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(s21_list_suite, swap_non_empty) {
  s21::list<int> s21_list = {21, 42, 84};
  s21::list<int> s21_list_other = {15, 25, 35};

  std::list<int> std_list = {21, 42, 84};
  std::list<int> std_list_other = {15, 25, 35};

  s21_list.swap(s21_list_other);
  std_list.swap(std_list_other);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list_other.size(), s21_list_other.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(s21_list_suite, reverse_empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.reverse();
  std_list.reverse();

  ASSERT_EQ(std_list.size(), s21_list.size());
}

TEST(s21_list_suite, reverse_00) {
  s21::list<int> s21_list = {21};
  std::list<int> std_list = {21};

  s21_list.reverse();
  std_list.reverse();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, reverse_01) {
  s21::list<int> s21_list = {21, 42};
  std::list<int> std_list = {21, 42};

  s21_list.reverse();
  std_list.reverse();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, reverse_02) {
  s21::list<int> s21_list = {21, 42, 84, 65, 45, 33, 44};
  std::list<int> std_list = {21, 42, 84, 65, 45, 33, 44};

  s21_list.reverse();
  std_list.reverse();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    ++s21_iter;
    ++std_iter;
  }

  std_iter = --std_list.end();
  for (auto iter = --s21_list.end(); iter != s21_list.end(); --iter) {
    ASSERT_EQ(*std_iter, *iter);
    --std_iter;
  }
}

TEST(s21_list_suite, insert_empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  auto s21_iter = s21_list.insert(s21_list.begin(), 42);
  auto std_iter = std_list.insert(std_list.begin(), 42);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(*std_iter, *s21_iter);
}

TEST(s21_list_suite, insert_only_one) {
  s21::list<int> s21_list = {42};
  std::list<int> std_list = {42};

  auto s21_iter = s21_list.insert(s21_list.begin(), 21);
  auto std_iter = std_list.insert(std_list.begin(), 21);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(*std_iter, *s21_iter);
}

TEST(s21_list_suite, insert_to_end) {
  s21::list<int> s21_list = {42, 21};
  std::list<int> std_list = {42, 21};

  auto s21_iter = s21_list.insert(s21_list.end(), 123);
  auto std_iter = std_list.insert(std_list.end(), 123);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(*std_iter, *s21_iter);

  list_check_data(s21_list, std_list);
}

TEST(s21_list_suite, insert_to_middle) {
  s21::list<int> s21_list = {21, 42, 84, 65, 45, 33, 44};
  std::list<int> std_list = {21, 42, 84, 65, 45, 33, 44};

  auto s21_pos = s21_list.begin();
  auto std_pos = std_list.begin();

  for (std::size_t i = 0; i < s21_list.size() / 2; ++i) {
    ++s21_pos;
    ++std_pos;
  }

  auto s21_iter = s21_list.insert(s21_pos, 123);
  auto std_iter = std_list.insert(std_pos, 123);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(*std_iter, *s21_iter);

  list_check_data(s21_list, std_list);
}

TEST(s21_list_suite, merge_first_empty) {
  s21::list<int> s21_list_dst;
  std::list<int> std_list_dst;

  s21::list<int> s21_list_src = {1, 4, 6, 8, 12};
  std::list<int> std_list_src = {1, 4, 6, 8, 12};

  s21_list_dst.merge(s21_list_src);
  std_list_dst.merge(std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, merge_second_empty) {
  s21::list<int> s21_list_src;
  std::list<int> std_list_src;

  s21::list<int> s21_list_dst = {1, 4, 6, 8, 12};
  std::list<int> std_list_dst = {1, 4, 6, 8, 12};

  s21_list_dst.merge(s21_list_src);
  std_list_dst.merge(std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, merge_normal00) {
  s21::list<int> s21_list_src = {1, 4, 6, 8, 12};
  std::list<int> std_list_src = {1, 4, 6, 8, 12};

  s21::list<int> s21_list_dst = {-1, 2, 5, 7, 10};
  std::list<int> std_list_dst = {-1, 2, 5, 7, 10};

  s21_list_dst.merge(s21_list_src);
  std_list_dst.merge(std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, merge_normal01) {
  s21::list<int> s21_list_src = {1, 4, 6, 8, 12};
  std::list<int> std_list_src = {1, 4, 6, 8, 12};

  s21::list<int> s21_list_dst = {2, 2, 5, 7, 10};
  std::list<int> std_list_dst = {2, 2, 5, 7, 10};

  s21_list_dst.merge(s21_list_src);
  std_list_dst.merge(std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, unique_empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.unique();
  std_list.unique();

  ASSERT_EQ(std_list.size(), s21_list.size());
}

TEST(s21_list_suite, unique_one) {
  s21::list<int> s21_list = {42};
  std::list<int> std_list = {42};

  s21_list.unique();
  std_list.unique();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, unique_normal) {
  s21::list<int> s21_list = {1, 2, 2, 2, 2, 3, 3, 2, 1, 1, 1, 8, 8, 8};
  std::list<int> std_list = {1, 2, 2, 2, 2, 3, 3, 2, 1, 1, 1, 8, 8, 8};

  s21_list.unique();
  std_list.unique();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());

  list_check_data(s21_list, std_list);
}

TEST(s21_list_suite, splice_empty) {
  s21::list<int> s21_list_src = {7, 7, 7};
  std::list<int> std_list_src = {7, 7, 7};

  s21::list<int> s21_list_dst;
  std::list<int> std_list_dst;

  s21_list_dst.splice(s21_list_dst.begin(), s21_list_src);
  std_list_dst.splice(std_list_dst.begin(), std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_src.empty(), s21_list_src.empty());

  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());
  ASSERT_EQ(std_list_dst.empty(), s21_list_dst.empty());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, splice_median) {
  s21::list<int> s21_list_src = {7, 7, 7};
  std::list<int> std_list_src = {7, 7, 7};

  s21::list<int> s21_list_dst = {1, 2, 3, 6, 8, 9};
  std::list<int> std_list_dst = {1, 2, 3, 6, 8, 9};

  auto s21_iter = s21_list_dst.begin();
  auto std_iter = std_list_dst.begin();

  for (int i = 0; i < 3; ++i) {
    ++s21_iter;
    ++std_iter;
  }

  s21_list_dst.splice(s21_iter, s21_list_src);
  std_list_dst.splice(std_iter, std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_src.empty(), s21_list_src.empty());

  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());
  ASSERT_EQ(std_list_dst.empty(), s21_list_dst.empty());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, splice_end) {
  s21::list<int> s21_list_src = {7, 7, 7};
  std::list<int> std_list_src = {7, 7, 7};

  s21::list<int> s21_list_dst = {1, 2, 3, 6, 8, 9};
  std::list<int> std_list_dst = {1, 2, 3, 6, 8, 9};

  s21_list_dst.splice(s21_list_dst.end(), s21_list_src);
  std_list_dst.splice(std_list_dst.end(), std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_src.empty(), s21_list_src.empty());

  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());
  ASSERT_EQ(std_list_dst.empty(), s21_list_dst.empty());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, sort_empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.sort();
  std_list.sort();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
}

TEST(s21_list_suite, sort_one) {
  s21::list<int> s21_list = {42};
  std::list<int> std_list = {42};

  s21_list.sort();
  std_list.sort();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, sort_normal) {
  s21::list<int> s21_list = {8, 7, 5, 9, 0, 1, 3, 2, 6, 4};
  std::list<int> std_list = {8, 7, 5, 9, 0, 1, 3, 2, 6, 4};

  s21_list.sort();
  std_list.sort();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());

  list_check_data(s21_list, std_list);
}

TEST(s21_list_suite, sort_sorted00) {
  s21::list<int> s21_list = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
  std::list<int> std_list = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

  s21_list.sort();
  std_list.sort();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());

  list_check_data(s21_list, std_list);
}

TEST(s21_list_suite, sort_sorted01) {
  s21::list<int> s21_list = {0, 1, 1, 2, 3, 4, 4, 4, 5, 6};
  std::list<int> std_list = {0, 1, 1, 2, 3, 4, 4, 4, 5, 6};

  s21_list.sort();
  std_list.sort();

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());

  list_check_data(s21_list, std_list);
}

TEST(s21_list_suite, move_assigment00) {
  s21::list<int> s21_list_src = {1, 2, 3, 6, 8, 9};
  std::list<int> std_list_src = {1, 2, 3, 6, 8, 9};

  s21::list<int> s21_list_dst = std::move(s21_list_src);
  std::list<int> std_list_dst = std::move(std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_src.empty(), s21_list_src.empty());
  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());
  ASSERT_EQ(std_list_dst.empty(), s21_list_dst.empty());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, move_assigment01) {
  s21::list<int> s21_list_src = {1, 2, 3, 6, 8, 9};
  std::list<int> std_list_src = {1, 2, 3, 6, 8, 9};

  s21::list<int> s21_list_dst = {1, 3, 4};
  std::list<int> std_list_dst = {1, 3, 4};

  s21_list_dst = std::move(s21_list_src);
  std_list_dst = std::move(std_list_src);

  ASSERT_EQ(std_list_src.size(), s21_list_src.size());
  ASSERT_EQ(std_list_src.empty(), s21_list_src.empty());
  ASSERT_EQ(std_list_dst.size(), s21_list_dst.size());
  ASSERT_EQ(std_list_dst.empty(), s21_list_dst.empty());

  list_check_data(s21_list_dst, std_list_dst);
}

TEST(s21_list_suite, insert_many_back00) {
  s21::list<int> s21_list;
  std::list<int> std_target = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  s21_list.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

  ASSERT_EQ(s21_list.size(), std_target.size());
  ASSERT_EQ(s21_list.empty(), std_target.empty());

  list_check_data(s21_list, std_target);
}

TEST(s21_list_suite, insert_many_back01) {
  s21::list<int> s21_list = {-3, -8, 77};
  std::list<int> std_target = {-3, -8, 77, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  s21_list.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

  ASSERT_EQ(s21_list.size(), std_target.size());
  ASSERT_EQ(s21_list.empty(), std_target.empty());

  list_check_data(s21_list, std_target);
}

TEST(s21_list_suite, insert_many_front00) {
  s21::list<int> s21_list;
  std::list<int> std_target = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  s21_list.insert_many_front(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

  ASSERT_EQ(s21_list.size(), std_target.size());
  ASSERT_EQ(s21_list.empty(), std_target.empty());

  list_check_data(s21_list, std_target);
}

TEST(s21_list_suite, insert_many_front01) {
  s21::list<int> s21_list = {-3, -8, 77};
  std::list<int> std_target = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1, -3, -8, 77};
  // 0  9  8  7  6  5  4  3  2  1  -3  -8  77
  s21_list.insert_many_front(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

  ASSERT_EQ(s21_list.size(), std_target.size());
  ASSERT_EQ(s21_list.empty(), std_target.empty());

  list_check_data(s21_list, std_target);
}

TEST(s21_list_suite, insert_many00) {
  s21::list<int> s21_list;
  std::list<int> std_target = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  auto res_iter =
      s21_list.insert_many(s21_list.begin(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

  ASSERT_EQ(s21_list.size(), std_target.size());
  ASSERT_EQ(s21_list.empty(), std_target.empty());
  ASSERT_EQ(*res_iter, 0);

  list_check_data(s21_list, std_target);
}

TEST(s21_list_suite, insert_many01) {
  s21::list<int> s21_list = {3, 3, 3};
  std::list<int> std_target = {3, 0, 9, 8, 7, 6, 5, 4, 3, 2, 1, 3, 3};
  auto res_iter =
      s21_list.insert_many(s21_list.begin()++, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

  ASSERT_EQ(s21_list.size(), std_target.size());
  ASSERT_EQ(s21_list.empty(), std_target.empty());
  ASSERT_EQ(*res_iter, 0);

  list_check_data(s21_list, std_target);
}
