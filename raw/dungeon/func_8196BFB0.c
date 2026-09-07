#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80024AF8(void *arg0, void *arg1, void *arg2,
                          s16 arg3, s16 arg4, s16 arg5);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);

extern s16 D_800269B4;
extern s32 D_800814A0;
extern u8 D_80083780[];

void func_8196BFB0(void *arg0, void *arg1, void *arg2)
{
    s32 height;
    s16 x;
    s16 z;
    s32 collide_x;
    s32 collide_y;
    s32 collide_z;
    u8 *camera;

    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x8C);
    FIELD(arg0, s32, 0x8C) += FIELD(arg0, s32, 0x98);
    collide_x = FIELD(arg1, u16, 2);
    collide_y = FIELD(arg1, u16, 6);
    collide_z = FIELD(arg1, s16, 0xA);
    D_800269B4 = 1;
    if ((s16)func_800A45D8(collide_x, collide_y, collide_z) != 0) {
        FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x8C);
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, s32, 0x98) = 0;
    }

    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x90);
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0x9C);
    if ((s16)func_800A45D8(FIELD(arg1, u16, 2),
                           FIELD(arg1, u16, 6),
                           FIELD(arg1, s16, 0xA)) != 0) {
        FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x90);
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, s32, 0x9C) = 0;
    }

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x94);
    FIELD(arg0, s32, 0x94) += FIELD(arg0, s32, 0xA0);

    height = FIELD(arg1, s16, 0xA);
    if ((s16)func_800BCB04(FIELD(arg1, u16, 2),
                           FIELD(arg1, u16, 6),
                           (s16)(FIELD(arg1, volatile u16, 0xA) - 4)) - 0x10 < height) {
        FIELD(arg0, s32, 0x94) = 0;
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg1, s16, 0xA) =
            func_800BCB04(FIELD(arg1, u16, 2),
                          FIELD(arg1, u16, 6),
                          (s16)(FIELD(arg1, u16, 0xA) - 4)) - 0x11;
        FIELD(arg1, s16, 8) = 0;
        FIELD(arg0, s16, 0x2C) = 0;
    }

    if (FIELD(arg0, s16, 0x50)++ >= 3) {
        x = FIELD(arg2, u16, 0x1C);
        z = FIELD(arg2, u16, 0x1E);
        x = x - 0x100;
        if (x < 0) {
            x = 0;
        }
        z = z - 0x100;
        if (z < 0) {
            z = 0;
        }
        FIELD(arg2, s16, 0x1C) = x;
        FIELD(arg2, s16, 0x1E) = z;
    }

    camera = D_80083780;
    func_80024AF8(arg0, arg1, arg2,
                  (s16)(FIELD(arg1, u16, 2) - FIELD(camera, u16, 2)),
                  (s16)(FIELD(arg1, u16, 6) - FIELD(camera, u16, 6)),
                  (s16)(FIELD(arg1, u16, 0xA) - FIELD(camera, u16, 0xA)));

    if (--FIELD(arg0, s16, 0x2C) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
