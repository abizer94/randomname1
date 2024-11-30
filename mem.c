#include <stdint.h>
#include <stddef.h>
#include "mem.h"

static uint8_t memoryarea[memsize]; //array we use uint8_t because its 1 byte long and makes lifer easier 
static Node *start;

int allocate_first(){
	start = (Node*) memoryarea;
	start->flag = 0;
	start->size = memsize - node_size;
	start->next = NULLN;
	start->prev = NULLN;
}

void* findsmallestfree(Node *memarea ,size_t size){
	Node *bestblk = (Node*) NULLN;
	uint32_t bestblks = memsize + 1;
	
	Node *currblk = memarea;
	while(currblk){
		if((!currblk->flag)&&(currblk->size>=size+node_size)&&currblk->size<=bestblks){
			bestblk = currblk;
			bestblks = currblk->size;
		}
		currblk = currblk->next;
	
	}
	return bestblk;
}

void *alloc(size_t size){
	Node *bestblk = (Node*) findsmallestfree(start,size);
	
	if(bestblk != NULLN){
		bestblk->size = bestblk->size - size - node_size;
		Node *newnode = (Node*) (((uint8_t*) bestblk)+node_size + bestblk -> size);
		// makes new node at address that is bestblk size + node size from the bestblk address
		newnode->size = size;
		newnode-> flag = 1;
		newnode->next = bestblk->next;
		newnode->prev = bestblk;
		if(bestblk->next != NULLN){
			bestblk->next->prev = newnode;//if there is a node after the bestblk make the prev node 
						      //of that point to the new node we made
		}
		bestblk->next = newnode;
		return (void*) ((uint8_t *)newnode + node_size);
	}
	return NULLN;
}

void freee (void *p){
	if(p == NULLN){
		return;
	}
	Node *curr = (Node*) ((uint8_t*)p - node_size);
	
	if(curr == NULLN){
		return;
	}
	
	curr->flag = 0;
	
	curr = mergenxtchk(curr);
	mergeprevchk(curr);
}

void *mergenxtchk(Node * curr){
	Node *prevn = curr->prev;
	if(prevn != NULLN && !prevn->flag){
		prevn->size += curr->size;
		prevn->size += node_size;
		
		prevn->next = curr->next;
		if(curr->next != NULLN){
			curr->next->prev = curr;
		}
	
	}
	return curr;
}

void *mergeprevchk(Node *curr) {
    Node *prev_mem_node = curr->prev;
    if (prev_mem_node != NULLN && !prev_mem_node->flag) {
    
        prev_mem_node->size += curr->size;
        prev_mem_node->size += node_size;

        prev_mem_node->next = curr->next;
        if (curr->next != NULLN) {
            curr->next->prev = prev_mem_node;
        }
    }
}







