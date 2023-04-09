#ifndef ZEROTIER_REQUEST_H_
#define ZEROTIER_REQUEST_H_
#include <iostream>
#include <string>
#include <string>
#include <curl/curl.h>

namespace net {

  size_t write_callback_function(char *ptr, size_t size, size_t nmemb, void *userdata);

  std::string make_json_request(const std::string& url, const std::string& token);

  std::string retrieve_networks(const std::string& token);

}

#endif
