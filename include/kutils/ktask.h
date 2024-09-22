#ifndef _KTASK_H
#define _KTASK_H

#include <stdint.h>

typedef enum {
    KTASK_QUEUED,
    KTASK_RUNNING,
    KTASK_WAITING,
    KTASK_COMPLETED
} ktask_state;

typedef struct _ktask_node{
    uint64_t reg[32];
    uint64_t pc;
    ktask_state state;
    uint64_t tid;
    struct _ktask_node *next;
} ktask_node;

void ktask_init();
void ktask_add(void(*task)());
void ktask_run_scheduler();

#endif