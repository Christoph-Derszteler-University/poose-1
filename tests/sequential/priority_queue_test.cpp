#include <gtest/gtest.h>
#include <string>
#include <sequential/priority_queue.hpp>

class priority_queue_test : public testing::Test {
    protected:
      using value_t = int;
      using priority_queue_t = containers::sequential::priority_queue<value_t>;
    
      priority_queue_t queue;
    
      priority_queue_test() : priority_queue() {}

      // 2042006 -> 69 -> 42
      void SetUp() override {
        queue.push(42);
        queue.push(69);
        queue.push(2042006);
      }
    };

TEST_F(priority_queue_test, CorrectContainerSize){
    EXPECT_EQ(queue.size(), 3);
}
TEST_F(priority_queue_test, DataIsInsertedCorrectly){
    queue.push(45);
    EXPECT_EQ(queue.back(), 42);
}

TEST_F(priority_queue_test, DataIsDeletedCorrectly){
    const auto& tmp = queue.top();
    EXPECT_EQ(tmp, 2042006);
    EXPECT_EQ(queue.size(), 2);
    EXPECT_FALSE(queue.empty());
}

TEST_F(priority_queue_test, QueueIsEmptyCorrectBehaviour){
    queue.pop();
    queue.pop();
    queue.pop();

    EXPECT_TRUE(queue.empty());
    ASSERT_THROW(queue.pop(), containers::sequential::empty_container);
    ASSERT_THROW(queue.top(), std::out_of_range);
}
