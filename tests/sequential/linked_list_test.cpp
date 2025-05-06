#include <gtest/gtest.h>
#include <string>
#include <sequential/linked_list.hpp>

class linked_list_test: public testing::Test {
    protected:
      using value_t = int;
      using linked_list_t = containers::sequential::linked_list<value_t>;
    
      linked_list_t list;
    
      linked_list_test() : list() {}

      // 10 -> -4 -> 200
      void SetUp() override {
        list.push_front(10);
        const auto front = list.front();
        list.insert_after(front, -4);
        list.insert_after(front->next, 200);
      }
    };

TEST_F(linked_list_test, CorrectContainerSize) {
    EXPECT_EQ(list.size(), 3);
}

TEST_F(linked_list_test, Emptyness) {
    EXPECT_FALSE(list.empty());
}

TEST_F(linked_list_test, ClearCollection) {
    list.clear();

    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST_F(linked_list_test, BehaviourOnEmpty) {
    const size_t old_length = list.size();

    for (size_t i = 0; i < old_length; i++) {
        list.pop_front();
    }
    
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());

    ASSERT_THROW(list.pop_front(), containers::sequential::empty_container);
}

TEST_F(linked_list_test, FrontInsertion) {
    const size_t old_length = list.size();
    list.push_front(0);
    EXPECT_EQ(list.front()->data, 0);
    EXPECT_EQ(list.size(), old_length + 1);
}

TEST_F(linked_list_test, MiddleInsertion) {
    const size_t old_length = list.size();
    auto front = list.front();
    list.insert_after(front->next, 100);
    EXPECT_EQ(front->next->next->data, 100);
    EXPECT_EQ(list.size(), old_length + 1);
}

TEST_F(linked_list_test, EraseAfterLastNode) {

    auto tail = list.front();
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    ASSERT_THROW(list.erase_after(tail), containers::sequential::invalid_node);
}
