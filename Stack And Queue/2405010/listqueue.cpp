#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    this->front_node=nullptr;
    // TODO: Initialize front_node and rear_node
    this->rear_node=nullptr;
    // TODO: Initialize current_size to 0
    this->current_size=0;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    this->clear();
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    Node *newnode=new Node(item);
    // TODO: Create a new node with the given item
    if(this->current_size==0)
    {
        this->front_node=newnode;
        this->rear_node=newnode;
    }
    else
    {
        this->rear_node->next=newnode;
        // TODO: Link the new node to the rear
        this->rear_node=newnode;
        // TODO: Update the rear_node
    }
    this->current_size++;
    return;
    // TODO: Increment the current size
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    if(this->front_node==nullptr)
    {
        cout<<"The queue is empty . Cannot dequeue."<<endl;
        return -1;
    }
    // TODO: Check if the queue is empty, display error message if it is
    int dequeued=this->front_node->data;
    // TODO: Store the data from the front node
    Node *temp=this->front_node;
    this->front_node=this->front_node->next;
    delete temp;
    // TODO: Update the front pointer to the next node
    this->current_size--;
    if(this->current_size==0)
    {
        this->rear_node=nullptr; //front node automatically becones nullptr
    }
    return dequeued;
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    Node *curr=this->front_node;
    // TODO: Traverse the linked list and delete each node
    while(curr!=nullptr)
    {
        Node *temp=curr;
        curr=curr->next;
        delete temp;
    }
    // TODO: Reset front and rear pointer
    this->front_node=nullptr;
    this->rear_node=nullptr;
    this->current_size=0;
    // TODO: Reset current_size to 0
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    return this->current_size;
    // TODO: Return the current size (current_size)
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    if(this->empty()==true)
    {
        cout<<"The queue is empty"<<endl;
        return -1;
    }
    return this->front_node->data;
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    if(this->empty()==true)
    {
        cout<<"The queue is empty"<<endl;
        return -1;
    }
    return this->rear_node->data;
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    if(this->front_node==nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
    // TODO: Return whether front is nullptr
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    string queue="";
    Node *curr=this->front_node;
    queue="<";
    while(curr!=nullptr)
    {
        if(curr!=this->rear_node)
        {
            queue+=to_string(curr->data);
            queue+=", ";
        }
        else
        {
            queue+=to_string(curr->data);
        }
        curr=curr->next;
    }
    queue+="|";
    return queue;
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
}
