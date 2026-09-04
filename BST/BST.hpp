#ifndef BST_H
#define BST_H

#include <iostream>

/**
 * Abstract Binary Search Tree
 * Template class for generic key-value pairs
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class BST {
public:
    // Default constructor
    BST() = default;
    
    // Virtual destructor for proper cleanup of derived classes
    virtual ~BST() = default;

    /**
     * Insert a key-value pair into the BST
     * @param key - Key to insert
     * @param value - Value to associate with the key
     * @return true if insertion was successful, false if key already exists
     */
    virtual bool insert(Key key, Value value) = 0;

    /**
     * Remove a key-value pair from the BST
     * @param key - Key to remove
     * @return true if removal was successful, false if key not found
     */
    virtual bool remove(Key key) = 0;

    /**
     * Find a value associated with a given key
     * @param key - Key to search for
     * @return true if key is found, false otherwise
     */
    virtual bool find(Key key) const = 0;

    /**
     * Get the value associated with a given key
     * @param key - Key to search for
     * @return Value associated with the key
     * @throws std::runtime_error if key is not found
     */
    virtual Value get(Key key) const = 0;

    /**
     * Update the value associated with a given key
     * @param key - Key to update
     * @param value - New value to associate with the key
     * @throws std::runtime_error if key is not found
     */
    virtual void update(Key key, Value value) = 0;

    /**
     * Clear all elements from the BST
     */
    virtual void clear() = 0;

    /**
     * Get the number of keys in the BST
     * @return Size of the BST
     */
    virtual size_t size() const = 0;

    /**
     * Check if the BST is empty
     * @return true if empty, false otherwise
     */
    virtual bool empty() const = 0;

    /**
     * Find the minimum key in the BST
     * @return The minimum key
     * @throws std::runtime_error if BST is empty
     */
    virtual Key find_min() const = 0;

    /**
     * Find the maximum key in the BST
     * @return The maximum key
     * @throws std::runtime_error if BST is empty
     */
    virtual Key find_max() const = 0;

    /**
     * Print the BST using specified traversal method
     * @param traversal_type - Character indicating traversal type:
     *                        'D' or 'd' = Default (nested parentheses) 
     *                        'I' or 'i' = In-order 
     *                        'P' or 'p' = Pre-order
     *                        'O' or 'o' = Post-order
     * @throws std::invalid_argument if traversal_type is invalid
     */
    virtual void print(char traversal_type = 'D') const = 0;

};

#endif // BST_H