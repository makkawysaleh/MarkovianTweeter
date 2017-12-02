//
// Created by Dikshant Adhikari on 12/1/17.
//

#ifndef MARKOTWEET_TWITTER_CLIENT_H
#define MARKOTWEET_TWITTER_CLIENT_H

#include "../dependencies/json/json.hpp"

using json = nlohmann::json;
using std::string;

class TwitterClient {

public:
    std::string get_token(const string &key, const string &secret);
    std::vector<string> get_tweets(const string &handle, const string &token);
};

#endif //MARKOTWEET_TWITTER_CLIENT_H
