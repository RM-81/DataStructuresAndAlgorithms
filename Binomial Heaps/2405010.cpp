#include "BinomialHeap.h"
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, Node*> nodes;

int main()
{

    BinomialHeap heaps[10];
    string command;
    while(cin >> command)
    {
        if(command == "I")
        {
            int h, x;
            cin >> h >> x;
            heaps[h].insert(x);
        }
        else if(command == "F")
        {
            int h;
            cin >> h;
            heaps[h].findMin();
        }
        else if(command == "E")
        {
            int h;
            cin >> h;
            int minimum = heaps[h].extractMin();
            if(minimum != -1)
            {
                cout << "Extract Min returned: " << minimum << endl;
            }
            else
            {
                cout << "Heap H" << h << " is empty. Extract Min failed" << endl;
            }
        }
        else if(command == "U")
        {
            int h1, h2;
            cin >> h1 >> h2;
            heaps[h1].unionFunction(heaps[h2]);
        }
        else if(command == "D")
        {
            int h, x, y;
            cin >> h >> x >> y;
            heaps[h].decreaseKey(x, y);
        }
        else if(command == "R")
        {
            int h, x;
            cin >> h >> x;
            heaps[h].removeKey(x);
        }
        else if(command == "P")
        {
            int h;
            cin >> h;
            heaps[h].printer(h);
        }
        else if(command == "V")
        {
            int h;
            cin >> h;
            heaps[h].visualizeHeap(h);
        }
        else if(command == "VU")
        {
            int h1, h2;
            cin >> h1 >> h2;
            heaps[h1].visualizeUnion(h1, h2, heaps[h2]);
        }
        else if(command == "STAT")
        {
            int h;
            cin >> h;
            heaps[h].printStatistics(h);
        }
        else
        {
            cout << "Invalid Command" << endl;
        }
    }
}
