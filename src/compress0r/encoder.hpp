#pragma once

#include <map>
#include <string>
#include <vector>

#include "./huffman.hpp"

namespace compress0r {

using Bits = std::vector<bool>;
using BitMap = std::map<char, Bits>;

std::string BitMapToString(const BitMap &bitmap);

class Encoder {
public:
  static BitMap toBitmap(const HuffTree &tree);

  static Bits encode(const BitMap &bitmap, const std::string &input);

  static Bits encode(const BitMap &bitmap, const char &input);
};

} // namespace compress0r
