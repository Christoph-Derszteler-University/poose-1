#include <gtest/gtest.h>
#include <functional>
#include <string>
#include <utility>

#include "associative/map/hash_map.hpp"

class hash_map_test : public testing::Test {
protected:
  using key_t = std::string;
  using value_t = int;
  using hash_map_t = containers::associative::hash_map<key_t, value_t>;

  static std::hash<key_t> hash_function;
  hash_map_t hash_map;

  hash_map_test() : hash_map(hash_function) {}

  void SetUp() override {
    hash_map.insert("key1", 1);
    hash_map.insert("key2", 2);
    hash_map.insert("key3", 3);
  }
};

TEST_F(hash_map_test, CorrectContainerSize) {
  EXPECT_EQ(hash_map.size(), 3);
}

TEST_F(hash_map_test, InsertAddsKeyValuePair) {
  hash_map.insert("key4", 4);
  ASSERT_TRUE(hash_map.find_by_key("key4").has_value());
  EXPECT_EQ(hash_map.find_by_key("key4").value(), 4);
}

TEST_F(hash_map_test, InsertDuplicateThrowsException) {
  EXPECT_THROW(
    hash_map.insert("key1", 10),
    containers::associative::duplicate_key<key_t>
  );
}

TEST_F(hash_map_test, InsertSafelyDoesNotThrow) {
  EXPECT_NO_THROW(hash_map.insert_safely("key1", 10));
  EXPECT_EQ(hash_map.find_by_key("key1").value(), 1);
}

TEST_F(hash_map_test, ExistsReturnsTrueForExistingKey) {
  EXPECT_TRUE(hash_map.find_by_key("key1").has_value());
  EXPECT_TRUE(hash_map.find_by_key("key2").has_value());
  EXPECT_TRUE(hash_map.find_by_key("key3").has_value());
}

TEST_F(hash_map_test, ExistsReturnsFalseForNonExistingKey) {
  EXPECT_FALSE(hash_map.find_by_key("nonexistent").has_value());
}

TEST_F(hash_map_test, FindByKeyOrThrowReturnsValueForExistingKey) {
  EXPECT_EQ(hash_map.find_by_key_or_throw("key1"), 1);
  EXPECT_EQ(hash_map.find_by_key_or_throw("key2"), 2);
  EXPECT_EQ(hash_map.find_by_key_or_throw("key3"), 3);
}

TEST_F(hash_map_test, FindByKeyOrThrowThrowsForNonExistingKey) {
  EXPECT_THROW(
    hash_map.find_by_key_or_throw("nonexistent"),
    containers::associative::value_not_found<key_t>
  );
}

TEST_F(hash_map_test, RemoveDeletesKeyValuePair) {
  hash_map.remove("key1");
  EXPECT_FALSE(hash_map.find_by_key("key1").has_value());
}

TEST_F(hash_map_test, RemoveNonExistingKeyDoesNotThrow) {
  EXPECT_NO_THROW(hash_map.remove("nonexistent"));
}

TEST_F(hash_map_test, IteratorBeginPointsToFirstElement) {
  const auto& it = hash_map.begin();
  EXPECT_NE(it, hash_map.end());
}

TEST_F(hash_map_test, IteratorEndPointsToPastLastElement) {
  const auto& it = hash_map.end();
  EXPECT_EQ(it, hash_map.end());
}

TEST_F(hash_map_test, ConstIteratorWorksCorrectly) {
  const auto& const_hash_map = hash_map;
  const auto& it = const_hash_map.cbegin();
  EXPECT_NE(it, const_hash_map.cend());
}