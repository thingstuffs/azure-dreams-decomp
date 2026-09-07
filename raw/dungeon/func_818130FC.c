#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80027AD0();
extern M2C_UNK func_8004CBFC();
extern M2C_UNK D_80078AB4;
extern M2C_UNK D_80078AD8;
extern M2C_UNK D_80079324;

void func_800280FC(void *arg0, void *arg1) {
    s16 var_a0;
    s16 var_a2;
    s32 var_a1;
    void **var_v1;
    void *temp_v0;

    *M2C_FIELD(arg1, M2C_UNK ***, 0) = &D_80078AB4;
    *M2C_FIELD(arg1, M2C_UNK ***, 4) = &D_80078AD8;
    func_8004CBFC(arg0 + 0x2C, &D_80079324, M2C_FIELD(arg1, s32 *, 8));
    *M2C_FIELD(arg1, s32 **, 0xC) = 0;
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x10), s32 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg1, void **, 0x10), void **, 4), s16 *, 8) = 0x58;
    *M2C_FIELD(arg1, s32 **, 0x14) = M2C_FIELD(arg0, s32 *, 0x4C) + 0x18;
    func_80027AD0(arg0, 0, 1);
    var_a1 = 6;
    var_a2 = 0x58;
    var_a0 = 0x90;
    var_v1 = arg1 + 0x18;
    do {
        M2C_FIELD(*var_v1, s32 *, 0) = 0;
        M2C_FIELD(M2C_FIELD(*var_v1, void **, 4), s16 *, 8) = var_a2;
        var_a1 += 1;
        temp_v0 = M2C_FIELD(*var_v1, void **, 4);
        var_v1 = (void **)((s8 *)((void **)((s8 *)var_v1 + 4)));
        M2C_FIELD(temp_v0, s16 *, 0xA) = var_a0;
        var_a0 += 0x10;
    } while (var_a1 < 0xE);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg1, void **, 0x38), void **, 4), s16 *, 8) = 0x4C;
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x38), s32 *, 0) = 0;
}
