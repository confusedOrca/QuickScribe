#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Recommender.h"

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
    if (!result.empty()) result.pop_back();
    return result;
}

void testInsertAndRecommend() {
    Recommender recommender;

    recommender.insertNTimes("apple", 5);
    recommender.insertNTimes("banana", 4);
    recommender.insertNTimes("applause", 3);
    
    cout << "Test 1: Insert and Recommend" << endl;

    vector<string> result = recommender.recommend("app", 2);
    checkResult(
        formatRecommendations(result) == "app apple applause",
        "Recommendations for 'app': " + formatRecommendations(result),
        "app apple applause"
    );

    result = recommender.recommend("ban", 5);
    checkResult(
        formatRecommendations(result) == "ban banana",
        "Recommendations for 'ban': " + formatRecommendations(result),
        "ban banana"
    );

    result = recommender.recommend("cherry", 2);
    checkResult(
        formatRecommendations(result) == "cherry",
        "Recommendations for 'cherry' : " + formatRecommendations(result),
        "cherry"
    );

    cout << "----------------------------" << endl;
}

void testRecommendationLimit() {
    Recommender recommender;

    recommender.insertNTimes("apple", 10);
    recommender.insertNTimes("banana", 9);
    recommender.insertNTimes("applause", 8);
    recommender.insertNTimes("orange", 7);
    recommender.insertNTimes("grape", 6);
    recommender.insertNTimes("bear", 11);
    
    cout << "Test 2: Recommendations Limit" << endl;

    vector<string> result = recommender.recommend("a", 3);
    checkResult(
        formatRecommendations(result) == "a apple applause",
        "Recommendations for 'a' with limit 3: " + formatRecommendations(result),
        "a apple applause"
    );

    result = recommender.recommend("b", 1);
    checkResult(
        formatRecommendations(result) == "b bear",
        "Recommendations for 'b' with limit 1: " + formatRecommendations(result),
        "b bear"
    );

    cout << "----------------------------" << endl;
}

int main() {
    testInsertAndRecommend();
    testRecommendationLimit();
    return 0;
}
