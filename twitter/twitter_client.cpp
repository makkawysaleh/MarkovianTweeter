//
// Created by Dikshant Adhikari on 12/1/17.
//

#include <iostream>
#include <map>
#include "twitter_client.h"
#include "../dependencies/curl/curl.h"
#include "../dependencies/base64/base64.hpp"

using std::string;
using std::map;
using std::vector;
using json = nlohmann::json;

// Given a key and secret returns a access_token and token_type from Twitter's server
string TwitterClient::get_token(const string &key, const string &secret) {

    // Build our authorization token using our key and secret by encoding it in Base64
    std::string key_secret =  key + ":" + secret;
    std::string authentication_token = "Basic " + Base64::encode(key_secret);

    // The URL to send our post request to
    string token_url = "https://api.twitter.com/oauth2/token";

    // Construct a map for our JSON params
    map<string, string> params;

    // Populate the params map
    // Required by the twitter API
    params["grant_type"] = "client_credentials";

    // Construct a map for our headers
    map<string, string> headers;

    // Populate the header map with authorization and content type
    // Required by the twitter API
    headers["Content-type"] = "application/x-www-form-urlencoded;charset=UTF-8";
    headers["Authorization"] = authentication_token;

    // Declare a new Curl object for making requests
    // Curl is a wrapper class around the curl library (libcurl)
    auto curl = new Curl();

    // Add our params and headers and make a POST request to exchange our authorization for a token
    string header = curl->post(token_url, params, headers);

    return header;
}

// For a given Twitter handle return tweets from that person
std::vector<string> TwitterClient::get_tweets(const string &handle, const string &token_header) {

    // Convert token header to a JSON object
    json token_object = json::parse(token_header);

    // Get token from the JSON header
    auto token_value = token_object.find("access_token");

    // Cast our token value to string
    string token = *token_value;

    // The search URL to send our get request to
    string search_url = "https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name="
                        + handle + "&tweet_mode=extended&count=200";

    // Construct our headers map
    map<string, string> headers;

    // Populate the header map with our bearer token
    headers["Authorization"] = "Bearer " + token;

    // Declare a new Curl object for making requests
    // Curl is a wrapper class around the curl library (libcurl)
    auto curl = new Curl();

    // Add header and make a get request
    string response = curl->get(search_url, headers);

    // Parse our string as JSON
    json json_response = json::parse(response);

    // A vector to hold tweet from a user
    vector<string> tweets;

    // Extract the text portion of the tweet and push it to our vector
    for (auto &element : json_response) {
        auto text = element.find("full_text");
        tweets.push_back(*text);
    }

    // Return a vector full of tweets
    return tweets;
}