#include "common.h"
#include "shared/dungeon_floor.h"


/* Clear the fields at offsets 0xA, 0xE, and 0x10 in all 36 entries. */
void func_800177A8(void) {
    s32 i;

    for (i = 0x23; i >= 0; i--) {
        D_800E2970[i].unk_0A = 0;
        D_800E2970[i].unk_0E = 0;
        D_800E2970[i].unk_10 = 0;
    }
}
