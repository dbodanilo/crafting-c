//
// Created by danil on 16/08/2020.
//

#ifndef CRAFTING_C_DLL_GENERIC_H
#define CRAFTING_C_DLL_GENERIC_H

typedef void* T;
//typedef int (*Comp)(T, T);
//typedef int (*Pred)(T);
//typedef int (*BiPred)(T, T);

typedef struct dll List;
List* newList();
void freeList(List*);

void testList();

//// Iterators
//Node* begin(List*);
//Node* end(List*);
//// not sure if these can be achieved in C
//// Node* rbegin(List*);
//// Node* rend(List*);
// end Iterators

// Capacity
int empty(List*);
size_t size(List*);
// max_size(List* list);
// end Capacity

// Element Access
T front(List*);
T back(List*);
// end Element Access

// Modifiers
void assign(List*, size_t, T);
void push_front(List*, T);
void pop_front(List*);
void push_back(List*, T);
void pop_back(List*);
//Node* insert(List*, Node*, T);
//// no overloading :(
//Node* insert(List*, Node*, size_t, T);
//Node* insert(List*, Node*, Node*, Node*);
//Node* erase(List*, Node*);
//Node* erase(List*, Node*, Node*);
void swap(List*, List*);
void resize(List*, size_t, T);
void clear(List*);
// end Modifiers

// Operations
//void splice_single(List*, Node*, List*, Node*);
//void splice(List*, Node*, List*, Node*, Node*);

//// name conflict with stdio.h function
////void remove(List*, T);
//void delete(List*, T, Comp);
////remove_if();
//void delete_if(List*, Pred);

//void unique(List*, BiPred);
//void merge(List*, Comp);
//void sort(List*, Comp);
void reverse(List*);
// end Operations

#endif //CRAFTING_C_DLL_GENERIC_H
