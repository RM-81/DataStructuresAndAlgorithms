#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() {
        // TODO: Implement destructor to free memory

    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        // TODO: Implement insertion logic

    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override {
        // TODO: Implement removal logic

    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override {
        // TODO: Implement find logic

    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override {
        // TODO: Implement get logic

    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override {
        // TODO: Implement update logic

    }

    /**
     * Clear all elements from the BST
     */
    void clear() override {
        // TODO: Implement clear logic

    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        // TODO: Implement size logic

    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        // TODO: Implement empty check logic

    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override {
        // TODO: Implement find_min logic

    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override {
        // TODO: Implement find_max logic

    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override {
        // TODO: Implement print logic
        
    }
    
};

#endif // LISTBST_H