#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>

/**
 * @class Node
 * @brief Represents a node in a Trie.
 * @field character Each node corresponds to a character (or an empty char).
 * @field wordFrequency 0 if the node is not a word end, otherwise the frequency of the word.
 * @field children A map of characters to the next node in the trie.
 */
class Node {
private:
    static const char EMPTY_CHAR = '\0';

public:
    char character;
    int wordFrequency;
    std::map<char, Node*> children;

    /**
     * @brief Constructor for initializing a Node with an optional character.
     * @param character The character this node represents (defaults EMPTY_CHAR).
     */
    Node(char character = EMPTY_CHAR);

    /**
     * @brief Adds a new character to the children of this node.
     * @param nextChar The character to add.
     * @return The new node created for the next character.
     */
    Node* addNextChar(char nextChar);

    /**
     * @brief checks if the node is a word end.
     * @return true if the node is a word end, false otherwise.
     */
    bool isWordEnd() const;

    /**
     * @brief Prints the existing children (next char) of this node.
     */
    void printChildren();
};

#endif // NODE_H
