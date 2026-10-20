#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_801720D0_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801720D0_0;   /* arg1 in update_rising_trail_emitter */

typedef struct S_801720D0_1 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_801720D0_1;   /* arg0 in update_rising_trail_emitter; pointer addresses record offset 0x2 */


struct S_80171F30_1; void spawn_jittered_trail_particle(struct S_80171F30_1 *, s32, s16, s16); /* extern */

/* Advance the countdown, update every other tick, and flag completion when it expires. */
void update_rising_trail_emitter(void *record_data, S_801720D0_0 *state) {
    u16 ticks_left;

    state->unk_0A = (u16) (state->unk_0A - 4);
    if (!(((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_18 & 1)) {
        spawn_jittered_trail_particle(record_data - 0x20, 0x8080, 8, 0);
    }
    ticks_left = ((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_18 - 1;
    ((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_18 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801720D0_1 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
