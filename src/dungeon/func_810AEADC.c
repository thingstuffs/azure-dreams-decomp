#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_801722DC_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801722DC_0;   /* arg0 in process_interaction_and_reset_state */


s32 advance_status_timers();                     /* extern */
s32 update_actor_movement_to_tile(move_state, motion, target_tile, actor);                                /* extern */
void reduce_actor_food_meter();            /* extern */
s32 check_actor_floor_trap();                /* extern */
extern M2C_UNK D_80170E54;

/* Process an interaction and reset the object's state when the checks allow it. */
void process_interaction_and_reset_state(S_801722DC_0 *state, s32 context, s32 source, s32 target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        reduce_actor_food_meter(target, 5);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = &D_80170E54;
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
