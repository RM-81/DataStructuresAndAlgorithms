#include <bits/stdc++.h>
#include <windows.h>
#include "IntervalScheduler.h"

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
            intervalSchedulerTree tree;
            unordered_map<int,pair<int,int>>eventMap;
            int nextId = 1;
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
                    string command;
                    s>>command;

                    if(command=="ADD")
                    {
                        int start,end;
                        s>>start>>end;
                        int id=nextId++;
                        auto t1=get_time_ns();
                        tree.add(id,start,end);
                        auto t2=get_time_ns();
                        eventMap[id]={start,end};
                        long long timeDuration=t2-t1;
                        statistics["add"].recordTime(timeDuration);
                        outFile<<tree.printer()<<endl;
                    }
                    else if(command=="REMOVE")
                    {
                        int id;
                        s>>id;
                        auto it=eventMap.find(id);
                        if(it==eventMap.end())
                        {
                            outFile<<"not found"<<endl;
                        }
                        else
                        {
                            int start=it->second.first;
                            long long t1=get_time_ns();
                            tree.remove(id,start);
                            long long t2=get_time_ns();
                            long long timeDuration=t2-t1;
                            eventMap.erase(id);
                            statistics["remove"].recordTime(timeDuration);
                            outFile<<tree.printer()<<endl;
                        }    
                    }
                    else if(command=="UPDATE")
                    {
                        int id,newStart,newEnd;
                        s>>id>>newStart>>newEnd;
                        auto it=eventMap.find(id);
                        if(it==eventMap.end())
                        {
                            outFile<<"not found"<<endl;
                        }
                        else
                        {
                            int oldStart=it->second.first;
                            long long t1=get_time_ns();
                            tree.update(id,oldStart,newStart,newEnd);
                            long long t2=get_time_ns();
                            long long timeDuration=t2-t1;
                            it->second={newStart,newEnd};
                            statistics["update"].recordTime(timeDuration);
                            outFile<<tree.printer()<<endl;
                        } 

                    }
                    else if(command=="CONFLICT")
                    {
                        int start,end;
                        s>>start>>end;
                        long long t1=get_time_ns();
                        bool hasConflict=tree.conflict(start,end);
                        long long t2=get_time_ns();
                        long long timeDuration=t2-t1;
                        statistics["conflict"].recordTime(timeDuration);
                        if(hasConflict==true)
                        {
                            outFile<<"yes"<<endl;
                        }
                        else
                        {
                            outFile<<"no"<<endl;
                        }

                    }
                    else if(command=="OVERLAPS")
                    {
                        int start,end;
                        s>>start>>end;
                        long long t1=get_time_ns();
                        vector<int>matches=tree.overlaps(start,end);
                        long long t2=get_time_ns();
                        long long timeDuration=t2-t1;
                        statistics["overlaps"].recordTime(timeDuration);
                        if(matches.empty()==true)
                        {
                            outFile<<"none"<<endl;
                        }
                        else
                        {
                            for(int i=0;i<matches.size();i++)
                            {
                                outFile<<matches[i];
                                if(i+1==matches.size())
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
                    }
                    else if(command=="AT")
                    {
                        int t;
                        s>>t;
                        long long t1=get_time_ns();
                        vector<int>matches=tree.at(t);
                        long long t2=get_time_ns();
                        long long timeDuration=t2-t1;
                        statistics["at"].recordTime(timeDuration);
                        if(matches.empty()==true)
                        {
                            outFile<<"none"<<endl;
                        }
                        else
                        {
                            for(int i=0;i<matches.size();i++)
                            {
                                outFile<<matches[i];
                                if(i+1==matches.size())
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
                    }
                    else if(command=="NEXT")
                    {
                        int t;
                        s>>t;
                        long long t1=get_time_ns();
                        const intervalNode *match=tree.next(t);
                        long long t2=get_time_ns();
                        long long timeDuration=t2-t1;
                        statistics["next"].recordTime(timeDuration);
                        if(match==nullptr)
                        {
                            outFile<<"none"<<endl;
                        }
                        else
                        {
                            outFile<<match->id<<" "<<match->start<<" "<<match->end<<endl;
                        }
                    }
                    else
                    {
                        outFile<<"Unknown Command"<<endl;
                    }
                }    
            }
            cout<<"operation, count, total_ns, average_ns"<<endl;
            vector<string>operations={"add","remove","update","conflict","overlaps","at","next"};
            for(const string &op: operations)
            {
                statistics[op].printOperation(op);
            }
        }
    }
    return 0;
}
