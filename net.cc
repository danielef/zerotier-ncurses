#include "net.hh"

namespace net {

  size_t write_callback_function(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Cast the userdata pointer to a std::string*
    std::string *response = reinterpret_cast<std::string*>(userdata);
    
    // Append the response data to the std::string
    response->append(ptr, size * nmemb);
    
    // Return the size of the response data
    return size * nmemb;
  }
  
  std::string make_json_request(const std::string& url, const std::string& token) {
    CURL *curl;
    CURLcode res;
    std::string response;
    
    curl_global_init(CURL_GLOBAL_ALL);
    
    curl = curl_easy_init();
    if(curl) {
      // Set the request URL
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      
      // Set the request headers
      struct curl_slist *headers = NULL;
      headers = curl_slist_append(headers, "Content-Type: application/json");
      std::string auth_header = "Authorization: Bearer " + token;
      headers = curl_slist_append(headers, auth_header.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      
      // Set the write callback function to handle the response data
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_function);
      
      // Set the userdata pointer to the response string
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
      
      // Make the request
      res = curl_easy_perform(curl);
      
      // Clean up
      curl_slist_free_all(headers);
      curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    
    return response;
  }
  
  nlohmann::json retrieve_networks(const std::string& token) {
    nlohmann::json data;
    try {
      std::string url = "https://my.zerotier.com/api/network";
      std::cout << url << std::endl;
      std::string req = make_json_request(url, token);
      data = nlohmann::json::parse(req);
    } catch (nlohmann::detail::parse_error& e) {
      std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return data;
  }

  nlohmann::json retrieve_members(const std::string& token, const std::string& network_id) {
    nlohmann::json data;
    try {
      std::string url = "https://my.zerotier.com/api/network/" + network_id + "/member";
      std::string req = make_json_request(url, token);
      data = nlohmann::json::parse(req);
    } catch (nlohmann::detail::parse_error& e) {
      std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return data;
  }
  
}
