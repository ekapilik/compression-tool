#include <gtest/gtest.h>

#include <compress0r/core.hpp>

using compress0r::encode, compress0r::HuffTree, compress0r::bits;

class EncodeTestFixture : public ::testing::Test {
protected:
  std::string test_string_;
  std::unique_ptr<HuffTree> huff_tree_encoded_;

  void insert_char(std::string &input, char c, size_t n) {
    for (size_t i = 0; i < n; i++) {
      input.push_back(c);
    }
  }

  EncodeTestFixture() {
    std::string practice_huffman_string_ = "";
    insert_char(practice_huffman_string_, 'E', 120);
    insert_char(practice_huffman_string_, 'T', 85);
    insert_char(practice_huffman_string_, 'O', 67);
    insert_char(practice_huffman_string_, 'H', 50);
    insert_char(practice_huffman_string_, 'G', 17);
    insert_char(practice_huffman_string_, 'V', 12);
    insert_char(practice_huffman_string_, 'X', 4);
    insert_char(practice_huffman_string_, 'J', 4);
    huff_tree_encoded_ = std::make_unique<HuffTree>(
        HuffTree::buildTree(practice_huffman_string_));
  }
};

TEST_F(EncodeTestFixture, CharacterEncoding) {
  auto &huff = *huff_tree_encoded_;

  EXPECT_EQ(encode(huff, 'O'), bits({0, 0}));
  EXPECT_EQ(encode(huff, 'J'), bits({1, 0, 0, 1, 0, 1}));
}

TEST_F(EncodeTestFixture, StringEncoding) {
  auto &huff = *huff_tree_encoded_;

  EXPECT_EQ(encode(huff, "VG"), bits({1, 0, 0, 1, 1, 1, 0, 0, 0}));
}
