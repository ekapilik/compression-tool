#pragma once

#include "frequency.hpp"
#include <cstddef>
#include <memory>
#include <queue>

namespace compress0r {

class HuffBaseNode {
public:
  virtual bool isLeaf() = 0;
  virtual size_t weight() = 0;
  virtual ~HuffBaseNode() = default;
};

class HuffLeafNode : public HuffBaseNode {
public:
  HuffLeafNode(char c, size_t freq) : c_(c), freq_(freq) {}

  char value() { return c_; }

  size_t weight() override { return freq_; }

  bool isLeaf() override { return true; }

private:
  char c_;
  size_t freq_;
};

class HuffInternalNode : public HuffBaseNode {
  using ptr = std::shared_ptr<HuffBaseNode>;

public:
  HuffInternalNode(ptr left, ptr right, size_t freq)
      : freq_(freq), left_(left), right_(right) {}

  size_t weight() override { return freq_; }

  ptr left() { return left_; }

  ptr right() { return right_; }

  bool isLeaf() override { return false; }

private:
  size_t freq_;
  ptr left_, right_;
};

class HuffTree {
  using ptr = std::shared_ptr<HuffBaseNode>;

public:
  HuffTree(char el, size_t freq)
      : root_(std::make_shared<HuffLeafNode>(el, freq)) {}

  HuffTree(ptr l, ptr r, size_t frequency)
      : root_(std::make_shared<HuffInternalNode>(l, r, frequency)) {}

  ptr root() const { return root_; }

  size_t weight() const { return root_->weight(); }

  bool operator==(const HuffTree &other) const {
    return weight() == other.weight();
  }

  bool operator!=(const HuffTree &other) const { return !(*this == other); }

  bool operator<(const HuffTree &other) const {
    return weight() < other.weight();
  }

  bool operator>(const HuffTree &other) const {
    return weight() > other.weight();
  }

  bool operator<=(const HuffTree &other) const {
    return weight() <= other.weight();
  }

  bool operator>=(const HuffTree &other) const {
    return weight() >= other.weight();
  }

  static HuffTree buildTree(const std::string &text) {
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

private:
  ptr root_;
};

} // namespace compress0r
