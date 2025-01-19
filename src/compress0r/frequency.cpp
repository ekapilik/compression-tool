#include "./frequency.hpp"

namespace compress0r {

size_t frequency(const std::basic_string<char> &s, const char &c) {
  size_t count = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == c) {
      ++count;
    }
  }
  return count;
}

} // namespace compress0r
