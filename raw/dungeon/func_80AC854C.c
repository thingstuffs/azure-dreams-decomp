#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743E8(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];

void func_80173D4C(void *arg0_in, void *arg1_in, void *arg2_in, void *arg3_in)
{
    register void *arg0 ASM_REG("$18");
    register void *arg1 ASM_REG("$19");
    register void *arg2 ASM_REG("$17");
    register void *arg3 ASM_REG("$16");
    s32 state;
    register u8 *table ASM_REG("$5");
    register void *check_arg ASM_REG("$4");
    u8 *status;
    s32 flags;

    arg0 = arg0_in;
    arg1 = arg1_in;
    arg2 = arg2_in;
    state = FIELD(arg0, u8, 0x9B);
    arg3 = arg3_in;
    if (state == 1) {
        goto active;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    table = D_80174E4C;
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    {
        register u8 *counter_base ASM_REG("$3");

        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA) =
            FIELD(counter_base, u16, 0xA) - 1;
    }
    goto increment_state;

active:
    if ((func_80042900(arg3, 1) << 16) == 0) {
        goto update_table;
    }
    status = (u8 *)&D_80083460;
    if (FIELD(status, u16, 2) & 0x1000) {
        goto done;
    }
    if (FIELD(arg3, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if (FIELD(arg3, u8, 0x25) == 0) {
        if (FIELD(status, u16, 2) & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, arg1, arg2, arg3);
        goto done;
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
    if ((func_80042900(arg3, 1) << 16) != 0) {
        s8 coordinate = FIELD(arg2, s8, 0x26);
        u8 *origin = D_80082E80;

        if ((coordinate != FIELD(origin, s8, 0x26)) || (coordinate < 0)) {
            if (func_8009FD40(origin, arg2) >= 2) {
                check_arg = arg3;
                goto final_check_call;
            }
            if (!(func_800A6D30(arg3) & 7)) {
                func_80042B68(arg3, 1);
            }
        } else {
            if (!(func_800A6D30(origin) & 7)) {
                func_80042B68(arg3, 1);
            }
        }
    }

    check_arg = arg3;
final_check_call:
    if ((func_80042900(check_arg, 1) << 16) != 0) {
        goto done;
    }

update_table:
    table = D_80174E54;
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(arg2,
        table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto assign_owner;
    }
    {
        register u8 *counter_base ASM_REG("$2");

        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA)++;
        ASM_KEEP(counter_base);
    }

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    {
        register u8 *counter_base ASM_REG("$2");

        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA)--;
        ASM_KEEP(counter_base);
    }

assign_owner:
    FIELD(arg0, void *, 0x8C) = &D_80171728;

done:
    return;
}

/* MECHANISM: Removing value-rewriting arg/table keeps recovered the 40-byte frame,
   retail save order, and v0-destination symbolic indexing. Nonvolatile counter RMW
   lets sh fill the jump delay; duplicated A6D30 paths merge with predecessor-held a0.
   A pinned $a0 final-check local exposes the call-only label needed by word 160. */
