#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 D_800269B4;
extern s32 D_800814A0;

void func_8196BE48(void *arg0, s32 arg1, void *arg2) {
    u8 *obj = arg0;
    u8 *page = (u8 *)&D_800269B4 - 0x69B4;
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v0_3;

    FIELD(obj, u16, 0x2C) = (u16)(FIELD(obj, u16, 0x2C) - 1);
    FIELD(arg2, u16, 0x1C) = (u16)(FIELD(arg2, u16, 0x1C) + 0x7C);
    FIELD(arg2, u16, 0x1E) = (u16)(FIELD(arg2, u16, 0x1E) + 0x54);
    temp_v0 = FIELD(obj, u16, 0x34) + 1;
    *(s16 *)(page + 0x69B4) = 1;
    FIELD(obj, u16, 0x34) = temp_v0;
    if ((s16)temp_v0 == 3) {
        temp_v0_2 = FIELD(obj, u16, 0x50) + 1;
        FIELD(obj, u16, 0x50) = temp_v0_2;
        if ((s16)temp_v0_2 < 7) {
            FIELD(obj, u16, 0x34) = 0;
            temp_v0_3 = FIELD(obj, u8, 0x40) + 0x18;
            FIELD(obj, u8, 0x40) = temp_v0_3;
            if ((temp_v0_3 & 0xFF) == 0x60) {
                FIELD(obj, u8, 0x40) = 0;
                FIELD(obj, u8, 0x41) = (u8)(FIELD(obj, u8, 0x41) + 0x20);
            }
        }
    }
    if ((s16)FIELD(obj, u16, 0x2C) <= 0) {
        FIELD(obj, u16, -2) = (u16)(FIELD(obj, u16, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
