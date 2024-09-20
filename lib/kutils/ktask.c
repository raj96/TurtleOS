#include "kutils/ktask.h"
#include "kutils/kmem.h"

#include "addr_op.h"
#include "csr_op.h"
#include "drivers/clint.h"

#include "kutils/console.h"

#define KTASK_DELTA 100000UL

extern void store_context(ktask_node *task);
extern void load_context(ktask_node *task);

void _ktask_delete(ktask_node *);

ktask_node *ktask_list, *current_task;
static uint64_t cpu_context[32];
static uint64_t tid = 0;

void _ktask_intr_handler() {
    // Disable interrupts
    mstatus_write(mstatus_read() & (~MSTATUS_MIE));

    store_context(current_task);

    if(current_task == NULL) {
        current_task = ktask_list;
        kprintf("\ncurrent_task is null, wrapping around\n");
        goto exitHandler;
    }

    if(current_task->state == KTASK_QUEUED) {
        kprintf("current_task(%u) is newly queued, exiting handler\n", current_task->tid);
        current_task->state = KTASK_RUNNING;
        goto exitHandler;
    }
    else if(current_task->state == KTASK_COMPLETED) {
        kprintf("current_task(%u) is completed, moving to the next task\n", current_task->tid);
        ktask_node *delete_this = current_task;
        current_task = current_task->next;
        if(current_task != NULL) {
            kprintf("current_task(%u) switched to new task\n", current_task->tid);
        }
        _ktask_delete(delete_this);
    } else {
        kprintf("current_task(%u) putting the current_task in waiting queue\n", current_task->tid);
        current_task->state = KTASK_WAITING;
        current_task = current_task->next;
        if(current_task != NULL) {
            kprintf("current_task(%u) moving to the next task\n", current_task->tid);
        }
    }

    exitHandler:
    CSRW_OP("mepc", (uint64_t)ktask_run_scheduler);

    ADDR_WRITE(CLINT_MTIMECMP, ADDR_READ(CLINT_MTIME, uint64_t) + KTASK_DELTA, uint64_t);
    mstatus_write(mstatus_read() | MSTATUS_MIE  | MSTATUS_MPIE | (MSTATUS_MPP_S & ~MSTATUS_MPP_M));

    asm volatile("mret");
}

void ktask_init() {
    ktask_list = NULL;
    current_task = NULL;
}

void ktask_add(void (*task)()) {
    ktask_node *new_task = kmalloc(sizeof(ktask_node));
    new_task->next = NULL;
    new_task->tid = tid++;
    new_task->state = KTASK_QUEUED;
    // Populate `ra` (x1) with the address of the task
    new_task->reg[1] = (uint64_t)task;
    
    if(ktask_list == NULL) {
        ktask_list = new_task;
        return;
    }

    ktask_node *t_klist = ktask_list;
    while(t_klist->next != NULL) {
        t_klist = t_klist->next;
    }
    t_klist->next = new_task;
}

void _ktask_delete(ktask_node *delete_this) {
     ktask_node **cur = &ktask_list;
    while((*cur) != delete_this) {
        cur = &((*cur)->next);
    }
    ktask_node *new_next = (*cur)->next;
    kfree(*cur);
    (*cur) = new_next;
}

void ktask_run_scheduler() {
    if(current_task != NULL) {
        load_context(current_task);
    }

    asm volatile("wfi");
}