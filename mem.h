#pragma once
#include <stdint.h>
#include <stddef.h>

#define NULLN ((void*)0)
#define memsize 4*1024
#define node_size sizeof(Node)

typedef struct Node {
struct Node *next;
struct Node *prev;
int flag;
int size;
}Node;

void *mergeprevchk(Node *curr);
void *mergenxtchk(Node * curr);
void freee (void *p);
void *alloc(size_t size);
void* findsmallestfree(Node *memarea ,size_t size);
int allocate_first();

