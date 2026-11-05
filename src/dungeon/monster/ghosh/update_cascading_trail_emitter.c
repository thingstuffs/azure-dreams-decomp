#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "dungeon/monster/ghosh.h"
#include "dungeon/monster/ghosh/trail_emitter.h"
#include "shared/object_node.h"

/* Decrement the record counter, calling the update on even counts and setting flags at zero. */
void update_cascading_trail_emitter(void *record_data) {
    u16 remaining;

    if (!(((GhoshTrailEmitterBody *)record_data)->remaining_ticks & 1)) {
        spawn_rising_trail_emitter();
    }
    remaining = ((GhoshTrailEmitterBody *)record_data)->remaining_ticks - 1;
    ((GhoshTrailEmitterBody *)record_data)->remaining_ticks = remaining;
    if ((remaining << 0x10) <= 0) {
        NODE_HEADER(record_data)->flags = (u16) (NODE_HEADER(record_data)->flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
