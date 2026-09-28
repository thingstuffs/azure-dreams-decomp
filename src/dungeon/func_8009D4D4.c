#include "common.h"
#include "shared/dungeon_status.h"


/* Returns whether any of the state fields at offsets 0x0A, 0x0C, and 0x10 is nonzero. */
s32 func_800A2C34(void) {
    u32 *state;

    state = ((u32 *)(&dungeonStatus));
    if (state[3] != 0 || state[4] != 0 || *(s16 *)((s8 *)state + 0xA) != 0) {
        return 1;
    }
    return 0;
}
