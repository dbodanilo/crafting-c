
#ifndef clox_compiler_h
#define clox_compiler_h

#include "object.h"
#include "vm.h"
#include "chunk.h"

ObjFunction* compile(const char* source, size_t len);
void markCompilerRoots();

#endif

