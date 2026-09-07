#include "common.h"

/* Checks bit 0x20 of the global flags word D_80083170; if set, forwards a
 * fixed flag value (0x515) to func_80053DA8 and then forwards this
 * function's own pointer argument to func_8004F558. */

extern int D_80083170[3]; /* size > 8 to force %hi/%lo access (see learnings) */
extern short func_80053DA8(int a0);
extern void func_8004F558(void *a0);

void func_8004F5B0(void *a0)
{
    if (D_80083170[0] & 0x20)
    {
        func_80053DA8(0x515);
        func_8004F558(a0);
    }
}
