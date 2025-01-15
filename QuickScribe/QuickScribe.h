#ifndef QUICKSCRIBE_H
#define QUICKSCRIBE_H

#include <string>
#include <vector>
#include "./StringCarousel/StringCarousel.h"
#include "../Serializer/TreeSerializer.h"
#include "../Recommender/Recommender.h"

/**
 * @class QuickScribe
 * @brief Provides functionality to manage word recommendations, serialization, and navigation of suggestions.
 * QuickScribe integrates the functionality of a trie-based recommender, a string carousel for recommendations,
 * and tree serialization/deserialization for persistence.
 */
class QuickScribe {
private:
    int recommendationSize;  ///< The maximum number of recommendations to fetch.
    std::vector<std::string> emptyStringRecommendations; ///< Cached recommendations for empty string
    StringCarousel* carousel; ///< Carousel to manage and navigate recommendations.
    TreeSerializer* serializer; ///< Serializer for saving and loading the recommendation trie.
    Recommender* recommender; ///< Recommender system for generating word suggestions.
    std::string filePath; ///< Path to the file used for saving the recommendation trie.

public:
    /**
     * @brief Constructs a QuickScribe object with the given file path and recommendation size.
     * If the file does not exist, the constructor checks if the file path ends with `.bin`.
     * If it does, a new recommendation trie is created and saved to that path. Otherwise,
     * an exception is thrown indicating an invalid path.
     * @param filePath Path to the file for loading or saving the serialized trie.
     * @param recommendationSize Maximum number of recommendations to fetch per query.
     * @throws std::invalid_argument if the file path is invalid.
     */
    QuickScribe(std::string filePath, int recommendationSize);

    /**
     * @brief Destructor for cleaning up allocated resources.
     */
    ~QuickScribe();

    /**
     * @brief Saves the current state of the recommendation trie to a file.
     */
    void save();

    /**
     * @brief Inserts a single word into the recommendation trie.
     * @param word The word to insert.
     */
    void insertWord(const std::string& word);

    /**
     * @brief Inserts a sentence into the recommendation trie by splitting it into individual words.
     * @param sentence The sentence to insert.
     */
    void insertSentence(const std::string& sentence);

    /**
     * @brief Fetches recommendations based on a given prefix.
     * @param prefix The prefix to search for.
     * @return The second string in carousel
     * Note: First string is always the prefix itself.
     */
    std::string fetchRecommendations(const std::string& prefix);

    /**
     * @brief Retrieves the current recommendation in the carousel.
     * @return The current recommendation as a string.
     */
    std::string currentRecommendation();

    /**
     * @brief Retrieves the next recommendation in the carousel.
     * @return The next recommendation as a string.
     */
    std::string nextReccomendation();

    /**
     * @brief Retrieves the previous recommendation in the carousel.
     * @return The previous recommendation as a string.
     */
    std::string previousRecommendation();
};

#endif // QUICKSCRIBE_H
