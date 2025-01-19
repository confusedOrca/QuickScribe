#ifndef STRINGCAROUSEL_H
#define STRINGCAROUSEL_H

#include <vector>
#include <string>
#include "../../Carousel/Carousel.h"

/**
 * @class StringCarousel
 * @brief A derived class from Carousel specialized for std::vector<std::string>.
 */
class StringCarousel : public Carousel<std::vector<std::string>> {
public:
    /**
     * @brief Constructor that initializes the StringCarousel with a vector of strings.
     * @param strings A vector of strings to initialize the carousel.
     * @throws std::invalid_argument if the vector is empty.
     */
    explicit StringCarousel(std::vector<std::string>& strings)
        : Carousel<std::vector<std::string>>(strings) {}

    /**
     * @brief Default constructor that initializes the StringCarousel with an empty vector.
     */
    StringCarousel() 
        : Carousel<std::vector<std::string>>(std::vector<std::string>{""}) {}
};

#endif // STRINGCAROUSEL_H
