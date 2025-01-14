#ifndef TREESERIALIZER_H
#define TREESERIALIZER_H

#include <iostream>
#include <fstream>
#include "../Recommender/Node/Node.h"

class TreeSerializer {
public:
    /**
     * @brief Serializes the tree starting from the root node into a binary file.
     * @param root Pointer to the root node of the tree.
     * @param filePath The relative path of the binary file.
     */
    static void serialize(Node* root, const std::string& filePath);

    /**
     * @brief Deserializes a tree from a binary file and returns the root node.
     * @param filePath The relative path of the binary file.
     * @return Pointer to the root node of the tree.
     */
    static Node* deserialize(const std::string& filePath);

private:
    static void serializeNode(std::ofstream& outFile, Node* node);
    
    static Node* deserializeNode(std::ifstream& inFile);
};

#endif // TREESERIALIZER_H