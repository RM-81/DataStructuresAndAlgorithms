#include <bits/stdc++.h>

using namespace std;


class intervalNode
{
    public:
    int id;
    int start;
    int end;
    int maxEnd;
    intervalNode *left;
    intervalNode *right;
    int height;

    intervalNode(int id, int start, int end) 
    {
        this->id=id;
        this->start=start;
        this->end=end;
        this->maxEnd=end;
        this->left=nullptr;
        this->right=nullptr;
        this->height=1;
    }
    intervalNode(int id, int start, int end, int maxEnd, intervalNode *left, intervalNode *right, int height)
    {
        this->id=id;
        this->start=start;
        this->end=end;
        this->maxEnd=maxEnd;
        this->left=left;
        this->right=right;
        this->height=height;
    }
};

class intervalSchedulerTree
{
    private:
    intervalNode *root;

    int getHeight(intervalNode *N) const
    {
        if(N==nullptr)
        {
            return 0;
        }
        else 
        {
            return N->height;
        }
    }

    int getMaxEnd(intervalNode *N)const
    {
        if(N==nullptr)
        {
            return INT_MIN;
        }
        else
        {
            return N->maxEnd;
        }
    }

    void updateNode(intervalNode *N)
    {
        if(N==nullptr)
        {
            return ;
        }
        else
        {
            N->height=1+max(getHeight(N->left),getHeight(N->right));
            N->maxEnd=max({N->end,getMaxEnd(N->left),getMaxEnd(N->right)});
        }
    }

    bool isLess(int start1, int id1, int start2, int id2) const
    {
        if(start1!=start2)
        {
            return (start1<start2);
        }
        else
        {
            return (id1<id2);
        }
    }

    intervalNode *leftRotate(intervalNode *N)
    {
        intervalNode *x= N->right;
        intervalNode *y= x->left;
        x->left=N;
        N->right=y;
        updateNode(N);
        updateNode(x);
        return x;
    }

    intervalNode *rightRotate(intervalNode *N)
    {
        intervalNode *x= N->left;
        intervalNode *y= x->right;
        x->right=N;
        N->left=y;
        updateNode(N);
        updateNode(x);
        return x;
    }

    int getBalance(intervalNode *N) const
    {
        if(N==nullptr)
        {
            return 0;
        }
        else
        {
            return getHeight(N->left)-getHeight(N->right);
        }
    }

    intervalNode *insertHelper(intervalNode *N, int id, int start, int end)
    {
        if(N==nullptr)
        {
            intervalNode *x= new intervalNode(id,start,end);
            return x;
        }
        else
        {
            if(isLess(start,id,N->start,N->id)==true)
            {
                N->left=insertHelper(N->left,id,start,end);
            }
            else
            {
                N->right=insertHelper(N->right,id,start,end);
            }
            updateNode(N);
            int balance=getBalance(N);
            if(balance>1 && getBalance(N->left)>=0) //LL
            {
                return rightRotate(N);
            }
            else if(balance<-1 && getBalance(N->right)<=0) //RR
            {
                return leftRotate(N);
            }
            else if(balance>1 && getBalance(N->left)<0) //LR
            {
                N->left=leftRotate(N->left);
                return rightRotate(N);
            }
            else if(balance<-1 && getBalance(N->right)>0) //RL
            {
                N->right=rightRotate(N->right);
                return leftRotate(N);
            }
            return N;
        }
    }

    intervalNode *minimumFinderHelper(intervalNode *N)
    {
        intervalNode *current= N; 
        while(current->left !=nullptr)
        {
            current=current->left;
        }
        return current;
    }

    intervalNode *eraseHelper(intervalNode *N, int id, int start)
    {
        if(N==nullptr)
        {
            return nullptr;
        }
        else
        {
            if(isLess(start,id, N->start, N->id)==true)
            {
                N->left=eraseHelper(N->left,id,start);
            }
            else if(isLess(N->start, N->id, start, id)==true)
            {
                N->right=eraseHelper(N->right,id,start);
            }
            else
            {
                if(N->left==nullptr && N->right==nullptr)  //no children
                {
                    delete N;
                    N=nullptr;
                }
                else if(N->left!=nullptr && N->right==nullptr) //left child
                {
                    intervalNode *temp= N->left;
                    delete N;
                    N=temp;
                }
                else if(N->left==nullptr && N->right!=nullptr) //right child
                {
                    intervalNode *temp= N->right;
                    delete N;
                    N=temp;
                }
                else if(N->left!=nullptr && N->right!=nullptr) //two child
                {
                    intervalNode *temp= minimumFinderHelper(N->right);
                    N->id=temp->id;
                    N->start=temp->start;
                    N->end=temp->end;
                    N->right=eraseHelper(N->right,temp->id,temp->start);
                }
            }
            if(N==nullptr)
            {
                return nullptr;
            }
            updateNode(N);
            int balance= getBalance(N);
            if(balance>1 && getBalance(N->left)>=0) //LL
            {
                return rightRotate(N);
            }
            else if(balance<-1 && getBalance(N->right)<=0) //RR
            {
                return leftRotate(N);
            }
            else if(balance>1 && getBalance(N->left)<0) //LR
            {
                N->left=leftRotate(N->left);
                return rightRotate(N);
            }
            else if(balance<-1 && getBalance(N->right)>0) //RL
            {
                N->right=rightRotate(N->right);
                return leftRotate(N);
            }
            return N;
        }
    }

    bool conflictHelper(intervalNode *N, int s, int e) const
    {
        if(N==nullptr)
        {
            return false;
        }
        if(N->maxEnd<=s)
        {
            return false;
        }
        if(conflictHelper(N->left,s,e)==true)
        {
            return true;
        }
        if(N->start<e && s<N->end)
        {
            return true;
        }
        if(N->start<e && conflictHelper(N->right,s,e)==true)
        {
            return true;
        }
        return false;
    }

    void overlapsHelper(intervalNode *N, int s, int e, vector<int>&events) const
    {
        if(N==nullptr)
        {
            return;
        }
        if(N->maxEnd<=s)
        {
            return;
        }
        overlapsHelper(N->left,s,e,events);
        if(N->start<e && s<N->end)
        {
            events.push_back(N->id);
        }
        if(N->start<e)
        {
            overlapsHelper(N->right,s,e,events);
        }
        return;
    }

    void atHelper(intervalNode *N, int t, vector<int>&events) const
    {
        if(N==nullptr)
        {
            return;
        }
        if(N->maxEnd<=t)
        {
            return;
        }
        atHelper(N->left,t,events);
        if(N->start<=t && t<N->end)
        {
            events.push_back(N->id);
        }
        if(N->start<=t)
        {
            atHelper(N->right,t,events);
        }
    }

    intervalNode *nextHelper(intervalNode *N, int t) const
    {
        intervalNode *current=N;
        intervalNode *temp=nullptr;
        while(current!=nullptr)
        {
            if(current->start>=t)
            {
                temp=current;
                current=current->left;
            }
            else
            {
                current=current->right;
            }
        }
        return temp;
    }

    string convertHelper(intervalNode *N) const
    {
        if(N==nullptr)
        {
            return "";
        }
        else
        {
            if(N->left==nullptr && N->right==nullptr)
            {
                return to_string(N->id);
            }
            else
            {
                return to_string(N->id)+"("+convertHelper(N->left)+","+convertHelper(N->right)+")";
            }
        }
    }

    void destroyHelper(intervalNode *N)
    {
        if(N==nullptr)
        {
            return;
        }
        destroyHelper(N->left);
        destroyHelper(N->right);
        delete N;
    }

    
    public:
    intervalSchedulerTree()
    {
        this->root=nullptr;
    }

    void add(int id, int start, int end)
    {
        root= insertHelper(root,id,start,end);
    }

    void remove (int id, int start) 
    {
        root=eraseHelper(root,id,start);
    }

    void update(int id, int oldStart, int newStart, int newEnd) 
    {
        remove(id,oldStart);
        add(id,newStart,newEnd);
    }

    bool conflict(int s,int e) const
    {
        return conflictHelper(root,s,e);
    }

    vector<int> overlaps(int s, int e) const
    {
        vector<int>events;
        overlapsHelper(root,s,e,events);
        return events;
    }

    vector<int> at(int t) const
    {
        vector<int> events;
        atHelper(root,t,events);
        return events;
    }

    intervalNode *next(int t) const
    {
        return nextHelper(root,t);
    }

    string printer() const
    {
        return convertHelper(root);
    }

    ~intervalSchedulerTree()
    {
        destroyHelper(root);
    }
};