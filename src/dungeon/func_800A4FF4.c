#include "common.h"

extern void apply_clamped_actor_value_delta(void *arg);

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
