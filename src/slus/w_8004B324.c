#include "common.h"

extern void func_8004B298(void *a0, void *a1);
extern void func_8004B2E0(void *a0, void *a1);

/* Forwards both pointers to func_8004B298, then func_8004B2E0. */
void func_8004B324(void *first_ptr, void *second_ptr)
{
    func_8004B298(first_ptr, second_ptr);
    func_8004B2E0(first_ptr, second_ptr);
}
