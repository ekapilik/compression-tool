#include "./huffman.hpp"
#include "./frequency.hpp"
#include <queue>

namespace compress0r {

/** HuffLeafNode **/
HuffLeafNode::HuffLeafNode(char c, size_t freq) : c_(c), freq_(freq) {}

char HuffLeafNode::value() { return c_; }

size_t HuffLeafNode::weight() { return freq_; }

bool HuffLeafNode::isLeaf() { return true; }

/** HuffInternalNode **/
HuffInternalNode::HuffInternalNode(ptr left, ptr right, size_t freq)
    : freq_(freq), left_(left), right_(right) {}

size_t HuffInternalNode::weight() { return freq_; }

ptr HuffInternalNode::left() { return left_; }

ptr HuffInternalNode::right() { return right_; }

bool HuffInternalNode::isLeaf() { return false; }

/** HuffTree **/
HuffTree::HuffTree(char el, size_t freq)
    : root_(std::make_shared<HuffLeafNode>(el, freq)) {}

HuffTree::HuffTree(ptr l, ptr r, size_t frequency)
    : root_(std::make_shared<HuffInternalNode>(l, r, frequency)) {}

ptr HuffTree::root() const { return root_; }

size_t HuffTree::weight() const { return root_->weight(); }

bool HuffTree::operator==(const HuffTree &other) const {
  return weight() == other.weight();
}

bool HuffTree::operator!=(const HuffTree &other) const {
  return !(*this == other);
}

bool HuffTree::operator<(const HuffTree &other) const {
  return weight() < other.weight();
}

bool HuffTree::operator>(const HuffTree &other) const {
  return weight() > other.weight();
}

bool HuffTree::operator<=(const HuffTree &other) const {
  return weight() <= other.weight();
}

bool HuffTree::operator>=(const HuffTree &other) const {
  return weight() >= other.weight();
}

HuffTree HuffTree::buildTree(const std::string &text) {
  std::priority_queue<HuffTree, std::vector<HuffTree>, std::greater<HuffTree>>
      trees;

  char final_char = static_cast<char>(127);
  for (char c = 0; c < final_char; ++c) {
    auto freq = frequency(text, c);
    if (freq > 0) {
      trees.push(HuffTree(c, freq));
    }
  }

  while (trees.size() > 1) {
    HuffTree left = trees.top();
    trees.pop();

    HuffTree right = trees.top();
    trees.pop();

    auto sum = left.weight() + right.weight();

    trees.push(HuffTree(left.root(), right.root(), sum));
  }

  return trees.top();
}

} // namespace compress0r
