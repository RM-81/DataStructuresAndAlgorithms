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
        for(int j=(i-1)/2;i>0;j=(j-1)/2)
        {
            if(this->heap[i]<this->heap[j])
            {
                int temp=this->heap[i];
                this->heap[i]=this->heap[j];
                this->heap[j]=temp;
                i=j;
            }
            else
            {
                break;
            }
        }
    }

    /**
     * Sifts down the node at index i to maintain heap property.
     */
void siftDown(int i)
    {
        for(int j=(i*2)+1;j<this->size;j=i*2+1)
        {
            if(((j+1)<this->size) && (this->heap[i]>this->heap[j]) && (this->heap[j]<=this->heap[j+1]))
            {
                int temp=this->heap[i];
                this->heap[i]=this->heap[j];
                this->heap[j]=temp;
                i=j;
            }
            else if(((j+1)<this->size) && (this->heap[i]>this->heap[j+1]) && (this->heap[j]>this->heap[j+1]))
            {
                int temp=this->heap[i];
                this->heap[i]=this->heap[j+1];
                this->heap[j+1]=temp;
                i=j+1;
            }
            else if((j<this->size) && ((j+1)>=this->size) && (this->heap[i]>this->heap[j]))
            {
                int temp=this->heap[i];
                this->heap[i]=this->heap[j];
                this->heap[j]=temp;
                i=j;
            }
            else
            {
                break;
            }
        }
    }

public:
    // Constructor initializes an empty heap
    MinHeap() : size(0) {}

    /**
     * Inserts a new element x into the heap.
     */
    void insert(int x)
    {
        this->size++;
        this->heap[this->getSize()-1]=x;
        this->siftUp(this->getSize()-1);
        return;
    }

    /**
     * Returns the minimum element without removing it.
     */
    int findMin()
    {
        if(this->isEmpty()==true)
        {
            std::cout<<"Heap is empty. No minimum element"<<std::endl;
            return -1;
        }
        else
        {
            return this->heap[0];
        }
    }

    /**
     * Removes and returns the minimum element from the heap.
     */

    int extractMin()
    {
        if(this->isEmpty()==true)
        {
            std::cout<<"Heap empty"<<std::endl;
            return -1;
        }
        else
        {
            int min=this->heap[0];
            this->heap[0]=this->heap[this->getSize()-1]; 
            this->size--;
            this->siftDown(0);
            return min;
        }
    }

    /**
     * Returns the number of elements in the heap.
     */
    int getSize()
    {
        return this->size;
    }

    /**
     * Checks if the heap is empty.
     * Returns true if empty, false otherwise.
     */
    bool isEmpty()
    {
        if(this->getSize()==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Decreases the value of the element at index i to newValue.
     */
    void decreaseKey(int i, int newValue)
    {
        if(i>=this->getSize())
        {
            std::cout<<"Invalid Index. Cannot decrease key"<<std::endl;
        }
        else
        {
            this->heap[i]=newValue;
            this->siftUp(i);
        }
    }

    /**
     * Deletes the element at index i.
     */
    void deleteKey(int i)
    {
        if(i<0 || i>this->getSize()-1)
        {
            std::cout<<"Invalid index"<<std::endl;
            return;
        }
        else if(this->isEmpty()==true)
        {
            std::cout<<"Heap empty"<<std::endl;
            return;
        }
        else
        {
            if(i==this->getSize()-1)
            {
                this->size--;
                return;
            }
            else 
            {
                int deleted=this->heap[i];
                this->heap[i]=this->heap[this->getSize()-1];
                this->size--;
                if(deleted<this->heap[i])
                {
                    this->siftDown(i);
                }
                else if(deleted>this->heap[i])
                {
                    this->siftUp(i);
                }  
                return;
            }
        }
    }

    /**
     * Prints the heap's content to the output file.
     * Format: "elem1 elem2 elem3 ..." (space-separated)
     */
    void printHeap(std::ofstream &outfile)
    {
        if(this->isEmpty()==true)
        {
            outfile<<"empty."<<std::endl;
            return ;
        }
        else
        {
            for(int i=0;i<this->getSize();i++)
            {
                outfile<<this->heap[i];
                outfile<<" ";
            }
            outfile<<std::endl;
        }
    }

    /**
     * Checks whether the Min Heap property is preserved.
     * Returns true if valid, false otherwise.
     */
    bool isValidMinHeap()
    {
        int flag=1;
        for(int i=0;i<this->getSize()/2;i++)
        {
            int leftChildIdx=2*i+1;
            int rightChildIdx=2*i+2;
            if(leftChildIdx<=this->size-1)
            {
                if((this->heap[leftChildIdx]<this->heap[i]))
                {
                    flag=0;
                }
            }
            if(rightChildIdx<=this->size-1)
            {
                if(this->heap[rightChildIdx]<this->heap[i])
                {
                    flag=0;
                }
            }
        }
        if(flag==0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    /**
     * Builds a heap from an unsorted array using bottom-up heapify.
     */
    void heapify(int arr[], int n)
    {
        for(int i=0;i<n;i++)
        {
            this->heap[i]=arr[i];
        }
        this->size=n;
        for(int i=n/2-1;i>=0;i--)
        {
            this->siftDown(i);
        }
    }

    /**
     * Returns all elements in sorted (ascending) order.
     * The original heap should remain UNCHANGED after this operation.
     */
    void heapSort(std::ofstream &outfile)
    {
        MinHeap tempHeap;
        for(int i=0;i<this->size;i++)
        {
            tempHeap.insert(this->heap[i]);
        }
        while(tempHeap.isEmpty()!=true)
        {
            outfile<<tempHeap.extractMin()<<" ";
        }
        outfile<<std::endl;
    }

    /**
     * Replaces the minimum element with a new value x in a single operation.
     * Returns the old minimum value.
     */
    int replaceMin(int x)
    {
        if(this->isEmpty()==true)
        {
            std::cout<<"Heap is empty."<<std::endl;
            return -1;
        }
        else
        {
            int oldValue=this->heap[0];
            this->heap[0]=x;
            if(x>oldValue)
            {
                siftDown(0);
            }
            return oldValue;
        }
    }
};

#endif // MINHEAP_H
