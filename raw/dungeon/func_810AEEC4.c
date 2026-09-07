#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170E54;
extern u8 D_80173C84[];

void func_801726C4(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96)--;
    switch (state) {
        case 0:
            if (FIELD(arg2, u16, 0x14) & 0x8000) {
                FIELD(arg0, u8, 0x9B) = 0xFF;
                FIELD(arg2, u16, 0x14) |= 0x6000;
                func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
                return;
            }
            FIELD(arg2, u8 *, 0x2C) = D_80173C84;
            func_80047784(arg2,
                D_80173C84[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, u8, 0x9B)++;
            return;

        case 1:
            if (((FIELD(arg2, s8, 4) == 6) &&
                 (FIELD(arg2, u16, 0x14) & 0x1000)) ||
                (FIELD(arg2, u16, 0x14) & 0x8000)) {
                func_800A56E0(0x808);
                func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
                FIELD(arg0, u8, 0x9B) = 0xFF;
            }
            return;

        case 0xFF:
            if (FIELD(arg2, u16, 0x14) & 0xE000) {
                func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
                func_800AD594(arg3, 0x200);
                FIELD(arg0, s32 *, 0x8C) = &D_80170E54;
                D_8008346C = 0;
                func_800A4ACC(arg3);
                if (FIELD(arg3, s8, 0x6D) == 0) {
                    FIELD(arg3, u16, 0x46) &= 0x7FFF;
                    return;
                }
                D_800E3DE8 = (u8 *)arg3 - 0x20;
            }
            return;
    }
}
