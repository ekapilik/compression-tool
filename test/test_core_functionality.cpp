#include <gtest/gtest.h>

#include "./load_data.hpp"
#include <compress0r/core.hpp>

using compress0r::frequency;

class FrequencyFixture : public ::testing::Test {
protected:
  FrequencyFixture() {}
};

TEST_F(FrequencyFixture, QuickFrequencyCorrect) {
  EXPECT_EQ(frequency("a", 'a'), 1);
  EXPECT_EQ(frequency("a", 'A'), 0);
  EXPECT_EQ(frequency("aAaAaAaa", 'A'), 3);
  EXPECT_EQ(frequency("abc\n   abc", 'a'), 2);
  EXPECT_EQ(frequency("Title: Les Misérables", 'e'), 3);
  EXPECT_EQ(frequency("\n\t\n\n", '\n'), 3);
}

TEST_F(FrequencyFixture, QuickFrequencyTrueNegatives) {
  EXPECT_NE(frequency("a", 'a'), 0);
  EXPECT_NE(frequency("abc\n   abc", 'a'), 1);
  EXPECT_NE(frequency("Title: Les Misérables", 'e'), 4);
}

TEST_F(FrequencyFixture, FrequencyFileCorrect) {
  std::string test_file_contents = test::DataLoader::load_les_miserables();
  EXPECT_EQ(frequency(test_file_contents, 'X'), 333);
  EXPECT_EQ(frequency(test_file_contents, 't'), 223'000);
  EXPECT_EQ(frequency(test_file_contents, '\n'), 73'589);
  EXPECT_EQ(frequency(test_file_contents, ' '), 516'353);
}

TEST_F(FrequencyFixture, FrequencyFileTrueNegatives) {
  std::string test_file_contents = test::DataLoader::load_les_miserables();
  EXPECT_NE(frequency(test_file_contents, 'X'), 334);
  EXPECT_NE(frequency(test_file_contents, 't'), 223);
}
