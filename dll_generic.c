//
// Created by danil on 16/08/2020.
//
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include "dll_generic.h"

typedef struct dll_node Node;
struct dll_node {
    T value;
    Node* previous;
    Node* next;
};

// constructor
Node* newNode(T val, Node* prev, Node* next) {
    Node* node = malloc(sizeof(Node));

    node->value = val;
    node->previous = prev;
    node->next = next;

    return node;
}

// destructor
void freeNode(Node* node) {
    if(node == NULL) return;

    // cracks when the same value is inserted at different positions
//    free(node->value);
    free(node);
}

struct dll {
    Node* first;
    Node* last;
    size_t length;
};

// constructor
List* newList() {
    List* list = malloc(sizeof(List));

    list->last = newNode(NULL, NULL, NULL);

    // empty list, range [first, last)
    list->first = list->last;

    list->length = 0;

    return list;
}

// destructor
void freeList(List* list) {
    if(list == NULL) return;

    clear(list);

    freeNode(list->last);
    free(list);
}

// Capacity
int empty(List* list) {
    return size(list) == 0;
}
size_t size(List* list) {
    assert(list != NULL);

    return list->length;
}
// end Capacity

// Element Access
T front(List* list) {
    assert(list != NULL);

    return list->first->value;
}
T back(List* list) {
    assert(list != NULL);

    // empty list
    if(list->first == list->last) return NULL;

    // at least will be a valid list->first (safe to dereference)
    return list->last->previous->value;
}
// end Element Access

// Modifiers
void assign(List* list, size_t n, T val) {
    for(size_t i = 0; i < n; ++i) {
        push_front(list, val);
    }
}

void push_front(List* list, T val) {
    assert(list != NULL);

    Node* node = newNode(val, NULL, list->first);

    // at most list->first equals list->last (i.e. is safe to dereference)
    list->first->previous = node;

    list->first = node;

    ++(list->length);
}
void push_back(List* list, T val) {
    assert(list != NULL);

    Node* node = newNode(val, list->last->previous, list->last);

    if(list->last->previous != NULL) list->last->previous->next = node;
    // empty list
    else list->first = node;

    list->last->previous = node;

    ++(list->length);
}

void pop_front(List* list) {
    assert(list != NULL);

    // empty list
    if(list->first == list->last) return;

    Node* popped = list->first;

    // at most popped->next equals list->last (safe to dereference)
    popped->next->previous = NULL;

    list->first = popped->next;

    freeNode(popped);

    --(list->length);
}
void pop_back(List* list) {
    assert(list != NULL);

    // empty list
    if(list->first == list->last) return;

    Node* popped = list->last->previous;

    // popped is at least the list->first (safe to dereference)
    if(popped->previous != NULL) popped->previous->next = list->last;
    // 1-element list
    else list->first = list->last;

    list->last->previous = popped->previous;

    freeNode(popped);

    --(list->length);
}

void swap(List* a, List* b) {
    assert(a != NULL);
    assert(b != NULL);

    Node* a_first = a->first;
    Node* a_last = a->last;
    size_t a_length = a->length;

    a->first = b->first;
    a->last = b->last;
    a->length = b->length;

    b->first = a_first;
    b->last = a_last;
    b->length = a_length;
}

void resize(List* list, size_t n, T val) {
    while(size(list) > n) {
        pop_back(list);
    }

    while(size(list) < n) {
        push_back(list, val);
    }
}

void clear(List* list) {
    resize(list, 0, NULL);
}
// end Modifiers

// Operations
//void delete(List* list, T val, Comp cmp) {
//    Node* current = list->first;
//    Node* last = list->last;
//    while(current != last) {
//        Node* next = current->next;
//
//        if(cmp(current->value, val) == 0) erase(list, current);
//
//        current = next;
//    }
//}
//void delete_if(List* list, Pred pred) {
//
//}

//void unique(List*, BiPred);
//void merge(List*, Comp);
//void sort(List*, Comp);

void reverse(List* list) {
    Node* current = list->first;
    Node* last = list->last;

    while(current != last) {
        push_front(list, current->value);

        Node* prev = current->previous;
        Node* next = current->next;

        // due to insertion, previous node always present (safe to dereference)
        prev->next = next;

        // next is at most list->last (safe to dereference)
        next->previous = prev;

        freeNode(current);

        --(list->length);

        current = next;
    }
}

// end Operations

// Testing
int* newInt(int val) {
    int* ptr = malloc(sizeof(int));
    *ptr = val;

    return ptr;
}

//int intcmp(const int* a, const int* b) {
//    assert(a != NULL && b != NULL);
//
//    // same variable
//    if(a == b) return 0;
//
//    // compare real values
//    return *a - *b;
//}

void testList() {
    puts("test generic list");

    List* list = newList();

    int len = 5;

    // Insertions
    assign(list, len, newInt(21));
    assert(list->length == len);

    List* otherList = newList();

    for(int i = 0; i < len; ++i) {
        push_front(otherList, newInt(i + 1));
        int* first_val = front(otherList);

        printf("pushed front: %d\n", *first_val);
    }
    reverse(otherList);

    swap(list, otherList);
//    assert(size(list) == size(otherList));

    for(int i = 0; i < len; ++i) {
        push_back(list, newInt(i + 1));
        int* last_val = back(list);

        printf("pushed back: %d\n", *last_val);
    }
    assert(list->length == 2*len);
    // end Insertions

    while(size(list) > len) {
        int* last_val = back(list);
        pop_back(list);

        printf("popped back: %d\n", *last_val);
    }
    assert(size(list) == len);

    while(!empty(list)) {
        int* first_val = front(list);
        pop_front(list);

        printf("popped front: %d\n", *first_val);
    }
    assert(size(list) == 0);

    clear(otherList);
    assert(size(otherList) == 0);

    freeList(otherList);
    freeList(list);

    puts("end test generic list");
}
// end Testing



