#include "kutils/kmem.h"
#include "kutils/console.h"

extern char stack_end[], mem_start[];

static char mem_bitmap[BITMAP_SIZE];
char *heap_start, *heap_end;
uint32_t *heap_alloc_info;
uint64_t num_pages;

void kmem_init() {
    kprintf("kmem_init\n");

    // Set all the pages free
    for(int i = 0; i < BITMAP_SIZE; i++) {
        mem_bitmap[i] = 0;
    }

    // reserve space for storing the number of pages allocated for each kmalloc call
    // this will be required to free the memory
    heap_alloc_info = (uint32_t *)stack_end;
    heap_end = mem_start + MEM_SIZE;
    num_pages = ((uint64_t)heap_end - (uint64_t)heap_alloc_info)/PAGE_SIZE;
    kprintf("pages: %u\n", num_pages);
    
    // Each bitmap allocation will have it's own 32 bit (4 bytes) counter for the number of pages allocated to it
    heap_start = (char *)heap_alloc_info + (num_pages * 4);

    // Allign the heap to the PAGE_SIZE
    heap_start += PAGE_SIZE - ((uint64_t)heap_start % PAGE_SIZE);
}

// kmalloc returns the void pointer to the allocated space of "size" bytes, returns NULL if could not allocate
void* kmalloc(uint64_t size) {
    uint16_t req_pages = 0;

    // Calculate the number of pages required
    if(size < PAGE_SIZE) {
        req_pages = 1;
    } else {
        req_pages = size / PAGE_SIZE;
        if(size % PAGE_SIZE != 0) {
            req_pages++;
        }
    }

    for(int i = 0; i < BITMAP_SIZE; i++) {
        if(mem_bitmap[i] == 0) {
            mem_bitmap[i] = 1;
            *(heap_alloc_info + i*4) = req_pages;
            return heap_start + i*PAGE_SIZE;
        }
    }

    return (void *)0;
}

void kfree(void *alloc_addr) {
    if((uint64_t)alloc_addr % PAGE_SIZE != 0) {
        kprintf("not on page boundary, cannot free");
        return;
    }

    uint64_t index = ((uint64_t)alloc_addr - (uint64_t)heap_start) / PAGE_SIZE;
    uint32_t num_alloc_pages = *(heap_alloc_info + index*4);

    if(mem_bitmap[index] != 1) {
        kprintf("cannot free, a free page");
        return;
    }

    while(num_alloc_pages > 0) {
        mem_bitmap[index++] = 0;
        num_alloc_pages--;
    }
}

void memfill(void *start_addr, uint64_t len, char value) {
    for(char *s = (char*)start_addr; len > 0; len--) {
        *s = value;
        s++;
    }
}