#include "Trie.h"
#include "Utils.h"      // toLower()

using namespace std;

Trie::Trie() : root(new Node()) {}

Trie::~Trie() {
    destroy(root);
}

void Trie::destroy(Node* node) {
    for (auto& pair : node->children) {
        destroy(pair.second);
    }
    delete node;
}

void Trie::clear() {
    destroy(root);
    root = new Node();
}

void Trie::insert(const string& name) {
    Node* cur = root;
    for (char c : toLower(name)) {
        if (cur->children.find(c) == cur->children.end()) {
            cur->children[c] = new Node();      // create the path if missing
        }
        cur = cur->children[c];
    }
    cur->isEnd = true;
    cur->displayName = name;
}

// DFS: visit this node, then each child in alphabetical order.
void Trie::collect(const Node* node, vector<string>& out, size_t limit) const {
    if (out.size() >= limit) return;
    if (node->isEnd) out.push_back(node->displayName);
    for (const auto& pair : node->children) {
        collect(pair.second, out, limit);
    }
}

vector<string> Trie::autocomplete(const string& prefix, size_t limit) const {
    vector<string> results;

    // 1) Walk down the prefix letters.
    const Node* cur = root;
    for (char c : toLower(prefix)) {
        auto it = cur->children.find(c);
        if (it == cur->children.end()) return results;   // prefix not found
        cur = it->second;
    }

    // 2) Collect every name below that point.
    collect(cur, results, limit);
    return results;
}
