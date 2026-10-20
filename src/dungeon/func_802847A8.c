#include "dungeon/level/generate.h"

void clear_generation_region_entries(void) {
    s32 i;

    for (i = 0x23; i >= 0; i--) {
        D_800E2970[i].unk_0A = 0;
        D_800E2970[i].unk_0E = 0;
        D_800E2970[i].unk_10 = 0;
    }
}
