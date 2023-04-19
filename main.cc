#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <unistd.h>

#include "net.hh"
#include "session.hh"
#include "ux.hh"
#include "nlohmann/json.hpp"

nlohmann::json config;
nlohmann::json tokens;
std::vector<nlohmann::json> members;
int current_members_index = 0;

void update_data() {
  std::cout << members.size() << std::endl;
  for (int i=0; i<tokens.size(); i++) {
    std::string current_token = tokens[i];
    std::cout << current_token << std::endl;
    nlohmann::json nets = net::retrieve_networks(current_token);
    std::cout << nets << std::endl;

    std::string network_id    = nets[0]["id"];
    std::string network_name  = nets[0]["config"]["name"];
    nlohmann::json mems = net::retrieve_members(current_token, network_id);
    if (members.size() < i) {
      members.push_back(mems);
    } else {
      members[i] = mems;
    }
    usleep(5000);
  }
}

int main(int argc, char** argv) {

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  config = session::load_config();
  std::cout << "Number of items in Data: " << session::size_config(config) << std::endl;
  tokens = config["token"];
  std::cout << "Number of items in Tokens: " << tokens.size() << std::endl;
  
  // Initialize ncurses
  initscr();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  start_color();
  auto [fg, bg] = ux::initial_colors();
  int w = 0;
  if (session::size_config(config) == 0 || tokens.size() == 0) {
    // First session
    std::string token = ux::token_dialog();
    config = session::add_token(config, token);
    session::save_config(config);
  } else {
    std::thread updater(update_data);
    std::cout << "tab: '" << members << "'" << std::endl;
    /*
    while (1) {
      //mems = net::retrieve_members(current_token, network_id);
      w = ux::sub_window(members[current_members_index]);
    }*/
    // Clean up ncurses
    endwin();
  }
  

  //std::cout << "tab: '" << c << "'" << std::endl;
  std::cout << "colors: fg: " << fg << ", bg: " <<  bg << " w: "<<  w << std::endl;


  return 0;
}
