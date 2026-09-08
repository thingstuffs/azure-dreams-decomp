#include "common.h"

extern void func_8004B1A4(u16 *a0);

/* Flags each entry in a null-terminated pointer array. */
void func_8004B248(u16 **entries)
{
    while (*entries != 0) {
        func_8004B1A4(*entries);
        entries++;
    }
}
