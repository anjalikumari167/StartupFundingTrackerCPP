#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <string>
#include <vector>

// A Trie (prefix tree) used for name autocomplete.
//
// Each node is one letter. Walking down from the root spells a name:
//
//   root -> a -> l -> p -> h -> a   ("alpha")
//        -> b -> e -> t -> a        ("beta")
//
// Typing a prefix = walk down that path, then collect every name below it.
// Time: O(L) to insert / reach a prefix, where L = length of the word.
class Trie {
private:
    struct Node {
        std::map<char, Node*> children;   // std::map keeps letters sorted (a, b, c...)
        bool isEnd = false;               // does a full name end here?
        std::string displayName;          // the original name (with capitals)
    };

    Node* root;

    void destroy(Node* node);             // frees memory of a whole subtree
    void collect(const Node* node, std::vector<std::string>& out, size_t limit) const;

public:
    Trie();
    ~Trie();

    // A Trie owns raw pointers, so copying it would be dangerous. Forbid it.
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    void insert(const std::string& name);   // case-insensitive
    void clear();                           // remove everything
    std::vector<std::string> autocomplete(const std::string& prefix, size_t limit = 10) const;
};

#endif
