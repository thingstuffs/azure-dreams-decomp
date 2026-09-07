#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8003F540();
extern M2C_UNK func_80053DA8();
extern M2C_UNK func_800C2E84();

extern M2C_UNK D_80082660[3];
extern M2C_UNK D_800CC4B0[3];
extern M2C_UNK D_800D6CF0[3];

typedef struct S_800CC41C_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    s16 unk_6C;
} S_800CC41C_0;   /* arg0 in func_800CC41C */

void func_800CC41C(S_800CC41C_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8003F540(0, 0x2C3D, 0x02000002, 0x010000EA);
    func_80053DA8(0x300);
    func_800C2E84(arg0, arg2, &D_800D6CF0);
    *((s8 *)D_80082660 + (arg0->unk_60 * 8)) = 0;
    arg0->unk_54 = &D_800CC4B0;
    arg0->unk_6C = 0x19;
}
