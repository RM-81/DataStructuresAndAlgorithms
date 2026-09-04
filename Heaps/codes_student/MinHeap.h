#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <climits>

#define MAX_CAPACITY 1000  // Defines the maximum capacity of the heap

class MinHeap
{
private:
    int heap[MAX_CAPACITY];  // Array to store heap elements
    int size;                // Current number of elements in the heap

    /**
     * Sifts up the node at index i to maintain heap property.
     */
    void siftUp(int i)
    {
        /**Write your code here**/
    }

    /**
     * Sifts down the node at index i to maintain heap property.
     */
    void siftDown(int i)
    {
        /**Write your code here**/
    }

public:
    // Constructor initializes an empty heap
    MinHeap() : size(0) {}

    /**
     * Inserts a new element x into the heap.
     */
    void insert(int x)
    {
        /**Write your code here**/
    }

    /**
     * Returns the minimum element without removing it.
     */
    int findMin()
    {
        /**Write your code here**/
    }

    /**
     * Removes and returns the minimum element from the heap.
     */
    int extractMin()
    {

        /**Write your code here**/
    }

    /**
     * Returns the number of elements in the heap.
     */
    int getSize()
    {
        /**Write your code here**/
    }

    /**
     * Checks if the heap is empty.
     * Returns true if empty, false otherwise.
     */
    bool isEmpty()
    {
        /**Write your code here**/
    }

    /**
     * Decreases the value of the element at index i to newValue.
     */
    void decreaseKey(int i, int newValue)
    {
        /**Write your code here**/
    }

    /**
     * Deletes the element at index i.
     */
    void deleteKey(int i)
    {
        /**Write your code here**/
    }

    /**
     * Prints the heap's content to the output file.
     * Format: "elem1 elem2 elem3 ..." (space-separated)
     */
    void printHeap(std::ofstream &outfile)
    {
        /**Write your code here**/
    }

    /**
     * Checks whether the Min Heap property is preserved.
     * Returns true if valid, false otherwise.
     */
    bool isValidMinHeap()
    {
        /**Write your code here**/
    }

    /**
     * Builds a heap from an unsorted array using bottom-up heapify.
     */
    void heapify(int arr[], int n)
    {
        /**Write your code here**/
    }

    /**
     * Returns all elements in sorted (ascending) order.
     * The original heap should remain UNCHANGED after this operation.
     */
    void heapSort(std::ofstream &outfile)
    {
        /**Write your code here**/
    }

    /**
     * Replaces the minimum element with a new value x in a single operation.
     * Returns the old minimum value.
     */
    int replaceMin(int x)
    {
        /**Write your code here**/
    }
};

#endif // MINHEAP_H
