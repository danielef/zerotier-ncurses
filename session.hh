#ifndef ZEROTIER_SESSION_HH_
#define ZEROTIER_SESSION_HH_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

void create_empty_file(const std::string& filename);

std::string home_dir();

#endif
