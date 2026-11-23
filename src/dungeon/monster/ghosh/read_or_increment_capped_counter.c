#include "common.h"
#include "shared/game_state.h"
#include "dungeon/monster/ghosh.h"

/* Return the stored count and optionally increment it up to 9999. */
s32 read_or_increment_capped_counter(s32 read_only) {
    register u32 high_byte;
    register u32 low_byte;
    u32 shifted;
    register u16 count;

    {
        high_byte = GAME_STATE->resident_bytes[4];
        low_byte = GAME_STATE->resident_bytes[5];
    }
    shifted = high_byte << 8;
    count = low_byte | shifted;

    if (read_only == 0) {
        if (count < 9999U) {
            if (low_byte < 255U) {
                low_byte++;
            } else {
                low_byte = 0;
                high_byte++;
            }
        }
        {
            GAME_STATE->resident_bytes[5] = low_byte;
            GAME_STATE->resident_bytes[4] = high_byte;
        }
    }

    return count;
}
