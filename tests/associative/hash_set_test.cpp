#include <gtest/gtest.h>
#include <functional>
#include <string>

#include "associative/set/hash_set.hpp"

class HashSetTest : public testing::Test {
protected:
  using key_t = std::string;
  using hash_set_t = containers::associative::hash_set<key_t>;

  constexpr static std::hash<std::string> hash_function;
  hash_set_t hash_set;

  HashSetTest() : hash_set(hash_function) {}

  void SetUp() override {
    hash_set.insert("key1");
    hash_set.insert("key2");
    hash_set.insert("key3");
  }
};

TEST_F(HashSetTest, CorrectContainerSize) {
  EXPECT_EQ(hash_set.size(), 3);
}

TEST_F(HashSetTest, InsertAddsKey) {
  hash_set.insert("key4");
  EXPECT_TRUE(hash_set.exists("key4"));
}

TEST_F(HashSetTest, InsertDuplicateThrowsException) {
  EXPECT_THROW(
    hash_set.insert("key1"),
    containers::associative::duplicate_key<std::string>
  );
}

TEST_F(HashSetTest, InsertSafelyDoesNotThrow) {
  EXPECT_NO_THROW(hash_set.insert_safely("key1"));
  EXPECT_EQ(hash_set.size(), 3);
}

TEST_F(HashSetTest, ExistsReturnsTrueForExistingKey) {
  EXPECT_TRUE(hash_set.exists("key1"));
  EXPECT_TRUE(hash_set.exists("key2"));
  EXPECT_TRUE(hash_set.exists("key3"));
}

TEST_F(HashSetTest, ExistsReturnsFalseForNonExistingKey) {
  EXPECT_FALSE(hash_set.exists("nonexistent"));
}

TEST_F(HashSetTest, RemoveDeletesKey) {
  hash_set.remove("key1");
  EXPECT_FALSE(hash_set.exists("key1"));
}

TEST_F(HashSetTest, RemoveNonExistingKeyDoesNotThrow) {
  EXPECT_NO_THROW(hash_set.remove("nonexistent"));
}

TEST_F(HashSetTest, IteratorBeginPointsToFirstElement) {
  const auto& it = hash_set.begin();
  EXPECT_NE(it, hash_set.end());
}

TEST_F(HashSetTest, IteratorEndPointsToPastLastElement) {
  const auto& it = hash_set.end();
  EXPECT_EQ(it, hash_set.end());
}

TEST_F(HashSetTest, ConstIteratorWorksCorrectly) {
  const auto& const_hash_set = hash_set;
  const auto& it = const_hash_set.cbegin();
  EXPECT_NE(it, const_hash_set.cend());
}