#include "common.h"
#include "dungeon/actor/motion.h"
#include "slus.h"
#include "dungeon/player/input.h"

typedef struct S_80096AE0_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_80096AE0_0;   /* actor in run_three_stage_actor_step */

typedef struct S_80096AE0_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80096AE0_1;   /* record in run_three_stage_actor_step */

typedef struct S_80096AE0_2 {
    u8 pad_00[0x88];
    s16 unk_88;
    s16 unk_8A;
} S_80096AE0_2;   /* range in run_three_stage_actor_step */

typedef struct S_80096AE0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80096AE0_3;   /* part in run_three_stage_actor_step */

/* Run the actor's three-stage 0x9B step script: stage 0 arms the 0x96 timer from the 0x88/0x8A gap, stage 1 raises the part's 0x800 flag, stage 2 counts the timer down and swaps in the 0x8C table. */
void run_three_stage_actor_step(S_80096AE0_0 *actor, S_80096AE0_1 *record, S_80096AE0_3 *part, S_80096AE0_2 *range)
{
    s32 state;
    u16 countdown;
    u16 value;

    state = actor->unk_9B;

    switch (state) {
    case 0:
        if ((actor->unk_A2 & 0x10) == 0) {
            return;
        }
        record->unk_14 = 0;
        if ((range->unk_88 - range->unk_8A) >= 0x41) {
            initialize_timed_motion_step(8, 0x10);
            actor->unk_96 = 0xC;
        } else {
            actor->unk_96 = 1;
        }
        actor->unk_9B = actor->unk_9B + 1;
    case 1:
        part->unk_14 = part->unk_14 | 0x800;
        actor->unk_9B = actor->unk_9B + 1;
        return;
    case 2:
        countdown = actor->unk_96 - 1;
        actor->unk_96 = countdown;
        if (((s32)(countdown << 16) <= 0) &&
            ((value = part->unk_14,
              part->unk_14 = value & 0xF7FF,
              (value & 0xE000) != 0) ||
             ((has_action_input_without_modifier() << 16) != 0))) {
            actor->unk_8C = handle_actor_commands_and_facing;
        }
        return;
    default:
        return;
    }
}

/* MECHANISM: Local joins keep actor/part live in s0/s1 across the real call,
   producing the 0x20 frame and exact s0/s1/ra save contract. Separate
   countdown/flag live ranges plus short-circuit RMW select retail v0/v1. */
