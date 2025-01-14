#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdio>
#include <sstream>
#include "TreeSerializer.h"

using namespace std;

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

void checkResult(bool condition, const string& result, const string& expected) {
    if (condition) cout << GREEN << result << " Expected: " << expected << RESET << endl;
    else cerr << RED << "Test failed: " << result << " Expected: " << expected << RESET << endl;
}

void dfs(Node* node, string& treeString) {
    if (!node) return;
    for (const auto& child : node->children) {
        char childChar = child.first;
        int wordFreq = child.second->wordFrequency;
        treeString += childChar + string("(") + to_string(wordFreq) + string(") ") ;

        dfs(child.second, treeString);
    }
}

void testLargeTree() {
    cout << "Test: Large Tree Serialization and Deserialization with DFS" << endl;

    Node* root = new Node();
    root->addNextChar('a')->wordFrequency = 10;
    root->addNextChar('b')->wordFrequency = 20;

    Node* nodeA = root->children['a'];
    nodeA->addNextChar('d')->wordFrequency = 30;
    nodeA->addNextChar('e')->wordFrequency = 40;

    Node* nodeB = root->children['b'];
    nodeB->addNextChar('f')->wordFrequency = 50;
    nodeB->addNextChar('g')->wordFrequency = 60;

    nodeA->children['d']->addNextChar('h')->wordFrequency = 70;
    nodeA->children['e']->addNextChar('i')->wordFrequency = 80;

    const string filePath = "../Data/tree.bin";

    try {
        TreeSerializer::serialize(root, filePath);

        Node* deserializedRoot = TreeSerializer::deserialize(filePath);

        string treeString = "";
        dfs(deserializedRoot, treeString);

        string expected = "a(10) d(30) h(70) e(40) i(80) b(20) f(50) g(60) ";

        checkResult(treeString == expected, "Tree string: " + treeString, expected);
    } catch (const exception& e) {
        cerr << RED << "Exception occurred: " << e.what() << RESET << endl;
    }

    remove(filePath.c_str());
    cout << "----------------------------" << endl;
}

int main() {
    testLargeTree();
    return 0;
}
