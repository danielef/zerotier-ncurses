
#include <iostream>
#include <fstream>
#include <filesystem>

#include "net.hh"
#include "session.hh"
#include "ux.hh"
#include "nlohmann/json.hpp"

int main(int argc, char** argv) {
  //std::ifstream input("example.json");
  //json data;
  //input >> data;

  std::cout << "Foo" << std::endl;
  std::cout << "Path separator: " << std::filesystem::path::preferred_separator << std::endl;

  nlohmann::json config = session::load_config();
  std::cout << "Number of items in Data: " << session::size_config(config) << std::endl;
  nlohmann::json tokens = config["token"];
  std::cout << "Number of items in Tokens: " << tokens.size() << std::endl;

  config = session::add_token(config, "bar");

  nlohmann::json tokens2 = config["token"];
  std::cout << "Number of items in Tokens: " << tokens2.size() << std::endl;

  session::save_config(config);
  
  // Initialize ncurses
  initscr();
  start_color();
  auto [fg, bg] = ux::initial_colors();
  int c = ux::draw_tabs();
  //std::string token = ux::token_dialog();
  
  // Clean up ncurses
  endwin();

  std::cout << "tab: '" << c << "'" << std::endl;
  std::cout << "colors: fg: " << fg << ", bg: " <<  bg << std::endl;
  
  nlohmann::json nets = nlohmann::json::parse(R"([{"id":"159924d630937523","type":"Network","clock":1681022367016,"config":{"authTokens":null,"creationTime":1645714346494,"capabilities":[],"enableBroadcast":true,"id":"159924d630937523","ipAssignmentPools":[{"ipRangeStart":"172.22.0.1","ipRangeEnd":"172.22.255.254"}],"lastModified":1645721655710,"mtu":2800,"multicastLimit":32,"name":"quantum","private":true,"remoteTraceLevel":0,"remoteTraceTarget":null,"routes":[{"target":"172.22.0.0/16"}],"rules":[{"etherType":2048,"not":true,"or":false,"type":"MATCH_ETHERTYPE"},{"etherType":2054,"not":true,"or":false,"type":"MATCH_ETHERTYPE"},{"etherType":34525,"not":true,"or":false,"type":"MATCH_ETHERTYPE"},{"type":"ACTION_DROP"},{"type":"ACTION_ACCEPT"}],"tags":[],"v4AssignMode":{"zt":true},"v6AssignMode":{"6plane":false,"rfc4193":false,"zt":false},"dns":{"domain":"","servers":null},"ssoConfig":{"enabled":false,"mode":""}},"description":"","rulesSource":"#\n# This is a default rule set that allows IPv4 and IPv6 traffic but otherwise\n# behaves like a standard Ethernet switch.\n#\n# Please keep in mind that ZeroTier versions prior to 1.2.0 do NOT support advanced\n# network rules.\n#\n# Since both senders and receivers enforce rules, you will get the following\n# behavior in a network with both old and new versions:\n#\n# (old: 1.1.14 and older, new: 1.2.0 and newer)\n#\n# old \u003c--\u003e old: No rules are honored.\n# old \u003c--\u003e new: Rules work but are only enforced by new side. Tags will NOT work, and\n#               capabilities will only work if assigned to the new side.\n# new \u003c--\u003e new: Full rules engine support including tags and capabilities.\n#\n# We recommend upgrading all your devices to 1.2.0 as soon as convenient. Version\n# 1.2.0 also includes a significantly improved software update mechanism that is\n# turned on by default on Mac and Windows. (Linux and mobile are typically kept up\n# to date using package/app management.)\n#\n\n#\n# Allow only IPv4, IPv4 ARP, and IPv6 Ethernet frames.\n#\ndrop\n\tnot ethertype ipv4\n\tand not ethertype arp\n\tand not ethertype ipv6\n;\n\n#\n# Uncomment to drop non-ZeroTier issued and managed IP addresses.\n#\n# This prevents IP spoofing but also blocks manual IP management at the OS level and\n# bridging unless special rules to exempt certain hosts or traffic are added before\n# this rule.\n#\n#drop\n#\tnot chr ipauth\n#;\n\n# Accept anything else. This is required since default is 'drop'.\naccept;\n","permissions":null,"ownerId":"9d621983-d934-4e6a-88aa-8b5ec6b738df","onlineMemberCount":0,"authorizedMemberCount":24,"totalMemberCount":24,"capabilitiesByName":{},"tagsByName":{},"ui":null}])");
  std::cout << std::setw(4) << nets << std::endl;

  return 0;
}
