//
// Created by Dikshant Adhikari on 12/1/17.
//

#ifndef MARKOTWEET_TWITTER_CLIENT_H
#define MARKOTWEET_TWITTER_CLIENT_H

#include <string>

class TwitterClient {

public:
    std::string get_token(const std::string key, const std::string secret);
    std::string get_tweets(const std::string handle, const std::string token);
};

#endif //MARKOTWEET_TWITTER_CLIENT_H
