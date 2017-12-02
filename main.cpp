#include <iostream>
#include "twitter/twitter_client.h"
#include "markov/markov.h"

using std::cout;
using std::endl;
using std::string;

using namespace std;

int main()
{
    // Get tweets for a given user and parse their tweets into a vector of words
    auto *client = new TwitterClient();
    string token = client->get_token("IkNpQ7rLdd2XBpx6TlI7QdviF", "tSiFZvRLVdNARZ9JqYxoZcIGgaiHpNJWxwZE0tAlloxr7rk3Td");
    auto tweets = client->get_tweets("realdonaldtrump", token);
    std::vector<string> words = client->make_wordlist(tweets);

    // Pass the vector of words into our markov generator
    Markov markov;
    std::vector<string> markov_words = markov.get_text(words);

    // Get our markov generated words
    for (auto &word : markov_words) {
        cout << word + " ";
    }
}
