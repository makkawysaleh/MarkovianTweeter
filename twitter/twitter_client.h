//
// Created by Dikshant Adhikari on 12/1/17.
// This file contains method definitions for receiving tweets for a given user
//

#ifndef MARKOTWEET_TWITTER_CLIENT_H
#define MARKOTWEET_TWITTER_CLIENT_H

#include "../dependencies/json/json.hpp"

using json = nlohmann::json;
using std::string;

class TwitterClient {

public:

    // Constructor
    TwitterClient() = default;

    // Destructor 
    ~TwitterClient() = default;
    
    // Retrieve token from a twitter server
    std::string get_token(const string &key, const string &secret);

    // Get tweets for a given user
    std::vector<string> get_tweets(const string &username, const string &token);

    // Make a vector of words from a user's past tweets
    std::vector<string> make_word_list(std::vector<string> tweets);
};

#endif //MARKOTWEET_TWITTER_CLIENT_H
