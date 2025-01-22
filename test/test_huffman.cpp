#include <gtest/gtest.h>

#include <compress0r/core.hpp>

using compress0r::HuffLeafNode, compress0r::HuffInternalNode,
    compress0r::HuffTree;

class HuffmanTreeFixture : public ::testing::Test {
protected:
  HuffmanTreeFixture() {}
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

TEST_F(HuffmanTreeFixture, BuildHuffTreeBasic) {
  /* should produce the following tree:
              6
              /\
             /  \
         (c, 3)  3
                 /\
                /  \
           (a, 1)  (b, 2)
  */

  auto huff_tree = HuffTree::buildTree("abbccc");

  auto root = reinterpret_cast<HuffInternalNode *>(huff_tree.root().get());
  EXPECT_EQ(root->weight(), 6);
  EXPECT_FALSE(root->isLeaf());

  // Left subtree
  auto left = reinterpret_cast<HuffLeafNode *>(root->left().get());
  EXPECT_EQ(left->value(), 'c');
  EXPECT_EQ(left->weight(), 3);

  // Right subtree
  auto right = reinterpret_cast<HuffInternalNode *>(root->right().get());

  // Left subtree of right subtree
  auto right_left = reinterpret_cast<HuffLeafNode *>(right->left().get());
  EXPECT_EQ(right_left->value(), 'a');
  EXPECT_EQ(right_left->weight(), 1);

  // Right subtree of right subtree
  auto right_right = reinterpret_cast<HuffLeafNode *>(right->right().get());
  EXPECT_EQ(right_right->value(), 'b');
  EXPECT_EQ(right_right->weight(), 2);
}
