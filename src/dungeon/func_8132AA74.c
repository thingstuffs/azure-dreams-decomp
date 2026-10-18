#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80172274_0 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_80172274_0;   /* arg0 in update_cascading_trail_emitter; pointer addresses record offset 0x2 */


void spawn_rising_trail_emitter();                            /* extern */

/* Decrement the record counter, calling the update on even counts and setting flags at zero. */
void update_cascading_trail_emitter(void *record_data) {
    u16 remaining;

    if (!(((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_18 & 1)) {
        spawn_rising_trail_emitter();
    }
    remaining = ((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_18 - 1;
    ((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_18 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80172274_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
