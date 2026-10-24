#include "common.h"
#include "shared/dungeon_floor.h"


/* Return the indexed entry value when its condition is nonzero, or zero otherwise. */
s32 get_active_region_data(s16 entry_index) {
    s32 value;
    u8 * value_2;
    s32 value_3;

    value = 0;
    if (entry_index >= 0) {
        s8 *entry;

        value_2 = (u8 *)dungeon_rooms;
        entry = (s8 *)value_2 + entry_index * 0x14;
        value_3 = *(s16 *)(entry + 0xA);
        if (value_3 == 0) {
            return 0;
        }
        value = *(s32 *)(entry + 0x10);
    }
    return value;
}

/* MECHANISM: Frameless leaf; assigning the halfword before the literal-zero guard preserves both zero
   delay slots. */
