#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64();
void func_8004491C(void *, void *);
s32 func_8004DA74();
M2C_UNK func_800A6BBC();
M2C_UNK func_800B1320();
M2C_UNK func_800B135C();
M2C_UNK func_800B13CC();
M2C_UNK func_800B1400();
extern M2C_UNK D_80089074;
extern M2C_UNK D_800A6B70;
extern M2C_UNK D_800B06F0;

void *func_800A6C00(void) {
    void *temp_a2;
    void *temp_s0;
    void *temp_s1;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != 0) {
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        temp_a2 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 2) = 0x3C;
        M2C_FIELD(temp_v1, s16 *, 6) = 0x40;
        M2C_FIELD(temp_s1, s16 *, 8) = 1;
        M2C_FIELD(temp_a2, s16 *, 0x1E) = 0x1800;
        M2C_FIELD(temp_a2, s16 *, 0x1C) = 0x1800;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800A6B70;
        func_8004491C(temp_v0, &D_800B06F0);
        temp_s0 = temp_v0 + 0x30;
        M2C_FIELD(temp_v0, void **, 0x20) = (void *)(temp_v0 + 0xF0);
        M2C_FIELD(temp_s1, void **, 4) = (void *)(temp_v0 + 0xC0);
        M2C_FIELD(temp_v0, s32 *, 0xF0) = func_8004DA74(temp_s0, &D_80089074, 0) & 0x7FFFFFFF;
        func_800B1320(temp_s0, 0xA8, (s16)((0 - (s8)M2C_FIELD(temp_s0, u8 *, 3)) + 8));
        func_800A6BBC(temp_s0, 4);
        func_800B135C(temp_s0, 8);
        func_800B13CC(temp_s0, 0x20);
        func_800B1400(temp_s0, 2);
        M2C_FIELD(temp_v0, s32 *, 0xC0) = 0x808080;
        M2C_FIELD(temp_v0, s32 *, 0xF4) = 0;
    }
    return temp_v0;
}
