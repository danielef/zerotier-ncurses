#include "ux.hh"

namespace ux {

  struct Member {
    std::string name;
    std::string ip;
    long last;
  };

  bool compareName(const Member& a, const Member& b) {
    return a.name < b.name;
  }

  std::array<short, 2> initial_colors() {
    short foreground, background;
    pair_content(1, &foreground, &background);
    return {foreground, background};
  }
  
  int draw_tabs() {
    // create the container window
    WINDOW *container_win = newwin(10, 40, 5, 5);
    box(container_win, 0, 0);
    wrefresh(container_win);
    
    // create the sub-windows
    WINDOW *sub_win1 = newwin(8, 38, 6, 6);
    WINDOW *sub_win2 = newwin(8, 38, 6, 6);
    
    // add content to the sub-windows
    wprintw(sub_win1, "This is sub-window 1");
    wprintw(sub_win2, "This is sub-window 2");
    
    // refresh the sub-windows to show the content
    wrefresh(sub_win1);
    wrefresh(sub_win2);
    
    
    // track the active sub-window index
    int active_win_index = 0;
    
    // loop to handle key-press events
    int ch;
    while ((ch = getchar()) != 'q') {
      switch (ch) {
      case '\t':  // switch to the next sub-window
        active_win_index = (active_win_index + 1) % 2;
        break;
      case '1':   // switch to sub-window 1
        active_win_index = 0;
        break;
      case '2':   // switch to sub-window 2
        active_win_index = 1;
        break;
      default:
        break;
      }
      
      // highlight the active sub-window
      if (active_win_index == 0) {
        wbkgd(sub_win1, COLOR_PAIR(1));
        wbkgd(sub_win2, COLOR_PAIR(2));
        wrefresh(sub_win1);
      } else {
        wbkgd(sub_win1, COLOR_PAIR(2));
        wbkgd(sub_win2, COLOR_PAIR(1));
        wrefresh(sub_win2);
      }
      
      // refresh the sub-windows to show the changes
      
      
    }
    
    //int c = getchar();
    return ch;

    // clean up the windows
    //delwin(sub_win1);
    //delwin(sub_win2);
    //delwin(container_win);
  }

  std::vector<Member> toMembers(nlohmann::json mems) {
    std::vector<Member> member;
    for (int i=0; i < mems.size(); i++) {
      std::string m_name = mems[i]["name"];
      std::string m_ip   = mems[i]["config"]["ipAssignments"][0];
      long ts_clock = mems[i]["clock"];
      long ts_last  = mems[i]["lastSeen"];
      long ts_diff  = ts_clock - ts_last;
      member.push_back({m_name, m_ip, ts_diff});
    }
    return member;
  }

  int sub_window(nlohmann::json mems) {
    std::vector<Member> member = toMembers(mems);
    std::sort(member.begin(), member.end(), compareName);
    // get the dimensions of the terminal
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    //int offset_x = 2;
    int offset_y = 2;

    WINDOW* sub_win = newpad(member.size(), max_x);
    
    //std::cout << "x: " << offset_x << "," << max_x - offset_x * 2 << std::endl;
    std::cout << "y: " << offset_y << "," << max_y - offset_y * 2 << std::endl;
    int b = getchar();
    // for (int i = 1; i < member.size() + 1 && i < (max_y - offset_y * 2) - 1  ; i++) {
    for (int i = 0; i < member.size(); i++) {
      //mvwprintw(sub_win, i, 2, (" " + member[i].name).c_str());
      wprintw(sub_win, (" " + member[i].name + "\n").c_str());
      //wrefresh(sub_win);
    }
    //mvwprintw(sub_win, 2, 1, "Hello World2");
    //wprintw(sub_win, "Hello World!");
    //box(sub_win, 0, 0);
    //wrefresh(sub_win);
    int ch;
    int ant_ch;
    int mrow = max_y - offset_y;
    int mcol = max_x; // - offset_x * 2;
    int rowcount = member.size() - mrow;
    int mypadpos = 0;

    prefresh(sub_win, 0, 0, offset_y, 0, mrow, mcol);
    while((ch = wgetch(sub_win)) != 'q')
      {
        ant_ch = ch;
        switch (ch)
          {
          case 65:
            if (mypadpos > 0)
              {
                //mypadpos--;
                prefresh(sub_win, --mypadpos, 0, offset_y, 0, mrow, mcol);
              }
            
            break;
          case 66:
            if (mypadpos < rowcount - 1 + offset_y)
              {
               prefresh(sub_win, ++mypadpos, 0, offset_y, 0, mrow, mcol);
              }
            
            break;
          }
      }

    //std::cout << "ch: " << ch << std::endl;
    return ant_ch;
  }
  
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
