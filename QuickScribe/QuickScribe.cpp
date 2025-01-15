#include "QuickScribe.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

QuickScribe::QuickScribe(std::string filePath, int recommendationSize): 
    filePath(std::move(filePath)), 
    recommendationSize(recommendationSize), 
    carousel(nullptr), 
    serializer(new TreeSerializer()), 
    recommender(new Recommender()) {
    std::ifstream file(this->filePath);
    if (!file) {
        if (this->filePath.size() >= 4 && this->filePath.substr(this->filePath.size() - 4) == ".bin") save();
        else throw std::invalid_argument("Invalid file path: Must end with .bin if creating a new file.");
    } else {
        Node* root = serializer->deserialize(this->filePath);
        recommender->setTrieRoot(root);
    }
}

QuickScribe::~QuickScribe() {
    delete carousel;
    delete serializer;
    delete recommender;
}

void QuickScribe::save() {
    if (!recommender || !recommender->getTrieRoot()) {
        throw std::runtime_error("Cannot save: Trie root is null.");
    }
    serializer->serialize(recommender->getTrieRoot(), filePath);
}

void QuickScribe::insertWord(const std::string& word) {
    recommender->insert(word);
}

void QuickScribe::insertSentence(const std::string& sentence) {
    std::istringstream stream(sentence);
    std::string word;
    while (stream >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        insertWord(word);
    }
}

std::string QuickScribe::fetchRecommendations(const std::string& prefix) {
    std::vector<std::string> recommendations = recommender->recommend(prefix, recommendationSize);

    if (carousel) delete carousel;
    carousel = new StringCarousel(recommendations);
    return carousel->moveNext();
}

std::string QuickScribe::currentRecommendation() {
    if (!carousel) return fetchRecommendations("");
    return carousel->getCurrent();
}

std::string QuickScribe::nextReccomendation() {
    if (!carousel) return fetchRecommendations("");
    return carousel->moveNext();
}

std::string QuickScribe::previousRecommendation() {
    if (!carousel) return fetchRecommendations("");
    return carousel->movePrev();
}
