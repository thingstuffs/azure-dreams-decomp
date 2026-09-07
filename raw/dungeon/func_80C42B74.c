#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);

extern u8 D_80045340;
extern s32 D_800DEC00;
extern u8 D_801741A0;

void func_80174374(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5) {
    void *obj;
    void *work;
    register void *part ASM_REG("$16");
    register void *pos ASM_REG("$21");
    s16 value;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        value = arg4;
        work = (u8 *)obj + 0x20;
        FIELD(work, s16, 0x1A) = 0x14;
        FIELD(work, s16, 0x1E) = arg4;
        FIELD(obj, void *, 0x10) = &D_801741A0;
        func_8004491C(obj, &D_80045340);

        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x10) = 0x20;
        FIELD(part, u16, 0x14) |= 0xC;

        pos = FIELD(obj, void *, 8);
        FIELD(work, s32, 0x40) = FIELD(arg1, s32, 0);
        FIELD(work, s32, 0x44) = FIELD(arg1, s32, 4);

        while (value >= 0x1001) {
            value -= 0x1000;
        }

        FIELD(pos, s32, 0) = FIELD(work, s32, 0x40) + func_80064584(value) * 0x280;
        FIELD(pos, s32, 4) = FIELD(work, s32, 0x44) + func_800644B8(value) * 0x280;
        FIELD(pos, u16, 0xA) = FIELD(arg1, u16, 0xA) + arg5;

        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x400;
        FIELD(part, s16, 0x1C) = 0x400;
        FIELD(part, u8, 0xE) = 0x60;
        FIELD(part, u8, 0xD) = 0xFF;
        FIELD(part, u8, 0xC) = 0xFF;
        FIELD(work, u8, 0) = 0xFF;
        FIELD(work, u8, 1) = FIELD(part, u8, 0xD);
        FIELD(work, u8, 2) = FIELD(part, u8, 0xE);

        func_8003DB94(part, &D_800DEC00, rand() & 1);
        FIELD(part, s16, 0x12) = 0x7DCF;
        FIELD(part, u16, 0x14) |= 0x100;
    }
}
