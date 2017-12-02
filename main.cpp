#include <iostream>
#include "twitter/twitter_client.h"

using std::cout;
using std::endl;
using std::string;

int main() {
    auto *client = new TwitterClient();
    string token = client->get_token("IkNpQ7rLdd2XBpx6TlI7QdviF", "tSiFZvRLVdNARZ9JqYxoZcIGgaiHpNJWxwZE0tAlloxr7rk3Td");
    auto tweets = client->get_tweets("@realdonaldtrump", token);

    for (auto &i : tweets) {
        cout << i << endl;
    }
    return 0;
}