#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"



typedef struct S_80172920_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172920_1;   /* flags in func_80172920 */


typedef struct S_80172920_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172920_3;   /* arg0 in func_80172920 */




extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

/* Attempt an action toward the target and update actor state on success. */
s32 func_80172920(S_80172920_3 *action_state, s32 effect_arg, Rec_D_80082E80 *target, void *actor) {
    volatile u64 frame_pad;
    s32 target_direction;

    ((EntityRec *)actor)->unk_71 &= 0x7F;

    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }

    target_direction = func_800A04F0(
        actor,
        target->unk_24,
        target->unk_25,
        ((EntityRec *)actor)->facing);

    if ((func_800A2CB8(actor, target_direction) << 16) == 0) {
        return 0;
    }

    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }

    if (!(((EntityRec *)actor)->unk_46 & 0x8000) &&
        (dungeonStatus.flags & 8)) {
        return -1;
    }

    if ((u32)(((0 - func_800A0134(target_direction, actor)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }

    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)actor - 0x20, effect_arg, 8, 0x300);

    if ((func_800A2B5C(actor) << 16) == 0) {
        action_state->unk_9A = 0x11;
        action_state->unk_9B = 0;
        action_state->unk_8C = 0;
        ((EntityRec *)actor)->unk_84 = 0x7C;
        ((EntityRec *)actor)->unk_85 = 4;
        ((EntityRec *)actor)->unk_6D--;

        func_8009C93C(actor, target, ((EntityRec *)actor)->facing, 1, 0);
        return 1;
    }

    return -1;
}

/* MECHANISM: An unused volatile u64 frame object plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   The early failure paths return -1 directly and the success block sits inside the
   final test's true arm (a failure-first `!= 0` return measured dist 9); explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */
