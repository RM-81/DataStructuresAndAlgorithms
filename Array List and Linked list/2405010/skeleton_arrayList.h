#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    int size;
    int capacity;
    int curr;
} arrayList;

void init(arrayList* list)
{
    list->size=0;
    list->capacity=2;
    list->curr=0;
    list->array=(int*)malloc(list->capacity*sizeof(int));
    if(list->array==NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

void free_list(arrayList* list)
{
    free(list->array);
    list->array=NULL;
    list->size=0;
    list->capacity=2;
}

void increase_capacity(arrayList* list)
{
    int old_cap=list->capacity;
    int new_cap=2*old_cap;
    int *temp=(int*)realloc(list->array,new_cap*sizeof(int));
    if(temp==NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->array=temp;
    list->capacity=new_cap;
    printf("Capacity increased from %d to %d\n", old_cap, new_cap);
}

void decrease_capacity(arrayList* list)
{
    if(list->capacity<=2){
        return; 
    }
    else if(list->size > list->capacity / 4){
        return; 
    }
    else
    {
    int old_cap=list->capacity;
    int new_cap=old_cap/2;
    int *temp=(int*)realloc(list->array,new_cap*sizeof(int));
    if(temp==NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->array=temp;
    list->capacity=new_cap;
    printf("Capacity decreased from %d to %d\n", old_cap, new_cap);
    }
}

void print(arrayList* list)
{
    if(list->size==0)
    {
        printf("[.]\n");
        return;
    }
    else
    {
        printf("[ ");
        for(int i=0;i<list->size;i++)
        {
            printf("%d",list->array[i]);
            if(i==list->curr)
            {
                printf("|");
            }
            printf(" ");
        }
        printf("]\n");
    }
}

void insert(int item, arrayList* list)
{
    if((2*(list->size+1))>list->capacity)
    {
        increase_capacity(list);
    }
    if(list->size==0)
    {
        list->array[0]=item;
        list->curr=0;
    }
    else
    {
    for(int i=list->size;i>list->curr+1;i--)
    {
        list->array[i]=list->array[i-1];
    }
    list->array[list->curr+1]=item;
    list->curr++;
    }
    list->size++;
}

int delete_cur(arrayList* list)
{
    if(list->size==0)
    {
        return -1;
    }
    else
    {
        if((4*(list->size-1))<list->capacity)
        {
            decrease_capacity(list);
        }
        int deleted=list->array[list->curr];
        for(int i=list->curr;i<list->size-1;i++)
        {
            list->array[i]=list->array[i+1];
        }
        if(list->curr>=list->size-1 && list->size>1)  //edge case of last cursor
        {
            list->curr--;
        }
        list->size--;
        return deleted;
    }
}

void append(int item, arrayList* list)
{
    if((2*(list->size+1))>list->capacity)
    {
        increase_capacity(list);
    }
    list->size++;
    list->array[list->size-1]=item;
}

int size(arrayList* list)
{
    return list->size;
}

void prev(int n, arrayList* list)
{
    if((list->curr-n)<0)
    {
        list->curr=0;
    }
    else
    {
        list->curr=list->curr-n;
    }
}

void next(int n, arrayList* list)
{
    if((list->curr+n)>list->size-1)
    {
        list->curr=list->size-1;
    }
    else
    {
        list->curr=list->curr+n;
    }
}

int is_present(int n, arrayList* list)
{
    int flag=0;
    for(int i=0;i<list->size;i++)
    {
        if(n==list->array[i])
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void clear(arrayList* list)
{
    list->size=0;
    list->capacity=2;
    list->curr=0;
    list->array=(int*)realloc(list->array,list->capacity*sizeof(int));
}

int delete_item(int item, arrayList* list)
{
    int curr;
    int flag=0;
    for(int i=0;i<list->size;i++)
    {
        if(item==list->array[i])
        {
           curr=i;
           flag=1;
           break;   
        }
    }
    if(flag==1)
    {
        for(int i=curr;i<list->size-1;i++)
        {
            list->array[i]=list->array[i+1];
            list->curr=curr;
        }
        list->size--;
        if((4*(list->size))<list->capacity)
        {
            decrease_capacity(list);
        }
        if(list->curr>list->size)
        {
            list->curr=list->size;
        }
        return 1;    
    }
    else
    {
        return 0;
    }    
}

void swap_ind(int ind1, int ind2, arrayList* list)
{
    if(ind1>=0 && ind1<list->size && ind2>=0 && ind2<list->size)
    {
        int temp=list->array[ind1];
        list->array[ind1]=list->array[ind2];
        list->array[ind2]=temp;
    }
    else
    {
        return;
    }   
}

int search(int item, arrayList* list)
{
    int idx;
    int flag=0;
    for(int i=0;i<list->size;i++)
    {
        if(item==list->array[i])
        {
            idx=i;
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        list->curr=idx;
        return idx;
    }
    else
    {
        return -1;
    }
}

int find(int ind, arrayList* list)
{
    int num;
    if(ind>=0 && ind<list->size)
    {
        num=list->array[ind];
        list->curr=ind;
        return num;
    }
    else
    {
        return -1;
    }
}

int update(int ind, int value, arrayList* list)
{
    int num;
    if(ind>=0 && ind<list->size)
    {
        num=list->array[ind];
        list->array[ind]=value; 
        list->curr=ind;
        return num;
    }
    else
    {
        return -1;
    }
}

int trim(arrayList* list)
{
    int last;
    if(list->size==0)
    {
        return -1;
    }
    else
    {
        last=list->array[list->size-1];
        list->size--;
        if((4*(list->size))<list->capacity)
        {
            decrease_capacity(list);
        }
        if((list->curr>=(list->size))&& list->size>0)
        {
            list->curr--;
        }
        return last;
    }
}

void reverse(arrayList* list)
{
    int temp;
    for(int i=0;i<(list->size)/2;i++)
    {
        temp=list->array[i];
        list->array[i]=list->array[list->size-i-1];
        list->array[list->size-i-1]=temp;
    }
}
