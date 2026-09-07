#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64();
s32 func_8004491C();
extern s32 D_800A3918[];
extern s32 D_800A3B1C[];
extern s32 D_800D0C40[];
typedef struct {
    s16 value;
    u8 pad[10];
} LargeS16;
extern LargeS16 D_80100D88;
extern LargeS16 D_80100D8A;

void func_800A47A8(s16 arg0) {
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1;
    void *temp_v1_2;
    s32 shifted;
    s32 *table;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 **, 0x10) = D_800A3918;
        func_8004491C(temp_v0, D_800A3B1C);
        shifted = arg0 << 0x10;
        ASM_USE(shifted);
        table = D_800D0C40;
        ASM_USE(table);
        shifted >>= 0xE;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 0xC), s32 *, 8) =
            *(s32 *)((s8 *)table + shifted);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, u8 *, 0xE) = 0xE0;
        M2C_FIELD(temp_v1, u8 *, 0xD) = 0xE0;
        M2C_FIELD(temp_v1, u8 *, 0xC) = 0xE0;
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        D_80100D88.value = 0;
        M2C_FIELD(temp_v1, s16 *, 2) = 0;
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        D_80100D8A.value = 0;
        M2C_FIELD(temp_v1, s16 *, 6) = 0;
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1, s16 *, 0xA) = 0x4000;
        temp_v0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0_2, s16 *, 0xC) = arg0;
        M2C_FIELD(temp_v0_2, s16 *, 2) = 0;
        M2C_FIELD(temp_v0_2, s16 *, 0x12) = 0;
        M2C_FIELD(temp_v0_2, s16 *, 0x14) = 0x80;
    }
}
