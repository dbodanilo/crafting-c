//
// Created by danil on 16/08/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "dll_str.h"

typedef struct dll_str_node StringNode;
struct dll_str_node {
    String value;
    StringNode* previous;
    StringNode* next;
};

struct dll_str {
    StringNode* first;
    StringNode* last;
    size_t length;
};

// String
String newString(size_t len) {
    return malloc((len + 1)*sizeof(char));
}

String stringFromInt(int val) {
    size_t len = snprintf(NULL, 0, "%d", val);

    String s = newString(len);
    sprintf(s, "%d", val);

    return s;
}

String stringFromChar(char val) {
    size_t len = 2;

    String s = newString(len);
    sprintf(s, "%c", val);

    return s;
}
// end String

// StringNode
StringNode* newStringNode(String val, StringNode* prev, StringNode* next) {
    StringNode* node = malloc(sizeof(StringNode));

    node->value = val;
    node->previous = prev;
    node->next = next;

    return node;
}

void freeStringNode(StringNode* node) {
    if(node == NULL) return;

    // cracks if same string pointer is shared between nodes
//    free(node->value);
    free(node);
}
// end StringNode

// Strings
Strings* newStringList() {
    Strings* list = malloc(sizeof(Strings));

    list->last = newStringNode(NULL, NULL, NULL);

    list->first = list->last;

    list->length = 0;

    return list;
}

void freeStringList(Strings* list) {
    if(list == NULL) return;

    while(list->length > 0) pop_front_string(list);

    freeStringNode(list->last);

    free(list);
}

// insertion
void push_front_string(Strings* list, String val) {
    assert(list != NULL);

    StringNode* prev = NULL;
    StringNode* next = list->first;

    StringNode* node = newStringNode(val, prev, next);

    next->previous = node;

    list->first = node;

    ++(list->length);
}
void push_back_string(Strings* list, String val) {
    assert(list != NULL);

    StringNode* prev = list->last->previous;
    StringNode* next = list->last;

    StringNode* node = newStringNode(val, prev, next);

    next->previous = node;

    if(prev != NULL) prev->next = node;
    // back is also front
    else list->first = node;

    ++(list->length);
}
// end insertion

// search
String front_string(Strings* list) {
    assert(list != NULL);

    return list->first->value;
}
String back_string(Strings* list) {
    assert(list != NULL);

    StringNode* last_valid = list->last->previous;

    return last_valid != NULL ? last_valid->value : NULL;
}
// end search

// deletion
void pop_front_string(Strings* list) {
    assert(list != NULL);

    // empty list
    if(list->first == list->last) return;

    StringNode* newFirst = list->first->next;

    // at most will be list->last (safe to dereference)
    newFirst->previous = NULL;

    list->first = newFirst;

    --(list->length);
}
void pop_back_string(Strings* list) {
    assert(list != NULL);

    // nothing to pop
    if(list->last->previous == NULL) return;

    StringNode* newLast = list->last->previous->previous;

    list->last->previous = newLast;

    if(newLast != NULL) newLast->next = list->last;
    // now empty list
    else list->first = list->last;

    --(list->length);
}
// end deletion
// end Strings

// tests
void testStringList() {
    puts("test string list");

    Strings* list = newStringList();

    int len = 10;

    // insertions
    // front
    for(int i = 0; i < len/2; ++i) {
        String s = stringFromChar('a' + i);

        push_front_string(list, s);

        // search
        String first = front_string(list);
        assert(strcmp(first, s) == 0);

        printf("pushed front: %s\n", first);
    }
    // back
    for(int i = len/2; i < len; ++i) {
        String s = stringFromChar('Z' - i);

        push_back_string(list, s);

        // search
        String last = back_string(list);
        assert(strcmp(last, s) == 0);

        printf("pushed back: %s\n", last);
    }
    assert(list->length == len);

    // deletions
    // back
    while(list->length > len/2) {
        String val = back_string(list);
        pop_back_string(list);

        printf("popped back: %s\n", val);
    }
    // front
    while(list->length > 0) {
        String val = front_string(list);
        pop_front_string(list);

        printf("popped front: %s\n", val);
    }
    assert(list->length == 0);

    freeStringList(list);

    puts("end test string list");
}
// end tests
