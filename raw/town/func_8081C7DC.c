#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

void *func_8003FC64();
void func_8004491C();
s32 rand();

extern u8 D_800268DC[];
extern u8 D_80045340[];
extern u8 D_800F1564[];

void func_800267DC(void *arg0) {
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, void *, 0x10) = D_800268DC;
        func_8004491C(temp_v0, D_80045340);
        temp_s1 = FIELD(temp_v0, void *, 8);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s1, s32, 0) = FIELD(arg0, s32, 0) + 0xFFF90000;
        FIELD(temp_s1, s32, 4) = FIELD(arg0, s32, 4) + 0xFFFD0000;
        FIELD(temp_s1, s32, 8) = FIELD(arg0, s32, 8);
        FIELD(temp_s1, s32, 0xC) = FIELD(arg0, s32, 0xC) >> 1;
        FIELD(temp_s1, s32, 0x14) = ((rand() & 0x1FF) - 0x100) << 10;
        FIELD(temp_s0, s16, 0x1E) = 0x800;
        FIELD(temp_s0, s16, 0x1C) = 0x800;
        FIELD(temp_s0, s16, 0x10) = 0x60;
        FIELD(temp_s0, void *, 0) = D_800F1564;
        FIELD(temp_s0, u16, 0x14) |= 0xD;
        FIELD(temp_s0, s32, 8) = FIELD(D_800F1564, s32, 4);
        FIELD(temp_s0, s8, 4) = 0;
        FIELD(temp_s0, s8, 5) = 0;
        FIELD(temp_s0, s32, 0xC) = 0x8080F0;
    }
}
