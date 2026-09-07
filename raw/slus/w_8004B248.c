#include "common.h"

extern void func_8004B1A4(u16 *a0);

/* Iterate over a NULL-terminated array of u16* pointers, invoking
   func_8004B1A4 on each non-null entry. */
void func_8004B248(u16 **a0)
{
    while (*a0 != 0) {
        func_8004B1A4(*a0);
        a0++;
    }
}
