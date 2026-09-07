#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8009CE1C(s32, s32, s32, s32, s32, s32, s32);
extern void func_800A56E0(s32);
extern void func_800CCFB4(void);

extern s32 D_800814A0;
extern u8 D_80083160[];

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern u8 *D_800E3D7C;

void func_800CCDA0(void *arg0, void *arg1, void *arg2)
{
    u16 value;
    u8 *base;

    if (FIELD(arg0, s16, 4) == 0) {
        FIELD(arg1, s32, 0x14) += 0x20000;

        value = FIELD(arg0, u16, 6) - 1;
        FIELD(arg0, u16, 6) = value;
        if ((value << 16) == 0) {
            func_800A56E0(0x701);
        }

        if (FIELD(arg0, s16, 0xA) < FIELD(arg1, s16, 0xA)) {
            func_8009CE1C(FIELD(arg0, s32, 0), 10,
                          D_800E3D7C[0x11], 8,
                          (FIELD(arg0, s16, 8) << 25) >> 16, 0, 2);

            base = D_80083160;
            FIELD(arg1, s32, 0x14) = -FIELD(arg1, s32, 0x14);
            FIELD(arg1, s32, 0xC) =
                func_80064584(FIELD(base, s16, 0xC8)) << 8;
            FIELD(arg1, s32, 0x10) =
                func_800644B8(FIELD(base, s16, 0xC8)) << 8;

            FIELD(arg2, u16, 0x14) |= 0xC;
            FIELD(arg0, u16, 6) = 12;
            FIELD(arg0, u16, 4)++;
            func_800CCFB4();
            return;
        }
    } else {
        u16 angle;
        s16 divisor;

        FIELD(arg1, s32, 0x14) += 0x80000;
        angle = FIELD(arg2, u16, 0x1A);
        divisor = FIELD(arg0, s16, 6);
        angle += (0x400 - angle) / divisor;
        FIELD(arg2, u16, 0x1A) = angle;

        {
            u16 nextAngle;

            value = FIELD(arg0, u16, 6);
            nextAngle = FIELD(arg2, volatile u16, 0x1A);
            if (value & 1) {
                value = nextAngle + 0x100;
            } else {
                value = nextAngle - 0x100;
            }
            FIELD(arg2, volatile u16, 0x1A) = value;
        }

        FIELD(arg2, u8, 0xC) -=
            FIELD(arg2, u8, 0xC) / FIELD(arg0, s16, 6);
        FIELD(arg2, u8, 0xD) -=
            FIELD(arg2, u8, 0xD) / FIELD(arg0, s16, 6);
        FIELD(arg2, u8, 0xE) -=
            FIELD(arg2, u8, 0xE) / FIELD(arg0, s16, 6);

        value = FIELD(arg0, u16, 6) - 1;
        FIELD(arg0, u16, 6) = value;
        if ((value << 16) == 0) {
            D_80083460.fieldA--;
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
}

/* MECHANISM: Keep the retail 0x38 frame and long-lived s1/s2/s3 argument roles.
   A nested second-angle u16 separates its lifetime from the first angle/divisor pair.
   Reusing value for parity/result emits the bnez delay-slot select without length drift. */
