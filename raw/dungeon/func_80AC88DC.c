#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_801743E8(void *, s32, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];

void func_801740DC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *actor ASM_REG("$18") = arg0;
    register s32 actor_index ASM_REG("$19") = arg1;
    register void *target ASM_REG("$17") = arg2;
    register void *entity ASM_REG("$16") = arg3;
    s32 state;
    s32 flags;
    s32 index;
    u8 *global_base;

#define arg0 actor
#define arg1 actor_index
#define arg2 target
#define arg3 entity

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA)--;
    }
    FIELD(arg2, void *, 0x2C) = D_80174E4C;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_80174E4C[index & 7], 0);
    goto increment_state;

state_one:
    if (FIELD(arg3, u8, 0x25) != 0) {
        u8 *counter_base;

        FIELD(arg2, void *, 0x2C) = D_80174E54;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        func_80047784(arg2, D_80174E54[index & 7], 0);
        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA)++;
        goto increment_state;
    }

    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, u16, 2) & 0x1000) {
        goto done;
    }
    ASM_CLOBBER("$4");
    ASM_CLOBBER("$5");
    ASM_CLOBBER("$6");
    if (FIELD(arg3, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        func_801743E8(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(arg3,
                (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if (FIELD(arg3, u8, 0x25) == 0) {
        goto done;
    }
    FIELD(arg2, void *, 0x2C) = D_80174E54;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, D_80174E54[index & 7], 0);
    FIELD(global_base, u16, 0xA)++;

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base2;

        counter_base2 = (u8 *)&D_80083460;
        FIELD(counter_base2, u16, 0xA)--;
    }
    FIELD(arg0, void *, 0x8C) = &D_80171728;

done:
    if (0) {
        ASM_KEEP(entity);
        ASM_KEEP(target);
        ASM_KEEP(actor);
        ASM_KEEP(actor_index);
    }
    return;
}

/* MECHANISM: Four pinned parameter locals, declared in retail emission order, produce the
   0x28 frame and s2/a0, s3/a1, s1/a2 saves while delaying s0/a3 into the branch slot.
   Clobbering incoming a0-a2 at the call-group dominator forces retail's three ABI reload moves. */
