#include "process.h"
#include "string.h"
#include "memory.h"
#include "scheduler.h"

struct pcb procTable [NPROC];

int create_proc(char *name, void (*entry)(void)) {
    int id = -1;
    for(int i = 0; i < NPROC; i++) {
        if (procTable[i].state == TERMINATED) {
            id = i;
            break;
        }
    }
    
    if (id == -1) {
        // all processes booked
        return -1;
    }

    if (strlen(name) >= NAME_LENGTH) {
        // name too large
        return -1;
    }

    if (!(procTable[id].stack_base = alloc_stack())) {
        return -1; // 0 = no stack allocated
    }

    strcpy(procTable[id].name, name);
    procTable[id].pid = id;
    procTable[id].state = READY;
    procTable[id].entry = entry;
    enqueue(id);

    return id;
}

int get_state(int pid) {
    if (pid < 0 || pid >= NPROC) {
        // invalid pid
        return -1;
    }
    return procTable[pid].state;
}

int set_state(int pid, int state) {
    if (pid < 0 || pid >= NPROC) {
        // invalid pid
        return -1;
    }
    if (state < TERMINATED || state > CURRENT) {
        // invalid state
        return -1;
    }
    procTable[pid].state = state;
    return 0;
}

int terminate_process(int pid) {
    if (pid < 0 || pid >= NPROC) return -1;
    if (procTable[pid].state == TERMINATED) return -1;
    free_stack(procTable[pid].stack_base);
    procTable[pid].stack_base = 0;
    return set_state(pid, TERMINATED);
}

int get_current(void) {
    int id = -1;
    for(int i = 0; i < NPROC; i++) {
        if (procTable[i].state == CURRENT) {
            id = i;
            break;
        }
    }

    if (id == -1) {
        // no process is currently running
        return -1;
    }

    return id;
}