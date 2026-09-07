#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_801747BC(void) __attribute__((noreturn));
extern s32 D_800814A0;

void func_80174600(void *arg0, s32 arg1, void *arg2)
{
    u8 *p = arg0;
    s16 timer;
    s32 value;
    s32 diff;
    u8 channel;

    FIELD(arg2, u16, 0x1A) += 0x320;

    if (FIELD(p, s16, 0x1A) >= 0x33) {
        FIELD(arg2, s8, 0xC) = (p[0] * (0x41 - FIELD(p, s16, 0x1A))) / 14;
        FIELD(arg2, u8, 0xD) = (p[1] * (0x41 - FIELD(p, s16, 0x1A))) / 14;
        FIELD(arg2, u8, 0xE) = (p[2] * (0x41 - FIELD(p, s16, 0x1A))) / 14;
        func_801747BC();
        return;
    }

    if (FIELD(p, s16, 0x1A) < 0x1A) {
        if (FIELD(p, s16, 0x1A) >= 0x10) {
            diff = (p[0] - p[1]) / (FIELD(p, s16, 0x1A) - 0xF);
            channel = p[1] + diff;
            p[1] = channel;
            FIELD(arg2, u8, 0xD) = channel;

            diff = (p[0] - p[2]) / (FIELD(p, s16, 0x1A) - 0xF);
            channel = p[2] + diff;
            p[2] = channel;
            FIELD(arg2, u8, 0xE) = channel;
            func_801747BC();
            return;
        }

        if (FIELD(p, s16, 0x1A) >= 8) {
            value = p[0] * (FIELD(p, s16, 0x1A) - 8);
            if (value < 0) {
                value += 7;
            }
            FIELD(arg2, s8, 0xC) = value >> 3;

            value = p[1] * (FIELD(p, s16, 0x1A) - 8);
            if (value < 0) {
                value += 7;
            }
            FIELD(arg2, u8, 0xD) = value >> 3;

            value = p[2] * (FIELD(p, s16, 0x1A) - 8);
            FIELD(arg2, u8, 0xE) = value / 8;
            func_801747BC();
            return;
        }

        FIELD(p, s16, 0x1A) = 0;
    }

    timer = FIELD(p, u16, 0x1A) - 1;
    FIELD(p, s16, 0x1A) = timer;
    if ((timer << 16) <= 0) {
        FIELD(p, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
