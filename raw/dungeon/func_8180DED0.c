#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 D_80026E3C;
extern s32 D_80045340;
extern s32 D_80083498;
extern s32 D_800DF358;

void *func_80026ED0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    register s16 p1 ASM_REG("$18");
    register s16 p2 ASM_REG("$19");
    register s16 p3 ASM_REG("$20");

    p1 = arg1;
    p2 = arg2;
    p3 = arg3;

    temp_v0 = func_8003FD64(0x12, &D_80083498);
    ASM_KEEP(p1);
    ASM_KEEP(p2);
    ASM_KEEP(p3);
    if (temp_v0 != NULL) {
        FIELD(temp_v0, void *, 0x10) = &D_80026E3C;
        func_8004491C(temp_v0, &D_80045340);
        temp_v0_2 = FIELD(temp_v0, void *, 8);
        FIELD(temp_v0_2, s16, 2) = arg0;
        FIELD(temp_v0_2, s16, 6) = p1;
        FIELD(temp_v0_2, s16, 0xA) = p2;
        temp_v1 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_v1, void *, 8) = &D_800DF358;
        FIELD(temp_v1, s32, 0xC) = 0x808080;
        FIELD(temp_v1, s16, 0x1E) = p3;
        FIELD(temp_v1, s16, 0x1C) = p3;
        FIELD(temp_v1, s16, 0x10) = 0x20;
        FIELD(temp_v1, u16, 0x14) |= 0xC;
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v1_2, s16, 0x66) = 0x20;
        FIELD(temp_v1_2, s16, 0x6A) = 0x80;
    }
    return temp_v0;
}
