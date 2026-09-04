#include <bits/stdc++.h>

using namespace std;

const int INF=1e9;

class Flight
{
    public:
    int ID; //mapping in 1's
    string flightID;
    string departureCity;
    string arrivalCity;
    string departureTime;
    string arrivalTime;

    Flight()
    {
        this->ID=-1;
        this->flightID=" ";
        this->departureCity=" ";
        this->arrivalCity=" ";
        this->departureTime=" ";
        this->arrivalTime=" ";
    }
    Flight(int ID, string flightID,string departureCity,string arrivalCity,string departureTime,string arrivalTime)
    {
        setDetails(ID,flightID,departureCity,arrivalCity,departureTime,arrivalTime);
    }

    void setDetails(int ID, string flightID,string departureCity,string arrivalCity,string departureTime,string arrivalTime)
    {
        this->ID=ID;
        this->flightID=flightID;
        this->departureCity=departureCity;
        this->arrivalCity=arrivalCity;
        this->departureTime=departureTime;
        this->arrivalTime=arrivalTime;
    }
    

    int getDepartureTime(const string &departureTime)
    {
        int hours=stoi(departureTime.substr(0,2));
        int minutes=stoi(departureTime.substr(3,2));
        return hours*60+minutes;
    }

    int getArrivalTime(const string &arrivalTime)
    {
        int hours=stoi(arrivalTime.substr(0,2));
        int minutes=stoi(arrivalTime.substr(3,2));
        return hours*60+minutes;
    }

};

class Graph
{
    private:
    int vertices; 
    vector<vector<int>> capacity; 
    vector<vector<int>> residualGraph;
    
    int bfs(int source, int sink, vector<int> &parent, const vector<vector<int>> &residualGraph)
    {
        fill(parent.begin(),parent.end(),-1);
        parent[source]=-2; 

        queue<pair<int,int>>q;
        q.push({source,INF});

        while(q.size()!=0)
        {
            int u=q.front().first;
            int currentFlow=q.front().second;
            q.pop();

            for(int v=0; v<vertices; v++)
            {
                if(parent[v]==-1 && residualGraph[u][v]>0)
                {
                    parent[v]=u;
                    int newFlow=min(currentFlow,residualGraph[u][v]);
                    if(v==sink)
                    {
                        return newFlow;
                    }
                    q.push({v,newFlow});
                }
            }
        }
        return 0;
    }

    public:
    Graph(int vertices)
    {
        this->vertices=vertices;
        capacity.assign(vertices, vector<int>(vertices,0));
    }

    void addEdge(int u, int v,int w)
    {
        capacity[u][v]=w;
    }

    int fordFulkerson(int source,int sink)
    {
        vector<int> parent(vertices);
        residualGraph = capacity;
        int maxFlow=0;
        int pathFlow=0;

        while((pathFlow=bfs(source,sink,parent,residualGraph))>0)
        {
            maxFlow+=pathFlow;
            int current=sink;

            while(current!=source)
            {
                int prev= parent[current];
                residualGraph[prev][current]-=pathFlow;
                residualGraph[current][prev]+=pathFlow;
                current=prev;
            }
        }
        return maxFlow;
    }

    bool isEdgeMatched(int u, int v)
    {
        if(capacity[u][v]==1 && residualGraph[u][v]==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    int F;
    cin>>F;
    vector<Flight>flights(F);

    for(int i=0;i<F;i++)
    {
        string flightID,departureCity,arrivalCity,departureTime,arrivalTime;
        cin>> flightID>>departureCity>>arrivalCity>>departureTime>>arrivalTime;
        flights[i].setDetails(i,flightID,departureCity,arrivalCity,departureTime,arrivalTime);
    }

    //maximum bipartite graph formation
    int source=0;
    int sink=2*F+1;
    Graph g(2*F+2);

    //src to v-out
    for(int i=0;i<F;i++)
    {
        g.addEdge(source,i+1,1); 
    }

    //valid connections
    for(int i=0;i<F;i++)
    {
        for(int j=0;j<F;j++)
        {
            if(i==j)
            {
                continue;
            }
            if((flights[i].arrivalCity==flights[j].departureCity) && (flights[i].getArrivalTime(flights[i].arrivalTime)+180<=flights[j].getDepartureTime(flights[j].departureTime)))
            {
                g.addEdge(i+1,F+j+1,1);
            }
        }
    }

    //v-in to sink
    for(int j=0;j<F;j++)
    {
        g.addEdge(j+F+1,sink,1);
    }

    int maxMatching=g.fordFulkerson(source,sink);
    int minAircraft=F-maxMatching;

    cout<<"Number of Aircraft: "<<minAircraft<<endl;

    vector<int>nextFlight(F,-1); //all flights next is -1
    vector<bool>hasPrev(F,false); //all prev false
    for(int i=0;i<F;i++)
    {
        int u=i+1;
        for(int j=0;j<F;j++)
        {
            int v=j+F+1;
            if(g.isEdgeMatched(u,v)==true)
            {
                nextFlight[i]=j;
                hasPrev[j]=true;
                break;
            }
        }
    }

    int airCraftCount=1;
    for(int i=0;i<F;i++)
    {
        if(hasPrev[i]==false)
        {
            cout<<"Aircraft "<< airCraftCount++<<" :";
            int current=i;
            while(current!=-1)
            {
                cout<<flights[current].flightID;
                current=nextFlight[current];
                if(current!=-1)
                {
                    cout<<" -> ";
                }
            }
            cout<<endl;
        }
    }
    return 0;
}