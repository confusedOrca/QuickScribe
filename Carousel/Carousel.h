#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <iterator>
#include <stdexcept>

/**
 * @class Carousel
 * @brief A template class that iterates over iterable objects in circular fashion.
 * @tparam Iterable The type of the iterable container (e.g., std::vector, std::list, etc.).
 */
template <typename Iterable>
class Carousel {
private:
    Iterable data;  ///< The entire data container.
    typename Iterable::iterator beginIter;  ///< The beginning iterator of the iterable.
    typename Iterable::iterator endIter;    ///< The ending iterator of the iterable.
    typename Iterable::iterator currentIter; ///< The current iterator.

public:
    /**
     * @brief Constructor that initializes the carousel with an iterable object.
     * @param iterable The iterable object (e.g., vector, list, deque, etc.).
     * @throws std::invalid_argument if the iterable is empty.
     */
    explicit Carousel(Iterable iterable);

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
Carousel<Iterable>::Carousel(Iterable iterable) {
    if (iterable.empty()) {
        throw std::invalid_argument("Cannot construct empty carousel.");
    }
    data = iterable;
    beginIter = data.begin();
    endIter = data.end();
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
