#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_800373DC();
extern void func_8003BC18();
extern u8 D_8003C558[12];
extern u8 D_8052F210[];
extern u8 D_80284430[];
extern s32 D_80284434[];

void func_808138C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_a0;
    void *temp_v0;
    s32 temp_v1;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, s32, 0x10) = (s32)D_8052F210;
        func_8003BC18(temp_v0, D_8003C558);
        temp_a0 = FIELD(temp_v0, void *, 0xC);
        FIELD(FIELD(temp_v0, void *, 8), s32, 0) = arg1;
        FIELD(FIELD(temp_v0, void *, 8), s32, 4) = arg2;
        FIELD(FIELD(temp_v0, void *, 8), s32, 8) = arg3;
        FIELD(temp_a0, s16, 0x1E) = 0x1000;
        FIELD(temp_a0, s16, 0x1C) = 0x1000;
        FIELD(temp_a0, s32, 0) = (s32)D_80284430;
        temp_v1 = D_80284434[0];
        FIELD(temp_a0, s8, 4) = 0;
        FIELD(temp_a0, s8, 5) = 0;
        FIELD(temp_a0, s32, 0xC) = arg0;
        FIELD(temp_a0, s32, 8) = temp_v1;
        if (arg0 != 0x808080) {
            if (arg0 == 0xF0F0F0) {
                FIELD(temp_a0, s16, 0x10) = 0x60;
                FIELD(FIELD(temp_v0, void *, 8), s32, 0x14) = 0xFFF00000;
                goto block_4;
            }
        } else {
block_4:
            FIELD(temp_a0, u16, 0x14) = FIELD(temp_a0, u16, 0x14) | 0xC;
        }
    }
}
