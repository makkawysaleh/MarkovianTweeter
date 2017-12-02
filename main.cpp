//
// Created by Dikshant Adhikari on 12/1/17.
// A file to run our program. Includes some utility functions to make life easier.
//

#include <iostream>
#include <fstream>
#include "twitter/twitter_client.h"
#include "markov/markov.h"

// Namespace our std library methods
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;

// Vector indices for our key and secret. Always stored in this order.
const int KEY = 0;
const int SECRET = 1;

// Get user input for a twitter username
string get_username() {
    string username;
    cout << endl;
    cout << "Please enter a twitter username or /quit to exit: ";
    cin >> username;
    return username;
}

// Get credentials from a text file
std::vector<string> get_credentials() {

    // Read a credentials.txt file. This file should be created manually
    // at the path from where the program is run.
    ifstream inputFile("credentials.txt");
    string line;

    std::vector<string> credentials;
    while (getline(inputFile, line))
    {
        credentials.push_back(line);
    }

    return credentials;
}

int main() {

    // Get credentials
    std::vector<string> credentials = get_credentials();

    // Check if the credentials were read from the file properly
    try {
        credentials.at(0);
        credentials.at(1);
    }
    catch (const std::out_of_range& e) {
        cout << "Error! Please populate the credentials.txt file with proper values." << endl;
        exit(0);
    }

    // Catch any exceptions due to invalid credentials or username
    try {
        // Exchange twitter api keys for a token
        auto *client = new TwitterClient();
        string token = client->get_token(credentials[KEY], credentials[SECRET]);

        while (true) {
            try {
                // Get username from the user or quit depending on user input
                string username = get_username();
                if (username == "/quit") {
                    cout << "Goodbye!" << endl;
                    exit(0);
                }

                // Get tweets for the given username
                auto tweets = client->get_tweets(username, token);
                std::vector<string> words = client->make_word_list(tweets);

                // Pass the vector of words into our markov generator
                Markov markov;
                std::vector<string> markov_words = markov.get_text(words);

                // Get our markov generated words
                for (auto &word : markov_words) {
                    cout << word + " ";
                }
                cout << endl;
            }
            catch (const std::invalid_argument &e) {
                cout << "No such user or user has no tweets! Please try a new user!" << endl;
            }
        }
    } catch(const::std::invalid_argument &e) {
        cout << "Invalid credentials! Please check your credentials and please try again!" << endl;
    }
}
