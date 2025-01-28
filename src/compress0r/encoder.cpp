#include "./encoder.hpp"
#include "./huffman.hpp"
#include <stack>

namespace compress0r {

std::string BitsToString(const Bits &bits) {
  std::string result;
  int count = 0;
  for (const auto &bit : bits) {
    result += bit ? "1" : "0";
    if (++count % 4 == 0) {
      result += " ";
    }
  }
  return result;
}

std::string BitMapToString(const BitMap &bitmap) {
  std::string result;
  for (const auto &[key, value] : bitmap) {
    result += key;
    result += ": ";
    result += BitsToString(value);
    result += "\n";
  }
  return result;
}

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
      stack.push({internal->right(), right_bits});
    }
  }
  return result;
}

Bits Encoder::encode(const BitMap &bitmap, const std::string &input) {
  Bits result;
  for (const char &c : input) {
    Bits encoded = Encoder::encode(bitmap, c);
    result.insert(result.end(), encoded.begin(), encoded.end());
  }
  return result;
}

Bits Encoder::encode(const BitMap &bitmap, const char &input) {
  return bitmap.at(input);
}

} // namespace compress0r
