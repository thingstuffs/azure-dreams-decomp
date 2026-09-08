#include "common.h"

extern void func_8004B298(void *a0, void *a1);
extern void func_8004B2E0(void *a0, void *a1);

/* Passes both pointers through func_8004B298 and func_8004B2E0 in order. */
void func_8004B324(void *first_ptr, void *second_ptr)
{
    func_8004B298(first_ptr, second_ptr);
    func_8004B2E0(first_ptr, second_ptr);
}
