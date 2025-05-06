#include <gtest/gtest.h>
#include <sequential/doubly_linked_list.hpp>
#include <string>

class doubly_linked_list_test : public testing::Test {
protected:
  using value_t = int;
  using doubly_linked_list_t =
      containers::sequential::doubly_linked_list<value_t>;

  doubly_linked_list_t list;

  doubly_linked_list_test() : list() {}

  // 200 -> -4 -> 10
  void SetUp() override {
    list.push_front(10);
    list.insert(list.front(), -4);
    list.insert(list.front(), 200);
  }
};

TEST_F(doubly_linked_list_test, CorrectContainerSize) {
  EXPECT_EQ(list.size(), 3);
}

TEST_F(doubly_linked_list_test, Emptyness) { EXPECT_FALSE(list.empty()); }

TEST_F(doubly_linked_list_test, ClearCollection) {
  list.clear();

  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST_F(doubly_linked_list_test, BehaviourOnEmpty) {
  const size_t old_length = list.size();

  list.clear();

  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());

  ASSERT_THROW(list.pop_front(), containers::sequential::empty_container);
  ASSERT_THROW(list.pop_back(), containers::sequential::empty_container);

  ASSERT_THROW(list.erase(list.front()), containers::sequential::invalid_node);
  ASSERT_THROW(list.erase(list.back()), containers::sequential::invalid_node);

  ASSERT_THROW(list.at(0), std::out_of_range);
}

TEST_F(doubly_linked_list_test, FrontInsertion) {
  const size_t old_length = list.size();
  list.push_front(0);
  EXPECT_EQ(list.front()->data, 0);
  EXPECT_EQ(list.size(), old_length + 1);
}

TEST_F(doubly_linked_list_test, BackInsertion) {
  const size_t old_length = list.size();
  list.push_back(0);
  EXPECT_EQ(list.back()->data, 0);
  EXPECT_EQ(list.size(), old_length + 1);
}

TEST_F(doubly_linked_list_test, MiddleInsertion) {
  const size_t old_length = list.size();
  auto front = list.front();
  list.insert(front->next, 100);
  EXPECT_EQ(front->next->data, 100);
  EXPECT_EQ(list.size(), old_length + 1);
}

TEST_F(doubly_linked_list_test, EraseTail) {
  list.erase(list.back());
  EXPECT_EQ(list.back()->data, -4);
}
