#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern s32 rand(void);
extern void func_8003DB94(void *arg0, void *arg1, s32 arg2);
extern void func_80045340(void);
extern void func_80172DFC(void);
extern u8 D_800DE870[];

void func_80172F44(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *object;
    void *transform;
    void *display;
    u8 *state;
    s32 value;
    s32 word8;
    u16 x;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = (u8 *)object + 0x20;
        FIELD(state, s16, 0x16) = 0x1A;
        FIELD(object, void *, 0x10) = func_80172DFC;
        func_8004491C(object, func_80045340);

        display = FIELD(object, void *, 0xC);
        FIELD(display, s16, 0x10) = 0x40;
        FIELD(display, s16, 6) = 6;
        FIELD(display, u16, 0x14) |= 0xC;

        transform = FIELD(object, void *, 8);
        FIELD(transform, s32, 0) = FIELD(arg0, s32, 0);
        FIELD(transform, s32, 4) = FIELD(arg0, s32, 4);
        
        x = FIELD(transform, u16, 2);
        word8 = FIELD(arg0, s32, 8);
        FIELD(transform, u16, 2) = x + arg1;
        FIELD(transform, s32, 8) = word8;
        FIELD(transform, u16, 6) += arg2;
        FIELD(transform, u16, 0xA) += arg3;

        value = rand();
        FIELD(state, s32, 0x58) = value - 0x8000;
        value = rand();
        FIELD(state, s32, 0x5C) = value - 0x8000;
        value = rand();
        FIELD(state, s32, 0x60) = value - 0x40000;

        display = FIELD(object, void *, 0xC);
        FIELD(display, s16, 0x1E) = 0x400;
        FIELD(display, s16, 0x1C) = 0x400;
        FIELD(display, u8, 0xE) = 0x16;
        FIELD(display, u8, 0xD) = 0x16;
        FIELD(display, u8, 0xC) = 0x16;
        FIELD(display, s16, 0x12) = 0x7DCF;
        FIELD(display, u16, 0x14) |= 0x100;
        func_8003DB94(display, D_800DE870, 0);
    }
}
