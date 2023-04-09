#include "session.hh"

namespace session {

  void create_empty_file(const std::string& filename) {
    std::ofstream file(filename);
    file << "{}";
    file.close();
  }
  
  std::string home_dir() {
    const char* home_env_var = std::getenv("HOME");
    const char* userprofile_env_var = std::getenv("USERPROFILE");
    std::string home_dir;
    if (home_env_var != nullptr) {
      home_dir = home_env_var;
    } else if (userprofile_env_var != nullptr) {
      home_dir = userprofile_env_var;
    } else {
      throw std::runtime_error("Error: Could not find either HOME or USERPROFILE environment variable.");
    }
    return home_dir;
  }
  
  nlohmann::json load_config() {
    std::string filename = home_dir() + std::filesystem::path::preferred_separator + ".zerotier_ncurses_config";
    std::cout << "Loading " + filename << std::endl;
    
    if(std::filesystem::exists(filename)) {
      std::cout << "File exists!" << std::endl;
    } else {
      std::cout << "File does not exist." << std::endl;
      create_empty_file(filename);
    }
    nlohmann::json data;
    try {
      std::ifstream input(filename);
      input >> data;
    } catch (nlohmann::detail::parse_error& e) {
      std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return data;
  }

  int save_config(nlohmann::json data) {
    std::string filename = home_dir() + std::filesystem::path::preferred_separator + ".zerotier_ncurses_config";
    std::cout << "Saving " + filename << std::endl;
    
    try {
      std::ofstream output(filename);
      output << std::setw(4) << data << std::endl;
    } catch (nlohmann::detail::parse_error& e) {
      std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return data.size();
  }
  
  int size_config(nlohmann::json data) {
    nlohmann::json token = data["token"];
    return token.size();
  }
  
  nlohmann::json add_token(nlohmann::json data, const std::string& tkn) {
    nlohmann::json token = data["token"];
    if (token.size() > 0) {
      // Looking for repeated tkns
      bool found = false;
      for (const auto& val : token) {
        if (val == tkn) {
          found = true;
          break;
        }
      }
      if (!found) {
        token.push_back(tkn);
      }
    } else {
      token = { tkn };
    }
    data["token"] = token;
    return data;
  }
  
}
