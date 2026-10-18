#include "modules/trap_effects_candidate.h"
#include "common.h"

typedef struct S_800CC18C_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x13];
    u8 unk_1B;
    u8 pad_1C[0xF];
    u8 unk_2B;
} S_800CC18C_0;   /* arg0 in resolve_random_trap_outcome; pointer addresses record offset 0x18 */



extern u8 D_800E1BDA[];
extern void adjust_source_value_and_finalize();
extern s32 play_sound_if_enabled();
extern void display_fixed_item_action_message();
extern s32 generate_random_value(void);
extern s32 begin_actor_random_warp(void *, s32, s32, void *);


/* Resolve a ranged random check, apply its effects, and return the outcome. */
s32 resolve_random_trap_outcome(void *entity, s32 forwarded_1, s32 forwarded_2, s32 forwarded_3) {
    s16 roll;
    s32 random_value;
    s32 remainder;
    s16 outcome;
    s32 feedback_kind;
    s32 feedback_or_result;

    outcome = 0;
    if (D_800E3D40 == 0) {
        random_value = generate_random_value() & 0xFFFF;
        if (((s32)(((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_1B)) != 0) {
            roll = ((s32)(((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_1B));
            remainder = random_value % roll;
            roll = remainder;
        } else {
            roll = 0;
        }
    } else {
        roll = 0;
    }
    if (roll < 0x40) {
        begin_actor_random_warp(entity, ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_00,
            ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_04, entity);
        play_sound_if_enabled(0x705);
        if (D_800E3D40 != 0) {
            outcome = -1;
        }
        feedback_kind = ((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_2B == 0;
    } else {
        outcome = 1;
        feedback_kind = (((S_800CC18C_0 *)((u8 *)entity - 0x18))->unk_2B == 0) * 2;
    }
    feedback_or_result = feedback_kind;
    if (feedback_or_result != 0) {
        if (feedback_or_result == 1) {
            adjust_source_value_and_finalize(entity, &D_800E1BDA);
        } else {
            display_fixed_item_action_message();
        }
    }
    if (((s16)(outcome)) < 0) {
        return 0;
    }
    if (((s16)(outcome)) != 0) {
        feedback_or_result = 1;
    } else {
        feedback_or_result = -1;
    }
    return feedback_or_result;
}
