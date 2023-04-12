
#include <iostream>
#include <fstream>
#include <filesystem>

#include "net.hh"
#include "session.hh"
#include "ux.hh"
#include "nlohmann/json.hpp"

int main(int argc, char** argv) {

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  nlohmann::json config = session::load_config();
  std::cout << "Number of items in Data: " << session::size_config(config) << std::endl;
  nlohmann::json tokens = config["token"];
  std::cout << "Number of items in Tokens: " << tokens.size() << std::endl;
  
  // Initialize ncurses
  initscr();
  start_color();
  auto [fg, bg] = ux::initial_colors();
  endwin();
  if (session::size_config(config) == 0 || tokens.size() == 0) {
    // First session
    std::string token = ux::token_dialog();
    config = session::add_token(config, token);
    session::save_config(config);
  } else {
    std::cout << "here!" << std::endl;
    for (int i=0; i<tokens.size(); i++) {
      std::string current_token = tokens[i];
      
      nlohmann::json nets = net::retrieve_networks(current_token);
      
      std::string network_id    = nets[0]["id"];
      std::string network_name  = nets[0]["config"]["name"];
      
      // We need to extract here data from nets and also for members!
      nlohmann::json mems = net::retrieve_members(current_token, network_id);

      std::cout << "idx: '" << i << "'" << ", id: '"   << network_id   << "'"<< std::endl;
      std::cout << "idx: '" << i << "'" << ", name: '" << network_name << "'"<< std::endl;
      std::cout << "" << std::endl;      
      // std::cout << std::setw(4) << nets << std::endl;      
      // std::cout << std::setw(4) << mems << std::endl;


      
    }
    
  }
  
  // Clean up ncurses

  //std::cout << "tab: '" << c << "'" << std::endl;
  std::cout << "colors: fg: " << fg << ", bg: " <<  bg << std::endl;


  return 0;
}
