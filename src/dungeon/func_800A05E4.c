#include "common.h"
#include "shared/dungeon_status.h"

/* Copy dungeonStatus.unk_1E into the 32-bit value D_8001362C. */
void func_800A5D44(void) {
    *(s32 *)0x8001362C = (s32) dungeonStatus.unk_1E;
}
