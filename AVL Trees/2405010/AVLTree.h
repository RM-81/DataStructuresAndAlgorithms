#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Node{
    public:
    T key;
    Node *left;
    Node *right;
    int height;

    Node(const T &key) 
    {
        this->key=key;
        this->left=nullptr;
        this->right=nullptr;
        this->height=1;
    }
    Node(const T &key, Node *left, Node *right, int height)
    {
        this->key=key;
        this->left=left;
        this->right=right;
        this->height=height;
    }
};

template <typename T> 
class AVLTree{
    private:
    Node<T> *root;

    int getHeight(Node<T> *N) const
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

    void updateHeight(Node<T> *x)
    {
        if(x==nullptr)
        {
            return ;
        }
        else
        {
            x->height=1+max(getHeight(x->left),getHeight(x->right));
        }
    }

    Node<T> *leftRotate(Node<T> *N)
    {
        Node<T> *x= N->right;
        Node<T> *y= x->left;
        x->left=N;
        N->right=y;
        updateHeight(N);
        updateHeight(x);
        return x;
    }

    Node<T> *rightRotate(Node<T> *N)
    {
        Node<T> *x= N->left;
        Node<T> *y= x->right;
        x->right=N;
        N->left=y;
        updateHeight(N);
        updateHeight(x);
        return x;
    }

    int getBalance(Node<T> *N) const
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

    Node<T> *insertHelper(Node<T> *N, T key, bool &checker)
    {
        if(N==nullptr)
        {
            Node<T> *x= new Node<T>(key);
            checker=true;
            return x;
        }
        else
        {
            if(key<N->key)
            {
                N->left=insertHelper(N->left,key,checker);
            }
            else if(key>N->key)
            {
                N->right=insertHelper(N->right,key,checker);
            }
            else
            {
                checker=false;
                return N;
            }
            updateHeight(N);
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

    Node <T> *minimumFinderHelper(Node <T> *N)
    {
        Node<T> *current= N;
        while(current->left !=nullptr)
        {
            current=current->left;
        }
        return current;
    }

    Node<T> *eraseHelper(Node<T> *N, T key, bool &checker)
    {
        if(N==nullptr)
        {
            checker=false;
            return nullptr;
        }
        else
        {
            if(key<N->key)
            {
                N->left=eraseHelper(N->left,key,checker);
            }
            else if(key>N->key)
            {
                N->right=eraseHelper(N->right,key,checker);
            }
            else
            {
                checker=true;
                if(N->left==nullptr && N->right==nullptr)  //no children
                {
                    delete N;
                    N=nullptr;
                }
                else if(N->left!=nullptr && N->right==nullptr) //left child
                {
                    Node <T> *temp= N->left;
                    delete N;
                    N=temp;
                }
                else if(N->left==nullptr && N->right!=nullptr) //right child
                {
                    Node <T> *temp= N->right;
                    delete N;
                    N=temp;
                }
                else if(N->left!=nullptr && N->right!=nullptr) //two child
                {
                    Node <T> *temp= minimumFinderHelper(N->right);
                    N->key=temp->key;
                    N->right=eraseHelper(N->right,temp->key,checker);
                }
            }
            if(N==nullptr)
            {
                return nullptr;
            }
            updateHeight(N);
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

    bool findHelper(Node<T> *N, const T &key) const
    {
        if(N == nullptr)
        {
            return false;
        }
        else
        {
            if(key<N->key)
            {
                return findHelper(N->left,key);
            }
            else if(key>N->key)
            {
                return findHelper(N->right,key);
            }
            else
            {
                return true;
            }
        }
    }

    void traverseHelper(Node <T> *N, vector <T> &order) const
    {
        if(N==nullptr)
        {
            return;
        }
        traverseHelper(N->left,order);
        order.push_back(N->key);
        traverseHelper(N->right,order);
    }

    string convertHelper(Node<T> *N) const
    {
        if(N==nullptr)
        {
            return "";
        }
        else
        {
            if(N->left==nullptr && N->right==nullptr)
            {
                return to_string(N->key);
            }
            else
            {
                return to_string(N->key)+"("+convertHelper(N->left)+","+convertHelper(N->right)+")";
            }
        }
    }

    void destroyHelper(Node<T> *N)
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
    AVLTree()
    {
        this->root=nullptr;
    }

    bool insert(const T &key)
    {
        bool inserted=false;
        root= insertHelper(root,key,inserted);
        return inserted;
    }

    bool erase (const T &key)
    {
        bool deleted=false;
        root=eraseHelper(root,key,deleted);
        return deleted;
    }

    bool find (const T &key) const
    {
        return findHelper(root,key);
    }

    vector<T> traverse () const
    {
        vector<T> order;
        traverseHelper(root,order);
        return order;
    }

    string printer() const
    {
        return convertHelper(root);
    }

    ~AVLTree()
    {
        destroyHelper(root);
    }
};