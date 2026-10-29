#include "common.h"
#include "dungeon/actor.h"

/* Updates the record and clamps the byte at 0x28 to the limit at 0x29. */
void apply_actor_delta_and_cap_value(s32 unused_0, s32 unused_1, s32 unused_2, u8 *record) {
    u8 limit;

    (void)unused_0;
    (void)unused_1;
    (void)unused_2;
    apply_clamped_actor_value_delta(record);
    limit = record[0x29];
    if (limit < record[0x28]) {
        record[0x28] = limit;
    }
}
