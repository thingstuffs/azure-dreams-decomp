#include "common.h"

#define U8(o, p)  (*(u8 *)((u8 *)(p) + (o)))
#define S8(o, p)  (*(s8 *)((u8 *)(p) + (o)))
#define U16(o, p) (*(u16 *)((u8 *)(p) + (o)))
#define S32(o, p) (*(s32 *)((u8 *)(p) + (o)))

extern s16 func_80042900(void *, s32);

void func_80041E70(void *arg0)
{
    s32 flags;
    s32 value;

    {
        s32 scale;
        s32 test;

        U16(0x6E, arg0) = 0x100;
        test = S32(0x54, arg0);
        ASM_SCHED_BARRIER();   /* MATCH pin: slus-diff */
        scale = 0x10;
        U8(0x87, arg0) = scale;
        if (test & 1) {
            s32 width;

            width = U16(0x6E, arg0);
            ASM_KEEP_NV(scale);   /* MATCH pin: slus-diff */
            scale *= 2;
            U8(0x87, arg0) = scale;
            U16(0x6E, arg0) = width * 2;
        }
    }

    {
        register s32 direction ASM_REG("$3");   /* MATCH pin: slus-diff */

        direction = func_80042900(arg0, 7);
        direction = (s16)direction;
        if (direction > 0) {
            U16(0x6E, arg0) = U16(0x6E, arg0) * 2;
            U8(0x87, arg0) = U8(0x87, arg0) * 2;
        } else if (direction < 0) {
            U16(0x6E, arg0) = (s32)(U16(0x6E, arg0) << 16) >> 17;
            U8(0x87, arg0) = U8(0x87, arg0) >> 1;
        }
    }

    if (S32(0x54, arg0) & 2) {
        value = U8(5, arg0) * 2;
        if (value >= 0x100) {
            value = 0xFF;
        }
        U8(0x29, arg0) = value;
    } else {
        U8(0x29, arg0) = U8(5, arg0);
    }

    if (S32(0x54, arg0) & 4) {
        value = U8(4, arg0) * 2;
        if (value >= 0x100) {
            value = 0xFF;
        }
        U8(0x66, arg0) = value;
    } else {
        U8(0x66, arg0) = U8(4, arg0);
    }

    if (S32(0x54, arg0) & 8) {
        value = U8(0, arg0) * 2;
        if (value >= 0x100) {
            value = 0xFF;
        }
        U8(0x68, arg0) = value;
    } else {
        U8(0x68, arg0) = U8(0, arg0);
    }

    if (S32(0x54, arg0) & 0x10) {
        value = U8(1, arg0) * 2;
        if (value >= 0x100) {
            value = 0xFF;
        }
        U8(0x69, arg0) = value;
    } else {
        U8(0x69, arg0) = U8(1, arg0);
    }

    {
        s32 i = 2;
        register u8 *slot ASM_REG("$4") = (u8 *)arg0 + 6;   /* MATCH pin: slus-diff */

        do {
            if (slot[8] != 0) {
                if (S32(0x54, arg0) & 0x80) {
                    value = slot[0xA] * 2;
                    if (value >= 0x64) {
                        value = 0x63;
                    }
                    slot[9] = value;
                } else {
                    slot[9] = slot[0xA];
                }
            }
            i--;
            slot -= 3;
        } while (i >= 0);
    }

    if (S32(0x54, arg0) & 0x04000000) {
        S32(0x14, arg0) |= 0x400;
        S32(0x1C, arg0) &= ~0x400;
    }

    if (S32(0x54, arg0) & 0x02000000) {
        S32(0x14, arg0) |= 0x200;
        S32(0x1C, arg0) &= ~0x200;
    } else {
        S32(0x14, arg0) &= ~0x200;
    }

    if (S32(0x54, arg0) & 0x08000000) {
        S32(0x14, arg0) |= 0x10;
        S32(0x1C, arg0) &= ~0x10;
    } else {
        S32(0x14, arg0) &= ~0x10;
    }

    if (S32(0x54, arg0) & 0x10000000) {
        S32(0x14, arg0) |= 0x20;
        S32(0x1C, arg0) &= ~0x20;
    } else {
        S32(0x14, arg0) &= ~0x20;
    }

    if (S32(0x54, arg0) & 0x20000000) {
        S32(0x14, arg0) |= 0x40;
        S32(0x1C, arg0) &= ~0x40;
    } else {
        S32(0x14, arg0) &= ~0x40;
    }

    if (S32(0x54, arg0) & 0x40000000) {
        S32(0x14, arg0) |= 0x80;
        S32(0x1C, arg0) &= ~0x80;
    } else {
        S32(0x14, arg0) &= ~0x80;
    }

    if (S32(0x54, arg0) & 0x200000) {
        S32(0x1C, arg0) |= 0x1000;
        S32(0x14, arg0) &= ~0x1000;
    }

    flags = S32(0x54, arg0);
    if ((flags & 0x800000) && ((u32)(U8(0x13, arg0) - 3) < 0x2B) && (U8(0x48, arg0) != 4)) {
        S32(0x54, arg0) = flags & 0xFF7FFFFF;
    }
}
