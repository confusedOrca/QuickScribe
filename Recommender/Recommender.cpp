#include <thread>
#include <mutex>
#include <future>
#include "Recommender.h"
#include "./Node/Node.h"
#include "./Recommendations/Recommendations.h"

Recommender::Recommender() {
    trieRoot = new Node();
}

void Recommender::collectWords(Node* node, const std::string& prefix, Recommendations& recommendations) {
    std::vector<std::future<void>> futures;
    std::mutex mtx;


    if (node->wordFrequency > 0) {
            std::lock_guard<std::mutex> lock(mtx);
            recommendations.addWord(prefix, node->wordFrequency);
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

std::vector<std::string> Recommender::recommend(const std::string& prefix, int n) {
    Node* curr = trieRoot;
    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end()) return {};
        curr = curr->children[c];
    }

    Recommendations recommendations(n + 1);
    recommendations.addWord(prefix, INFINITY_INT);
    collectWords(curr, prefix, recommendations);
    return recommendations.getRecommendations();
}

void Recommender::collectWords(Node* node, const std::string& prefix, Recommendations& recommendations) {
    if (node->wordFrequency > 0) recommendations.addWord(prefix, node->wordFrequency);

    for (auto& [character, nextNode] : node->children) {
        collectWords(nextNode, prefix + character, recommendations);
    }
}
