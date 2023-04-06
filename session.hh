#ifndef ZEROTIER_SESSION_HH_
#define ZEROTIER_SESSION_HH_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "nlohmann/json.hpp"

void create_empty_file(const std::string& filename);

std::string home_dir();

nlohmann::json load_config();

int save_config(nlohmann::json data);

int size_config(nlohmann::json data);

int add_token(nlohmann::json data, const std::string& tkn);

#endif
