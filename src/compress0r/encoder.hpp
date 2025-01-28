#pragma once

#include <map>
#include <string>
#include <vector>

#include "./huffman.hpp"

namespace compress0r {

using Bits = std::vector<bool>;
using BitMap = std::map<char, Bits>;

std::string BitMapToString(const BitMap &bitmap);
BitMap toBitmap(const HuffTree &tree);

class Encoder {
public:
  Encoder(const BitMap &bitmap);

  Encoder(const HuffTree &tree);

  Bits encode(const std::string &input);

  Bits encode(const char &input);

  BitMap bitmap() const { return bitmap_; }

protected:
  BitMap bitmap_;
};

} // namespace compress0r
