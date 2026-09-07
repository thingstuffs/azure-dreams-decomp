#include "common.h"

extern s32 func_80069EF8(void);
extern void func_80025338(void *, s32, s32, s32, s32, s32, s32);
extern void func_800256AC(void) __attribute__((noreturn));
extern void func_800257A8(void) __attribute__((noreturn));
extern void func_800257F0(void) __attribute__((noreturn));
extern void *D_80024038[];

typedef struct {
    u8 bytes[12];
} UnkCopy12;

extern UnkCopy12 D_80026658;
extern s16 D_80026664;
extern s32 D_800814A0;

void func_81875C70(u8 *arg0, void *arg1, u8 *arg2)
{
    u8 *p = arg0;
    u8 old;
    u16 temp;
    u16 h0;
    u16 timer0;
    register u16 state0 ASM_REG("$2");
    register u16 limit0 ASM_REG("$3");
    u16 timer1;
    u16 state1;
    u16 h1;
    register s32 i ASM_REG("$20");
    register s32 cond ASM_REG("$2");
    register s32 color ASM_REG("$6");
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 velocity;
    s32 state;

    state = *(s16 *)p;
    D_80026664 = 1;

    {
        static void *const jt_keep[] = {
            &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3,
            &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7
        };
        if ((u32)state >= 8) {
            return;
        }
        (void)jt_keep;
        goto *D_80024038[(u32)state];
    }

jt_c0:
        h0 = *(u16 *)(p + 0x1A);
        ASM_KEEP(h0);
        old = p[0x34];
        *(u16 *)(p + 0x68) = 0;
        *(u16 *)(p + 0x6A) = h0;
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        timer0 = *(u16 *)(p + 0xE) + 0x28;
        *(u16 *)(p + 0xE) = timer0;
        if ((s16)timer0 < 0x800) {
            return;
        }
        limit0 = 0x800;
        state0 = *(u16 *)p;
        ASM_KEEP(state0);
        *(u16 *)(p + 0xE) = limit0;
        func_800257A8();

jt_c1:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        timer1 = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = timer1;
        if ((s16)timer1 >= 11) {
            state1 = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = state1 + 1;
        }
        h1 = *(u16 *)(p + 0x1A);
        *(u16 *)(p + 0x68) = 0;
        *(s32 *)(p + 0x74) = 0;
        *(s32 *)(p + 0x80) = -0x900;
        *(u16 *)(p + 0x6A) = h1;
        func_800257F0();
        return;

jt_c2:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        if (*(s16 *)(p + 0x6A) < 31) {
            goto advance;
        }
        velocity = *(s32 *)(p + 0x74) + *(s32 *)(p + 0x80);
        *(s32 *)(p + 0x68) += velocity;
        *(s32 *)(p + 0x74) = velocity;
        *(u16 *)(p + 0x1A) = *(u16 *)(p + 0x6A);
        func_800257F0();
        return;

jt_c3:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        temp = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = temp;
        if ((s16)temp >= 31) {
            goto advance;
        }
        func_800257F0();
        return;

jt_c4:
        *(UnkCopy12 *)(p + 0x2C) = D_80026658;
        *(u8 **)(arg2 + 8) = p + 0x2C;
        temp = *(u16 *)p;
        *(u16 *)(p + 2) = 0;
        *(u16 *)p = temp + 1;
        *(s16 *)(*(u8 **)(p + 0x40) + 0x88) = 1;

        i = 0;
        ASM_KEEP(i);
        r0 = (func_80069EF8() & 0xFF) | 0x80;
        i++;
        r1 = (s16)((func_80069EF8() & 0x7F) - 0x40);
        r2 = (s16)((func_80069EF8() & 0x7F) - 0x40);
        r3 = (s16)((func_80069EF8() & 0x3F) - 0x60);
        color = 0xE04040;
        ASM_KEEP(color);
        func_80025338(p - 0x20, 0, color, r0, r1, r2, r3);
        cond = i < 0x20;
        if (cond) {
            func_800256AC();
        }
        return;

jt_c5:
        temp = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = temp;
        if ((s16)temp >= 16) {
            goto advance;
        }
        func_800257F0();
        return;

jt_c6:
        if (arg2[0xC] >= 5) {
            arg2[0xC] -= 5;
            arg2[0xD] -= 5;
            arg2[0xE] -= 5;
        }
        if (arg2[0xC] < 6) {
            goto advance;
        }
        return;

advance:
    temp = *(u16 *)p;
    *(u16 *)(p + 2) = 0;
    *(u16 *)p = temp + 1;
    func_800257F0();

jt_c7:
        temp = *(u16 *)(p + 2) - 1;
        *(u16 *)(p + 2) = temp;
        if ((s32)(temp << 16) > 0) {
            return;
        }
        *(u16 *)(p - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    return;
}
