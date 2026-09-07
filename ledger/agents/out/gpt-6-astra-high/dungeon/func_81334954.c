#include "common.h"

typedef unsigned long long u64;

typedef struct S_8016B954_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    s8 unk_85;
} S_8016B954_0;   /* arg3 in func_8016B954 */

typedef struct S_8016B954_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8016B954_1;   /* flags in func_8016B954 */

typedef struct S_8016B954_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016B954_2;   /* arg2 in func_8016B954 */

typedef struct S_8016B954_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8016B954_3;   /* arg0 in func_8016B954 */



extern s32 D_80083460;

extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

/* Attempts an action toward the target and initializes the action state on success. */
s32 func_8016B954(S_8016B954_3 *action_state, s32 action_id, S_8016B954_2 *target, void *actor) {
    volatile u64 frame_pad;
    s32 target_direction;
    s32 *global_flags;

    ((S_8016B954_0 *)actor)->unk_71 &= 0x7F;
    global_flags = &D_80083460;

    if (((S_8016B954_1 *)global_flags)->unk_02 & 0x2000) {
        goto shared_failure;
    }

    target_direction = func_800A04F0(
        actor,
        target->unk_24,
        target->unk_25,
        ((S_8016B954_0 *)actor)->unk_2A);

    if ((func_800A2CB8(actor, target_direction) << 16) == 0) {
        return 0;
    }

    if (((S_8016B954_1 *)global_flags)->unk_02 & 0x2000) {
        return -1;
    }

    if (!(((S_8016B954_0 *)actor)->unk_46 & 0x8000) &&
        (((S_8016B954_1 *)global_flags)->unk_02 & 8)) {
        return -1;
    }

    if ((u32)(((0 - func_800A0134(target_direction, actor)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }

    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)actor - 0x20, action_id, 8, 0x300);

    if ((func_800A2B5C(actor) << 16) == 0) {
        goto success;
    }

shared_failure:
    return -1;

success:
    action_state->unk_9A = 0x11;
    action_state->unk_9B = 0;
    action_state->unk_8C = 0;
    ((S_8016B954_0 *)actor)->unk_84 = 0x80;
    ((S_8016B954_0 *)actor)->unk_85 = 32;
    ((S_8016B954_0 *)actor)->unk_6D--;

    func_8009C93C(actor, target, ((S_8016B954_0 *)actor)->unk_2A, 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile u64 frame object plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   A shared mid-function failure block restores both branch targets and polarity;
   explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */
