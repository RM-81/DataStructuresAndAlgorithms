#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node* next;
    struct node* prev;
} node;

typedef struct 
{
    node *head;
    node *tail;
    node *curr;
    int size;
} linkedList;

void init(linkedList* list)
{
    list->head=NULL;
    list->tail=NULL;
    list->curr=NULL;
    list->size=0;
}

void free_list(linkedList* list)
{
    while(list->head!=NULL)
    {
       node *temp=list->head->next;
       free(list->head);
       list->head=temp; 
    }
    list->tail=NULL;
    list->curr=NULL;
    list->size=0;
}

void print(linkedList* list)
{
    if(list->head==NULL)
    {
        printf("[.]\n");
        return;
    }
    node*temp=list->head;
    printf("[ ");
    while(temp!=NULL)
    {
        node*shift=temp->next;
        printf("%d",temp->element);
        if(list->curr==temp)
        {
            printf("|");
        }
        printf(" ");
        temp=shift;
    }
    printf("]\n");
}

void insert(int item, linkedList* list)
{
    node *newnode=(node*)malloc(sizeof(node));
    newnode->element=item;
    if(list->head==NULL)
    {
        list->head=newnode;
        list->tail=newnode;
        list->curr=newnode;
        newnode->prev=NULL;
        newnode->next=NULL;
    }
    else if(list->curr==list->tail)
    {
        newnode->prev=list->curr;
        newnode->next=NULL;
        list->curr->next=newnode;
        list->tail=newnode;
        list->curr=newnode; //goes to newnode
    }
    else
    {
        newnode->prev=list->curr;
        newnode->next=list->curr->next;
        newnode->next->prev=newnode;
        list->curr->next=newnode;
        list->curr=newnode; //goes to newnode
    } 
    list->size++;
}

int delete_cur(linkedList* list)
{
    if(list->curr==NULL)
    {
        return -1;
    }
    else if(list->curr==list->head)
    {
        int deleted=list->head->element;
        node *temp=list->curr;
        list->head=list->head->next;
        if(list->head!=NULL)  //other nodes after deletion
        {
            list->head->prev=NULL;
            list->curr=list->head;
        }
        else   //single node
        {
            list->tail=NULL;
            list->curr=NULL;
        }

        free(temp);
        list->size--;
        return deleted;
    }
    else if(list->curr==list->tail)
    {
        int deleted=list->curr->element;
        node *temp=list->curr;
        list->tail=list->curr->prev;
        list->tail->next=NULL;
        list->curr=list->tail;
        free(temp);
        list->size--;
        return deleted;
    }
    else
    {
        int deleted=list->curr->element;
        node *temp=list->curr;
        temp->prev->next=list->curr->next;
        temp->next->prev=list->curr->prev;
        list->curr=temp->next; //it was moved otherwise it itself was deleted
        free(temp);
        list->size--;
        return deleted;
    }
}

void append(int item, linkedList* list)
{
    if(list->head==NULL)
    {
        insert(item,list);
    }
    else
    {
        node*temp=list->curr;
        list->curr=list->tail;
        insert(item,list);
        list->curr=temp;
    }
}

int size(linkedList* list)
{
    return list->size;
}

void prev(int n, linkedList* list)
{
    if(list->head==NULL)
    {
        return;
    }
    else if(list->curr==list->head)
    {
        return;
    }
    else
    {
        while(n>0)
        {
            list->curr=list->curr->prev;
            n--;
            if(list->curr==list->head)
            {
                break;
            }
        }
    }
}

void next(int n, linkedList* list)
{
    if(list->head==NULL)
    {
        return;
    }
    else if(list->curr==list->tail)
    {
        return;
    }
    else
    {
        while(n>0)
        {
            list->curr=list->curr->next;
            n--;
            if(list->curr==list->tail)
            {
                break;
            }
        }
    } 
}

int is_present(int n, linkedList* list)
{
    int flag=0;
    node*temp=list->head;
    while(temp!=NULL)
    {
        if(temp->element==n)
        {
            flag=1;
            break;
        }
        temp=temp->next;
    }
    return flag;
}

void clear(linkedList* list)
{
    free_list(list);
}

int delete_item(int item, linkedList* list)
{
    int flag=0;
    if(list->head==NULL)
    {
        return 0;
    }
    else
    {
    node*temp=list->head;
    while(temp!=NULL)
    {
        if(temp->element==item)
        {
            if(temp==list->curr)
            {
                delete_cur(list);
                flag=1;
                break;
            }
            else
            {         
            list->curr=temp;
            delete_cur(list);
            flag=1;
            break;
            }
        }
        temp=temp->next;
    }
    return flag; 
    }
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    if(list->head==NULL||ind1>=list->size||ind2>=list->size||ind1==ind2)
    {
        return;
    }
    else if(ind1<0 ||ind2<0)
    {
        return;
    }
    else
    {
        int tracker1=0,tracker2=0;
        node*temp1=list->head;
        node*temp2=list->head;
        while(tracker1!=ind1)
        {
            temp1=temp1->next;
            tracker1++;
        }
        while(tracker2!=ind2)
        {
            temp2=temp2->next;
            tracker2++;
        }
        int temp=temp1->element;
        temp1->element=temp2->element;
        temp2->element=temp;
    }
}


int search(int item, linkedList* list)
{
    int flag=-1;
    int idx=0;
    node*temp=list->head;
    while(temp!=NULL)
    {
        if(temp->element==item)
        {
            flag=idx;
            list->curr=temp;
            break;
        }
        temp=temp->next;
        idx++;
    }
    return flag;
}

int find(int ind, linkedList* list)
{
    if(ind<0 ||ind>=list->size||list->head==NULL)
    {
        return -1;
    }
    else
    {
        int item;
        node*temp=list->head;
        int tracker=0;
        while(tracker!=ind)
        {
            temp=temp->next;
            tracker++;
        }
        item=temp->element;
        list->curr=temp;
        return item;
    }
}

int update(int ind, int value, linkedList* list)
{
    if(ind<0 ||ind>=list->size||list->head==NULL)
    {
        return -1;
    }
    else
    {
        int item;
        node*temp=list->head;
        int tracker=0;
        while(tracker!=ind)
        {
            temp=temp->next;
            tracker++;
        }
        item=temp->element;
        temp->element=value;
        list->curr=temp;
        return item;
    }
}

int trim(linkedList* list)
{
    if(list->head==NULL)
    {
        return -1;
    }
    int item=list->tail->element;
    if(list->curr==list->tail)
    {
        delete_cur(list);
    }
    else
    {
        node*temp=list->curr;
        list->curr=list->tail;
        delete_cur(list);
        list->curr=temp;
  
    }
    return item;
}

void reverse(linkedList* list)
{
    if(list->head==NULL || list->head==list->tail)
    {
        return;
    }
    else
    {
        int curr_idx=0;
        node *idx_count=list->head;
        while(idx_count!=list->curr)
        {
            idx_count=idx_count->next;
            curr_idx++;
        }
        node *swap=list->head;
        while(swap!=NULL)
        {
            node*temp=swap->next;
            swap->next=swap->prev;
            swap->prev=temp;
            swap=swap->prev; //because next and prev are swapped
        }
        node *fix=list->head;
        list->head=list->tail;
        list->tail=fix;
        node *newcurr=list->head;
        while(curr_idx>0)
        {
            newcurr=newcurr->next;
            curr_idx--;
        }
        list->curr=newcurr;
    }
}