#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace test {

class DataLoader {
public:
  static std::string load_les_miserables() {
    return load_file_contents(les_miserables_filenames);
  }

protected:
  static std::string load_file_contents(std::vector<std::string> filenames) {
    bool file_found = false;
    std::string file_contents;
    for (const auto &filename : filenames) {
      std::ifstream file{filename};
      if (file.is_open()) {
        file_found = true;
        file_contents = std::string(std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>());
        size_t file_size_bytes = file_contents.size() * sizeof(char);
        std::cout << "[DataLoader] Loaded file: " << filename << " of size "
                  << file_size_bytes << " Bytes." << std::endl;
      }
    }
    if (!file_found) {
      std::string file_names_list;
      for (const auto &filename : filenames) {
        file_names_list += filename + ", ";
      }
      throw std::runtime_error(
          "[DataLoader] Could not open any of the following files using the "
          "current working directory: " +
          std::filesystem::current_path().string() + ": " + file_names_list +
          ".");
    }
    return file_contents;
  }

  static std::vector<std::string> les_miserables_filenames;
};

inline std::vector<std::string> DataLoader::les_miserables_filenames = {
    "./data/test.txt", "./test/data/test.txt"};

} // namespace test
