//
// Created by Dikshant Adhikari on 12/1/17.
//

#include <iostream>
#include <map>
#include "twitter_client.h"
#include "../dependencies/barbeque/barbeque.h"
#include "../dependencies/base64/base64.hpp"

using std::string;
using std::map;
using json = nlohmann::json;

// Given a key and secret returns a access_token and token_type from Twitter's server
std::string TwitterClient::get_token(const std::string &key, const std::string &secret) {

    // Build our authorization token using our key and secret by encoding it in Base64
    std::string key_secret =  key + ":" + secret;
    std::string authentication_token = "Basic " + Base64::encode(key_secret);

    // The URL to send our post request to
    string token_url = "https://api.twitter.com/oauth2/token";

    // Construct a map for our JSON params. Much like a Python Dict
    map<string, string> params;

    // Populate the params map
    params["grant_type"] = "client_credentials";

    // Construct our headers map
    map<string, string> headers;

    // Populate the header map
    headers["Content-type"] = "application/x-www-form-urlencoded;charset=UTF-8";
    headers["Authorization"] = authentication_token;

    // Declare a new Barbeque object
    auto bbq = new Barbeque();

    // Add our params and headers and make a POST request
    string header = bbq->post(token_url, params, headers);

    return header;
}

// For a given Twitter handle return tweets from that person
std::string TwitterClient::get_tweets(const std::string &handle, const std::string &token_header) {

    // Convert token header to a JSON object
    json token_object = json::parse(token_header);

    // Get token from the JSON header
    auto token_value = token_object.find("access_token");

    // Cast our token value to string
    string token = *token_value;

    // The search URL to send our get request to
    string search_url = "https://api.twitter.com/1.1/search/tweets.json?q=" + handle;

    // Construct our headers map
    map<string, string> headers;

    // Populate the header map with our bearer token
    headers["Authorization"] = "Bearer " + token;

    // Declare a new Barbeque object
    auto bbq = new Barbeque();

    // Add header and make a get request
    string response = bbq->get(search_url, headers);

    return response;
}