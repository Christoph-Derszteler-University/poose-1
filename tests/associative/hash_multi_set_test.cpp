#include <gtest/gtest.h>
#include <functional>
#include <string>
#include <vector>

#include "associative/set/hash_multi_set.hpp"

class hash_multi_set_test : public ::testing::Test {
protected:
  using key_t = std::string;
  using hash_multi_set_t = containers::associative::hash_multi_set<key_t>;

  hash_multi_set_t hash_multi_set;

  hash_multi_set_test() : hash_multi_set(std::hash<key_t>()) {}

  void SetUp() override {
    hash_multi_set.insert("key1");
    hash_multi_set.insert("key2");
    hash_multi_set.insert("key3");
    hash_multi_set.insert("key1"); // Duplicate key
  }
};

TEST_F(hash_multi_set_test, InsertAddsKey) {
  hash_multi_set.insert("key4");
  EXPECT_TRUE(hash_multi_set.exists("key4"));
}

TEST_F(hash_multi_set_test, InsertAllowsDuplicates) {
  hash_multi_set.insert("key1");
  EXPECT_EQ(hash_multi_set.size(), 5) << "with 2 duplicates of 'key1', the size of the container should be 5";
}

TEST_F(hash_multi_set_test, ExistsReturnsTrueForExistingKey) {
  EXPECT_TRUE(hash_multi_set.exists("key1"));
  EXPECT_TRUE(hash_multi_set.exists("key2"));
  EXPECT_TRUE(hash_multi_set.exists("key3"));
}

TEST_F(hash_multi_set_test, ExistsReturnsFalseForNonExistingKey) {
  EXPECT_FALSE(hash_multi_set.exists("nonexistent"));
}

TEST_F(hash_multi_set_test, CountReturnsCorrectOccurrences) {
  EXPECT_EQ(hash_multi_set.size(), 4) << "with 1 duplicate of 'key1', the size of the container should be 4";
}

TEST_F(hash_multi_set_test, RemoveDeletesSingleOccurrence) {
  hash_multi_set.remove("key1");
  EXPECT_EQ(hash_multi_set.size(), 2) << "without any 'key1', the size of the container should be 2";
}

TEST_F(hash_multi_set_test, RemoveAllDeletesAllOccurrences) {
  hash_multi_set.remove("key1");
  EXPECT_FALSE(hash_multi_set.exists("key1"));
}

TEST_F(hash_multi_set_test, RemoveNonExistingKeyDoesNotThrow) {
  EXPECT_NO_THROW(hash_multi_set.remove("nonexistent"));
}

TEST_F(hash_multi_set_test, IteratorBeginPointsToFirstElement) {
  const auto& it = hash_multi_set.begin();
  EXPECT_EQ(it, hash_multi_set.begin());
  EXPECT_NE(it, hash_multi_set.end());
}

TEST_F(hash_multi_set_test, IteratorEndPointsToPastLastElement) {
  const auto& it = hash_multi_set.end();
  EXPECT_EQ(it, hash_multi_set.end());
}

TEST_F(hash_multi_set_test, ConstIteratorWorksCorrectly) {
  const auto& it = hash_multi_set.cbegin();
  EXPECT_NE(it, hash_multi_set.cend());
}

TEST_F(hash_multi_set_test, IteratorEqualityIsCorrect) {
  auto comparison = containers::associative::hash_multi_set<std::string>(std::hash<std::string>());
  comparison.insert("key5");
  comparison.insert("key3");
  const auto& first = hash_multi_set.begin();
  const auto& second = comparison.begin();

  EXPECT_EQ(first, hash_multi_set.begin()) << "equal iterators of the same container must be equal";
  EXPECT_EQ(second, comparison.begin()) << "equal iterators of the same container must be equal";
  EXPECT_NE(first, second) << "iterators at the same position of two different containers must not be equal";
}