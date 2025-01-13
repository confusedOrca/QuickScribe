#include <iostream>
#include <stdexcept>
#include "Recommendations.h"
using namespace std;

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

void checkResult(bool condition, const string& result, const string& expected) {
    if (condition) cout << GREEN << result << " Expected: " << expected << RESET << endl;
    else cerr << RED << "Test failed: " << result << " Expected: " << expected << RESET << endl;
}

string formatRecommendations(const vector<string>& recommendations) {
    string result = "";
    for (const auto& word : recommendations) {
        result += word + " ";
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

void testCreateRecommendations() {
    cout << "Test 1: Create Recommendations" << endl;

    try {
        Recommendations rec(5);
        checkResult(true, "Recommendations created successfully.", "");
    } catch (const exception& e) {
        checkResult(false, string("Error: ") + e.what(), "");
    }

    try {
        Recommendations rec(0);
    } catch (const std::invalid_argument& e) {
        checkResult(true, "Error: " + string(e.what()), "maxSize must be greater than 0.");
    }

    cout << "----------------------------" << endl;
}

void testAddWord() {
    Recommendations rec(3);
    cout << "Test 2: Add Words to Recommendations" << endl;
    
    rec.addWord("apple", 5);
    rec.addWord("banana", 3);
    rec.addWord("cherry", 7);

    checkResult(
        formatRecommendations(rec.getRecommendations()) == "cherry apple banana",
        "Recommendations after adding 3 words: " + formatRecommendations(rec.getRecommendations()),
        "cherry apple banana"
    );

    try {
        rec.addWord("banana", 6);
    } catch (const std::invalid_argument& e) {
        checkResult(true, "Error: " + string(e.what()), "Word already exists.");
    }

    try {
        rec.addWord("date", -1);
    } catch (const std::invalid_argument& e) {
        checkResult(true, "Error: " + string(e.what()), "Frequency must be greater than 0.");
    }

    rec.addWord("date", 6);

    checkResult(
        formatRecommendations(rec.getRecommendations()) == "cherry date apple",
        "Recommendations after adding 'date': " + formatRecommendations(rec.getRecommendations()),
        "cherry date apple"
    );

    cout << "----------------------------" << endl;
}

void testRecommendationSize() {
    Recommendations rec(2);

    cout << "Test 3: Maintain Recommendations List Size" << endl;

    rec.addWord("apple", 5);
    rec.addWord("banana", 3);
    rec.addWord("cherry", 7);

    checkResult(
        formatRecommendations(rec.getRecommendations()) == "cherry apple",
        "Recommendations after adding 3 words with max size 2: " + formatRecommendations(rec.getRecommendations()),
        "cherry apple"
    );

    cout << "----------------------------" << endl;
}

int main() {
    testCreateRecommendations();
    testAddWord();
    testRecommendationSize();
    return 0;
}
