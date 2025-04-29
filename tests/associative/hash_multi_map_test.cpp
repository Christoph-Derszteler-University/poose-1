#include <gtest/gtest.h>
#include <functional>
#include <string>
#include <vector>

#include "associative/map/hash_multi_map.hpp"

class hash_multi_map_test : public ::testing::Test {
protected:
  using key_t = std::string;
  using value_t = int;
  using hash_multi_map_t = containers::associative::hash_multi_map<key_t, value_t>;

  hash_multi_map_t hash_multi_map;

  static std::hash<std::string> hash_function;
  hash_multi_map_test() : hash_multi_map(hash_function) {}

  void SetUp() override {
    hash_multi_map.insert("key1", 1);
    hash_multi_map.insert("key2", 2);
    hash_multi_map.insert("key3", 3);
    hash_multi_map.insert("key1", 10); // Duplicate key with different value
  }
};

TEST_F(hash_multi_map_test, InsertAddsKeyValuePair) {
  hash_multi_map.insert("key4", 4);
  EXPECT_TRUE(hash_multi_map.exists("key4", 4));
  EXPECT_TRUE(hash_multi_map.exists_by_key("key4"));
}

TEST_F(hash_multi_map_test, InsertAllowsDuplicateKeys) {
  hash_multi_map.insert("key1", 100);
  EXPECT_TRUE(hash_multi_map.exists("key1", 100));
  EXPECT_EQ(hash_multi_map.size(), 5) << "With 3 occurrences of 'key1', the size should be 5";
}

TEST_F(hash_multi_map_test, ExistsReturnsTrueForExistingKey) {
  EXPECT_TRUE(hash_multi_map.exists_by_key("key1"));
  EXPECT_TRUE(hash_multi_map.exists_by_key("key2"));
  EXPECT_TRUE(hash_multi_map.exists_by_key("key3"));
}

TEST_F(hash_multi_map_test, ExistsReturnsFalseForNonExistingKey) {
  EXPECT_FALSE(hash_multi_map.exists_by_key("nonexistent"));
}

TEST_F(hash_multi_map_test, RemoveDeletesSingleOccurrence) {
  hash_multi_map.remove("key1", 1);
  ASSERT_FALSE(hash_multi_map.exists("key1", 1));
  ASSERT_TRUE(hash_multi_map.exists_by_key("key1"));
  ASSERT_EQ(hash_multi_map.size(), 3) << "With only 1 occurrence of 'key1', the size should be 3";
}

TEST_F(hash_multi_map_test, RemoveAllDeletesAllOccurrences) {
  hash_multi_map.remove_by_key("key1");
  EXPECT_FALSE(hash_multi_map.exists_by_key("key1"));
  ASSERT_EQ(hash_multi_map.size(), 2) << "With no occurrences of 'key1', the size should be 2";
}

TEST_F(hash_multi_map_test, RemoveNonExistingKeyDoesNotThrow) {
  EXPECT_NO_THROW(hash_multi_map.remove_by_key("nonexistent"));
}

TEST_F(hash_multi_map_test, IteratorBeginPointsToFirstElement) {
  const auto& it = hash_multi_map.begin();
  EXPECT_NE(it, hash_multi_map.end());
}

TEST_F(hash_multi_map_test, IteratorEndPointsToPastLastElement) {
  const auto& it = hash_multi_map.end();
  EXPECT_EQ(it, hash_multi_map.end());
}

TEST_F(hash_multi_map_test, ConstIteratorWorksCorrectly) {
  const auto& const_hash_multi_map = hash_multi_map;
  const auto& it = const_hash_multi_map.cbegin();
  EXPECT_NE(it, const_hash_multi_map.cend());
}
