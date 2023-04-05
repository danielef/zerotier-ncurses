#include <iostream>
#include <fstream>
#include <filesystem>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char** argv) {
  //std::ifstream input("example.json");
  //json data;
  //input >> data;

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  return 0;
}

