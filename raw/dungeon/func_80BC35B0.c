#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801732A4(void) __attribute__((noreturn));

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern s32 D_801719DC;
extern u8 D_8017464C[8];
extern u8 D_80174654[8];
extern u8 D_8017465C[8];
extern u8 D_80174664[8];

void func_80172DB0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4, &&L5 };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 6) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 5;
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        func_801732A4();
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if (FIELD(arg0, s32, 0xA4) != 0) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_8017464C;
    func_80047784(arg2,
        D_8017464C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 8;
    FIELD(arg0, u8, 0x9B)++;
    func_801732A4();

L1:
    {
        u16 timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((s16)timer > 0 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174654;
    func_80047784(arg2,
        D_80174654[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x707);
    FIELD(arg0, u16, 0x96) = 6;
    FIELD(arg0, s32, 0xAC) = 0x80000;
    FIELD(arg0, s32, 0xB0) = (s32)0xFFFE0000;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg1, s32, 0x0C) =
        -*(s16 *)(&D_8006CCD8 + (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 18;
    FIELD(arg1, s32, 0x10) =
        -*(s16 *)(&D_8006CCE8 + (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 18;
    func_801732A4();

L2:
    FIELD(arg0, s32, 0xA4) += FIELD(arg0, s32, 0xAC);
    FIELD(arg0, s32, 0xAC) += FIELD(arg0, s32, 0xB0);
    if (FIELD(arg0, s16, 0x96) < 2) {
        FIELD(arg1, s32, 0x0C) =
            *(s16 *)(&D_8006CCD8 + (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 19;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)(&D_8006CCE8 + (((u16)FIELD(arg3, s16, 0x2A) >> 8) & 0xE)) << 19;
    }
    {
        u16 timer = FIELD(arg0, u16, 0x96);

        FIELD(arg0, u16, 0x96) = timer - 1;
        if ((s16)timer > 0 && !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
    }
    func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x804);
    func_801732A4();

L3:
    FIELD(arg0, s32, 0xA4) += FIELD(arg0, s32, 0xAC);
    FIELD(arg0, s32, 0xAC) += FIELD(arg0, s32, 0xB0);
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_8017465C;
    func_80047784(arg2,
        D_8017465C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, s32, 0xA4) = 0;
    func_801732A4();

L4:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80174664;
    func_80047784(arg2,
        D_80174664[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 4;
    FIELD(arg0, s32, 0xA4) = 0;
    FIELD(arg0, u8, 0x9B)++;
    {
        s32 coord = FIELD(arg2, u8, 0x24) << 6;
        s32 current = FIELD(arg1, s16, 2) - 0x20;

        FIELD(arg1, s32, 0x0C) = ((coord - current) << 16)
            / FIELD(arg0, s16, 0x96);
    }
    {
        s32 coord = FIELD(arg2, u8, 0x25) << 6;
        s32 current = FIELD(arg1, s16, 6) - 0x20;

        FIELD(arg1, s32, 0x10) = ((coord - current) << 16)
            / FIELD(arg0, s16, 0x96);
    }
    func_801732A4();

L5:
    {
        s16 timer = FIELD(arg0, s16, 0x96);

        if (timer != 0) {
            {
                s32 coord = FIELD(arg2, u8, 0x24) << 6;
                s32 current = FIELD(arg1, s16, 2) - 0x20;

                FIELD(arg1, s32, 0x0C) = ((coord - current) << 16) / timer;
            }
            {
                s32 coord = FIELD(arg2, u8, 0x25) << 6;
                s32 current = FIELD(arg1, s16, 6) - 0x20;

                FIELD(arg1, s32, 0x10) = ((coord - current) << 16)
                    / FIELD(arg0, s16, 0x96);
            }
        }
    }
    FIELD(arg0, u16, 0x96)--;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    func_800AD594(arg3, 0x100);
    FIELD(arg0, s32 *, 0x8C) = &D_801719DC;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg1, s16, 2) = (FIELD(arg2, u8, 0x24) << 6) + 0x20;
    FIELD(arg1, s16, 6) = (FIELD(arg2, u8, 0x25) << 6) + 0x20;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
}
