#include "../twitter/twitter_client.h"
#include "markov.h"

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

    for (i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    for (i = 0; i < nwords; i++) {
        std::vector<string> &suf = state_map[prefix];
        const string &w = suf[rand() % suf.size()];
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
