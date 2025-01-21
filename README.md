# QuickScribe

A local autocomplete program that uses users' typing history to generate prefix trees and suggests words based on frequency.

## Key Components

### 1. Recommender
- A Prefix tree where each node has a character value, frequency value, and a hash map of pointers to child nodes.
- `frequency > 0` indicates it is a word end node.
- Uses DFS to collect all words for a given prefix.
- Uses the `Recommendation` object to keep track of the most frequent words.

### 2. Recommendations
- A min heap of most frequently used words for a given prefix. 
  - Priority is based on the frequency of words.
- Tracks its size to ensure only the top `N` most frequent words are returned while not exceeding the max size.
- Min Heap is used instead of Max Heap since we need to keep track of the least frequent word in our heap to decide if to include an incoming word or not.
- During retrieval, it builds a list of strings from end to beginning by continuously popping the root of the heap to get a list of `n` most frequent words in descending order of their frequency.

### 3. Serializer
- Saves the Recommender tree by serializing all its nodes.

### 4. Carousel
- A generic wrapper around linear iterable objects to index elements of them in circular order.

### 5. QuickScribe
- Combines a `Recommender`, `Serializer`, and a `String Carousel`.
- Abstracts away all details.
- Provides functions to:
  - Save or load a tree.
  - Fetch recommendations.
  - Get recommendations.
  - Insert new words into the tree.

### 6. QuickScribe Program
- Uses a keylogger to track words being typed.
- Uses a typing simulator to programmatically type.
- Uses QuickScribe to fetch recommendations for current prefixes and cycle through them when `INSERT` is pressed.
- Replaces prefixes with word suggestions by simulating typing.
