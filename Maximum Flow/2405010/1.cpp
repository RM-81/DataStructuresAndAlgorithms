#include <bits/stdc++.h>

using namespace std;

const int INF=1e9;

class Graph
{
    private:
    int vertices; 
    vector<vector<int>> capacity; 
    
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
        vector<vector<int>> residualGraph=capacity;
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
};

int main()
{
    int N,M;
    cin>>N>>M;
    Graph g(N);
    int u,v,w;
    for(int i=0;i<M;i++)
    {
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    cout<<g.fordFulkerson(0,N-1)<<endl;
    return 0;
}