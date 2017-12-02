// This files defines the class structure for Curl
// Modified By: Dikshant Adhikari
// Modified from the Barbeque library by Grant McGovern found at https://github.com/g12mcgov/Barbeque
// New changes made by me include adding support for headers in GET requests and removing redundant get and post methods not
// used by this program

#ifndef CURL_H
#define CURL_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <map>

using std::string;
using std::map;
using std::cout;
using std::endl;

class Curl {

public:
    // Declare libcurl object
    CURL *curl;

    // Declare object to hold libcurl response bytes
    CURLcode res;

    // Constructor
    Curl();

    // Destructor
    ~Curl();

    // GET method
    string get(string &url, map<string, string> &headers_map);

    // POST method
    string post(string &url, map<string, string> &params, map<string, string> &headers_map);

private:
    // To store response codes from HTTP Request
    unsigned int http_status;
};

#endif
