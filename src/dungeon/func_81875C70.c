#include "common.h"
#include "shared/object_flags.h"

extern s32 func_80069EF8(void);
extern void func_80025338(void *, s32, s32, s32, s32, s32, s32);

typedef struct {
    u8 bytes[12];
} UnkCopy12;

extern UnkCopy12 D_80026658;
extern s16 D_80026664;

/* Per-state particle step: the c4 state spawns 0x20 randomised sparks in one do-while. */
void func_81875C70(u8 *data, void *unused, u8 *context)
{
    u8 *p = data;
    s16 old;
    u16 temp;
    u16 h0;
    u16 timer0;
    u16 state0;
    u16 limit0;
    u16 timer1;
    s32 adv;
    u16 state1;
    u16 h1;
    s32 i;
    s32 color;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 velocity;
    s32 state;

    state = *(s16 *)p;
    D_80026664 = 1;

    switch (state) {
    case 0:
        h0 = *(u16 *)(p + 0x1A);
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
        *(u16 *)(p + 0xE) = limit0;
        *(u16 *)p = state0 + 1;
        return;

    case 1:
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
        return;

    case 2:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        if (*(s16 *)(p + 0x6A) < 31) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        velocity = *(s32 *)(p + 0x74) + *(s32 *)(p + 0x80);
        *(s32 *)(p + 0x68) += velocity;
        *(s32 *)(p + 0x74) = velocity;
        *(u16 *)(p + 0x1A) = *(u16 *)(p + 0x6A);
        return;

    case 3:
        old = p[0x34];
        p[0x34] = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p[0x34] = old - 0x1E;
        }
        temp = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = temp;
        if ((s16)temp >= 31) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        return;

    case 4:
        *(UnkCopy12 *)(p + 0x2C) = D_80026658;
        *(u8 **)(context + 8) = p + 0x2C;
        temp = *(u16 *)p;
        *(u16 *)(p + 2) = 0;
        *(u16 *)p = temp + 1;
        *(s16 *)(*(u8 **)(p + 0x40) + 0x88) = 1;

        i = 0;
        do {
            r0 = (func_80069EF8() & 0xFF) | 0x80;
            i++;
            r1 = (s16)((func_80069EF8() & 0x7F) - 0x40);
            r2 = (s16)((func_80069EF8() & 0x7F) - 0x40);
            r3 = (s16)((func_80069EF8() & 0x3F) - 0x60);
            color = 0xE04040;
            func_80025338(p - 0x20, 0, color, r0, r1, r2, r3);
        } while (i < 0x20);
        return;

    case 5:
        temp = *(u16 *)(p + 2) + 1;
        *(u16 *)(p + 2) = temp;
        if ((s16)temp >= 16) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        return;

    case 6:
        if (context[0xC] >= 5) {
            context[0xC] -= 5;
            context[0xD] -= 5;
            context[0xE] -= 5;
        }
        if (context[0xC] < 6) {
            adv = *(u16 *)p;
            *(u16 *)(p + 2) = 0;
            *(u16 *)p = adv + 1;
            return;
        }
        return;

    case 7:
        temp = *(u16 *)(p + 2) - 1;
        *(u16 *)(p + 2) = temp;
        if ((s32)(temp << 16) > 0) {
            return;
        }
        *(u16 *)(p - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    default:
        return;
    }
}
