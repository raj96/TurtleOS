// Bitmap allocator

#include "kutils/kmem.h"
#include "kutils/console.h"

extern char stack_end[], mem_start[];

static uint8_t mem_bitmap[BITMAP_SIZE];
char *heap_start, *heap_end;
uint32_t *heap_alloc_info;
uint64_t num_pages;

uint8_t _bitmap_get_bit(uint64_t bit) {
    return (mem_bitmap[bit/8] >> (7 - (bit % 8))) & 1;
}

void _bitmap_set_bit(uint64_t bit) {
    uint8_t mask = 1 << (7 - (bit % 8));

    mem_bitmap[bit/8] |= mask;
}

void _bitmap_clear_bit(uint64_t bit) {
    uint8_t mask = 1 << (7 - (bit % 8));

    mem_bitmap[bit/8] &= (~mask);
}

// returns the bit number where the smallest continuous block (scb) of pages begin
// it searches for the smallest continuous block of pages where `req_pages` can fit
// this helps in slowing fragmentation
int64_t _bitmap_get_scb(uint32_t req_pages) {
    uint64_t scb_len = num_pages+1, t_scb_len;
    int64_t scb_index = -1, t_scb_index = 0;

    for(uint64_t i = 0; i < num_pages; i++) {
        if(_bitmap_get_bit(i) == 1) { continue; }
        else {
            t_scb_index = i;
            t_scb_len = 0;
            while(i < num_pages && _bitmap_get_bit(i++) == 0) {
                t_scb_len++;
            }
            kprintf("t_scb_len: %d\treq_pages: %d\tscb_len: %d\n", t_scb_len, req_pages, scb_len);
            if(t_scb_len >= req_pages && t_scb_len < scb_len) {
                scb_len = t_scb_len;
                scb_index = t_scb_index;
            }
        }
    }

    return scb_index;
}

// TODO: defragmentation routine
void _kmem_defragment() {

}

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
    
    // Each bitmap allocation will have it's own 32 bit (4 bytes) counter for the number of pages allocated to it
    heap_start = (char *)heap_alloc_info + (num_pages * 4);

    // Allign the heap to the PAGE_SIZE
    heap_start += PAGE_SIZE - ((uint64_t)heap_start % PAGE_SIZE);
}

// kmalloc returns the void pointer to the allocated space of "size" bytes, returns NULL if could not allocate
void* kmalloc(uint64_t size) {
    uint32_t req_pages = 0;

    // Calculate the number of pages required
    if(size < PAGE_SIZE) {
        req_pages = 1;
    } else {
        req_pages = size / PAGE_SIZE;
        if(size % PAGE_SIZE != 0) {
            req_pages++;
        }
    }

    uint64_t scb = _bitmap_get_scb(req_pages);
    if(scb == -1) {
        // TODO: check if defragmentation is needed, that is, space is available but is not continuous
        return (void *)0;
    }

    *(heap_alloc_info + scb*4) = req_pages;
    while(req_pages > 0) {
        _bitmap_set_bit(scb + (req_pages-1));
        req_pages--;
    }
    return heap_start + scb*PAGE_SIZE;
}

void kfree(void *alloc_addr) {
    if((uint64_t)alloc_addr % PAGE_SIZE != 0) {
        kprintf("not on page boundary, cannot free");
        return;
    }

    uint64_t index = ((uint64_t)alloc_addr - (uint64_t)heap_start) / PAGE_SIZE;
    uint32_t num_alloc_pages = *(heap_alloc_info + index*4);

    if(_bitmap_get_bit(index) != 1) {
        kprintf("cannot free, a free page");
        return;
    }

    while(num_alloc_pages > 0) {
        _bitmap_clear_bit(index++);
        num_alloc_pages--;
    }
}

void memfill(void *start_addr, uint64_t len, char value) {
    for(char *s = (char*)start_addr; len > 0; len--) {
        *s = value;
        s++;
    }
}