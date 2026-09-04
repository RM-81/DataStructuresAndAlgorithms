#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    this->capacity=initial_capacity;
    this->front_idx=0;
    this->rear_idx=0;    
    // TODO: Allocate memory for the array with the specified initial capacity
    this->data=new int [this->capacity];
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    delete[] this->data;
    this->data=nullptr;
    this->capacity=2;
    this->front_idx=0;
    this->rear_idx=0;    
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    if((this->rear_idx+1)%(this->capacity)==this->front_idx)
    {
        int new_cap=this->capacity*2;
        this->resize(new_cap);
    }
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    this->data[this->rear_idx]=item;
    this->rear_idx=(this->rear_idx+1)%this->capacity;
    // TODO: Add the new element to the rear of the queue
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    if(this->empty()==true)
    {
        cout<<"The Queue is Empty"<<endl;
        return -1;
    }
    // TODO: Decrement current_size and return the element at the front of the queue
    int dequeued=this->data[this->front_idx];
    // TODO: Update front index
    this->front_idx=(this->front_idx+1)%this->capacity;
    int curr_size=this->size();
    // TODO: If the array is less than 25% full, resize it to half its current capacity (but not less than 2)
    if(4*curr_size<this->capacity && curr_size>0)
    {
        int new_cap=this->capacity/2;
        if((this->capacity)>2)
        {
            this->resize(new_cap);
        }
    }
    // TODO: Return the dequeued element
    return dequeued;
}

// Clear implementation
void ArrayQueue::clear()
{
    delete[] this->data;
    this->capacity=2;
    this->data=new int[this->capacity];
    this->front_idx=0;
    this->rear_idx=0;
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
}

// Size implementation
int ArrayQueue::size() const
{
    int size;
    // TODO: Return the number of elements currently in the queue
    if(this->rear_idx>this->front_idx)
        {
            size=this->rear_idx-this->front_idx;
        }
    else if(this->rear_idx==this->front_idx)  //roundup bug unsolved
        {
            size=0;
        } 
    else
        {
            size=this->capacity-this->front_idx+this->rear_idx;
        }
        return size;
}

// Front implementation
int ArrayQueue::front() const
{
    if(this->empty()==true)
    {
        cout<<"The queue is empty"<<endl;
        return -1;
    }
    else
    {
        return this->data[this->front_idx];
    }
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    if(this->empty()==true)
    {
        cout<<"The queue is empty"<<endl;
        return -1;
    }
    else
    {
        if(this->rear_idx==0)
        {
            return this->data[this->capacity-1];
        }
        else
        {
            return this->data[this->rear_idx-1];
        }
    }
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
}

// Empty implementation
bool ArrayQueue::empty() const
{
    if(this->front_idx==this->rear_idx)
        {
            return true;
        }
    else
        {
            return false;
        }
}

// Print implementation
string ArrayQueue::toString() const
{
    if(this->empty()==true)
    {
        string queue="<|";
        return queue;
    }
    else
    {
        string queue="<";
        for(int i=0;i<this->size();i++)
        {
            if(i!=this->size()-1)
            {
                int idx=(this->front_idx+i)%this->capacity;
                queue+=to_string(this->data[idx]);
                queue+=", ";
            }
            else
            {
                int idx=(this->front_idx+i)%this->capacity;
                queue+=to_string(this->data[idx]);
            }  
        }
        queue+="|"; 
        return queue;
    }
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    int prev_size=this->size();
    // TODO: Create a new array with the new capacity;
    int *temp=new int [new_capacity];
    // TODO: Copy elements from the old array to the new array
    for(int i=0;i<prev_size;i++)
    {
        temp[i]=this->data[(this->front_idx+i)%(this->capacity)];
    }
    // TODO: Delete the old array
    delete [] this->data;
    // TODO: Update the data pointer and capacity
    this->data=temp;
    this->front_idx=0;
    this->rear_idx=prev_size;
    this->capacity=new_capacity;
    // TODO: Update front and rear indices
}

int ArrayQueue::getCapacity() const
{
    return this->capacity;
}