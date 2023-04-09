
#include <iostream>
#include <fstream>
#include <filesystem>

#include "session.hh"
#include "ux.hh"
#include "nlohmann/json.hpp"

int main(int argc, char** argv) {
  //std::ifstream input("example.json");
  //json data;
  //input >> data;

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  nlohmann::json config = session::load_config();
  std::cout << "Number of items in Data: " << session::size_config(config) << std::endl;
  nlohmann::json tokens = config["token"];
  std::cout << "Number of items in Tokens: " << tokens.size() << std::endl;

  config = session::add_token(config, "bar");

  nlohmann::json tokens2 = config["token"];
  std::cout << "Number of items in Tokens: " << tokens2.size() << std::endl;

  session::save_config(config);
  
  // Initialize ncurses
  initscr();
  start_color();
  auto [fg, bg] = ux::initial_colors();
  int c = ux::draw_tabs();
  //std::string token = ux::token_dialog();
  
  // Clean up ncurses
  endwin();

  std::cout << "tab: '" << c << "'" << std::endl;
  std::cout << "colors: fg: " << fg << ", bg: " <<  bg << std::endl;

  return 0;
}
