//
// Created by danil on 16/08/2020.
//

#ifndef CRAFTING_C_DLL_STR_H
#define CRAFTING_C_DLL_STR_H

/*
 * Get a “Hello, world!” program written and running.
 * Set up whatever Makefiles or IDE projects you need.
 * If you have a debugger, get comfortable with it.
 *
 * To get some practice with pointers,
 * define a doubly-linked list of heap-allocated strings.
 * Write functions to insert, find, and delete items from it.
 * Test them.
 */

typedef char* String;

typedef struct dll_str Strings;

Strings* newStringList();
void freeStringList(Strings*);

void push_front_string(Strings*, String);
String front_string(Strings*);
void pop_front_string(Strings*);

void push_back_string(Strings*, String);
String back_string(Strings*);
void pop_back_string(Strings*);

void testStringList();

#endif //CRAFTING_C_DLL_STR_H
