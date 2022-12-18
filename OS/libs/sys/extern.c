#include "syscalls.c"

extern uint16_t __tempmem__[1000];
#define appmain(name) extern int __ ## name ## main__