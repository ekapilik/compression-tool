#include "./encoder.hpp"
#include "./huffman.hpp"
#include <stack>

namespace compress0r {

BitMap Encoder::toBitmap(const HuffTree &tree) {
  BitMap result;
  std::stack<std::pair<std::shared_ptr<HuffBaseNode>, Bits>> stack;

  stack.push({tree.root(), Bits()});
  while (!stack.empty()) {
    auto [node, bits] = stack.top();
    stack.pop();
    if (node->isLeaf()) {
      auto leaf = std::dynamic_pointer_cast<HuffLeafNode>(node);
      result[leaf->value()] = bits;
    } else {
      auto internal = std::dynamic_pointer_cast<HuffInternalNode>(node);

      auto left_bits = bits;
      left_bits.push_back(0);
      stack.push({internal->left(), left_bits});

      auto right_bits = bits;
      right_bits.push_back(1);
      stack.push({internal->right(), bits});
    }
  }
  return result;
}

Bits Encoder::encode(const std::string &input) {
  HuffTree tree = HuffTree::buildTree(input);
  BitMap bitmap = toBitmap(tree);
  return encode(bitmap, input);
}

Bits Encoder::encode(const BitMap &bitmap, const std::string &input) {
  Bits result;
  for (const auto &c : input) {
    Bits encoded = encode(bitmap, c);
    result.insert(result.end(), encoded.begin(), encoded.end());
  }
  return result;
}

Bits encode(const BitMap &bitmap, const char &input) {
  Bits result;

  return result;
}

} // namespace compress0r
