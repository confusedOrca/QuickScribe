#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "QuickScribe.h"
#include <filesystem>

using namespace std;

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

void checkResult(bool condition, const string& result, const string& expected) {
    if (condition) 
        cout << GREEN << "Passed: " << result << " Expected: " << expected << RESET << endl;
    else 
        cerr << RED << "Test failed: " << result << " Expected: " << expected << RESET << endl;
}

void testInsertAndFetch() {
    cout << "Test 1: Insert and Fetch Recommendations" << endl;

    try {
        QuickScribe quickScribe("test.bin", 2);
        cout << "QuickScribe instance created." << endl;

        quickScribe.insertSentence("apple banana cherry");
        quickScribe.insertSentence("add a banana to smoothie.");
        quickScribe.insertSentence("apple is amazing. Add it!!!");

        cout << "Fetching recommendations for 'a'" << endl;
        string result = quickScribe.fetchRecommendations("a");
        checkResult(
            result == "apple",
            "First recommendation for 'a': " + result,
            "apple"
        );

        result = quickScribe.nextReccomendation();
        checkResult(
            result == "add",
            "Next recommendation for 'a': " + result,
            "add"
        );

        result = quickScribe.nextReccomendation();
        checkResult(
            result == "a",
            "Next recommendation for 'a': " + result,
            "a"
        );

        result = quickScribe.previousRecommendation();
        checkResult(
            result == "add",
            "Previous recommendation for 'a': " + result,
            "add"
        );

        quickScribe.save();
        cout << "----------------------------" << endl;
    } catch (const std::exception& e) {
        cerr << RED << "Exception during QuickScribe construction or operation: " << e.what() << RESET << endl;
    }
}

void testPersistence() {
    cout << "Test 2: Persistence" << endl;

    try {
        QuickScribe quickScribe("test.bin", 2);
        cout << "QuickScribe instance created." << endl;

        string result = quickScribe.fetchRecommendations("a");
        checkResult(
            result == "apple",
            "First recommendation for 'a': " + result,
            "apple"
        );

        result = quickScribe.nextReccomendation(); 
        checkResult(
            result == "add",
            "Next recommendation for 'a': " + result,
            "add"
        );

        result = quickScribe.nextReccomendation(); 
        checkResult(
            result == "a",
            "Next recommendation for 'a': " + result,
            "a"
        );

        result = quickScribe.previousRecommendation();
        checkResult(
            result == "add",
            "Previous recommendation for 'a': " + result,
            "add"
        );

        quickScribe.save();

        cout << "----------------------------" << endl;
    } catch (const std::exception& e) {
        cerr << RED << "Exception during QuickScribe construction or operation: " << e.what() << RESET << endl;
    }
}

int main() {
    std::filesystem::remove("test.bin");
    testInsertAndFetch();
    testPersistence();
    std::filesystem::remove("test.bin"); 
    return 0;
}
