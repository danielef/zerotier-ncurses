
#include <iostream>
#include <fstream>
#include <filesystem>
#include "session.hh"
#include "nlohmann/json.hpp"

int main(int argc, char** argv) {
  //std::ifstream input("example.json");
  //json data;
  //input >> data;

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  nlohmann::json config = load_config();
  std::cout << "Number of items in Data: " << size_config(config) << std::endl;
  nlohmann::json tokens = config["token"];
  std::cout << "Number of items in Tokens: " << tokens.size() << std::endl;

  return 0;
}

