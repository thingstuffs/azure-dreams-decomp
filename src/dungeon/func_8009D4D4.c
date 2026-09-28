#include "common.h"
#include "shared/dungeon_status.h"


/* Returns whether any of the state fields at offsets 0x0A, 0x0C, and 0x10 is nonzero. */
s32 func_800A2C34(void) {

    if (((u32)dungeonStatus.unk_0C) != 0 || ((u32)dungeonStatus.unk_10) != 0 || dungeonStatus.unk_0A != 0) {
        return 1;
    }
    return 0;
}
