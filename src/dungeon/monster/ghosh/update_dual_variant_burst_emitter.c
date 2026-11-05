#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_801723D0_2 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_801723D0_2;   /* arg0 in update_dual_variant_burst_emitter; pointer addresses record offset 0x2 */


struct S_80171F30_1; void spawn_jittered_trail_particle(struct S_80171F30_1 *, s32, s16, s16); /* extern */

/* Advance record values, perform six updates, and flag an expired counter. */
void update_dual_variant_burst_emitter(void *record_data, ObjectPosition *offset_record, SpriteFrameState *value_record) {
    void * base_addr;
    u16 remaining;

    base_addr = record_data - 0x20;
    offset_record->x.unsigned_parts.integer = (u16) (offset_record->x.unsigned_parts.integer + 0x10);
    value_record->angle_z = (u16) (value_record->angle_z + 0x1F4);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 1);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 1);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 1);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 2);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 2);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 2);
    remaining = ((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_18 - 1;
    ((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_18 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_801723D0_2 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801723D0_2 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
