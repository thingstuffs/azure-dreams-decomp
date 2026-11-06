#include "common.h"
#include "dungeon/monster/ghosh/rising_trail_emitter.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/entity.h"




struct S_80171F30_1; void spawn_jittered_trail_particle(struct S_80171F30_1 *, s32, s16, s16); /* extern */

/* Advance the countdown, update every other tick, and flag completion when it expires. */
void update_rising_trail_emitter(void *record_data, ObjectPosition *state) {
    GhoshRisingTrailEmitterBody *body = record_data;
    u16 ticks_left;

    state->z.unsigned_parts.integer = (u16) (state->z.unsigned_parts.integer - 4);
    if (!(body->remaining_ticks & 1)) {
        spawn_jittered_trail_particle(record_data - 0x20, 0x8080, 8, 0);
    }
    ticks_left = body->remaining_ticks - 1;
    body->remaining_ticks = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(body)->flags = (u16) (NODE_HEADER(body)->flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
