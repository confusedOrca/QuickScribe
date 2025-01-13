#include <iostream>
#include <stdexcept>
#include "./Node.h"
using namespace std;

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

void checkResult(bool condition, const string& result, const string& expected) {
    if (condition) cout << GREEN << result << " Expected: " << expected << RESET << endl;
    else cerr << RED << "Test failed: " << result << " Expected: " << expected << RESET << endl;
}

void testCreateNode() {
    cout << "Test 1: Create Node" << endl;

    Node* A = new Node('a');
    A->wordFrequency++;

    checkResult(
        A->character == 'a', 
        "Node 1: Character: " + string(1, A->character),
        "a"
    );

    checkResult(
        A->isWordEnd(), 
        "Node 1: Is word end? " + string(A->isWordEnd()? "True" : "False"),
        "True"
    );

    Node* nodeEmpty = new Node();
    bool nodeEmptyIsWordEnd = nodeEmpty->isWordEnd();
    
    checkResult(
        nodeEmpty->character == '\0', 
        "Node 2: Character: " + string(1, nodeEmpty->character),
        "\0"
    );

    checkResult(
        !nodeEmpty->isWordEnd(), 
        "Node 2: Is word end? " + string(nodeEmpty->isWordEnd() ? "True" : "False"),
        "False"
    );

    cout << "----------------------------" << endl;
}

void testAddChildren() {
    Node* R = new Node();
    Node* A = R->addNextChar('a');
    Node* B = R->addNextChar('b');
    Node* C = B->addNextChar('c');
    Node* D = B->addNextChar('d');

    cout << "Test 2: Add Children to Root and NodeB" << endl;

    checkResult(
        R->children.size() == 2 && R->children.count('a') && R->children.count('b'),
        "Root children: a b",
        "a b"
    );

    checkResult(
        B->children.size() == 2 && B->children.count('c') && B->children.count('d'),
        "Node 'b' children: c d",
        "c d"
    );

    cout << "----------------------------" << endl;
}

int main() {
    testCreateNode();
    testCreateNode();
    return 0;
}
