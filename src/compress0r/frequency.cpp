#include "./frequency.hpp"

namespace compress0r {

/**
 * @brief Count the number of times a character appears in a string.
 * @param s The string to search.
 * @param c The character to search for.
 * @return The number of times the character appears in the string.
 */
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
