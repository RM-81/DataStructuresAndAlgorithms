#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int element;
    node* next;
    node* prev;
} node;

typedef struct 
{
    // declare head, tail, cur and other variables you need
} linkedList;

void init(linkedList* list)
{
    // implement initialization
}

void free_list(linkedList* list)
{
    // implement destruction of list
}

void print(linkedList* list)
{
    // implement list printing
}

void insert(int item, linkedList* list)
{
    // implement insert function
}

int delete_cur(linkedList* list)
{
    // implement deletion of current index function
}

void append(int item, linkedList* list)
{
    // implement append function
}

int size(linkedList* list)
{
    // implement size function
}

void prev(int n, linkedList* list)
{
    // implement prev function
}

void next(int n, linkedList* list)
{
    // implement next function
}

int is_present(int n, linkedList* list)
{
    // implement presence checking function
}

void clear(linkedList* list)
{
    // implement list clearing function
}

int delete_item(int item, linkedList* list)
{
    // implement item deletion function
}

void swap_ind(int ind1, int ind2, linkedList* list)
{
    // implement swap function
}


int search(int item, linkedList* list)
{
    // implement search function
}

int find(int ind, linkedList* list)
{
    // implement find function
}

int update(int ind, int value, linkedList* list)
{
    // implement update function at metioned index position
}

int trim(linkedList* list)
{
    // implement trim function
}

void reverse(linkedList* list)
{
    // implement reverse function
}

// you can define helper functions you need