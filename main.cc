
#include <iostream>
#include <fstream>
#include <filesystem>
#include "session.hh"
#include "nlohmann/json.hpp"


using json = nlohmann::json;

int main(int argc, char** argv) {
  //std::ifstream input("example.json");
  //json data;
  //input >> data;

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  json data = load_config();
  std::cout << "Number of items in Data: " << data.size() << std::endl;
  
  return 0;
}

