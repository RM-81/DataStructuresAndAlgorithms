#define BINOMIAL_HEAP_H

#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
    int key;
    int degree;
    Node *parent;
    Node *child;
    Node *sibling;
    
    Node()
    {
        this->key=0;
        this->degree=0;
        this->parent=nullptr;
        this->child=nullptr;
        this->sibling=nullptr;
    }

    Node(int k)
    {
        this->key=k;
        this->degree=0;
        this->parent=nullptr;
        this->child=nullptr;
        this->sibling=nullptr;
    }

};

extern unordered_map<int,Node*>nodes;

class BinomialHeap
{
    private:
    Node *head;
    int size;

    void linkTrees(Node *parent,Node *child)
    {
        child->parent=parent;
        child->sibling=parent->child;
        parent->child=child;
        parent->degree++;
    }

    Node *mergeRoots(Node *root1,Node *root2)
    {
        if(root1==nullptr)
        {
            return root2;
        }
        if(root2==nullptr)
        {
            return root1;
        }
        Node *newHead=nullptr;
        Node *tail=nullptr;
        if(root1->degree<=root2->degree)
        {
            newHead=root1;
            root1=root1->sibling;
        }
        else
        {
            newHead=root2;
            root2=root2->sibling;
        }
        tail=newHead;
        while(root1!=nullptr && root2!=nullptr)
        {
            if(root1->degree<=root2->degree)
            {
                tail->sibling=root1;
                root1=root1->sibling;
            }
            else
            {
                tail->sibling=root2;
                root2=root2->sibling;
            }
            tail=tail->sibling;
        }
        if(root1!=nullptr)
        {
            tail->sibling=root1;
        }
        else
        {
            tail->sibling=root2;
        }
        return newHead;
    }
    
    Node* unionHelper(Node *a1, Node *a2, bool verbose = false)
    {
        if(a1==nullptr)
        {
            return a2;
        }
        if(a2==nullptr)
        {
            return a1;
        }
        Node *newHead=mergeRoots(a1,a2);
        if(newHead==nullptr)
        {
            return nullptr;
        }
        Node *previous=nullptr;
        Node *current=newHead;
        Node *next=current->sibling;

        while(next!=nullptr)
        {
            if((current->degree != next->degree) || (next->sibling!=nullptr && next->sibling->degree==current->degree))
            {
                previous=current;
                current=next;
            }
            else if(current->key<=next->key)
            {
                current->sibling=next->sibling;
                if (verbose) {
                    cout << "Linking B" << current->degree << " (parent " << current->key 
                         << ") -> B" << (current->degree + 1) << " (child " << next->key << ")\n";
                }
                linkTrees(current,next);
            }
            else 
            {
                if(previous==nullptr)
                {
                    newHead=next;
                }
                else
                {
                    previous->sibling=next;
                }
                if (verbose) {
                    cout << "Linking B" << next->degree << " (parent " << next->key 
                         << ") -> B" << (next->degree + 1) << " (child " << current->key << ")\n";
                }
                linkTrees(next,current);
                current=next;
            }
            next=current->sibling;
        }
        return newHead;
    }

    void visualizeTree(Node* node, string prefix, bool isLast) 
    {
        if (!node) return;
        cout << prefix << (isLast ? "\\--" : "|--") << "[" << node->key << " : degree " << node->degree << "]\n";
        
        Node* child = node->child;
        while (child) {
            visualizeTree(child, prefix + (isLast ? "   " : "|  "), child->sibling == nullptr);
            child = child->sibling;
        }
    }

    public:
    BinomialHeap()
    {
        this->head=nullptr;
        this->size=0;
    }
    BinomialHeap(Node *head)
    {
        this->head=head;
        this->size=1;
    }
    void insert(int k)
    {
        Node *newNode=new Node(k);
        nodes[k]=newNode;
        this->head=unionHelper(this->head,newNode);
        this->size++;
    }
    void findMin()
    {
        if(this->head==nullptr)
        {
            cout<<"Minimum key not found"<<endl;
            return;
        }
        else
        {
            Node *current=this->head;
            int minimum=current->key;
            while(current!=nullptr)
            {
                if(current->key<minimum)
                {
                    minimum=current->key;
                }
                current=current->sibling;
            }
            cout<<"Find Min returned: "<<minimum<<endl;
        }
    }

    int extractMin()
    {
        if(head==nullptr)
        {
            return -1;
        }
        else
        {
            Node *minimumNode=this->head;
            Node *minimumPrevious=nullptr;
            Node *current=this->head->sibling;
            Node *previous=this->head;
            while(current!=nullptr)
            {
                if(current->key<minimumNode->key)
                {
                    minimumNode=current;
                    minimumPrevious=previous;
                }
                previous=current;
                current=current->sibling;
            }
            int minimumKey=minimumNode->key;
            if(minimumPrevious!=nullptr)
            {
                minimumPrevious->sibling=minimumNode->sibling;
            }
            else
            {
                head=minimumNode->sibling;
            }
            Node *child=minimumNode->child;
            Node *reverseChild=nullptr;
            while(child!=nullptr)
            {
                Node *nextChild=child->sibling;
                child->sibling=reverseChild;
                child->parent=nullptr;
                reverseChild=child;
                child=nextChild;
            }
            this->head=this->unionHelper(this->head,reverseChild);
            this->size--;
            nodes.erase(minimumKey);
            delete minimumNode;
            return minimumKey;
        }
    }

    void decreaseKey(int oldKey, int newKey)
    {
        if(nodes.find(oldKey)==nodes.end())
        {
            return;
        }
        else
        {
            Node *node=nodes[oldKey];
            nodes.erase(oldKey);
            node->key=newKey;
            nodes[newKey]=node;

            while(node->parent!=nullptr && node->key<node->parent->key)
            {
                int temp=node->key;
                node->key=node->parent->key;
                node->parent->key=temp;
                nodes[node->key]=node;
                nodes[node->parent->key]=node->parent;
                node=node->parent;
            }
        }
    }

    void removeKey(int key)
    {
        static int smallest=-2e9;
        decreaseKey(key,smallest);
        extractMin();
        smallest--;
    }

    void unionFunction(BinomialHeap &other, bool verbose = false)
    {
        this->head=this->unionHelper(this->head, other.head, verbose);
        this->size=this->size+other.size;
        other.head=nullptr;
        other.size=0;
    }

    void printer(int id)
    {
        cout<<"Printing Binomial Heap H"<<id<<endl;
        cout<<"Heap size: "<<this->size<<endl;
        if(this->size==0)
        {
            cout<<"Heap H"<<id<<" is empty"<<endl;
            return;
        }
        else
        {
            Node *current=this->head;
            while(current!=nullptr)
            {
                cout<<"Binomial Tree, B"<<current->degree<<endl;
                vector<vector<int>>level;
                queue<pair<Node*,int>>q;
                q.push({current,0});
                while(q.empty()!=true)
                {
                    auto nodeset=q.front();
                    q.pop();
                    Node *node=nodeset.first;
                    int depth=nodeset.second;
                    if(depth>=level.size())
                    {
                        level.push_back(vector<int>());
                    }
                    level[depth].push_back(node->key);
                    Node *child=node->child;
                    while(child!=nullptr)
                    {
                        q.push({child,depth+1});
                        child=child->sibling;
                    }
                }
                for(int i=0;i<level.size();i++)
                {
                    sort(level[i].begin(),level[i].end());
                    cout<<"Level "<<i<<":";
                    for(int k:level[i])
                    {
                        cout<<" "<<k;      
                    }
                    cout<<endl;
                }
                current=current->sibling;
            }
        }
    }

    void visualizeHeap(int h) 
    {
        cout << "=== Visualizing Heap H" << h << " ===\n";
        Node* curr = this->head;
        if (!curr) 
        {
            cout << "Heap is empty.\n";
            cout << "===========================\n";
            return;
        }
        while (curr) 
        {
            cout << "Root B" << curr->degree << " ->\n";
            visualizeTree(curr, "", true);
            curr = curr->sibling;
        }
        cout << "===========================\n";
    }

    void visualizeUnion(int h1_id, int h2_id, BinomialHeap &other)
    {
        cout << "=== Visualizing Union of H" << h1_id << " and H" << h2_id << " ===\n";
        cout << "--- Before Union H" << h1_id << " ---\n";
        this->visualizeHeap(h1_id);
        cout << "--- Before Union H" << h2_id << " ---\n";
        other.visualizeHeap(h2_id);
        
        cout << "--- Union Process ---\n";
        this->unionFunction(other, true);
        
        cout << "--- After Union H" << h1_id << " ---\n";
        this->visualizeHeap(h1_id);
        cout << "=========================================\n";
    }


    void printStatistics(int h) 
    {
        cout << "=== Structural Statistics for Heap H" << h << " ===\n";
        cout << "Total Nodes (Size): " << this->size << "\n";
        
        if (!this->head) 
        {
            cout << "Forest composition: Empty\n";
            cout << "Max Tree Depth: 0\n";
            cout << "=======================================\n";
            return;
        }

        vector<int> orders;
        int maxDepth = 0;
        Node* curr = this->head;
        
        while (curr) 
        {
            orders.push_back(curr->degree);
            if (curr->degree > maxDepth) 
            {
                maxDepth = curr->degree;
            }
            curr = curr->sibling;
        }

        cout << "Binomial Trees Present (Orders): ";
        for (size_t i = 0; i < orders.size(); i++) 
        {
            cout << "B" << orders[i] << (i + 1 < orders.size() ? ", " : "");
        }
        cout << "\n";
        cout << "Max Tree Order / Depth: B" << maxDepth << " (Height: " << maxDepth << ")\n";
        cout << "=======================================\n";
    }
};


