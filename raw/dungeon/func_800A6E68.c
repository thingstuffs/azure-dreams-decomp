#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_800814A0[3];

extern void func_8009A028();
extern void func_8009A21C();
extern void func_800A2B04();
extern void func_800A32A4();
extern s32 func_800AC7C8();
extern void func_800AC7CC(void) __attribute__((noreturn));
extern void func_800AC7CC_returning(void) __asm__("func_800AC7CC");
extern s16 func_800BCB04();

s32 func_800AC5C8(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 force;
    u16 count;
    s32 state;
    u8 x;
    u8 y;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    {
        register s32 rv_low ASM_REG("$2");

        rv_low = 0;
        ASM_KEEP(rv_low);
        func_800AC7CC();
        return rv_low;
    }

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    {
        register s32 rv_high ASM_REG("$2");

        rv_high = 0;
        ASM_KEEP(rv_high);
        func_800AC7CC();
        return rv_high;
    }

state_0:
        FIELD(arg3, u16, 0x6A) = FIELD(arg3, u16, 0x2A) & 0xFFF;
        FIELD(arg0, u8, 0x9B)++;
        /* fall through */

state_1:
        FIELD(arg3, u16, 0x2A) += 0x200;
        FIELD(arg1, s32, 0x14) -= 0x10000;

        count = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = count;
        if ((s16)count > 0) {
            return 0;
        }

        FIELD(arg1, s32, 0x14) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg0, u16, 0x96) = 0x10;

        if (!(FIELD(arg3, s32, 0x14) & 0x4000)) {
            D_80083460.field_A--;
            func_800A32A4(arg3);
            func_8009A028(arg3);
            FIELD(arg3, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            return func_800AC7C8();
        }

        FIELD(arg3, u16, 0x88) = func_800BCB04(
            (FIELD(arg2, u8, 0x24) << 6) | 0x20,
            (FIELD(arg2, u8, 0x25) << 6) | 0x20,
            -0x400);
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, s32, 0x1C) &= 0xFFFEFFFF;
        FIELD(arg0, u16, 0x96) = 0x10;
        FIELD(arg0, u8, 0x9B)++;
        return func_800AC7C8();

state_2:
        FIELD(arg3, u16, 0x2A) += 0x200;
        count = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = count;
        if ((s16)count > 0) {
            return 0;
        }

        FIELD(arg0, s32, 0x90) = 0;
        x = FIELD(arg2, u8, 0x24);
        y = FIELD(arg2, u8, 0x25);
        if (FIELD(arg3, s32, 0x1C) & 0x2000) {
            force = 0x300;
        } else {
            force = 0x3000;
        }
        func_8009A21C(x, y, force);
        {
            register D_80083460_t *status ASM_REG("$2");

            status = &D_80083460;
            ASM_KEEP(status);
            status->field_A--;
        }
        {
            register u16 restored ASM_REG("$3");
            register s32 rv ASM_REG("$2");

            restored = FIELD(arg3, u16, 0x6A);
            ASM_USE(restored);
            rv = 1;
            ASM_USE(rv);
            FIELD(arg3, u16, 0x2A) = restored;
            func_800AC7CC_returning();
            return 0;
        }
}

/* MECHANISM: vars=0 frame holds arg0/arg2/arg3 and 0x10 in s1/s2/s0/s3.
   A signed ladder duplicates the two v0=0 noreturn default tails instead of merging them.
   Non-overlap v0 status/rv and v1 restored pins reproduce the case-2 live ranges.
   Ordered ASM_USE plus the returning alias/return 0 retains lhu;li;j;sh and dead move v0,zero. */
