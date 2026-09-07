#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8003F540();
extern M2C_UNK func_80053DA8();
extern M2C_UNK func_800C2E84();

extern M2C_UNK D_80082660[3];
extern M2C_UNK D_800CC4B0[3];
extern M2C_UNK D_800D6CF0[3];

void func_800CC41C(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8003F540(0, 0x2C3D, 0x02000002, 0x010000EA);
    func_80053DA8(0x300);
    func_800C2E84(arg0, arg2, &D_800D6CF0);
    *((s8 *)D_80082660 + (M2C_FIELD(arg0, s32 *, 0x60) * 8)) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800CC4B0;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0x19;
}
