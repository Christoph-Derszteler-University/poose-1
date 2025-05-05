#include <gtest/gtest.h>
#include <string>

#include  "sequential/list_queue.hpp"

class list_queue_test : public testing::Test {
    protected:
      using value_t = int;
      using list_queue_t = containers::sequential::list_queue<value_t>;
    
      list_queue_t list_queue;
    
      list_queue_test() : list_queue() {}
    
      void SetUp() override {
        list_queue.enqueue(42);
        list_queue.enqueue(69);
        list_queue.enqueue(2042006);
      }
    };

TEST_F(list_queue_test, CorrectContainerSize){
    EXPECT_EQ(list_queue.size(), 3);
}
TEST_F(list_queue_test, DataIsInsertedCorrectly){
    list_queue.enqueue(45);
    EXPECT_EQ(list_queue.back(), 45);
}
TEST_F(list_queue_test, DataIsDeletedCorrectly){
    const auto&  tmp = list_queue.dequeue();
    EXPECT_EQ(tmp, 42);
    EXPECT_EQ(list_queue.size(), 2);
    EXPECT_FALSE(list_queue.empty());
}
TEST_F(list_queue_test, QueueIsEmptyCorrectBehaviour){
    list_queue.dequeue();
    list_queue.dequeue();
    list_queue.dequeue();

    EXPECT_TRUE(list_queue.empty());
    ASSERT_THROW(list_queue.dequeue(), containers::sequential::empty_container);
}
