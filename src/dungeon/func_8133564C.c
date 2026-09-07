#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern void func_80047784(void *, u8, s32);
extern void func_800A56E0(s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_8016A36C[];
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern u8 D_80173A20[];
extern u8 D_80173A28[];
extern u8 D_80173A30[];
extern u8 D_80173A38[];
extern u8 D_80175DC0;
extern u8 D_80175DC1;

void func_8016C64C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 local;
    s16 count;
    s32 value;
    s32 delta;
    u8 *table;
    u8 *current;
    u8 *global;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        FIELD(arg3, s16, 0x64) = 0;
        FIELD(arg0, u8, 0x9B)++;
        D_80175DC1 = 0;
        FIELD(arg0, s16, 0x96) = 6;
        if (FIELD(arg0, u8, 0xB0) < 2) {
            return;
        }
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &local);
        FIELD(arg0, s16, 0x94) = 1;
        return;

    case 1:
        count = --FIELD(arg0, u16, 0x96);
        if (count > 0) {
            FIELD(arg1, s32, 0xC) =
                FIELD((u8 *)&D_8006CCD8,
                      s16, (FIELD(arg3, u16, 0x6A) >> 8) & 0xE) << 18;
            FIELD(arg1, s32, 0x10) =
                FIELD((u8 *)&D_8006CCE8,
                      s16, (FIELD(arg3, u16, 0x6A) >> 8) & 0xE) << 18;
            return;
        }
        if (count != 0) {
            return;
        }
        FIELD(arg1, s32, 0xC) =
            FIELD((u8 *)&D_8006CCD8,
                  s16, (FIELD(arg3, u16, 0x6A) >> 8) & 0xE) << 18;
        FIELD(arg1, s32, 0x10) =
            FIELD((u8 *)&D_8006CCE8,
                  s16, (FIELD(arg3, u16, 0x6A) >> 8) & 0xE) << 18;
        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        count = FIELD(arg0, s16, 0x96);
        if (count != 0) {
            value = FIELD(arg2, u8, 0x24) << 6;
            delta = FIELD(arg1, s16, 2);
            delta -= 0x20;
            FIELD(arg1, s32, 0xC) =
                ((value - delta) << 16) / count;
            value = FIELD(arg2, u8, 0x25) << 6;
            delta = FIELD(arg1, s16, 6);
            delta -= 0x20;
            FIELD(arg1, s32, 0x10) =
                ((value - delta) << 16) / FIELD(arg0, s16, 0x96);
        }
        if (FIELD(arg0, s16, 0x96)-- > 0) {
            return;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg0, u8, 0x9B)++;

        switch (FIELD(arg0, u8, 0xAC)) {
        case 0:
            table = D_801739A0;
            if (FIELD(arg2, u8 *, 0x2C) == table) {
                return;
            }
            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(
                arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        case 1:
            current = FIELD(arg2, u8 *, 0x2C);
            table = D_801739A8;
            if (current == table) {
                return;
            }
            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(
                arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        case 2:
            current = FIELD(arg2, u8 *, 0x2C);
            table = D_801739B0;
            if (current == table) {
                return;
            }
            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(
                arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        case 3:
            table = D_801739B8;
            if (FIELD(arg2, u8 *, 0x2C) == table) {
                return;
            }
            FIELD(arg2, u8 *, 0x2C) = table;
            func_80047784(
                arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        default:
            return;
        }

    case 3:
        if (D_80175DC1 != 0) {
            if (D_80175DC0 == 0) {
                return;
            }
            if (FIELD(arg3, u8, 0x28) == 0) {
                FIELD(arg0, s16, 0x96) = 0;
                FIELD(arg0, u8, 0x9B) += 2;
                return;
            }
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B)++;
            func_800A56E0(0x300);
            return;
        }
        FIELD(arg0, u8, 0x9B) += 2;
        return;

    case 4:
        count = ++FIELD(arg0, u16, 0x96);
        if (count < 0x50) {
            return;
        }
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 5:
        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0xC) = 0;
            switch (FIELD(arg0, u8, 0xAC)) {
            case 0:
                func_800AAA54(arg0, arg1, arg2, D_80173A20);
                return;
            case 1:
                func_800AAA54(arg0, arg1, arg2, D_80173A28);
                return;
            case 2:
                func_800AAA54(arg0, arg1, arg2, D_80173A30);
                return;
            case 3:
                func_800AAA54(arg0, arg1, arg2, D_80173A38);
                return;
            default:
                return;
            }
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        global = (u8 *)&D_80083460;
        if (FIELD(global, u8 *, 0x10) == (u8 *)arg3 - 0x20) {
            FIELD(global, u32, 0x10) &= 0x7FFFFFFF;
        }
        FIELD(arg0, u8 *, 0x8C) = D_8016A36C;
        return;
    }
}
