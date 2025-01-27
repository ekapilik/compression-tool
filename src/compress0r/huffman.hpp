#pragma once

#include <cstddef>
#include <memory>

namespace compress0r {

class HuffBaseNode {
public:
  virtual bool isLeaf() = 0;
  virtual size_t weight() = 0;
  virtual ~HuffBaseNode() = default;
};

class HuffLeafNode : public HuffBaseNode {
public:
  HuffLeafNode(char c, size_t freq);

  char value();

  size_t weight() override;

  bool isLeaf() override;

private:
  char c_;
  size_t freq_;
};

using ptr = std::shared_ptr<HuffBaseNode>;

class HuffInternalNode : public HuffBaseNode {
public:
  HuffInternalNode(ptr left, ptr right, size_t freq);

  size_t weight() override;

  ptr left();

  ptr right();

  bool isLeaf() override;

private:
  size_t freq_;
  ptr left_, right_;
};

class HuffTree {
public:
  HuffTree(char el, size_t freq);

  HuffTree(ptr l, ptr r, size_t frequency);

  ptr root() const;

  size_t weight() const;

  bool operator==(const HuffTree &other) const;

  bool operator!=(const HuffTree &other) const;

  bool operator<(const HuffTree &other) const;

  bool operator>(const HuffTree &other) const;

  bool operator<=(const HuffTree &other) const;

  bool operator>=(const HuffTree &other) const;

  static HuffTree buildTree(const std::string &text);

private:
  ptr root_;
};

} // namespace compress0r
