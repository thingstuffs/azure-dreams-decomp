#include "common.h"

extern void func_8004B634(void);
extern void func_8003F320(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);

/* Calls func_8004B634 and func_8003F320, then forwards pointers to func_800253A0 with third argument 2. */
void func_8004B6BC(void *first_ptr, void *second_ptr, void *last_ptr)
{
    func_8004B634();
    func_8003F320();
    func_800253A0(first_ptr, second_ptr, 2, last_ptr);
}
