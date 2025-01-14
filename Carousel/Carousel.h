#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <iterator>
#include <stdexcept>

/**
 * @class Carousel
 * @brief A template class that iterates over iterable objects in circular fashion.
 * @tparam Iterable The type of the iterable container (e.g., std::vector, std::list).
 */
template <typename Iterable>
class Carousel {
private:
    typename Iterable::iterator beginIter;  ///< The beginning iterator of the iterable.
    typename Iterable::iterator endIter;    ///< The ending iterator of the iterable.
    typename Iterable::iterator currentIter; ///< The current iterator.

public:
    /**
     * @brief Constructor that initializes the carousel with an iterable object.
     * @param iterable The iterable object (e.g., vector, list, deque, etc.).
     * @throws std::invalid_argument if the iterable is empty.
     */
    Carousel(Iterable& iterable);

    /**
     * @brief Gets the current element in the carousel.
     * @return The current element in the carousel.
     */
    typename Iterable::value_type getCurrent() const;

    /**
     * @brief Moves the iterator to the previous element, wrapping around if needed.
     * @return The current element in the carousel after moving.
     */
    typename Iterable::value_type movePrev();

    /**
     * @brief Moves the iterator to the next element, wrapping around if needed.
     * @return The current element in the carousel after moving.
     */
    typename Iterable::value_type moveNext();
};

template <typename Iterable>
Carousel<Iterable>::Carousel(Iterable& iterable) {
    if (std::distance(iterable.begin(), iterable.end()) < 1) {
        throw std::invalid_argument("Cannot construct empty carousel.");
    }
    beginIter = iterable.begin();
    endIter = iterable.end();
    currentIter = beginIter;
}

template <typename Iterable>
typename Iterable::value_type Carousel<Iterable>::getCurrent() const {
    return *currentIter;
}

template <typename Iterable>
typename Iterable::value_type Carousel<Iterable>::movePrev() {
    if (currentIter == beginIter) currentIter = std::prev(endIter);
    else currentIter--;
    return *currentIter;
}

template <typename Iterable>
typename Iterable::value_type Carousel<Iterable>::moveNext() {
    if (std::next(currentIter) == endIter) currentIter = beginIter;
    else currentIter++;
    return *currentIter;
}

#endif // CAROUSEL_H
