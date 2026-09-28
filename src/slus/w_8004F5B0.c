#include "common.h"
#include "shared/game_work.h"

extern short SD_Call(int a0);
extern void func_8004F558(void *a0);

/* If global flag 0x20 is set, dispatches 0x515 and forwards the payload. */
void func_8004F5B0(void *payload)
{
    if (((int)gameWork.unk_010) & 0x20)
    {
        SD_Call(0x515);
        func_8004F558(payload);
    }
}
