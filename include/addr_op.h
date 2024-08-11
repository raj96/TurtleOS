#ifndef _ADDR_OP_H
#define _ADDR_OP_H

#include <stdint.h>

#define ADDR_WRITE(addr, value, type) (*(volatile type*)addr = value)   
#define ADDR_READ(addr, type) (*(volatile type*)addr)   

#endif