#include "common.h"

typedef struct {
    void *unk0;
    u8 pad4[0x44];
    u16 timer;
    s16 unk4A;
    u16 state;
} Unk818DAD38Owner;

typedef struct {
    u8 pad0[4];
    s8 unk4;
    s8 unk5;
    u8 pad6[6];
    u32 unkC;
    u8 pad10[4];
    u16 flags;
    u8 pad16[6];
    u16 unk1C;
    u16 unk1E;
} Unk818DAD38Target;

extern void func_800478B8(Unk818DAD38Target *);
extern void func_8002466C(void) __attribute__((noreturn));
extern u32 D_800814A0[];

/* Advance the target's growth animation, then fade its color and mark completion. */
void func_818DAD38(Unk818DAD38Owner *owner, s32 unused,
                   Unk818DAD38Target *target) {
    s16 state;
    u16 next_scale;
    u16 *owner_flags;

    owner_flags = (u16 *)((u8 *)owner->unk0 + 0x52);
    *owner_flags |= 0x8000;
    owner->timer--;
    func_800478B8(target);

    if (target->flags & 0x6000) {
        target->unk4 = 0;
        target->unk5 = 0;
    }

    state = owner->state;
    if (state == 0) {
        goto grow;
    }
    if (state == 1) {
        goto fade;
    }
    func_8002466C();
    return;

grow:
    target->unk1C += 0x200;
    next_scale = target->unk1E + 0x200;
    target->unk1E = next_scale;
    if (next_scale >= 0x1C00) {
        target->unk1C = 0xC00;
        target->unk1E = 0x1800;
        owner->unk4A = 0;
        target->unkC = 0x808080;
    }
    if ((s16)owner->timer <= 0) {
        owner->state++;
        func_8002466C();
        return;
    }
    goto done;

fade:
    if ((u8)target->unkC < 9) {
        target->unkC = 0;
        ((u16 *)owner)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_8002466C();
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    target->unkC += 0xFFEFEFF0;

done:
}

/* MECHANISM: Explicit state-test labels keep all three noreturn dispatcher tails at their retail sites.
   ASM_SCHED_BARRIER blocks the else constant hoist, restoring the global-page delay slot and 83-word length.
   Updating unk1C before unk1E selects retail's v1/v0 load-add order while held s1/s0 preserve the 0x20 frame. */
