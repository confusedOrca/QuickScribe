#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Carousel.h"

using namespace std;

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

void checkResult(bool condition, const string& result, const string& expected) {
    if (condition) cout << GREEN << result << " Expected: " << expected << RESET << endl;
    else cerr << RED << "Test failed: " << result << " Expected: " << expected << RESET << endl;
}

void testCarousel() {
    cout << "Test 1: Carousel with vector" << endl;

    vector<int> vec = {1, 2, 3, 4};
    Carousel<vector<int>> carousel(vec);

    checkResult(
        carousel.getCurrent() == 1, 
        "Current element: " + to_string(carousel.getCurrent()), 
        "1");

    carousel.moveNext();
    checkResult(
        carousel.getCurrent() == 2, 
        "Current element after moveNext: " + to_string(carousel.getCurrent()), 
        "2");

    carousel.movePrev();
    checkResult(
        carousel.getCurrent() == 1, 
        "Current element after movePrev: " + to_string(carousel.getCurrent()), 
        "1");

    carousel.moveNext();
    carousel.moveNext();
    carousel.moveNext();
    carousel.moveNext();
    checkResult(
        carousel.getCurrent() == 1, 
        "Current element after circular moveNext: " + to_string(carousel.getCurrent()), 
        "1");

    carousel.movePrev();
    checkResult(
        carousel.getCurrent() == 4, 
        "Current element after circular movePrev: " + to_string(carousel.getCurrent()), 
        "4");

    cout << "----------------------------" << endl;
}

void testEmptyIterable() {
    cout << "Test 2: Empty iterable" << endl;

    try {
        vector<int> emptyVec;
        Carousel<vector<int>> carousel(emptyVec);
        cout << RED << "Test failed: No exception thrown for empty iterable" << RESET << endl;
    } catch (const std::invalid_argument& e) {
        checkResult(true, "Exception caught: " + string(e.what()), "Iterable cannot be empty");
    }

    cout << "----------------------------" << endl;
}

int main() {
    testCarousel();
    testEmptyIterable();
    return 0;
}
