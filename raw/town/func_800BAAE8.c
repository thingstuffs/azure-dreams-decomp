#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8009CDB4();
extern M2C_UNK func_8009CDCC();
extern M2C_UNK func_8009CE34();
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];
extern u8 D_800D43F0[];

void func_800B8248(void) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 var_a0;
    s32 var_s0;
    u8 temp_v0;
    u8 *temp_s1;
    void *temp_s4;
    void *temp_t0;
    void *temp_v0_2;

    func_8009CDB4();
    func_8009CDCC(0x3FU, 0U, 0x10U, 0x10U, D_800D43F0);
    var_s0 = 0;
    temp_s4 = (void *)0x80010000;
    temp_s1 = D_800D2644;
    do {
        var_a0 = var_s0 & 0xFF;
        temp_t0 = (void *)((var_a0 * 2) + (s32)temp_s4);
        temp_v0 = M2C_FIELD(temp_t0, u8 *, 0x33A4);
        if (temp_v0 != 0) {
            M2C_FIELD((void *)((temp_v0 << 5) + (s32)temp_s1), s16 *, 0xA) = 1;
            temp_v0_2 = (var_a0 * 8) + D_800D2EA4;
            temp_a0 = M2C_FIELD(temp_v0_2, u8 *, 0);
            temp_a1 = M2C_FIELD(temp_v0_2, u8 *, 1);
            temp_a2 = M2C_FIELD(temp_v0_2, u8 *, 2);
            temp_a3 = M2C_FIELD(temp_v0_2, u8 *, 3);
            temp_v0 = M2C_FIELD(temp_t0, u8 *, 0x33A4);
            func_8009CDCC(temp_a0, temp_a1, temp_a2, temp_a3,
                          (temp_v0 << 5) + (D_800D2644 + 0xC));
        }
        var_s0 += 1;
    } while ((u32)(u8)var_s0 < 0x21U);
    func_8009CE34();
}
