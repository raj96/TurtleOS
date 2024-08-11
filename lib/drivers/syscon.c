#include "drivers/syscon.h"
#include "addr_op.h"

void syscon_poweroff() {
    ADDR_WRITE(SYSCON_ADDR, SYSCON_POWEROFF_VALUE, uint32_t);
}

void syscon_reboot() {
    ADDR_WRITE(SYSCON_ADDR, SYSCON_REBOOT_VALUE, uint32_t);
}