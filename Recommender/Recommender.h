#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include <string>

/**
 * Node class represents a single node in the trie structure.
 */
class Node;

/**
 * Recommendations class is a helper class used to store and manage recommendations.
 */
class Recommendations;

/**
 * RECOMMENDER class provides functionality for maintaining a trie structure and generating word recommendations based on a prefix.
 * @field trieRoot Root node of the trie structure.
 */
class Recommender {
private:
    Node* trieRoot;
    static const int INFINITY_INT = ~(1 << 31);

    /**
     * Helper function to recursively collect words from the trie that match a given prefix.
     * @param node Pointer to the current node in the trie.
     * @param prefix The current prefix being searched for.
     * @param recommendations Object to store and manage the collected recommendations.
     */
    void collectWords(Node* node, const std::string& prefix, Recommendations& recommendations);

public:
    Recommender();

    /**
     * Inserts a word into the trie structure.
     * @param word The word to insert into the trie.
     */
    void insert(const std::string& word);

    /**
     * inserts a word N number of times
     * @param word The word to insert into the trie.
     * @param N The number of times to insert the word.
     */
    void insertNTimes(const std::string& word, int N);

    /**
     * Generates a list of word recommendations based on a given prefix.
     * @param prefix The prefix to search for in the trie.
     * @param n The maximum number of recommendations to return.
     * @return A vector of recommended words matching the prefix, up to the specified number.
     */
    std::vector<std::string> recommend(const std::string& prefix, int n);
};

#endif
