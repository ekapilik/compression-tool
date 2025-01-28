#include <gtest/gtest.h>

#include <compress0r/core.hpp>

using compress0r::Encoder, compress0r::HuffTree, compress0r::Bits,
    compress0r::BitMap;

class EncodeTestFixture : public ::testing::Test {
protected:
  std::string test_string_;
  std::unique_ptr<HuffTree> huff_tree_encoded_;
  BitMap bitmap_;

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
    bitmap_ = Encoder::toBitmap(*huff_tree_encoded_);
  }
};

TEST_F(EncodeTestFixture, BitMap) {
  std::cout << "bitmap: \n" << compress0r::BitMapToString(bitmap_) << std::endl;
  EXPECT_EQ(bitmap_.size(), 8);
  EXPECT_EQ(bitmap_['O'], Bits({0, 0}));
  EXPECT_EQ(bitmap_['T'], Bits({0, 1}));
  EXPECT_EQ(bitmap_['G'], Bits({1, 0, 0, 0}));
  EXPECT_EQ(bitmap_['X'], Bits({1, 0, 0, 1, 0, 1}));
  EXPECT_EQ(bitmap_['J'], Bits({1, 0, 0, 1, 0, 0}));
  EXPECT_EQ(bitmap_['V'], Bits({1, 0, 0, 1, 1}));
  EXPECT_EQ(bitmap_['H'], Bits({1, 0, 1}));
  EXPECT_EQ(bitmap_['E'], Bits({1, 1}));
}

TEST_F(EncodeTestFixture, CharacterEncoding) {
  EXPECT_EQ(Encoder::encode(bitmap_, 'O'), Bits({0, 0}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'T'), Bits({0, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'G'), Bits({1, 0, 0, 0}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'X'), Bits({1, 0, 0, 1, 0, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'J'), Bits({1, 0, 0, 1, 0, 0}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'V'), Bits({1, 0, 0, 1, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'H'), Bits({1, 0, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, 'E'), Bits({1, 1}));
}

TEST_F(EncodeTestFixture, StringEncoding) {
  EXPECT_EQ(Encoder::encode(bitmap_, "TV"), Bits({0, 1, 1, 0, 0, 1, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, "OE"), Bits({0, 0, 1, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, "VG"), Bits({1, 0, 0, 1, 1, 1, 0, 0, 0}));
  EXPECT_EQ(Encoder::encode(bitmap_, "OTH"), Bits({0, 0, 0, 1, 1, 0, 1}));
  EXPECT_EQ(Encoder::encode(bitmap_, "HO"), Bits({1, 0, 1, 0, 0}));
}
