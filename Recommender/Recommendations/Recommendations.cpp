#include "Recommendations.h"
#include <stdexcept>
#include <iostream>

Recommendations::Recommendations(int maxSize) : maxSize(maxSize) {
    if (maxSize <= 0) throw std::invalid_argument("maxSize must be greater than 0.");
}

void Recommendations::addWord(std::string word, int frequency) {
    if (wordSet.count(word)) throw std::invalid_argument("Word already exists.");

    if (frequency <= 0) throw std::invalid_argument("Frequency must be greater than 0.");

    if (recommendations.size() == maxSize && frequency < recommendations.top().frequency) return;
    
    Recommendation newRec{word, frequency};
    recommendations.push(newRec);
    wordSet.insert(word);

    if (recommendations.size() > maxSize) {
        Recommendation minRec = recommendations.top();
        recommendations.pop();
        wordSet.erase(minRec.word);
    }
}


std::vector<std::string> Recommendations::getRecommendations() {
    std::vector<std::string> result(recommendations.size());
    std::priority_queue<Recommendation, std::vector<Recommendation>, std::greater<Recommendation>> tempHeap = recommendations;
    for (int i = result.size() - 1; i >= 0; --i) {
        result[i] = tempHeap.top().word; 
        tempHeap.pop();
    }

    return result;
}


