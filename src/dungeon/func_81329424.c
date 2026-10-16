#include "common.h"
#include "shared/dungeon_floor.h"


/* Sets flag 0x40 in D_800E296C[0]. */
void dungeonSetBossEffectFlag(void) {
    D_800E296C = (s32)(D_800E296C | 0x40);
}
