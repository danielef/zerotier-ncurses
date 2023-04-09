#ifndef ZEROTIER_UX_HH_
#define ZEROTIER_UX_HH_

#include <array>
#include <cstdio>
#include <string>
#include <ncurses.h>

namespace ux {

  std::array<short, 2> initial_colors();

  int draw_tabs();

  std::string token_dialog();

}

#endif
