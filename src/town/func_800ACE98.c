#include "common.h"

extern s32 func_80064584(s32 arg0);
extern void func_80094378(void *arg0, void *arg1, s32 arg2);
extern void func_80095094(void *arg1);
extern s16 func_80095978(void *arg1, void *arg2);
extern void func_80095A94(void *arg1, s16 arg2, void *arg3);
extern void func_80095C80(void *arg1);
extern void func_800A9F14(void *arg1);
extern void func_800AA6DC(void);
extern void func_800AA820(void);
extern void func_800AAA58(void *arg0, void *arg1, s32 arg2);

extern u8 D_80083160[];
extern u8 D_800CFCEF;
extern s32 D_800D0B14;
extern u8 D_800FE488[];
extern s16 D_80100D18;
extern s32 D_80100D1C;
extern u8 D_80100D60[];
extern s16 D_80100D80;
extern s16 D_80100D82;

void func_800AA5F8(void *arg0, void *arg1, s32 arg2) {
    s32 arg2_local;
    u8 *buttons;
    u8 *position;
    s16 angle;
    s32 wave;
    s32 rise;

    arg2_local = arg2;
    buttons = D_80083160;
    func_80095C80(arg1);
    func_80095094(arg1);
    angle = func_80095978(arg1, D_800FE488);
    if (angle - *(s16 *)((u8 *)arg1 + 0xA) >= 4) {
        if (D_800CFCEF == 0) {
            u32 pagebase;
            func_80094378(arg0, arg1, arg2_local);
            pagebase = 0x800D0000;
            ASM_PAGEBASE_PIN(pagebase);   /* MATCH pin: retail delay-slot contents depend on it */
            func_800AA6DC();
            return;
        }
    } else if (D_800CFCEF == 0) {
        func_80095A94(arg1, angle, D_800FE488);
    }

    if ((*(s32 *)(buttons + 0x10) & 0x40) && D_80100D1C >= 0x800) {
        func_800AAA58(arg0, arg1, arg2_local);
        D_800D0B14 = 0;
        return;
    }

    if (*(s32 *)(buttons + 8) & 0x2000) {
        if (D_80100D80 < 0x100) {
            D_80100D80 = (u16)D_80100D80 + 8;
        } else {
            D_80100D80 = 0x100;
        }
    }
    if (*(s32 *)(buttons + 8) & 0x8000) {
        if (D_80100D80 < -0xFF) {
            D_80100D80 = -0x100;
        } else {
            D_80100D80 = (u16)D_80100D80 - 8;
        }
    }
    if (*(s32 *)(buttons + 8) & 0x4000) {
        if (D_80100D82 < 0x100) {
            D_80100D82 = (u16)D_80100D82 + 8;
        } else {
            D_80100D82 = 0x100;
        }
    }
    if (*(s32 *)(buttons + 8) & 0x1000) {
        if (D_80100D82 < -0xFF) {
            D_80100D82 = -0x100;
        } else {
            D_80100D82 = (u16)D_80100D82 - 8;
        }
    }

    position = D_80100D60;
    wave = func_80064584(*(s16 *)(position + 2) - 0x400);
    *(s32 *)position += 0x500000 - (wave << 10);
    rise = D_80100D1C;
    *(u16 *)((u8 *)arg0 + 0x10) = *(u16 *)(position + 2);

    if (rise < 0x800) {
        D_80100D1C = rise + 0x80;
    } else {
        D_80100D1C = 0x800;
    }
    if (D_80100D18 < 0x1000) {
        D_80100D18 = (u16)D_80100D18 + 0x100;
    } else {
        D_80100D18 = 0x1000;
    }
    func_800A9F14(arg1);
}
