#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 D_80024398[];
extern s32 D_80045340[];

void func_800244BC(s32 arg0, void *arg1)
{
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    u16 flags;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v0_2, s16, 0x28) = 0x27;
        FIELD(temp_v0_2, s16, 0x2A) = 0x27;
        FIELD(temp_v0_2, s32, 0x20) = arg0;
        FIELD(temp_v0, void *, 0x10) = D_80024398;
        func_8004491C(temp_v0, D_80045340);
        temp_v1 = FIELD(temp_v0, void *, 8);
        FIELD(temp_v1, s32, 0) = FIELD(arg1, s32, 0);
        FIELD(temp_v1, s32, 4) = FIELD(arg1, s32, 4);
        FIELD(temp_v1, s32, 8) = FIELD(arg1, s32, 8);
        temp_v1_2 = FIELD(temp_v0, void *, 0xC);
        flags = FIELD(temp_v1_2, u16, 0x14);
        FIELD(temp_v1_2, s16, 0x1E) = 0x1000;
        FIELD(temp_v1_2, s16, 0x1C) = 0x1000;
        FIELD(temp_v1_2, u8, 0xE) = 0x80;
        FIELD(temp_v1_2, u8, 0xD) = 0x80;
        FIELD(temp_v1_2, u8, 0xC) = 0x80;
        FIELD(temp_v1_2, u16, 0x14) = flags | 0x80;
    }
}
