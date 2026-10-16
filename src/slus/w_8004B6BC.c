#include "common.h"

extern void func_8004B634(void);
extern void drainCdCommandQueue(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);

/* Calls func_8004B634 and drainCdCommandQueue, then forwards the pointers to func_800253A0 with mode 2. */
void func_8004B6BC(void *first_ptr, void *second_ptr, void *last_ptr)
{
    func_8004B634();
    drainCdCommandQueue();
    func_800253A0(first_ptr, second_ptr, 2, last_ptr);
}
