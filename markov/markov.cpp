//
// Created by Dikshant Adhikari on 12/2/17.
// File with implementation details for methods used to generate text via Markov chains
// Taken and modified from https://stackoverflow.com/questions/4081662/explain-markov-chain-algorithm-in-laymans-terms
//

#include "markov.h"

using std::string;
// Add word to suffix deque, update prefix
void Markov::add(Prefix &prefix, const string &s) {
    if (prefix.size() == NPREF) {
        state_map[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}

// To our list of words extracted from tweets add our prefixes
void Markov::build(Prefix &prefix, std::vector<string> &words) {
    for (auto &word : words) {
        add(prefix, word);
    }
}

// Produce output, one word per line
std::vector<string> Markov::generate(int nwords) {

    Prefix prefix;
    int i;

    std::vector<string> markov_words;

    std::srand(static_cast<unsigned int>(std::time(0)));

    for (i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    for (i = 0; i < nwords; i++) {
        std::vector<string> &suf = state_map[prefix];
        const string &w = suf[std::rand() % suf.size()];
        if (w == NONWORD)
            break;
        markov_words.push_back(w);
        prefix.pop_front();
        prefix.push_back(w);
    }

    return markov_words;
}

// Return the generated markov words
std::vector<string> Markov::get_text(std::vector<string> &words) {
    Prefix prefix((unsigned long) NPREF, NONWORD);
    build(prefix, words);
    add(prefix, NONWORD);
    std::vector<string> generated_words = generate(MAXGEN);
    return generated_words;
}
