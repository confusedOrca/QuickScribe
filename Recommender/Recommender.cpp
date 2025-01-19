#include <thread>
#include <mutex>
#include <future>
#include "Recommender.h"
#include "./Node/Node.h"
#include "./Recommendations/Recommendations.h"

Recommender::Recommender() {
    trieRoot = new Node();
}

Recommender::~Recommender() {
    destroyTree(trieRoot);
}

void Recommender::destroyTree(Node* node) {
    if (node == nullptr) return;
    for (auto& [character, nextNode] : node->children) {
        destroyTree(nextNode);
    }
    delete node;
}

void Recommender::setTrieRoot(Node* root) {
    if (trieRoot != nullptr) destroyTree(trieRoot);
    trieRoot = root;
}

Node* Recommender::getTrieRoot() {
    return trieRoot;
}

void Recommender::insert(const std::string& word) {
    Node* curr = trieRoot;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new Node();
        }
        curr = curr->children[c];
    }
    curr->wordFrequency++;
}

void Recommender::insertNTimes(const std::string& word, int N) {
    Node* curr = trieRoot;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end()) {
            curr->children[c] = new Node();
        }
        curr = curr->children[c];
    }
    curr->wordFrequency += N;
}

std::vector<std::string> Recommender::recommend(const std::string& prefix, int n) {
    Node* curr = trieRoot;
    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) return {prefix};
        curr = curr->children[c];
    }

    Recommendations recommendations(n + 1);
    recommendations.addWord(prefix, INFINITY_INT);
    collectWords(curr, prefix, recommendations);
    return recommendations.getRecommendations();
}

void Recommender::collectWords(Node* node, const std::string& prefix, Recommendations& recommendations) {
    std::vector<std::future<void>> futures;
    std::mutex mtx;


    if (node->wordFrequency > 0) {
        std::lock_guard<std::mutex> lock(mtx);
        try {
            recommendations.addWord(prefix, node->wordFrequency);
        } catch (const std::invalid_argument& e) {
            if (std::string(e.what()) == "Word already exists.") {
                //do nothing
            } else {
                throw;
            }
        }
    }


    for (auto& [character, nextNode] : node->children) {
        std::string newPrefix = prefix + character;
        futures.push_back(
            std::async(std::launch::async, [this, nextNode, newPrefix, &recommendations, &mtx]() {
            collectWords(nextNode, newPrefix, recommendations);
        }));
    }

    for (auto& future : futures) {
        future.get();
    }
}