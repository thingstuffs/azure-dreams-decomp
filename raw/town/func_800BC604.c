#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80033D08(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8008F134(void);
extern void func_800B9EC4(void);

extern s32 D_800814A0;

void func_800B9D64(void *arg0, void *arg1)
{
    s16 angle;
    s16 angle2;
    s32 sector;
    s32 value;

    if (*FIELD(arg0, u8 *, 0x98) == 0) {
        func_8008F134();
        func_80033D08(arg0);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800B9EC4();
        return;
    }

    angle = FIELD(FIELD(arg0, void *, 0x9C), s16, 0x66);
    sector = angle / 0x200;
    if ((s8)(sector % 4) == FIELD(arg0, s8, 0x97)) {
        value = func_800644B8((s16)(angle % 0x200) * 2);
        FIELD(arg1, s32, 8) = -((value >> 4) * 0x1E00);
        FIELD(arg0, s16, 0x66) = 30;
        func_800B9EC4();
        return;
    }

    if (FIELD(arg0, s16, 0x66) != 0) {
        s32 value2;
        s32 magnitude;

        FIELD(arg0, s16, 0x66) = (u16)FIELD(arg0, s16, 0x66) - 3;
        angle2 = FIELD(FIELD(arg0, void *, 0x9C), s16, 0x66);
        magnitude = ((func_80064584((s16)(angle2 % 0x200) * 0x18) >> 4)
                     * FIELD(arg0, s16, 0x66)) << 8;
        value2 = -magnitude;
        
        FIELD(arg1, s32, 8) = value2;
        if (value2 > 0) {
            FIELD(arg1, s32, 8) = magnitude;
            func_800B9EC4();
        }
    } else {
        FIELD(arg1, s32, 8) = 0;
    }
}
