#include <bits/stdc++.h>
#include <windows.h>
#include "AVLTree.h"

using namespace std;

#ifdef _WIN32
inline long long get_time_ns() { //windows QPC (more precise)
    LARGE_INTEGER count,freq;
    QueryPerformanceCounter(&count);
    QueryPerformanceFrequency(&freq);
    return (long long)((count.QuadPart*1000000000LL)/freq.QuadPart); //doesn't round to zero 
}
#else
inline long long get_time_ns() {  //MINGW scheduler
    auto now =std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
}
#endif

class timingCounter
{
    private:
    long long count=0;
    long long totalNanoSeconds=0;
    public:
    timingCounter()
    {
        this->count=0;
        this->totalNanoSeconds=0;
    }
    void recordTime(long long time)
    {
        this->count++;
        this->totalNanoSeconds+=time;
    }
    long long getCount() const
    {
        return count;
    }
    long long getTotalNanoSeconds() const
    {
        return totalNanoSeconds;
    }
    long long getAverageNanoSeconds() const
    {
        if(this->count==0)
        {
            return 0;
        }
        else
        {
            return totalNanoSeconds/count;
        }
    }
    void printOperation(const string &operationName)
    {
        cout<<operationName<<", "<<count<<", "<<totalNanoSeconds<<", ";
        if(count==0)
        {
            cout<<"N/A"<<endl;
        }
        else
        {
            cout<<getAverageNanoSeconds()<<endl;
        }
    }
};


int main(int argc, char *argv[])
{
    if(argc<3)
    {
        return 0;
    }
    else
    {
        ifstream inFile(argv[1]);
        ofstream outFile(argv[2]);
        if(inFile.is_open()!=true || outFile.is_open()!=true)
        {
            return 0;
        }
        else
        {
            AVLTree<int> tree;
            unordered_map<string,timingCounter> statistics;
            string line;
            while(getline(inFile,line))
            {
                if(line.empty()==true)
                {
                    continue;
                }
                else
                {
                    stringstream s(line);
                    char command;
                    s>>command;

                    if(command=='I')
                    {
                        int x;
                        s>>x;
                        auto t1=get_time_ns();
                        bool status=tree.insert(x);
                        auto t2=get_time_ns();
                        long long timeDuration=t2-t1;
                        statistics["insert"].recordTime(timeDuration);
                        if(status==true)
                        {
                            outFile<<tree.printer()<<endl;
                        }
                        else
                        {
                            outFile<<"duplicate"<<endl;
                        }
                    }
                    else if(command=='D')
                    {
                        int x;
                        s>>x;
                        long long t1 = get_time_ns();
                        bool status = tree.erase(x);
                        long long t2 = get_time_ns();
                        long long timeDuration = t2 - t1;
                        statistics["delete"].recordTime(timeDuration);
                        if(status==true)
                        {
                            outFile<<tree.printer()<<endl;
                        }
                        else
                        {
                            outFile<<"not found"<<endl;
                        }
                    }
                    else if(command=='F')
                    {
                        int x;
                        s>>x;
                        long long t1 = get_time_ns();
                        bool status = tree.find(x);
                        long long t2 = get_time_ns();
                        long long timeDuration = t2 - t1;
                        statistics["find"].recordTime(timeDuration);
                        if(status==true)
                        {
                            outFile<<"found"<<endl;
                        }
                        else
                        {
                            outFile<<"not found"<<endl;
                        }
                    }
                    else if(command=='T')
                    {
                        long long t1 = get_time_ns();
                        vector<int> order= tree.traverse();
                        long long t2 = get_time_ns();
                        long long timeDuration = t2 - t1;
                        statistics["traverse"].recordTime(timeDuration);
                        for(int i=0;i<order.size();i++)
                        {
                            outFile<<order[i];
                            if(i+1==order.size())
                            {
                                outFile<<"";
                            }
                            else
                            {
                                outFile<<" ";
                            }
                        }
                        outFile<<endl;
                    }
                    else
                    {
                        outFile<<"Unknown Command"<<endl;
                    }
                }    
            }
            cout<<"operation, count, total_ns, average_ns"<<endl;
            vector<string>operations={"insert", "delete", "find", "traverse"};
            for(const string &op: operations)
            {
                statistics[op].printOperation(op);
            }
        }
    }
    return 0;
}