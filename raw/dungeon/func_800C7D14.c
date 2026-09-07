#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 func_800419EC();
extern s32 func_800A56E0();
extern s32 func_800CD66C();
extern s32 func_800CD6AC();
extern s32 D_800814A0;
extern s32 D_80083460;

void func_800CD474(void *arg0, void *arg1, void *arg2) {
    s16 state;
    s32 color;
    u16 timer;
    u16 timer2;
    u16 timer3;
    u16 value;
    s32 *global_base;

    state = FIELD(arg0, s16, 4);
    if (state == 0) {
        FIELD(arg1, s32, 0x14) += 0x20000;
        timer = FIELD(arg0, u16, 6) - 1;
        FIELD(arg0, u16, 6) = timer;
        if ((timer << 16) == 0) {
            func_800A56E0(0x701);
        }
        if ((FIELD(arg1, s16, 0xA) + 0x10) >= FIELD(arg0, s16, 0xA)) {
            func_800419EC(8, 8);
            value = FIELD(arg0, u16, 0xA);
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s16, 0xA) = value;
            FIELD(arg0, u16, 6) = 8;
            FIELD(arg0, s16, 4) = (u16)FIELD(arg0, s16, 4) + 1;
            func_800A56E0(0x612);
        }
        color = 0x404040;
        if (FIELD(arg0, u16, 0xC) & 1) {
            color = 0x808080;
        }
        FIELD(arg2, s32, 0xC) = color;
        func_800CD66C();
        return;
    }
    if (state == 1) {
        color = 0x404040;
        if (FIELD(arg0, u16, 0xC) & 1) {
            color = 0x808080;
        }
        FIELD(arg2, s32, 0xC) = color;
        timer2 = FIELD(arg0, u16, 6) - 1;
        FIELD(arg0, u16, 6) = timer2;
        if ((timer2 << 16) <= 0) {
            FIELD(arg0, u16, 6) = 0x10;
            FIELD(arg2, s32, 0xC) = 0x808080;
            FIELD(arg0, s16, 4) = (u16)FIELD(arg0, s16, 4) + 1;
            if (FIELD(arg0, s16, 8) == 0) {
                func_800CD6AC(FIELD(arg0, s32, 0), 0x10);
                func_800CD66C();
                return;
            }
        }
        FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
        FIELD(arg0, u16, 0xC) += 1;
        return;
    }
    FIELD(arg2, u8, 0xC) = FIELD(arg2, u8, 0xC) -
                           (FIELD(arg2, u8, 0xC) / (s16)FIELD(arg0, u16, 6));
    FIELD(arg2, u8, 0xD) = FIELD(arg2, u8, 0xD) -
                           (FIELD(arg2, u8, 0xD) / (s16)FIELD(arg0, u16, 6));
    FIELD(arg2, u8, 0xE) = FIELD(arg2, u8, 0xE) -
                           (FIELD(arg2, u8, 0xE) / (s16)FIELD(arg0, u16, 6));
    timer3 = FIELD(arg0, u16, 6) - 1;
    FIELD(arg0, u16, 6) = timer3;
    if ((timer3 << 16) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        global_base = &D_80083460;
        FIELD(global_base, u16, 0xA) -= 1;
    }
    FIELD(arg1, s32, 8) += FIELD(arg1, s32, 0x14);
    FIELD(arg0, u16, 0xC) += 1;
}
