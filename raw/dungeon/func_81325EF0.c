#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

s32 func_80042900(void *, s32);
void func_80042B68(void *, s32);
void func_80047784(void *, s32, s32);
s32 func_8009A180(void *, void *);
s16 func_8009FD40(void *, void *);
s32 func_800A2C34(void *);
s32 func_800A6D30(void);
void func_800A9A04(void *);
void func_800A9A0C(void *);
void func_800AA258(void *, s32, void *, void *);
s32 func_800AA6B4(void *, s32, void *, void *);
void func_800AA888(void *, s32, void *, void *);
void func_8016DA34(void) __attribute__((noreturn));
void func_8016DA7C(void) __attribute__((noreturn));
void func_8016DAA4(void *, s32, void *, void *);

extern u16 D_80013714;
extern u8 *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u16 D_80083462;
extern u8 D_8016B778[];
extern u8 D_801746A4[];
extern u8 D_801746AC[];
extern u8 D_801746C4[];

void func_8016D6F0(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *room_base;
    register u8 *table ASM_REG("$5");
    u8 *counter_base;
    u8 *base8008;
    u8 *base8001;
    register u8 *clear_page ASM_REG("$2");
    register u8 *clear_base ASM_REG("$4");
    register void *call_obj ASM_REG("$4");
    register u8 *update_base ASM_REG("$2");
    s32 state;
    s32 bits;
    s32 mask;
    s8 room;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        func_8016DA7C();
        return;
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_two;
    }
    func_8016DA7C();
    return;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    base8008 = (u8 *)0x80080000;
    table = D_801746A4;
    ASM_KEEP(base8008);
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80047784(
        arg2,
        table[((FIELD(base8008, s16, 0x3228) +
                FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    counter_base = D_80083460;
    ASM_KEEP(counter_base);
    FIELD(counter_base, u16, 0xA)--;
    func_8016DA34();
    return;

state_one:
    if ((func_80042900(arg3, 1) << 0x10) == 0) {
        goto post_actions;
    }
    base8008 = (u8 *)0x80080000;
    ASM_KEEP(base8008);
    if (FIELD(base8008, u16, 0x3462) & 0x1000) {
        goto done;
    }
    if (FIELD(arg0, u8, 0xB4) == 0) {
        ASM_SCHED_BARRIER();
        base8001 = (u8 *)0x80010000;
        ASM_KEEP(base8001);
        if (!(FIELD(base8001, u16, 0x3714) & 8)) {
            if (FIELD(arg3, s16, 0x64) != 0) {
                if (func_800AA6B4(arg0, arg1, arg2, D_801746C4) != 0) {
                    func_8016DA7C();
                    return;
                }
            }
            goto action_body;
        }
    }
    if (FIELD(arg3, s16, 0x64) != 0) {
        clear_page = (u8 *)0x80080000;
        ASM_KEEP(clear_page);
        clear_base = clear_page + 0x3460;
        ASM_KEEP(clear_base);
        if (FIELD(clear_base, s32, 0x10) ==
            (u32)((u8 *)arg3 - 0x20)) {
            FIELD(clear_base, s32, 0x10) &= 0x7FFFFFFF;
        }
    }

action_body:
    if ((func_800A2C34(arg3) << 0x10) != 0) {
        goto done;
    }
    bits = FIELD(arg3, s32, 0x1C);
    mask = bits & 0x100;
    ASM_SCHED_BARRIER();
    call_obj = arg0;
    if (mask) {
        func_800AA258(call_obj, arg1, arg2, arg3);
        func_8016DA7C();
        return;
    }
    if (bits & 0x80000) {
        func_800AA888(call_obj, arg1, arg2, arg3);
        func_8016DAA4(arg0, arg1, arg2, arg3);
        func_8016DA7C();
        return;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 0x10) != 0) {
        base8008 = (u8 *)0x80080000;
        ASM_KEEP(base8008);
        if ((func_8009A180(
                 arg3,
                 FIELD(FIELD(base8008, u8 *, 0x14A8), void *, 0x58) + 0x20)
             << 0x10) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 0x10) != 0) {
        room_base = D_80082E80;
        room = FIELD(arg2, s8, 0x26);
        if ((room != FIELD(room_base, s8, 0x26)) || (room < 0)) {
            if (func_8009FD40(room_base, arg2) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(arg3, 1);
        }
    }

second_check:
    if ((func_80042900(arg3, 1) << 0x10) != 0) {
        goto done;
    }

post_actions:
    table = D_801746AC;
    base8008 = (u8 *)0x80080000;
    ASM_KEEP(base8008);
    FIELD(arg2, u8 *, 0x2C) = table;
    func_80047784(
        arg2,
        table[((FIELD(base8008, s16, 0x3228) +
                FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto set_callback;
    }
    update_base = D_80083460;
    ASM_KEEP(update_base);
    FIELD(update_base, u16, 0xA)++;
    FIELD(arg0, u8, 0x9B)++;
    func_8016DA7C();
    return;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    update_base = D_80083460;
    ASM_KEEP(update_base);
    FIELD(update_base, u16, 0xA)--;

set_callback:
    FIELD(arg0, void *, 0x8C) = D_8016B778;

done:
    return;
}
