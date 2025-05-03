#include <gtest/gtest.h>
#include <functional>
#include <string>

#include "associative/set/hash_set.hpp"

class hash_set_test : public testing::Test {
protected:
  using key_t = std::string;
  using hash_set_t = containers::associative::hash_set<key_t>;

  hash_set_t hash_set;

  hash_set_test() : hash_set(std::hash<std::string>()) {}

  void SetUp() override {
    hash_set.insert("key1");
    hash_set.insert("key2");
    hash_set.insert("key3");
  }
};

TEST_F(hash_set_test, CorrectContainerSize) {
  EXPECT_EQ(hash_set.size(), 3);
}

TEST_F(hash_set_test, InsertAddsKey) {
  hash_set.insert("key4");
  EXPECT_TRUE(hash_set.exists("key4"));
}

TEST_F(hash_set_test, InsertDuplicateThrowsException) {
  EXPECT_THROW(
    hash_set.insert("key1"),
    containers::associative::duplicate_key<std::string>
  );
}

TEST_F(hash_set_test, InsertSafelyDoesNotThrow) {
  EXPECT_NO_THROW(hash_set.insert_safely("key1"));
  EXPECT_EQ(hash_set.size(), 3);
}

TEST_F(hash_set_test, ExistsReturnsTrueForExistingKey) {
  EXPECT_TRUE(hash_set.exists("key1"));
  EXPECT_TRUE(hash_set.exists("key2"));
  EXPECT_TRUE(hash_set.exists("key3"));
}

TEST_F(hash_set_test, ExistsReturnsFalseForNonExistingKey) {
  EXPECT_FALSE(hash_set.exists("nonexistent"));
}

TEST_F(hash_set_test, RemoveDeletesKey) {
  hash_set.remove("key1");
  EXPECT_FALSE(hash_set.exists("key1"));
}

TEST_F(hash_set_test, RemoveNonExistingKeyDoesNotThrow) {
  EXPECT_NO_THROW(hash_set.remove("nonexistent"));
}

TEST_F(hash_set_test, IteratorBeginPointsToFirstElement) {
  const auto& it = hash_set.begin();
  EXPECT_EQ(it, hash_set.begin());
  EXPECT_NE(it, hash_set.end());
}

TEST_F(hash_set_test, IteratorEndPointsToPastLastElement) {
  const auto& it = hash_set.end();
  EXPECT_EQ(it, hash_set.end());
}

TEST_F(hash_set_test, ConstIteratorWorksCorrectly) {
  const auto& const_hash_set = hash_set;
  const auto& it = const_hash_set.cbegin();
  EXPECT_NE(it, const_hash_set.cend());
}

TEST_F(hash_set_test, IteratorEqualityIsCorrect) {
  auto comparison = containers::associative::hash_set<std::string>(std::hash<std::string>());
  comparison.insert("key5");
  comparison.insert("key3");
  const auto& first = hash_set.begin();
  const auto& second = comparison.begin();

  EXPECT_EQ(first, hash_set.begin()) << "equal iterators of the same container must be equal";
  EXPECT_EQ(second, comparison.begin()) << "equal iterators of the same container must be equal";
  EXPECT_NE(first, second) << "iterators at the same position of two different containers must not be equal";
}