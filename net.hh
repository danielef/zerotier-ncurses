#ifndef ZEROTIER_REQUEST_H_
#define ZEROTIER_REQUEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "nlohmann/json.hpp"

namespace net {

  size_t write_callback_function(char *ptr, size_t size, size_t nmemb, void *userdata);

  std::string make_json_request(const std::string& url, const std::string& token);

  nlohmann::json retrieve_networks(const std::string& token);

  nlohmann::json retrieve_members(const std::string& token, const std::string& network_id);

}

#endif
