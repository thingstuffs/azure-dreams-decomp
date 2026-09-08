#include "common.h"

extern void func_8004B1A4(u16 *a0);

/* Call func_8004B1A4 for each entry in a null-terminated list of u16 pointers. */
void func_8004B248(u16 **entries)
{
    while (*entries != 0) {
        func_8004B1A4(*entries);
        entries++;
    }
}
