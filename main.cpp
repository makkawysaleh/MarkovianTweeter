#include <iostream>
#include "twitter/twitter_client.h"

using std::cout;
using std::endl;
using std::string;

int main() {
    auto *client = new TwitterClient();
    json token = client->get_token("IkNpQ7rLdd2XBpx6TlI7QdviF", "tSiFZvRLVdNARZ9JqYxoZcIGgaiHpNJWxwZE0tAlloxr7rk3Td");
    cout << client->get_tweets("realdonaldtrump", token) << endl;
    return 0;
}