#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"



typedef struct S_8016B954_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8016B954_1;   /* flags in func_8016B954 */






extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

/* Attempts an action toward the target and initializes the action state on success. */
s32 func_8016B954(Rec_func_800A9E70_arg0 *action_state, s32 action_id, Rec_D_80082E80 *target, void *actor) {
    volatile u64 frame_pad;
    s32 target_direction;

    ((EntityRec *)actor)->unk_71 &= 0x7F;

    if (dungeonStatus.flags & 0x2000) {
        goto shared_failure;
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

    func_800C7930((u8 *)actor - 0x20, action_id, 8, 0x300);

    if ((func_800A2B5C(actor) << 16) == 0) {
        goto success;
    }

shared_failure:
    return -1;

success:
    action_state->unk_9A.as_s8 = 0x11;
    action_state->unk_9B.as_s8 = 0;
    action_state->unk_8C = 0;
    *(unsigned char *)&((EntityRec *)actor)->unk_84 = 0x80;
    ((EntityRec *)actor)->unk_85 = 32;
    ((EntityRec *)actor)->unk_6D--;

    func_8009C93C(actor, target, ((EntityRec *)actor)->facing, 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile u64 frame object plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   A shared mid-function failure block restores both branch targets and polarity;
   explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */
