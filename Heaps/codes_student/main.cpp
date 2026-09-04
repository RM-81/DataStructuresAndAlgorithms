#include "MinHeap.h"
#include <fstream>
#include <sstream>

int main()
{
    MinHeap heap;

    std::ifstream infile("input.txt");
    std::ofstream outfile("output.txt");

    if (!infile.is_open() || !outfile.is_open())
    {
        std::cerr << "Error opening input/output file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int command, value, index, n;
        iss >> command;

        try
        {
            switch (command)
            {
            case 1:  // insert(x)
                iss >> value;
                heap.insert(value);
                outfile << "Inserted " << value << " into the heap." << std::endl;
                break;

            case 2:  // extract-min()
                outfile << "Extracted Min: " << heap.extractMin() << std::endl;
                break;

            case 3:  // find-min()
                outfile << "Min: " << heap.findMin() << std::endl;
                break;

            case 4:  // get-size()
                outfile << "Heap size: " << heap.getSize() << std::endl;
                break;

            case 5:  // is-empty()
                outfile << "Is heap empty? " << (heap.isEmpty() ? "Yes" : "No") << std::endl;
                break;

            case 6:  // delete-key(index)
                iss >> index;
                heap.deleteKey(index);
                outfile << "Deleted element at index " << index << std::endl;
                break;

            case 7:  // decrease-key(index, new_value)
                iss >> index >> value;
                heap.decreaseKey(index, value);
                outfile << "Decreased key at index " << index << " to " << value << std::endl;
                break;

            case 8:  // print-heap()
                outfile << "Heap: ";
                heap.printHeap(outfile);
                break;

            case 9:  // is-valid-min-heap()
                outfile << "Min Heap property is "
                        << (heap.isValidMinHeap() ? "preserved." : "violated!")
                        << std::endl;
                break;

            case 10:  // heapify(arr, n)
            {
                iss >> n;
                int* arr = new int[n];
                for (int i = 0; i < n; i++)
                {
                    iss >> arr[i];
                }
                heap.heapify(arr, n);
                delete[] arr;
                outfile << "Heap built from array." << std::endl;
                break;
            }

            case 11:  // heap-sort()
                outfile << "Sorted: ";
                heap.heapSort(outfile);
                break;

            case 12:  // replace-min(x)
                iss >> value;
                outfile << "Replaced Min: " << heap.replaceMin(value) 
                        << " with " << value << std::endl;
                break;

            default:
                outfile << "Unknown command: " << command << std::endl;
                break;
            }
        }
        catch (const std::exception &e)
        {
            outfile << "Error: " << e.what() << std::endl;
        }
    }

    infile.close();
    outfile.close();

    return 0;
}
