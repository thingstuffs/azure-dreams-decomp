#include "common.h"

extern int D_80083170[3]; /* size > 8 to force %hi/%lo access (see learnings) */
extern short SD_Call(int a0);
extern void func_8004F558(void *a0);

/* If global flag 0x20 is set, dispatches 0x515 and forwards the payload. */
void func_8004F5B0(void *payload)
{
    if (D_80083170[0] & 0x20)
    {
        SD_Call(0x515);
        func_8004F558(payload);
    }
}
