#include <iostream>
#include <vector>
#include <cmath>
#include <list>

using namespace std;

class Edge
{
    public:
    int u,v;
    float distance;
};

class City
{
    public:
    int id;
    float x,y;    
};

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

    ~Graph() 
    {
        delete[] adjacencyList;
    }
};




float calculateDistance(float x1,float x2,float y1,float y2);
void mergeCityHelper(vector <City> &cities,int left,int mid,int right);
void mergeEdgeHelper(vector <Edge> &edges,int left,int mid,int right);
void mergeSortCity(vector <City> &cities,int left,int right);
void mergeSortEdge(vector <Edge> &edges,int left,int right);
void probSolve(int start,int end,vector<City>&cities,Graph &graph,int M,vector<Edge>&final);
void localDFS(int node,vector<bool>&visited,vector<list<int>>&localAdj);
bool locallyConnected(int u,int v,vector<int>&idToLocal,vector<list<int>>&localAdj,int groupSize);



float calculateDistance(float x1,float x2,float y1,float y2)
{
    float dx=x2-x1;
    float dy=y2-y1;
    float p=dx*dx;
    float q=dy*dy;
    return sqrt(p+q);
}
void mergeCityHelper(vector <City> &cities,int left,int mid,int right)
{
    int n1=mid-left+1;
    int n2=right-mid;
    vector <City> lft(n1);
    vector <City> rt(n2);

    for(int i=0;i<n1;i++)
    {
        lft[i]=cities[left+i];
    }

    for(int i=0;i<n2;i++)
    {
        rt[i]=cities[mid+1+i];
    }

    int i=0,j=0,k=left;

    while(i<n1 && j<n2)
    {
        if(lft[i].x<=rt[j].x)
        {
            cities[k]=lft[i];
            i++;
        }
        else
        {
            cities[k]=rt[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        cities[k]=lft[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        cities[k]=rt[j];
        j++;
        k++;
    }
}


void mergeSortCity(vector <City> &cities,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    else
    {
        int mid=left+(right-left)/2;
        mergeSortCity(cities,left,mid);
        mergeSortCity(cities,mid+1,right);
        mergeCityHelper(cities,left,mid,right);
    }
}

void mergeEdgeHelper(vector <Edge> &edges,int left,int mid,int right)
{
    int n1=mid-left+1;
    int n2=right-mid;
    vector <Edge> lft(n1);
    vector <Edge> rt(n2);

    for(int i=0;i<n1;i++)
    {
        lft[i]=edges[left+i];
    }

    for(int i=0;i<n2;i++)
    {
        rt[i]=edges[mid+1+i];
    }

    int i=0,j=0,k=left;

    while(i<n1 && j<n2)
    {
        if(lft[i].distance<=rt[j].distance)
        {
            edges[k]=lft[i];
            i++;
        }
        else
        {
            edges[k]=rt[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        edges[k]=lft[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        edges[k]=rt[j];
        j++;
        k++;
    }
}


void mergeSortEdge(vector <Edge> &edges,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    else
    {
        int mid=left+(right-left)/2;
        mergeSortEdge(edges,left,mid);
        mergeSortEdge(edges,mid+1,right);
        mergeEdgeHelper(edges,left,mid,right);
    }
}

void localDFS(int node,vector<bool>&visited,vector<list<int>>&localAdjList)
{
    visited[node] = true;
    for(int neigh:localAdjList[node])
    {
        if(visited[neigh]==false)
        {
            localDFS(neigh,visited,localAdjList);
        }       
    }
}

bool locallyConnected(int u,int v,vector<int>&idToLocalGraph,vector<list<int>>&localAdjList,int groupSize)
{
    int localU = idToLocalGraph[u];
    int localV = idToLocalGraph[v];
    vector<bool> visited(groupSize, false);
    localDFS(localU, visited, localAdjList);
    return visited[localV];
}



void probSolve(int start,int end,vector<City>&cities,Graph&graph,int M,vector<Edge>&final) 
{
    int n=end-start+1;
    if (n<=M) 
    {
        vector<Edge> allEdges;
        for (int i=start;i<=end;i++) 
        {
            for (int j=i+1;j<=end;j++) 
            {
                Edge edge;
                edge.u=cities[i].id;
                edge.v=cities[j].id;
                edge.distance=calculateDistance(cities[i].x,cities[j].x,cities[i].y,cities[j].y);
                allEdges.push_back(edge);
            }
        }

        if (allEdges.size()!=0) 
        {
            mergeSortEdge(allEdges,0,allEdges.size()-1);
        }

        vector<int>idToLocalGraph(graph.verticeNum+1,-1);
        for (int i=0;i<n;i++)
        {
            idToLocalGraph[cities[start+i].id]=i;
        } 
        vector<list<int>>localAdjList(n);

        for (Edge &edge:allEdges) 
        {
            if (!locallyConnected(edge.u,edge.v,idToLocalGraph,localAdjList,n)) 
            {
                localAdjList[idToLocalGraph[edge.u]].push_back(idToLocalGraph[edge.v]);
                localAdjList[idToLocalGraph[edge.v]].push_back(idToLocalGraph[edge.u]);
                graph.addEdge(edge.u,edge.v);
                final.push_back(edge);
            }
        }
    } 
    else 
    {
        int mid=start+(end-start)/2;
        probSolve(start,mid,cities,graph,M,final);
        probSolve(mid+1,end,cities,graph,M,final);
        Edge bestConnection;
        bool found=false;

        for (int i=mid;((i>=start) && ((mid-i)<M));i--) 
        {
            for (int j=mid+1;((j<=end) && ((j-mid-1)<M));j++)
             {
                float distance=calculateDistance(cities[i].x,cities[j].x,cities[i].y,cities[j].y);
                if ((found==false) || (distance<bestConnection.distance)) 
                {
                    bestConnection.distance=distance;
                    bestConnection.u=cities[i].id;
                    bestConnection.v=cities[j].id;
                    found=true;
                }
            }
        }
        if (found==true) 
        {
            graph.addEdge(bestConnection.u,bestConnection.v);
            final.push_back(bestConnection);
        }
    }
}



int main()
{
    int totalCity,baseCase;
    cin>>totalCity;
    cin>>baseCase;
    if(baseCase>50 || baseCase<2)
    {
        cout<<"Invalid base case. Enter numbers from 2 to 50"<<endl;
        cin>>baseCase;
    }
    vector<City>cities;
    for(int i=0;i<totalCity;i++)
    {
        City c1;
        cin>>c1.id>>c1.x>>c1.y;
        cities.push_back(c1);
    }
    if(cities.size()!=0)
    {
        mergeSortCity(cities,0,cities.size()-1);
    }
    Graph graph(totalCity+1);
    vector<Edge> finale;
    if(totalCity>0)
    {
        probSolve(0,cities.size()-1,cities,graph,baseCase,finale);
    }
    else
    {
        return 0;
    }
    float totalCost=0.00;
    for(int i=0;i<(int)finale.size();i++)
    {
        totalCost+=(float)finale[i].distance;
    }
    cout<<"Total Cost: "<<(float)totalCost<<endl;
    cout<<"Edges:"<<endl;
    for(int i=0;i<(int)finale.size();i++)
    {
        cout<<finale[i].u<<" "<<finale[i].v<<endl;
    }
    return 0;
}



