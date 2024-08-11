#ifndef _SYSCON
#define _SYSCON

#define SYSCON_ADDR    0x100000
#define SYSCON_POWEROFF_VALUE   0x5555
#define SYSCON_REBOOT_VALUE     0x7777

void syscon_poweroff();
void syscon_reboot();

#endif