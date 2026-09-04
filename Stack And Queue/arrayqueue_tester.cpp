#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "queue.h"
using namespace std;

/*
g++ arrayqueue_tester.cpp arrayqueue.cpp
.\a.exe <number_of_tests>
*/

int main(int argc, char *argv[])
{
    int N = 10;
    if (argc > 1)
    {
        N = atoi(argv[1]);
        if (N <= 0)
        {
            cout << "Invalid number of tests. Using default value of 1.\n";
            N = 10;
        }
    }
    srand((unsigned)time(0));
    Queue *my_queue = new ArrayQueue();
    queue<int> stl_queue;

    {
        cout << "Initializing queue with random elements...\n";
        int initial_size = rand() % 20 + 1; // Random initial size between 1 and 10
        for (int i = 0; i < initial_size; ++i)
        {
            int val = rand() % 100;
            my_queue->enqueue(val);
            stl_queue.push(val);
        }
        cout << "Initial queue: " << my_queue->toString() << endl
             << endl;
    }

    int success_count = 0;
    for (int i = 0; i < N; ++i)
    {
        int op = rand() % 6; // Random operation

        switch (op)
        {
        case 0:
        {
            cout << "Operation " << i + 1 << ": clear()";
            my_queue->clear();
            stl_queue = queue<int>();
            if (my_queue->empty())
            {
                cout << " \033[32m[OK]\033[0m\n";
                success_count++;
            }
            else
                cout << " \033[31m[Mismatch!]\033[0m\n";

            {
                cout << "Reinitializing queue with random elements...\n";
                int initial_size = rand() % 50 + 1; // Random initial size between 1 and 20
                for (int i = 0; i < initial_size; ++i)
                {
                    int val = rand() % 100;
                    my_queue->enqueue(val);
                    stl_queue.push(val);
                }
            }
        }
        break;

        case 1:
        {
            int val = rand() % 100;
            cout << "Operation " << i + 1 << ": enqueue(" << val << ")";
            my_queue->enqueue(val);
            stl_queue.push(val);

            if (my_queue->back() == stl_queue.back())
            {
                cout << " \033[32m[OK]\033[0m\n";
                success_count++;
            }
            else
                cout << " \033[31m[Mismatch!]\033[0m\n";
        }

        break;

        case 2:
        {
            int my_dequeued = my_queue->dequeue();

            int stl_dequeued = -1;
            if (!stl_queue.empty())
            {
                stl_dequeued = stl_queue.front();
                stl_queue.pop();
            }

            cout << "Operation " << i + 1 << ": dequeue() -> MyQueue: " << my_dequeued << ", STL: " << stl_dequeued;
            if (my_dequeued == stl_dequeued)
            {
                cout << " \033[32m[OK]\033[0m\n";
                success_count++;
            }
            else
                cout << " \033[31m[Mismatch!]\033[0m\n";
        }
        break;

        case 3:
        {
            int my_front = my_queue->front();
            int stl_front = -1;
            if (!stl_queue.empty())
            {
                stl_front = stl_queue.front();
            }
            cout << "Operation " << i + 1 << ": front() -> MyQueue: " << my_front << ", STL: " << stl_front;
            if (my_front == stl_front)
            {
                cout << " \033[32m[OK]\033[0m\n";
                success_count++;
            }
            else
                cout << " \033[31m[Mismatch!]\033[0m\n";
        }
        break;

        case 4:
        {
            int my_back = my_queue->back();
            int stl_back = -1;
            if (!stl_queue.empty())
            {
                stl_back = stl_queue.back();
            }
            cout << "Operation " << i + 1 << ": back() -> MyQueue: " << my_back << ", STL: " << stl_back;
            if (my_back == stl_back)
            {
                cout << " \033[32m[OK]\033[0m\n";
                success_count++;
            }
            else
                cout << " \033[31m[Mismatch!]\033[0m\n";
        }
        break;

        case 5:
        {
            int my_size = my_queue->size();
            int stl_size = stl_queue.size();
            cout << "Operation " << i + 1 << ": size() -> MyQueue: " << my_size << ", STL: " << stl_size;
            if (my_size == stl_size)
            {
                cout << " \033[32m[OK]\033[0m\n";
                success_count++;
            }
            else
                cout << " \033[31m[Mismatch!]\033[0m\n";
        }
        break;

        default:
            break;
        }
        cout << my_queue->toString() << endl
             << endl;

        int capacity = ((ArrayQueue *)my_queue)->getCapacity();
        if ((my_queue->size() < capacity / 4 && capacity > 2))
        {
            cout << "\033[31m[Error]\033[0m Queue size is less than 25\% of its capacity." << endl;
            exit(1);
        }
        
        else if (capacity < 2)
        {
            cout << "\033[31m[Error]\033[0m Queue capacity is less than 2." << endl;
            exit(1);
        }
    }

    delete my_queue;

    if (success_count == N)
        cout << "\033[32mAll operations passed!\033[0m\n";
    else
        cout << "\033[31mSome operations failed.\033[0m\n";
    return 0;
}