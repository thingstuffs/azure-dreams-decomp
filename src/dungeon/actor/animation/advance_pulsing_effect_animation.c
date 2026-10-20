#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad_00[0x96];
    u16 value_96;
    u8 pad_98[3];
    u8 state_9b;
    u8 pad_9c[0x16];
    u16 value_b2;
} State;

typedef struct {
    u8 pad_00[0x14];
    s32 value_14;
} Position;

typedef struct {
    u8 pad_00[0xc];
    u8 pad_0c;
    u8 pad_0d;
    u8 value_0e;
    u8 pad_0f[0xd];
    u16 value_1c;
    u16 value_1e;
} Motion;


extern s32 func_800644B8(s32 angle);
extern s32 unlink_entity_node(void *node);
extern s32 has_pending_action_or_turn_count(void *unused);
extern s32 detach_record_and_update_slot_state(void *record);

/* Animate a staged shrinking and fading effect, then release its object. */
void advance_pulsing_effect_animation(State *state, Position *position, Motion *motion, void *object) {
    u16 counter;
    u8 shade;
    s32 one = 1;

    switch (state->state_9b) {
    case 0:
        if ((has_pending_action_or_turn_count(object) << 16) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
        state->value_b2 = 4;
        state->value_96 = 0;
        state->state_9b = state->state_9b + 1;
    case 1:
        counter = state->value_96 + 1;
        state->value_96 = counter;
        motion->value_1c = motion->value_1c + func_800644B8((counter << 16) >> 11);
        motion->value_1e = motion->value_1e - func_800644B8((s16)state->value_96 << 5);
        counter = state->value_b2 - 1;
        state->value_b2 = counter;
        if ((counter << 16) <= 0) {
            state->state_9b = state->state_9b + 1;
        }
        return;
    case 2:
        counter = state->value_96 - 1;
        state->value_96 = counter;
        if ((counter << 16) <= 0) {
            state->value_96 = one;
        }
        motion->value_1c = motion->value_1c - func_800644B8((s16)state->value_96 << 5) * 2;
        motion->value_1e = motion->value_1e + func_800644B8((s16)state->value_96 << 5) * 4;
        position->value_14 = position->value_14 + (s32)0xfffe0000;
        shade = motion->value_0e - 4;
        motion->value_0e = shade;
        motion->pad_0d = shade;
        motion->pad_0c = shade;
        if ((s16)motion->value_1c <= 0) {
            g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
            detach_record_and_update_slot_state(object);
            unlink_entity_node(object);
            ((u16 *)object)[-1] = ((u16 *)object)[-1] | 0x8000;
            object_flag_block.flags = object_flag_block.flags | 0x8000;
        }
        return;
    }
}
