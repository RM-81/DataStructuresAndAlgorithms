#include <iostream>
#include <vector>
#include <list>


using namespace std;

class Graph
{
    public:
    int verticeNum ;
    list<int> *adjacencyList;
    
    Graph()
    {
        this->verticeNum=0;
        adjacencyList=NULL;
    }
    Graph(int vertices)
    {
        this->verticeNum=vertices;
        adjacencyList=new list<int> [vertices];
    }

    void addEdge(int vertice1, int vertice2)
    {
        adjacencyList[vertice1].push_back(vertice2);
        adjacencyList[vertice2].push_back(vertice1);
    }
    bool edgeChecker(int u, int v) 
    {
        int flag=0;
        for(int neighbor : adjacencyList[u]) 
        {
            if (neighbor == v)
            {
                flag=1;
                break;
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

    void DFS(int node,bool visited[],vector<int> &group)
    {
        visited[node]=true;
        group.push_back(node);
        for(int neighbour:adjacencyList[node])
        {
            if(visited[neighbour]!=true)
            {
                DFS(neighbour,visited,group);
            }
        }
    } 
    
    ~Graph() 
    {
        delete[] adjacencyList;
    }
};



int main()
{
    int numTeams;
    cin>>numTeams;
    Graph newGraph(numTeams);
    if(numTeams==0)
    {
        cout<<" No teams are participating in the tournament"<<endl;
        return 0;
    }
    else
    {
        int u, v;
        char startBracket,comma,endBracket;
        while (cin >> startBracket) 
        {
            if(startBracket != '[') 
            {
                break;
            }
            cin >> u >> comma >> v >> endBracket;
            newGraph.addEdge(u, v);
        }
        bool *visited=new bool [numTeams];
        for(int i=0;i<numTeams;i++)
        {
            visited[i]=false; 
        }
        vector<vector<int>>allGroup;
        for(int i=0;i<numTeams;i++)
        {
            if(visited[i]==false)
            {
                vector<int>group;
                newGraph.DFS(i,visited,group);
                allGroup.push_back(group);
            }
        }
        cout<<allGroup.size()<<endl;

        for(int i=0;i<allGroup.size();i++)
        {
            cout<<"Group "<<i+1<<" : ";
            if(allGroup[i].size()!=0)
            {
                cout<<"{";
                for(int j=0;j<allGroup[i].size()-1;j++)
                {
                    cout<<allGroup[i][j]<<", ";
                }
                cout<<allGroup[i][allGroup[i].size()-1];
                cout<<"} ";
            }
            cout<<"| ";
            int flag=1;
            bool matchFound=false;
            for(int j=0;j<allGroup[i].size();j++)
            {
                for(int k=j+1;k<allGroup[i].size();k++)
                {
                    if(newGraph.edgeChecker(allGroup[i][j],allGroup[i][k])==false)
                    {
                        if(matchFound==true)
                        {
                            cout<<", ";
                        }
                        cout<<"["<<allGroup[i][j]<<","<<allGroup[i][k]<<"] ";
                        flag=0;
                        matchFound=true;
                    }
                }
            }
            if(flag==1)
            {
                cout<<"none";
            }
            cout<<endl;
        }
        delete []visited;
    }
    return 0;    
}

