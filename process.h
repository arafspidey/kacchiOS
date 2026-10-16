#ifndef PROCESS_H
#define PROCESS_H

#define NPROC 8
#define NAME_LENGTH 16

#define TERMINATED 0
#define READY 1
#define CURRENT 2

#include "types.h"

struct pcb {
    int pid;
    int state;
    char name[NAME_LENGTH];
    void (*entry)(void);
    void *stack_base;
    uint32_t esp;
};

int create_proc(char *name, void (*entry)(void));
int get_state(int pid);
int terminate_process(int pid);
int set_state(int pid, int state);
int get_current(void);

#endif