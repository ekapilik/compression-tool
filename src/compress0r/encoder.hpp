#pragma once

#include <map>
#include <string>
#include <vector>

#include "./huffman.hpp"

namespace compress0r {

using Bits = std::vector<bool>;
using BitMap = std::map<char, Bits>;

class Encoder {
public:
  static BitMap toBitmap(const HuffTree &tree);

  Bits encode(const std::string &input);

  Bits encode(const BitMap &bitmap, const std::string &input);

  Bits encode(const BitMap &bitmap, const char &input);
};

} // namespace compress0r
