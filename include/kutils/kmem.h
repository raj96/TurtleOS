#ifndef _KMEM_H
#define _KMEM_H

#include <stdint.h>

#define PAGE_SIZE   (2 * 1024)                      // 2KB
#define MEM_SIZE    (128 * 1024 * 1024)             // 128 MB
#define BITMAP_SIZE ((MEM_SIZE / PAGE_SIZE) / 8)    // Space will be used to store bitmap (in bytes)

#define NULL ((void *)0)

void kmem_init();
void* kmalloc(uint64_t size);
void kfree(void *allocated);

void memfill(void *start_addr, uint64_t len, char value);

#endif