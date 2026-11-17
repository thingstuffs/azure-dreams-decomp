#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/monster/ghosh/trail_emitter.h"
#include "m2c_compat.h"

void spawn_jittered_trail_particle(ObjectNodeHeader *, s32, s16, s16); /* extern */

/* Advance record values, perform six updates, and flag an expired counter. */
void update_dual_variant_burst_emitter(GhoshTrailEmitterBody *record_data, ObjectPosition *offset_record, SpriteFrameState *value_record) {
    ObjectNodeHeader *base_addr;
    u16 remaining;

    base_addr = NODE_HEADER(record_data);
    offset_record->x.unsigned_parts.integer = (u16) (offset_record->x.unsigned_parts.integer + 0x10);
    value_record->angle_z = (u16) (value_record->angle_z + 0x1F4);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 1);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 1);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 1);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 2);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 2);
    spawn_jittered_trail_particle((base_addr), 0x8080, 0x1C, 2);
    remaining = record_data->remaining_ticks - 1;
    record_data->remaining_ticks = remaining;
    if ((remaining << 0x10) <= 0) {
        NODE_HEADER(record_data)->flags = NODE_HEADER(record_data)->flags | 0x8000;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
