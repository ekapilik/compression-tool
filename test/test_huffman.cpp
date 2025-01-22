#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

#include <compress0r/core.hpp>

using compress0r::HuffLeafNode, compress0r::HuffInternalNode,
    compress0r::HuffTree;

class HuffmanTreeFixture : public ::testing::Test {
protected:
  std::string test_filename = "./data/test.txt";
  std::ifstream test_file{test_filename};
  std::string test_file_contents;

  HuffmanTreeFixture() {
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

TEST_F(HuffmanTreeFixture, HuffLeafNode) {
  HuffLeafNode leaf('a', 5);
  EXPECT_EQ(leaf.value(), 'a');
  EXPECT_EQ(leaf.weight(), 5);
  EXPECT_TRUE(leaf.isLeaf());
}

TEST_F(HuffmanTreeFixture, HuffInternalNode) {
  auto left = std::make_shared<HuffLeafNode>('a', 5);
  auto right = std::make_shared<HuffLeafNode>('b', 10);
  HuffInternalNode internal(left, right, 15);
  EXPECT_EQ(internal.weight(), 15);
  EXPECT_FALSE(internal.isLeaf());
  EXPECT_EQ(internal.left(), left);
  EXPECT_TRUE(internal.left()->isLeaf());
  EXPECT_EQ(internal.right(), right);
  EXPECT_TRUE(internal.right()->isLeaf());
}

TEST_F(HuffmanTreeFixture, HuffTreeConstructorTwoArg) {
  HuffTree tree('a', 5);
  EXPECT_TRUE(tree.root()->isLeaf());
  EXPECT_EQ(tree.root()->weight(), 5);
}

TEST_F(HuffmanTreeFixture, HuffTreeConstructorThreeArg) {
  // Leaf nodes
  auto leaf_a = std::make_shared<HuffLeafNode>('a', 5);
  auto leaf_b = std::make_shared<HuffLeafNode>('b', 10);
  HuffTree tree_a(leaf_a, leaf_b, 15);
  EXPECT_FALSE(tree_a.root()->isLeaf());
  EXPECT_EQ(tree_a.root()->weight(), 15);

  // Internal nodes
  auto leaf_c = std::make_shared<HuffLeafNode>('c', 20);
  auto leaf_d = std::make_shared<HuffLeafNode>('d', 25);
  auto internal_a = std::make_shared<HuffInternalNode>(leaf_a, leaf_b, 15);
  auto internal_b = std::make_shared<HuffInternalNode>(leaf_c, leaf_d, 45);
  HuffTree tree_b(internal_a, internal_b, 60);
}

TEST_F(HuffmanTreeFixture, HuffTreeOperators) {
  HuffTree tree_a('a', 5);
  HuffTree tree_b('b', 10);

  EXPECT_EQ(tree_a, tree_a);
  EXPECT_NE(tree_a, tree_b);
  EXPECT_LT(tree_a, tree_b);
  EXPECT_GT(tree_b, tree_a);
  EXPECT_LE(tree_a, tree_b);
  EXPECT_GE(tree_b, tree_a);
}

TEST_F(HuffmanTreeFixture, BuildHuffTree) {
  auto huff_tree = HuffTree::buildTree("abbccc");
}
