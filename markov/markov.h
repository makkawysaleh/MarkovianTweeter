//
// Created by Dikshant Adhikari on 12/2/17.
// A class that defines methods for generating text via Markov chain
// Taken and modified from https://stackoverflow.com/questions/4081662/explain-markov-chain-algorithm-in-laymans-terms
//

#ifndef MARKOTWEET_MARKOV_H
#define MARKOTWEET_MARKOV_H

#include <iostream>
#include <unordered_map>
#include <deque>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <regex>
#include <map>

using Prefix = std::deque<std::string>;
using Suffixes = std::vector<std::string>;
using std::string;

class Markov {

private:
    // Maximum number of words to generate
    const int MAXGEN = 1000;
    // New line is not a word and works as a delimiter
    const std::string NONWORD = "\n";
    // Number of prefixes
    const int NPREF = 2;
    // A map to hold our states
    std::map<Prefix, std::vector<string> > state_map;

public:
    Markov() = default;

    // Add word to suffix deque, update prefix
    void add(Prefix &prefix, const string &s);

    // Add prefixes to the ist of words extracted from tweets add our prefixes
    void build(Prefix &prefix, std::vector<string> &words);

    // Produce output, one word per line
    std::vector<string> generate(int nwords);

    // Return the generated markov words
    std::vector<string> get_text(std::vector<string> &words);
};

#endif //MARKOTWEET_MARKOV_H
