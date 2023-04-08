#include "ux.hh"

namespace ux {
  
  std::string token_dialog() {

    int height = 5, width = 40, start_y, start_x;

    // get the dimensions of the terminal
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    // calculate the starting coordinates for the window
    start_y = (max_y - height) / 2;
    start_x = (max_x - width) / 2;

    // Create the dialog window
    WINDOW* dialogWindow = newwin(5, 40, start_y, start_x);

    // Draw the contents of the dialog window
    mvwprintw(dialogWindow, 1, 3, "Please enter your Zerotier token:");
    box(dialogWindow, 0, 0);
    wrefresh(dialogWindow);
    WINDOW* inputBox = subwin(dialogWindow, 3, 36, start_y + 2, start_x + 2);
    //box(inputBox, 0, 0);
    wrefresh(inputBox);

    // Get user input from the text input box
    char name[32];
    mvwgetstr(inputBox, 0, 1, name);
    //int c = getchar();

    return std::string(name);
  }
  
}
