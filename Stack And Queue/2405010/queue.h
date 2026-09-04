#pragma once
#include <string>
using namespace std;

/**
 * Queue - Abstract Data Type (ADT) that follows the First-In-First-Out (FIFO) principle
 * This interface defines the operations that any queue implementation must support
 */
class Queue
{
public:
    /**
     * Enqueues an element at the back of the queue
     * @param value The element to enqueue
     */
    virtual void enqueue(int value) = 0;

    /**
     * Removes and returns the element at the front of the queue
     * @return The element at the front of the queue
     */
    virtual int dequeue() = 0;

    /**
     * Clears all elements from the queue
     */
    virtual void clear() = 0;

    /**
     * Returns the element at the front of the queue without removing it
     * @return The element at the front of the queue
     */
    virtual int front() const = 0;

    /**
     * Returns the element at the back of the queue without removing it
     * @return The element at the back of the queue
     */
    virtual int back() const = 0;

    /**
     * Checks if the queue is empty
     * @return true if the queue is empty, false otherwise
     */
    virtual bool empty() const = 0;

    /**
     * Returns the current number of elements in the queue
     * @return The number of elements in the queue
     */
    virtual int size() const = 0;

    /**
     * Prints the elements in the queue from front to back
     */
    virtual string toString() const = 0;

    /**
     * Virtual destructor
     */
    virtual ~Queue() = default;
};

/**
 * ArrayQueue - Implementation of Queue ADT using a dynamic array
 * Provides efficient queue operations with automatic resizing when needed
 */
class ArrayQueue : public Queue
{
private:
    int *data;     // Pointer to dynamically allocated array
    int capacity;  // Maximum number of elements the array can currently hold
    int front_idx; // Index of the front element
    int rear_idx;  // Index of the rear element

public:
    /**
     * Constructor
     * @param capacity Initial capacity of the queue (default: 2)
     */
    ArrayQueue(int capacity = 2);

    /**
     * Destructor - Cleans up any dynamically allocated memory
     */
    ~ArrayQueue();

    // Queue interface implementation
    void enqueue(int value) override;
    int dequeue() override;
    void clear() override;
    int front() const override;
    int back() const override;
    bool empty() const override;
    int size() const override;
    string toString() const override;

    // Additional method to get the current capacity of the queue
    int getCapacity() const;

private:
    /**
     * Resizes the internal array when it becomes full or too empty
     * @param new_capacity The new capacity of the array
     */
    void resize(int new_capacity);
};

/**
 * ListQueue - Implementation of Queue ADT using a singly linked list
 * Provides efficient queue operations with dynamic memory allocation per element
 */
class ListQueue : public Queue
{
private:
    /**
     * Node - Structure representing a single element in the linked list
     */
    struct Node
    {
        int data;   // Value stored in this node
        Node *next; // Pointer to the next node in the list

        /**
         * Node constructor
         * @param value The value to store in this node
         * @param next_node Pointer to the next node (default: nullptr)
         */
        Node(int value, Node *next_node = nullptr) : data(value), next(next_node) {}
    };

    Node *front_node; // Pointer to the front node of the queue
    Node *rear_node;  // Pointer to the rear node of the queue
    int current_size; // Number of elements currently in the queue

public:
    /**
     * Constructor - Creates an empty queue
     */
    ListQueue();

    /**
     * Destructor - Cleans up any dynamically allocated memory
     */
    ~ListQueue();

    // Queue interface implementation
    void enqueue(int value) override;
    int dequeue() override;
    void clear() override;
    int front() const override;
    int back() const override;
    bool empty() const override;
    int size() const override;
    string toString() const override;
};
