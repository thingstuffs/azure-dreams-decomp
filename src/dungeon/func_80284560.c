#include "modules/dungeon_floor_generate.h"

void dungeonClearThirtySixTableFields(void) {
    s8 *entry;
    s32 remaining;

    entry = D_800E2970;
    remaining = 0x24;
    do {
        ((floor_generate_isolated_80284560_S_80017560_0 *)entry)->unk_0C = 0;
        remaining -= 1;
        entry += 0x14;
    } while (remaining > 0);
}
