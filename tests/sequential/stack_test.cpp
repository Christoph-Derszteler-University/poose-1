#include <gtest/gtest.h>
#include <string>

#include  "sequential/list_stack.hpp"

class list_stack_test : public testing::Test {
    protected:
      using value_t = int;
      using list_stack_t = containers::sequential::list_stack<value_t>;
    
      list_stack_t list_stack;
    
      list_stack_test() : list_stack() {}
    
      void SetUp() override {
        list_stack.push(42);
        list_stack.push(69);
        list_stack.push(2042006);
      }
    };

TEST_F(list_stack_test, CorrectContainerSize){
    EXPECT_EQ(list_stack.size(), 3);
}
TEST_F(list_stack_test, DataIsInsertedCorrectly){
    list_stack.push(45);
    EXPECT_EQ(list_stack.top(), 45);
}
TEST_F(list_stack_test, DataIsDeletedCorrectly){
    const auto&  tmp = list_stack.pop();
    EXPECT_EQ(tmp, 45);
    EXPECT_EQ(list_stack.size(), 3);
    EXPECT_FALSE(list_stack.empty());
}
TEST_F(list_stack_test, ListIsEmptyCorrectBehaviour){
    list_stack.pop();
    list_stack.pop();
    list_stack.pop();

    EXPECT_TRUE(list_stack.empty());
    ASSERT_THROW(list_stack.pop(), containers::sequential::empty_container);
}
