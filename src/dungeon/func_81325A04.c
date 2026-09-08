#include "common.h"

#define FIELD(type, p, off) (*(type)((s8 *)(p) + (off)))

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228[];
extern s32 D_80083460[];
extern u8 D_8016B778[];
extern u8 D_8017467C[];
extern u8 D_80174684[];
extern u8 D_801746C4[];
extern u8 D_801746CC[];

extern s32 func_800A2B04();
extern s32 func_800AAA54();
extern s32 func_800AD4D0();
extern s32 func_80047784();
extern u8 *func_8016D470() __attribute__((noreturn));
extern u8 *func_8016D528() __attribute__((noreturn));
extern u8 *func_8016D590() __attribute__((noreturn));

u8 *func_8016D204(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 state;
    s16 timer;
    s16 next;
    u16 raw;
    s32 value;
    s32 below2;
    s32 x;
    s32 y;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;
    s32 *shared;
    u8 *chosen;
    register u32 page ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    register u8 *tail_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */

    state = FIELD(u8 *, arg0, 0x9B);
    if (state == 1) {
        goto state1_body;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0_body;
        }
        return;
    }
       /* MATCH pin: retail delay-slot fill depends on it */
    if (state == 2) {
        goto state2_body;
    }
    if (state == 3) {
        goto state3_body;
    }
    return;

state0_body:
    func_800AD4D0(arg3);
    FIELD(s16 *, arg0, 0x96) = 12;
    FIELD(u8 *, arg0, 0x9B) = (u8)(FIELD(u8 *, arg0, 0x9B) + 1);
    if (FIELD(u8 *, arg3, 0x28) == 0) {
        FIELD(s32 *, arg1, 0x14) = 0;
        FIELD(s32 *, arg1, 0x10) = 0;
        FIELD(s32 *, arg1, 0x0C) = 0;
        if (FIELD(u8 *, arg0, 0xB4) != 0) {
            page = (u32)D_8016B778;
            ASM_KEEP(page);   /* MATCH pin: retail keeps a computation the compiler would drop */
            FIELD(u8 *, arg0, 0x9B) = 0;
            return func_8016D590();
        }
        goto initialize;
    }
    chosen = (u8 *)3;
    if (!(FIELD(u16 *, arg2, 0x14) & 0x8000)) {
        return chosen;
    }
    FIELD(s16 *, arg0, 0x96) = 0;
    FIELD(u8 *, arg0, 0x9B) = (u32)chosen;
    return;

state1_body:
        raw = FIELD(u16 *, arg0, 0x96);
        raw--;
        FIELD(u16 *, arg0, 0x96) = raw;
        timer = (s16)raw;
        if (timer >= 11) {
            FIELD(s32 *, arg1, 0x0C) =
                *(s16 *)((u8 *)D_8006CCD8 + ((FIELD(u16 *, arg3, 0x6A) >> 8) & 0xE)) << 20;
            FIELD(s32 *, arg1, 0x10) =
                *(s16 *)((u8 *)D_8006CCE8 + ((FIELD(u16 *, arg3, 0x6A) >> 8) & 0xE)) << 20;
            FIELD(u16 *, arg2, 0x14) |= 0x800;
            return;
        }
        if (timer >= 7) {
            x = FIELD(s32 *, arg1, 0x0C);
            if (x < 0) {
                x += 3;
            }
            y = FIELD(s32 *, arg1, 0x10);
            FIELD(s32 *, arg1, 0x0C) = x >> 2;
            if (y < 0) {
                y += 3;
            }
            FIELD(s32 *, arg1, 0x10) = y >> 2;
            return;
        }
        below2 = timer < 2;
        if (!below2) {
            FIELD(s32 *, arg1, 0x10) = 0;
            FIELD(s32 *, arg1, 0x0C) = 0;
            return;
        }
        if (timer == state) {
            FIELD(u16 *, arg2, 0x14) &= 0xF7FF;
            return;
        }
        if (timer != 0) {
            return (u8 *)(u32)below2;
        }
        timer = 4;
        page = FIELD(u8 *, arg0, 0x9B);
        ASM_KEEP(page);   /* MATCH pin: retail keeps a computation the compiler would drop */
        FIELD(s16 *, arg0, 0x96) = timer;
        return func_8016D470();
state2_body:
    timer = FIELD(s16 *, arg0, 0x96);
    if (timer != 0) {
        ax = FIELD(u8 *, arg2, 0x24) << 6;
        dy = FIELD(s16 *, arg1, 2) - 32;
        FIELD(s32 *, arg1, 0x0C) = ((ax - dy) << 16) / timer;
        ax2 = FIELD(u8 *, arg2, 0x25) << 6;
        dy2 = FIELD(s16 *, arg1, 6) - 32;
        FIELD(s32 *, arg1, 0x10) =
            ((ax2 - dy2) << 16) / FIELD(s16 *, arg0, 0x96);
    }
    page = FIELD(u16 *, arg0, 0x96);
    next = (s16)(page - 1);
    page <<= 16;
    FIELD(s16 *, arg0, 0x96) = next;
    if ((s32)page > 0) {
            return (u8 *)page;
    }
    FIELD(s32 *, arg1, 0x14) = 0;
    FIELD(s32 *, arg1, 0x10) = 0;
    FIELD(s32 *, arg1, 0x0C) = 0;
    FIELD(u8 *, arg0, 0x9B) = (u8)(FIELD(u8 *, arg0, 0x9B) + 1);
    return;

state3_body:
    FIELD(s32 *, arg1, 0x14) = 0;
    FIELD(s32 *, arg1, 0x10) = 0;
    FIELD(s32 *, arg1, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(u8 *, arg2, 0x24), FIELD(u8 *, arg2, 0x25));
    if (FIELD(u8 *, arg3, 0x28) != 0) {
        goto state3_continue;
    }
    FIELD(s32 *, arg1, 0x14) = 0;
    FIELD(s32 *, arg1, 0x10) = 0;
    FIELD(s32 *, arg1, 0x0C) = 0;
    if (FIELD(u8 *, arg0, 0xB4) != 0) {
        goto state3_tail;
    }
initialize:
    FIELD(u8 *, arg0, 0x9B) = 0;
    func_800AAA54(arg0, arg1, arg2, D_801746CC);
    return;

state3_tail:
    page = (u32)D_8016B778;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a computation the compiler would drop */
    FIELD(u8 *, arg0, 0x9B) = 0;
    return func_8016D590();

state3_continue:
    if (FIELD(s32 *, arg2, 0x2C) == (s32)D_801746C4) {
        if (FIELD(u8 *, arg0, 0xB3) == 0) {
            page = 0x80170000;
            ASM_KEEP(page);   /* MATCH pin: retail keeps a computation the compiler would drop */
            tail_a1 = (u8 *)page + 18044;
            ASM_TAILSLOT_PIN(tail_a1);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8016D528();
            return (u8 *)0;
        }
        if (FIELD(s32 *, arg2, 0x2C) != (s32)D_80174684) {
            FIELD(s32 *, arg2, 0x2C) = (s32)D_80174684;
            value = D_80083228[0] + FIELD(s16 *, arg3, 0x2A);
            func_80047784(arg2, D_80174684[((value + 0x100) >> 9) & 7], 0);
        }
    }
    shared = D_80083460;
    if (shared[4] == (s32)((u8 *)arg3 - 0x20)) {
        shared[4] &= 0x7FFFFFFF;
    }
    FIELD(u8 **, arg0, 0x8C) = D_8016B778;
    return D_8016B778;
}
