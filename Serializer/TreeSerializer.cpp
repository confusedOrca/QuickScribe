#include "TreeSerializer.h"

void TreeSerializer::serialize(Node* root, const std::string& filePath) {
    if (!root) throw std::invalid_argument("Root node is null.");

    std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
    if (!outFile) throw std::ios_base::failure("Failed to open file for writing.");

    serializeNode(outFile, root);
    outFile.close();
}

Node* TreeSerializer::deserialize(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) throw std::ios_base::failure("Failed to open file for reading.");

    Node* root = deserializeNode(inFile);
    inFile.close();
    return root;
}

void TreeSerializer::serializeNode(std::ofstream& outFile, Node* node) {
    if (!node) return;

    outFile.write(reinterpret_cast<const char*>(&node->character), sizeof(node->character));
    outFile.write(reinterpret_cast<const char*>(&node->wordFrequency), sizeof(node->wordFrequency));

    size_t childrenCount = node->children.size();
    outFile.write(reinterpret_cast<const char*>(&childrenCount), sizeof(childrenCount));

    for (const auto& [key, child] : node->children) {
        outFile.write(reinterpret_cast<const char*>(&key), sizeof(key));
        serializeNode(outFile, child);
    }
}

Node* TreeSerializer::deserializeNode(std::ifstream& inFile) {
    if (inFile.eof()) return nullptr;

    char character;
    int wordFrequency;
    inFile.read(reinterpret_cast<char*>(&character), sizeof(character));
    inFile.read(reinterpret_cast<char*>(&wordFrequency), sizeof(wordFrequency));

    Node* node = new Node(character);
    node->wordFrequency = wordFrequency;

    size_t childrenCount;
    inFile.read(reinterpret_cast<char*>(&childrenCount), sizeof(childrenCount));

    for (size_t i = 0; i < childrenCount; ++i) {
        char childKey;
        inFile.read(reinterpret_cast<char*>(&childKey), sizeof(childKey));
        node->children[childKey] = deserializeNode(inFile);
    }

    return node;
}
