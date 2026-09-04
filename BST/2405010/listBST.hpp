#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>
/**
 * Binary Search Tree implementation using linked list structure
 * 
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value> {
private:
    /**
     * Node class for the binary search tree
     */
    class Node {
    public:
        Key key;
        Value value;
        Node* left;
        Node* right;
        
        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    size_t node_count;
    
    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    void order(Node *n)const
    {
        if(n==NULL)
        {
            return;
        }
        else
        {
            std::cout<<"("<<n->key<<":"<<n->value;
            if(n->left!=NULL && n->right==NULL)
            {
                std::cout<<" ";
                order(n->left);
            }
            else if(n->right!=NULL && n->left==NULL)
            {
                std::cout<<" () ";
                order(n->right);
            }
            else if(n->right!=NULL && n->left!=NULL)
            {
                std::cout<<" ";
                order(n->left);
                std::cout<<" ";
                order(n->right);
            }
            std::cout<<")";
        }
    }
    void inorder(Node *n)const
    {
        if(n==NULL)
        {
            return;
        }
        else
        {
            inorder(n->left);
            std::cout<<"("<<n->key <<":"<<n->value <<") ";
            inorder(n->right);
        }
    }
    void preorder(Node *n)const
    {
        if(n==NULL)
        {
            return;
        }
        else
        {
            std::cout<<"("<<n->key <<":"<<n->value <<") ";
            preorder(n->left);
            preorder(n->right);
        }
    }
    void postorder(Node *n)const
    {
        if(n==NULL)
        {
            return;
        }
        else
        {
            postorder(n->left);
            postorder(n->right);
            std::cout<<"("<<n->key <<":"<<n->value <<") ";
        }
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}
    
    /**
     * Destructor
     */
    ~ListBST() 
    {
        clear();
        this->node_count=0;
        this->root=NULL;
        // TODO: Implement destructor to free memory
    }
    
    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override {
        // TODO: Implement insertion logic
        if(find(key)==true)
        {
            return false;
        }
        else
        {
            Node *newnode=new Node(key,value);
            if(this->root==NULL)
            {
                this->root=newnode;
                this->node_count++;
                return true;
            }
            else
            {
                Node *temp=this->root;
                while(temp!=NULL)
                {
                    if(key<temp->key)
                    {
                        if(temp->left==NULL)
                        {
                            temp->left=newnode;
                            this->node_count++;
                            return true;
                            
                        }
                        temp=temp->left;
                    }
                    else 
                    {
                        if(temp->right==NULL)
                        {
                            temp->right=newnode;
                            this->node_count++;
                            return true;
                        }
                        temp=temp->right;
                    }
                }
            }
        }
        return false;
    }
    
    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override 
    {
        // TODO: Implement removal logic
        if(find(key)==false)
        {
            return false;
        }
        else
        {
            Node *temp=this->root;
            Node *parent=NULL;
            while(temp!=NULL)
            {
                if(key<temp->key)
                {
                    parent=temp;
                    temp=temp->left;
                }
                else if(key>temp->key)
                {
                    parent=temp;
                    temp=temp->right;
                }
                else
                {
                    if((temp->right==NULL) && (temp->left==NULL))
                    {
                        if(parent==NULL)
                        {
                            this->root=NULL;
                        }
                        else if(parent->left==temp)
                        {
                            parent->left=NULL;
                        }
                        else
                        {
                            parent->right=NULL;
                        }
                        delete temp;
                        this->node_count--;
                        return true;
                    }
                    else if((temp->right!=NULL)&&(temp->left==NULL))
                    {
                        if(parent==NULL)
                        {
                            this->root=temp->right;
                        }
                        else if(parent->left==temp)
                        {
                            parent->left=temp->right;
                        }
                        else
                        {
                            parent->right=temp->right;
                        }
                        delete temp;
                        this->node_count--;
                        return true;
                    }
                    else if((temp->left!=NULL)&&(temp->right==NULL))
                    {
                        if(parent==NULL)
                        {
                            this->root=temp->left;
                        }
                        else if(parent->left==temp)
                        {
                            parent->left=temp->left;
                        }
                        else
                        {
                            parent->right=temp->left;
                        }
                        delete temp;
                        this->node_count--;
                        return true;
                    }
                    else
                    {
                        Node *changed;
                        Node *changed_parent;
                        changed_parent=temp;
                        changed=temp->right;
                        while(changed->left!=NULL)
                        {
                            changed_parent=changed;
                            changed=changed->left;
                        }
                        temp->key=changed->key;
                        temp->value=changed->value;
                        if(changed_parent->left==changed)
                        {
                            changed_parent->left=changed->right;
                        }
                        else
                        {
                            changed_parent->right=changed->right;
                        }
                        delete changed;
                        this->node_count--;
                        return true;
                    }
                }
            } 
        }
        return false;
    }
    
    /**
     * Find if a key exists in the BST
     */
    bool find(Key key) const override 
    {
        int flag=0;
        if(this->root==NULL)
        {
            flag=0;
        }
        else
        {
            Node *temp=this->root;
            while(temp!=NULL)
            {
                if(key<temp->key)
                {
                    temp=temp->left;
                }
                else if(key>temp->key)
                {
                    temp=temp->right;
                }
                else
                {
                    flag=1;
                    break;
                }
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
        // TODO: Implement find logic
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override 
    {
        // TODO: Implement get logic
        if(find(key)==false)
        {
            throw std::runtime_error("Key not found");
        }
        else
        {
            Node *temp=this->root;
            while(temp!=NULL)
            {
                if(key<temp->key)
                {
                    temp=temp->left;
                }
                else if(key>temp->key)
                {
                    temp=temp->right;
                }
                else
                {
                    return temp->value;
                }
            }    
        }
        throw std::runtime_error("Key not found");
    }


    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override 
    {
        // TODO: Implement update logic
        if(find(key)==false)
        {
            throw std::runtime_error("Key not found");
        }
        else
        {
            Node *temp=this->root;
            while(temp!=NULL)
            {
                if(key<temp->key)
                {
                    temp=temp->left;
                }
                else if(key>temp->key)
                {
                    temp=temp->right;
                }
                else
                {
                    temp->value=value;
                    return;
                }
            }    
        }
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override 
    {
        while(this->root!=NULL)
        {
            remove(this->root->key);
        }
        this->root=NULL;
        this->node_count=0;
        // TODO: Implement clear logic
    }
    
    /**
     * Get the number of keys in the BST
     */
    size_t size() const override {
        return this->node_count;
        // TODO: Implement size logic
    }
    
    /**
     * Check if the BST is empty
     */
    bool empty() const override {
        if(this->node_count==0){
            return true;
        }
        else{
            return false;
        }    
        // TODO: Implement empty check logic
    }
    
    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override 
    {
        // TODO: Implement find_min logic
        if(empty()==true)
        {
            throw std::runtime_error("No Nodes found");
        }
        else
        {
            Node *temp=this->root;
            while(temp->left!=NULL)
            {
                temp=temp->left;
            }
            return temp->key;
        }
    }
    
    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override 
    {
        // TODO: Implement find_max logic
        if(empty()==true)
        {
            throw std::runtime_error("No Nodes found");
        }
        else
        {
            Node *temp=this->root;
            while(temp->right!=NULL)
            {
                temp=temp->right;
            }
            return temp->key;
        }
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override 
    {
        if(traversal_type=='I')
        {
            inorder(this->root);
        }
        else if(traversal_type=='P')
        {
            preorder(this->root);
        }
        else if(traversal_type=='O')
        {
            postorder(this->root);
        }
        else
        {
            order(this->root);
        }
        // TODO: Implement print logic    
    }    
};

#endif // LISTBST_H