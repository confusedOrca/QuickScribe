#include "./Node.h"

Node::Node(char character) : character(character), wordFrequency(0) {}

Node* Node::addNextChar(char nextChar) {
    if (children.find(nextChar) == children.end()) {
        children[nextChar] = new Node(nextChar);
    }
    return children[nextChar];
}

bool Node::isWordEnd() const {
    return wordFrequency > 0;
}

void Node::printChildren() {
    for (const auto& child : children) {
        std::cout << child.first << " ";
    }
    std::cout << std::endl;
}
