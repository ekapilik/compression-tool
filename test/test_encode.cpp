#include <gtest/gtest.h>

#include <compress0r/core.hpp>
#include <memory>

using compress0r::Encoder, compress0r::HuffTree, compress0r::Bits,
    compress0r::BitMap;

using std::make_unique;

class EncodeTestFixture : public ::testing::Test {
protected:
  std::unique_ptr<Encoder> encoder_;

  void insert_char(std::string &input, char c, size_t n) {
    for (size_t i = 0; i < n; i++) {
      input.push_back(c);
    }
  }

  EncodeTestFixture() {
    std::string test_string = "";
    insert_char(test_string, 'E', 120);
    insert_char(test_string, 'T', 85);
    insert_char(test_string, 'O', 67);
    insert_char(test_string, 'H', 50);
    insert_char(test_string, 'G', 17);
    insert_char(test_string, 'V', 12);
    insert_char(test_string, 'X', 4);
    insert_char(test_string, 'J', 4);
    encoder_ = make_unique<Encoder>(HuffTree::buildTree(test_string));
  }
};

TEST_F(EncodeTestFixture, BitMap) {
  auto bitmap_ = encoder_->bitmap();
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
  EXPECT_EQ(encoder_->encode('O'), Bits({0, 0}));
  EXPECT_EQ(encoder_->encode('T'), Bits({0, 1}));
  EXPECT_EQ(encoder_->encode('G'), Bits({1, 0, 0, 0}));
  EXPECT_EQ(encoder_->encode('X'), Bits({1, 0, 0, 1, 0, 1}));
  EXPECT_EQ(encoder_->encode('J'), Bits({1, 0, 0, 1, 0, 0}));
  EXPECT_EQ(encoder_->encode('V'), Bits({1, 0, 0, 1, 1}));
  EXPECT_EQ(encoder_->encode('H'), Bits({1, 0, 1}));
  EXPECT_EQ(encoder_->encode('E'), Bits({1, 1}));
}

TEST_F(EncodeTestFixture, StringEncoding) {
  EXPECT_EQ(encoder_->encode("TV"), Bits({0, 1, 1, 0, 0, 1, 1}));
  EXPECT_EQ(encoder_->encode("OE"), Bits({0, 0, 1, 1}));
  EXPECT_EQ(encoder_->encode("VG"), Bits({1, 0, 0, 1, 1, 1, 0, 0, 0}));
  EXPECT_EQ(encoder_->encode("OTH"), Bits({0, 0, 0, 1, 1, 0, 1}));
  EXPECT_EQ(encoder_->encode("HO"), Bits({1, 0, 1, 0, 0}));
}
