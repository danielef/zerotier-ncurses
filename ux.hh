#ifndef ZEROTIER_UX_HH_
#define ZEROTIER_UX_HH_

#include <array>
#include <cstdio>
#include <string>
#include <iostream> // for prints
#include <ncurses.h>
#include "nlohmann/json.hpp"

namespace ux {

  std::array<short, 2> initial_colors();

  int draw_tabs();

  int sub_window(nlohmann::json mems);

  std::string token_dialog();

}

#endif
