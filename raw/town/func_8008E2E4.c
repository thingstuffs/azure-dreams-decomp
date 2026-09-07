#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern s32 D_800CFC7C[];

void func_8008BA44(void *obj)
{
    void *inner;
    void *test_inner;
    s32 data;

    inner = FIELD(obj, void *, 0);
    FIELD(inner, u16, 0xA) = (u16)(FIELD(inner, u16, 0xA) - 0x100);
    test_inner = FIELD(obj, void *, 0);
    if (FIELD(test_inner, s16, 0xA) < 0) {
        FIELD(test_inner, u16, 0xA) = 0;
        FIELD(obj, void *, 0x68) = D_8008BC58;
        FIELD(obj, volatile s16, 0x64) = (s8)D_800CFC70[FIELD(obj, s16, 0x66)];
        data = D_800CFC7C[FIELD(obj, s16, 0x66)];
        FIELD(obj, s16, 0x64) = 0x16;
        FIELD(obj, s32, 0x6C) = data;
    }
}
