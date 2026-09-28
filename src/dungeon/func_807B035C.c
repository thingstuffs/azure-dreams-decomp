#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"

extern void *D_800FBE1C;
extern s8 D_800DCF4D;

/* Set the current entity state to one, reset the global status, increment the counter, and set flag 8. */
void func_807B035C(void) {
    *((s8 *)D_800FBE1C + 0xD8) = 1;
    D_800DCF4D = -1;
    dungeonStatus.unk_0A++;
    D_80013714 |= 8;
}
