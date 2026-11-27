#include "shared/object_node.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/data.h"


typedef struct S_819598B4_1 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { u32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xE];
    u16 unk_1E;
} S_819598B4_1;   /* parameters in update_ring_effect */

typedef struct S_819598B4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_819598B4_2;   /* values in update_ring_effect */

   /* D_800E3D7C[0] in update_ring_effect */

#include "dungeon/effect/sprite_effect_count_data.h"

/* Eases a sprite into position and brightness, optionally spawns a ring, then fades and removes the
   sprite. */
void update_ring_effect(FollowingColorBlendEffectBody *state, S_819598B4_2 *values, S_819598B4_1 *parameters) {
    s16 value0A;
    s16 value3C;
    s32 byteDistance;
    s16 timerNextFirst;
    s16 timerNextSecond;
    s16 stateId;
    u16 value1E;
    s32 byteValue;
    s32 nextByteValue;
    u8 tickCountNext;
    u8 byteNext;

    sprite_effect_update_count++;
    stateId = state->stage;
    switch (stateId) {
    case 0:
        value1E = parameters->unk_1E;
        byteValue = parameters->unk_0C.at00.v;
        parameters->unk_1E = (u16)(value1E + ((s32)(0x1000 - value1E) / state->stage_ticks));
        byteDistance = 0x80 - byteValue;
        value3C = state->radius_scale;
        nextByteValue = byteValue + ((byteDistance - value3C) / state->stage_ticks);
        parameters->unk_0C.at00.v = nextByteValue;
        parameters->unk_0C.at01.v = nextByteValue;
        parameters->unk_0C.at02.v = nextByteValue;
        values->unk_02 = (s16)((u16)values->unk_02 + ((s32)(state->target_x
            - values->unk_02) / state->stage_ticks));
        values->unk_06 = (s16)((u16)values->unk_06 + ((s32)(state->target_y
            - values->unk_06) / state->stage_ticks));
        value0A = values->unk_0A;
        values->unk_0A = (values->unk_0A + ((s32)(state->target_z
            - value0A) / state->stage_ticks));
        timerNextFirst = (u16)state->stage_ticks - 1;
        state->stage_ticks = timerNextFirst;
        if ((timerNextFirst << 0x10) <= 0) {
            state->stage_ticks = 0x10;
            parameters->unk_1E = 0x1000;
            parameters->unk_0C.at00u.v = 0x00808080;
            if (state->radius_scale != 0) {
                state->stage = 2;
            } else {
                state->stage++;
            }
        }
        break;
    case 1:
        if (state->ring_index == 0) {
            if (create_linked_object_chain(state->spawn_x, state->spawn_y,
                state->spawn_z, dungeon_actor_ring_anchor->facing) == 0) {
                break;
            }
            spawn_ring_sparks(state->spawn_x, state->spawn_y,
                state->spawn_z);
        }
        state->stage_ticks = 0x10;
        state->stage++;
        break;
    case 2:
        byteNext = parameters->unk_0C.at00.v;
        byteNext -= (s32)byteNext / state->stage_ticks;
        parameters->unk_0C.at00.v = byteNext;
        parameters->unk_0C.at01.v = byteNext;
        parameters->unk_0C.at02.v = byteNext;
        timerNextSecond = (u16)state->stage_ticks - 1;
        state->stage_ticks = timerNextSecond;
        if ((timerNextSecond << 0x10) <= 0) {
            NODE_HEADER(state)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }

    if (state->ring_index != 0) {
        return;
    }
    if (state->radius_scale != 0) {
        return;
    }
    tickCountNext = ring_effect_work[9] + 1;
    ring_effect_work[9] = tickCountNext;
    if ((u32)(tickCountNext & 0xFF) >= 0x20U) {
        ring_effect_work[9] = 0;
    }
}
