#ifndef RECOMMENDATIONS_H
#define RECOMMENDATIONS_H

#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

/**
 * @class Recommendations
 * @brief Maintains a dynamic list of the most frequent words upto maxSize.
 */
class Recommendations {
private:
    /**
     * @struct Recommendation
     * @brief Represents a single word recommendation along with its frequency.
     * overridden operators ensures comparison is based on 
     */
    struct Recommendation {
        std::string word;
        int frequency;

        bool operator<(const Recommendation& other) const {
            return frequency < other.frequency;
        }

        bool operator>(const Recommendation& other) const {
            return frequency > other.frequency; 
        }

        bool operator==(const Recommendation& other) const {
            return frequency == other.frequency;
        }
    };

    std::unordered_set<std::string> wordSet;  ///< Tracks words already added to recommendations.
    std::priority_queue<Recommendation, std::vector<Recommendation>, std::greater<Recommendation>> recommendations;///< Min heap: stores recommendations in sorted order.
    int maxSize;  ///< Maximum allowed size of the recommendations list.

public:
    /**
     * @brief Constructor to initialize the Recommendations object.
     * @param maxSize The maximum size of the recommendations.
     * @throws invalid_argument if `maxSize` is less than or equal to 0.
     */
    Recommendations(int maxSize);

    /**
     * @brief Adds new words to the recommendations list, maintaining the order of frequency.
     * If frequency <  min frequency (root frequency): returns
     * Else inserts new word into recommendations heap.
     * If size > maxSize removes minimum frequency element by popping root.
     * @param word The word to be added to the recommendations list.
     * @param frequency The frequency of the word to be added.
     * @throws std::invalid_argument if the word already exists or if frequency <= 0.
     */
    void addWord(std::string word, int frequency);

    /**
     * @brief Retrieves recommendations words in descending order of frequency.
     * Inserts words from last idx to start by repeatedly popping the root.
     * @return A vector of strings representing the recommended words.
     */
    std::vector<std::string> getRecommendations();
};

#endif // RECOMMENDATIONS_H
