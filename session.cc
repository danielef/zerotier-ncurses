#include "session.hh"

void create_empty_file(const std::string& filename) {
  std::ofstream file(filename);
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
