#include "common.h"
#include "shared/dungeon_status.h"

extern s32 D_8001362C;

/* Copy dungeonStatus.unk_1E into the 32-bit value D_8001362C. */
void func_800A5D44(void) {
    D_8001362C = (s32) dungeonStatus.unk_1E;
}
