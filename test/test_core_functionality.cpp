#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

#include <compress0r/core.hpp>

using compress0r::frequency;

class Frequency : public ::testing::Test {
protected:
  std::string test_filename = "./data/test.txt";
  std::ifstream test_file{test_filename};
  std::string test_file_contents;

  Frequency() {
    if (!test_file.is_open()) {
      throw std::runtime_error(
          "[Frequency Test Fixture] Could not open file: " + test_filename +
          ". Current path: " + std::filesystem::current_path().string());
    } else {
      test_file_contents =
          std::string((std::istreambuf_iterator<char>(test_file)),
                      std::istreambuf_iterator<char>());
    }
  }
};

TEST_F(Frequency, QuickFrequencyCorrect) {
  EXPECT_EQ(frequency("a", 'a'), 1);
  EXPECT_EQ(frequency("abc\n   abc", 'a'), 2);
  EXPECT_EQ(frequency("Title: Les Misérables", 'e'), 3);

  EXPECT_EQ(frequency("\n\t\n\n", '\n'), 3);
}

TEST_F(Frequency, FrequencyFileCorrect) {
  EXPECT_EQ(frequency(test_file_contents, 'X'), 333);
  EXPECT_EQ(frequency(test_file_contents, 't'), 223'000);
  EXPECT_EQ(frequency(test_file_contents, '\n'), 73'589);
  EXPECT_EQ(frequency(test_file_contents, ' '), 516'353);
}
