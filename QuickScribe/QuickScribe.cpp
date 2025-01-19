#include "QuickScribe.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <iostream>

QuickScribe::QuickScribe(std::string filePath, int recommendationSize) 
    : filePath(filePath), recommendationSize(recommendationSize) {
    std::cout << "Initializing QuickScribe with file path: " << filePath << std::endl;
    
    std::ifstream file(filePath);
    if (!file) {
        std::cout << "File not found! Creating one." << std::endl;
        if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".bin") {
            std::cout << "File will be saved as a .bin file." << std::endl;
            save(); // Ensure the save function works
        } else {
            std::cout << "Invalid file path: " << filePath << " (must end with .bin)" << std::endl;
            throw std::invalid_argument("Invalid file path: Must end with .bin if creating a new file.");
        }
    } else {
        std::cout << "Reading from file: " << filePath << "'" << std::endl;
        try {
            Node* root = serializer.deserialize(filePath);
            std::cout << "Deserialization successful." << std::endl;
            recommender.setTrieRoot(root);
        } catch (const std::exception& e) {
            std::cout << "Error during deserialization: " << e.what() << std::endl;
            throw;
        }
    }
}

QuickScribe::~QuickScribe() {}

void QuickScribe::save() {
    if (!recommender.getTrieRoot()) throw std::runtime_error("Cannot save: Trie root is null.");
    serializer.serialize(recommender.getTrieRoot(), filePath);
}

void QuickScribe::insertWord(const std::string& word) {
    recommender.insert(word);
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
    std::vector<std::string> recommendations = recommender.recommend(prefix, recommendationSize);
    carousel = StringCarousel(recommendations);
    return carousel.moveNext();
}



std::string QuickScribe::currentRecommendation() {
    return carousel.getCurrent();
}

std::string QuickScribe::nextReccomendation() {
    return carousel.moveNext();
}

std::string QuickScribe::previousRecommendation() {
    return carousel.movePrev();
}

