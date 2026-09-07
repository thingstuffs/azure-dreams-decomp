#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
typedef s32 (*Callback)(s32);

extern s8 D_80016000[];

void func_800164E0(void) {
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;

    FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20), Callback, 0x248)(0);
    temp_v1 = FIELD(FIELD(D_80016000, void *, 0), void *, 0x1C);
    FIELD(temp_v1, s32, 0x10) = FIELD(temp_v1, s32, 4) + 0x20;
    temp_v1_2 = FIELD(FIELD(D_80016000, void *, 0), void *, 0x1C);
    FIELD(temp_v1_2, s32, 0x14) = FIELD(temp_v1_2, s32, 8);
    FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20), Callback, 0x258)(0xD);
    temp_v1_3 = FIELD(FIELD(D_80016000, void *, 0), void *, 0x1C);
    FIELD(temp_v1_3, s32, 0x18) = FIELD(temp_v1_3, s32, 4);
    temp_v1_4 = FIELD(FIELD(D_80016000, void *, 0), void *, 0x1C);
    FIELD(temp_v1_4, s32, 0x1C) = FIELD(temp_v1_4, s32, 8);
}
