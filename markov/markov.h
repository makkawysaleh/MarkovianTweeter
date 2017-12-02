//
// Created by Dikshant Adhikari on 12/2/17.
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
#include <random>
#include <regex>

using Prefix = std::deque<std::string>;
using Suffixes = std::vector<std::string>;

class Markov {

private:
    const int MAXGEN = 1024;
    const std::string NONWORD = "\n";
    const int NPREF = 2;
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
