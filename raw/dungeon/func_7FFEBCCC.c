#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003A7C4();
void *func_8003CF18();
extern u16 D_80094422[5];
extern M2C_UNK D_800E2BB8;
extern M2C_UNK D_8010D648;

void func_7FFEBCCC(void *arg0, s32 arg1) {
    s32 temp_arg1;
    void *temp_a0;
    void *temp_a0_2;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003CF18(0x12);
    if (temp_v0 != NULL) {
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8010D648;
        M2C_FIELD(temp_v0, void **, 0x44) = arg0;
        M2C_FIELD(temp_v0, s16 *, 0x3E) = 0x32;
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a0, u16 *, 0x14) =
            (u16)(M2C_FIELD(temp_a0, u16 *, 0x14) | 0xC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, u16 *, 2) =
            (u16)M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2);
        M2C_FIELD(temp_v1, u16 *, 6) =
            (u16)M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 0xA) =
            (u16)M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA);
        temp_a0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a0_2, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_a0_2, u8 *, 0xC) = 0x80;
        temp_arg1 = *(volatile s32 *)&arg1;
        M2C_FIELD(temp_a0_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0_2, s32 *, 0xC) = temp_arg1;
        M2C_FIELD(temp_v0, s32 *, 0x2C) = temp_arg1;
        M2C_FIELD(temp_a0_2, s16 *, 0x12) = 0x7DCE;
        M2C_FIELD(temp_a0_2, u16 *, 0x14) =
            (u16)(M2C_FIELD(temp_a0_2, u16 *, 0x14) | 0x100);
        func_8003A7C4(temp_a0_2, &D_800E2BB8, 0);
        D_80094422[0] += 1;
    }
}
