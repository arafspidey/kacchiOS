#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

int alloc_stack(void); // return stack_base
void free_stack(int stack_base);

#endif