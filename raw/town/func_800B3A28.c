#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004CBFC();
extern M2C_UNK func_800B08D4();
extern M2C_UNK func_800B0C68();
extern M2C_UNK func_800B0D0C();
extern M2C_UNK func_800B0FD4();
extern M2C_UNK D_800788E0;
extern M2C_UNK D_800792DC;
extern M2C_UNK D_800D15F4;

void func_800B1188(void *arg0) {
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    s32 temp_a0_2;
    s32 var_a2;
    void *temp_a0;

    *M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), M2C_UNK ***, 0) = &D_800788E0;
    temp_a0 = arg0 + 0x34;
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), void ***, 4) = temp_a0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), void ***, 4), void **, 4), s16 *, 0xA) = 0x2F;
    func_800B08D4(temp_a0);
    func_800B0C68(arg0);
    func_8004CBFC(arg0 + 0x28, &D_800792DC, M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), s32 *, 8));
    var_a2 = 4;
    var_a1 = 0xC8;
    var_t0 = 0x55;
    var_a3 = 0x58;
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0xCC), M2C_UNK ***, 0xC) = &D_800D15F4;
    do {
        temp_a0_2 = var_a2 * 4;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x10), void **, 4), s16 *, 8) = -0x50;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x10), void **, 4), s16 *, 0xA) = var_a3;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x24), void **, 4), s16 *, 8) = 0x56;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x24), void **, 4), s16 *, 0xA) = var_t0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x38), void **, 4), s16 *, 8) = 0x3C;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x38), void **, 4), s16 *, 0xA) = var_a1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x4C), void **, 4), s16 *, 8) = 0x8C;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x4C), void **, 4), s16 *, 0xA) = var_a1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x60), void **, 4), s16 *, 8) = 0x34;
        var_a2 -= 1;
        var_a3 -= 0x10;
        var_t0 -= 0x10;
        M2C_FIELD(M2C_FIELD(M2C_FIELD((temp_a0_2 + M2C_FIELD(arg0, s32 *, 0xCC)), void **, 0x60), void **, 4), s16 *, 0xA) = var_a1;
        var_a1 -= 0x10;
    } while (var_a2 >= 0);
    func_800B0D0C(arg0, var_a1, var_a2, var_a3);
    func_800B0FD4(arg0);
}
