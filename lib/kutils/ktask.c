#include "kutils/ktask.h"
#include "kutils/kmem.h"

#include "addr_op.h"
#include "csr_op.h"
#include "drivers/clint.h"

#include "kutils/console.h"

extern void switch_regs(volatile uint64_t store_here[32], volatile uint64_t load_from_here[32]);

ktask_node *ktask_list;
static uint64_t tid = 0;
volatile ktask_node *current_task, *old_task;

void _ktask_intr_handler() {
    mstatus_write(mstatus_read() & (~MSTATUS_MIE));

    old_task = current_task;
    current_task = current_task->next;

    if(current_task == NULL) {
        current_task = ktask_list;
    }

    if(current_task == NULL) {
        ADDR_WRITE(CLINT_MTIMECMP, ADDR_READ(CLINT_MTIME, uint64_t) + 500000UL, uint64_t);
        mstatus_write(mstatus_read() | MSTATUS_MIE);
        asm volatile("wfi");
    }

    current_task->state = KTASK_RUNNING;
    if(old_task->state == KTASK_STOPPED) {
        ktask_node *t_klist = ktask_list;
        while(t_klist->next != old_task) {
            t_klist = t_klist->next;
        }
        t_klist->next = NULL;
    } else {
        old_task->state = KTASK_WAITING;
    }
    
    ADDR_WRITE(CLINT_MTIMECMP, ADDR_READ(CLINT_MTIME, uint64_t) + 500000UL, uint64_t);
    mstatus_write(mstatus_read() | MSTATUS_MIE);

    switch_regs(old_task->reg, current_task->reg);
    current_task->state = KTASK_STOPPED;
}

void ktask_init() {
    ktask_list = NULL;

    current_task = (ktask_node *)kmalloc(sizeof(ktask_node));
    old_task = (ktask_node *)kmalloc(sizeof(ktask_node));
}

void ktask_add(void (*task)()) {
    ktask_node *new_task = kmalloc(sizeof(ktask_node));
    new_task->next = NULL;
    new_task->tid = tid++;
    new_task->state = KTASK_QUEUED;
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

void ktask_run_scheduler() {
    asm volatile("wfi");
}