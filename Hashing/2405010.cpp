#include <bits/stdc++.h>

using namespace std;

bool isPrime(int n)
{
    if(n<=1)
    {
        return false;
    }
    else if(n==2)
    {
        return true;
    }
    else 
    {
        int count=0;
        for(int i=2;i*i<=n;i++)
        {
            if(n%i==0)
            {
                count++;
            }
        }
        if(count==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int getNextPrime(int n)
{
    int nextPrime=n+1;
    while(isPrime(nextPrime)==false)
    {
        nextPrime++;
    }
    return nextPrime;
}

int getPreviousPrime(int n)
{
    int previousPrime=n-1;
    while(isPrime(previousPrime)==false)
    {
        previousPrime--;
    }
    return previousPrime;
}

string randomWordGenerator(int size)
{
    static const char consonants[]="bcdfghjklmnpqrstvwxyz";
    static const char vowels[]="aeiou";
    static mt19937 gen(1337);  
    uniform_int_distribution<>distributeConsonants(0,sizeof(consonants)-2);
    uniform_int_distribution<>distributeVowels(0,sizeof(vowels)-2);
    string word;
    word.reserve(size);
    for(int i=0;i<size;i++)
    {
        if(i%2!=0)
        {
            word+=consonants[distributeConsonants(gen)];
        }
        else
        {
            word+=vowels[distributeVowels(gen)];
        }
    }
    return word;
}

unsigned long hash1(const string& str) 
{
    unsigned long hash=5381;
    for (char c:str) 
    {
        hash=((hash<<5)+hash)+c;    //DJB2 hashing
    } 
    return hash;
}

unsigned long hash2(const string& str)
{
    unsigned long hash=2166136261u;
    for (char c:str) 
    {
        hash^=c;
        hash*=16777619u;    //FNV 1a hashing
    }
    return hash;
}

unsigned long auxHash(const string& str)
{
    unsigned long hash=0;
    for (char c:str) 
    {
        hash=c+(hash<<6)+(hash<<16)-hash;  //SDBM hashing
    }
    return (hash%10007)+1;
}

enum resolutionType
{
    CHAINING,
    DOUBLE_HASHING,
    CUSTOM_PROBING
};

class Entry
{
    public:
    string key;
    int value;
    bool isOccupied;
    bool isDeleted;
    Entry()
    {
        key="";
        value=-1;
        isOccupied=false;
        isDeleted=false;
    }
};

class hashTable
{
    public:
    const double maximumLoadFactor=0.5;
    const int initialTableSize=13;
    const double minimumLoadFactor=0.25;
    int currentSize;
    int numberOfElements;
    int elementsAtLastResize;
    int insertionsAfterLastResize;
    int deletionAfterLastResize;
    resolutionType resolution;
    unsigned long (*primaryHash) (const string&);
    double a1,a2;
    vector<list<pair<string,int>>>chainTable;
    vector<Entry>openTable;
    long long totalCollisions;

    void reHash(int newSize)
    {
        int oldSize=currentSize;
        currentSize=newSize;
        elementsAtLastResize=numberOfElements;
        insertionsAfterLastResize=0;
        deletionAfterLastResize=0;
        if(resolution==CHAINING)
        {
            auto oldChain=chainTable;
            chainTable.clear();
            chainTable.resize(currentSize);
            numberOfElements=0;
            for(int i=0;i<oldSize;i++)
            {
                for(const auto &j: oldChain[i])
                {
                    insertInternal(j.first,j.second);
                }
            }
        }
        else
        {
            auto oldOpenTable=openTable;
            openTable.clear();
            openTable.resize(currentSize);
            numberOfElements=0;
            for(int i=0;i<oldSize;i++)
            {
                if(oldOpenTable[i].isOccupied==true && oldOpenTable[i].isDeleted==false)
                {
                    insertInternal(oldOpenTable[i].key, oldOpenTable[i].value);
                }
            }
        }
    }

    void checkAndResize(bool isInserted) 
    {
        double currentLoadFactor=(double)numberOfElements/currentSize;
        
        if(isInserted==true) 
        {
            if(currentLoadFactor>maximumLoadFactor && insertionsAfterLastResize>=elementsAtLastResize/2) 
            {
                reHash(getNextPrime(2*currentSize));
            }
        } 
        else 
        {
            if(currentLoadFactor<minimumLoadFactor && currentSize>initialTableSize && deletionAfterLastResize>=elementsAtLastResize/2) 
            {
                reHash(getPreviousPrime(currentSize/2));
            }
        }
    }

    bool insertInternal(const string& key, int value) 
    {
        unsigned long h=primaryHash(key);
        
        if(resolution==CHAINING) 
        {
            int index=h%currentSize;
            if(chainTable[index].empty()==false) 
            {
                totalCollisions++;
            }
            for(auto&v:chainTable[index]) 
            {
                if(v.first==key)
                {
                    return false;
                } 
            }
            chainTable[index].push_back({key, value});
            numberOfElements++;
            return true;
        } 
        else 
        {
            int index=h%currentSize;
            if(openTable[index].isOccupied==true && openTable[index].isDeleted==false) 
            {
                totalCollisions++;
            }
            int firstDeletedSlot=-1;
            for(int i=0;i<currentSize;++i) 
            {
                int probeIndex;
                if(resolution==DOUBLE_HASHING) 
                {
                    probeIndex=(h+i*auxHash(key)) % currentSize;
                } 
                else 
                {
                    probeIndex=(h+(unsigned long)(a1*i*auxHash(key)+a2*i*i))%currentSize;
                }

                if(openTable[probeIndex].isOccupied==true && openTable[probeIndex].isDeleted==false) 
                {
                    if (openTable[probeIndex].key == key) 
                    {
                        return false;
                    }
                } 
                else 
                {
                    if(openTable[probeIndex].isDeleted==true && firstDeletedSlot == -1) 
                    {
                        firstDeletedSlot = probeIndex;
                    }
                    if(openTable[probeIndex].isOccupied==false) 
                    {
                        int targetIdx=(firstDeletedSlot!=-1)?firstDeletedSlot:probeIndex;
                        openTable[targetIdx].key=key;
                        openTable[targetIdx].value=value;
                        openTable[targetIdx].isOccupied=true;
                        openTable[targetIdx].isDeleted=false;
                        numberOfElements++;
                        return true;
                    }
                }
            }
        }
        return false;
    }

public:
    hashTable(resolutionType res, unsigned long (*hFunc)(const string&), double c1 = 1.0, double c2 = 1.0)
        : currentSize(13),numberOfElements(0),elementsAtLastResize(0), 
          insertionsAfterLastResize(0),deletionAfterLastResize(0),
          resolution(res),primaryHash(hFunc),a1(c1),a2(c2),totalCollisions(0) 
    {
        if (resolution==CHAINING) 
        {
            chainTable.resize(currentSize);
        } 
        else 
        {
            openTable.resize(currentSize);
        }
    }

    bool insert(const string& key, int value) 
    {
        bool success=insertInternal(key, value);
        if (success==true) 
        {
            insertionsAfterLastResize++;
            checkAndResize(true);
        }
        return success;
    }

    bool remove(const string& key) 
    {
        unsigned long h = primaryHash(key);
        if (resolution==CHAINING) 
        {
            int idx=h%currentSize;
            for (auto it=chainTable[idx].begin();it!=chainTable[idx].end();++it) 
            {
                if (it->first==key) 
                {
                    chainTable[idx].erase(it);
                    numberOfElements--;
                    deletionAfterLastResize++;
                    checkAndResize(false);
                    return true;
                }
            }
        } 
        else 
        {
            for (int i=0;i<currentSize;++i) 
            {
                int probeIdx;
                if (resolution==DOUBLE_HASHING) 
                {
                    probeIdx=(h+i*auxHash(key))%currentSize;
                } 
                else 
                {
                    probeIdx=(h+(unsigned long)(a1*i*auxHash(key)+a2*i*i))%currentSize;
                }

                if (openTable[probeIdx].isOccupied==false) 
                {
                    return false;
                }
                if (openTable[probeIdx].isOccupied==true && openTable[probeIdx].isDeleted==false && openTable[probeIdx].key == key) 
                {
                    openTable[probeIdx].isDeleted = true;
                    numberOfElements--;
                    deletionAfterLastResize++;
                    checkAndResize(false);
                    return true;
                }
            }
        }
        return false;
    }

    int searchHits(const string& key) 
    {
        unsigned long h=primaryHash(key);
        int hits=0;

        if(resolution==CHAINING) 
        {
            int idx=h%currentSize;
            for(const auto& v:chainTable[idx]) 
            {
                hits++;
                if(v.first==key)
                {
                    return hits;
                }
            }
            return hits;
        } 
        else 
        {
            for(int i=0;i<currentSize;++i) 
            {
                hits++;
                int probeIdx;
                if(resolution==DOUBLE_HASHING) 
                {
                    probeIdx=(h+i*auxHash(key))%currentSize;
                } 
                else 
                {
                    probeIdx=(h+(unsigned long)(a1*i*auxHash(key)+a2*i*i))%currentSize;
                }

                if(openTable[probeIdx].isOccupied==false)
                {
                    return hits;
                }
                if(openTable[probeIdx].isOccupied==true&&openTable[probeIdx].isDeleted==false&&openTable[probeIdx].key==key) 
                {
                    return hits;
                }
            }
        }
        return hits;
    }

    long long getCollisions()const 
    { 
        return totalCollisions; 
    }
};


int main() 
{
    const int NUM_KEYS=10000;
    const int WORD_LEN=10;
    const int SEARCH_KEYS=1000;

    vector<string>keys;
    vector<int>values;
    unordered_set<string>uniqueSet;

    int seq=1;
    while(keys.size()<NUM_KEYS) 
    {
        string w=randomWordGenerator(WORD_LEN);
        if (uniqueSet.find(w)==uniqueSet.end()) 
        {
            uniqueSet.insert(w);
            keys.push_back(w);
            values.push_back(seq++);
        }
    }

    resolutionType methods[]={CHAINING,DOUBLE_HASHING,CUSTOM_PROBING};
    string methodNames[]={"Chaining Method","Double Hashing","Custom Probing"};


    cout<<left<<setw(20)<<" "<<setw(26)<<"Hash1"<<setw(26)<<"Hash2"<<"\n";
    cout<<left<<setw(20)<<" "<<setw(16)<<"Collisions"<<setw(10)<<"Avg Hits"<<setw(16)<<"Collisions"<<setw(10)<<"Avg Hits"<<"\n";
    cout << string(81,'-')<<"\n";

    for (int m=0;m<3;++m) 
    {

        hashTable ht1(methods[m],hash1,1.0,1.0);
        for (size_t i=0;i<keys.size();++i) 
        {
            ht1.insert(keys[i], values[i]);
        }
        
        long long hits1=0;
        for (int i=0;i<SEARCH_KEYS;++i) 
        {
            hits1+=ht1.searchHits(keys[i]);
        }
        double avgHits1=(double)hits1/SEARCH_KEYS;


        hashTable ht2(methods[m],hash2,1.0,1.0);
        for (size_t i=0;i<keys.size();++i) 
        {
            ht2.insert(keys[i],values[i]);
        }

        long long hits2=0;
        for (int i=0;i<SEARCH_KEYS;++i) 
        {
            hits2+=ht2.searchHits(keys[i]);
        }
        double avgHits2=(double)hits2/SEARCH_KEYS;


        cout <<left<<setw(20)<<methodNames[m]<<setw(16)<<ht1.getCollisions()<<setw(10)<<fixed<<setprecision(2)<<avgHits1<<setw(16)<<ht2.getCollisions()<<setw(10)<<avgHits2<<"\n";
    }

    return 0;
}