#include "common.h"

extern void func_8017120C(void) __attribute__((noreturn));
extern void func_80171264(void) __attribute__((noreturn));

#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_801710B8(void *arg0, void *arg1)
{
    u32 tail_page;
    s32 delta;

    S32_AT(arg1, 0x0) += S32_AT(arg0, 0x40);
    S32_AT(arg1, 0x4) += S32_AT(arg0, 0x44);
    S32_AT(arg1, 0x8) += S32_AT(arg0, 0x48);

    S32_AT(arg0, 0x40) += S32_AT(arg0, 0x4c);
    S32_AT(arg0, 0x44) += S32_AT(arg0, 0x50);
    S32_AT(arg0, 0x48) += S32_AT(arg0, 0x54);

    if (S32_AT(arg0, 0x40) > 0x40000) {
        S32_AT(arg0, 0x40) = 0x40000;
    }
    if (S32_AT(arg0, 0x40) < -0x40000) {
        S32_AT(arg0, 0x40) = -0x40000;
    }
    if (S32_AT(arg0, 0x44) > 0x40000) {
        S32_AT(arg0, 0x44) = 0x40000;
    }
    if (S32_AT(arg0, 0x44) < -0x40000) {
        S32_AT(arg0, 0x44) = -0x40000;
    }
    if (S32_AT(arg0, 0x48) > 0x40000) {
        S32_AT(arg0, 0x48) = 0x40000;
    }
    if (S32_AT(arg0, 0x48) < -0x40000) {
        S32_AT(arg0, 0x48) = -0x40000;
    }

    if (S16_AT(arg0, 0x5a) > S16_AT(arg1, 0x2)) {
        delta = S16_AT(arg0, 0x5a) - S16_AT(arg1, 0x2);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < 17) {
            S32_AT(arg0, 0x4c) = 0x1000;
        } else {
            tail_page = 0x10000;
            ASM_PAGEBASE_PIN(tail_page);
            func_8017120C();
            return;
        }
    } else {
        delta = S16_AT(arg0, 0x5a) - S16_AT(arg1, 0x2);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x4c) = (delta < 17) ? -0x1000 : -0x10000;
    }

    if (S16_AT(arg0, 0x5e) > S16_AT(arg1, 0x6)) {
        delta = S16_AT(arg0, 0x5e) - S16_AT(arg1, 0x6);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < 17) {
            S32_AT(arg0, 0x50) = 0x1000;
        } else {
            tail_page = 0x10000;
            ASM_PAGEBASE_PIN(tail_page);
            func_80171264();
            return;
        }
    } else {
        delta = S16_AT(arg0, 0x5e) - S16_AT(arg1, 0x6);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x50) = (delta < 17) ? -0x1000 : -0x10000;
    }

    if (S16_AT(arg0, 0x62) > S16_AT(arg1, 0xa)) {
        delta = S16_AT(arg0, 0x62) - S16_AT(arg1, 0xa);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta < 17) {
            S32_AT(arg0, 0x54) = 0x1000;
            return;
        } else {
            S32_AT(arg0, 0x54) = 0x10000;
            return;
        }
    } else {
        delta = S16_AT(arg0, 0x62) - S16_AT(arg1, 0xa);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x54) = (delta < 17) ? -0x1000 : -0x10000;
        return;
    }
}
