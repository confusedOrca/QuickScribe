# QuickScribe

Local autocomplete program that tracks typing history in a prefix tree and provides autocomplete suggestions.

## Key Components

### 1. Recommender
- A Prefix tree where each node has a character value, frequency value, and a hash map of pointers to child nodes.
- `frequency > 0` indicates it is a word end node.
- Uses a multithreaded DFS to collect all words for a given prefix.
- Uses the `Recommendation` object to keep track of the most frequent words.

### 2. Recommendations
- A min-heap of the top `N` most frequently used words for a given prefix.
  - Priority is based on the frequency of words.
  - 0 <= `N` <= max size
- Min Heap is used instead of Max Heap since we must keep track of the least frequent word in our heap to decide whether to include an incoming word.
- During retrieval, it builds a list of strings from end to beginning by continuously popping the root of the heap to get a list of `n` most frequent words in descending order of their frequency.

### 3. Serializer
- Saves the Recommender tree by serializing all its nodes.

### 4. Carousel
- A generic wrapper around linear iterable objects to index elements of them in circular order.

### 5. QuickScribe
- Combines a `Recommender,` `Serializer,` and a `String Carousel.`
- Abstracts away all details.
- Provides functions to:
  - Save or load a tree.
  - Fetch recommendations.
  - Get recommendations.
  - Insert new words into the tree.

### 6. QuickScribe Program
- A keylogger is used to track words being typed.
- A typing simulator is used to type programmatically.
- Uses QuickScribe to fetch recommendations for prefixes.
- Fetches and cycles through through suggestions when `INSERT` is pressed.
- Replaces prefixes with word suggestions by simulating typing.
