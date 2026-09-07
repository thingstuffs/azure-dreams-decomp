#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800A44E0(s32, s32, s16, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_8009B4B0(void *, u16, u16);
extern s32 func_800A2CB8(void *);
extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, void *, s32, s32);
extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801764A0[];

s32 func_80172438(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 attempt;
    s32 x;
    s32 y;
    s32 direction;
    s32 offset;
    s32 next_x;
    s32 next_y;
    u16 call_direction;
    s16 *x_step;
    s16 *y_step;
    s16 floor;
    register s32 spawn ASM_REG("$5");

    FIELD(arg3, u8, 0x71) &= 0x7F;
    if (D_80083462 & 0x2000) {
        return -1;
    }

    attempt = 0;
    direction = ((u16)FIELD(arg3, u16, 0x2A) >> 9) & 7;
    offset = direction << 1;
    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    x_step = (s16 *)((u8 *)&D_8006CCD8 + offset);
    FIELD(arg0, u16, 0xB2) = 0;
    call_direction = direction;

    do {
        s32 try_x = (s16)x;
        s32 try_y = (s16)y;
        s32 floor_x;
        s32 floor_y;
        register s16 *y_base ASM_REG("$2");

        FIELD(arg0, u16, 0xB2)++;
        if ((func_800A44E0((try_x << 6) & 0xFFC0,
                           (try_y << 6) & 0xFFC0,
                           FIELD(arg3, s16, 0x88), call_direction << 9)
             << 16) != 0) {
            FIELD(arg0, u16, 0xB2)--;
            return 2;
        }

        y_base = (s16 *)&D_8006CCE8;
        floor_x = (((try_x + *x_step) << 6) + 0x20) & 0xFFE0;
        y_step = (s16 *)(offset + (u8 *)y_base);
        floor_y = (((try_y + *y_step) << 6) + 0x20) & 0xFFE0;
        floor = func_800BCB04(floor_x,
                              floor_y,
                              (s16)(FIELD(arg3, u16, 0x88) - 0x20));
        if (floor >= 0x201) {
            FIELD(arg0, u16, 0xB2)--;
            return 3;
        }
        if ((u16)(floor - FIELD(arg3, u16, 0x88) + 0x3F) >= 0x7F) {
            FIELD(arg0, u16, 0xB2)--;
            return 3;
        }

        next_x = x + *(u16 *)x_step;
        next_y = y + *(u16 *)y_step;
        spawn = func_8009B4B0(arg3, (u16)next_x, (u16)next_y);
        FIELD(arg3, s32, 0x60) = spawn;
        if (spawn != 0) {
            break;
        }

        attempt++;
        x += *(u16 *)x_step;
        y += *(u16 *)y_step;
    } while (attempt < 4);

    if (attempt >= 4) {
        return 3;
    }
    if ((func_800A2CB8(arg3) << 16) == 0) {
        return 0;
    }
    if (D_80083462 & 0x2000) {
        return -1;
    }
    if (!(FIELD(arg3, u16, 0x46) & 0x8000) && (D_80083462 & 8)) {
        return -1;
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    FIELD(arg0, s8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg0, s8, 0x9A) = 0x17;
    FIELD(arg2, void *, 0x2C) = D_801764A0;
    func_80047784(arg2,
                  D_801764A0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    return 1;
}
