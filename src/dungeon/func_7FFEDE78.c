#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80035208();
extern s8 D_800CFC24[12];


void func_8008B5D8(s32 arg0, s32 arg1) {
    D_800CFC24[3] = (s8)(arg0 >> 8);
    D_800CFC24[2] = arg0;
    D_800CFC24[4] = (s8)(arg0 >> 0x10);
    D_800CFC24[5] = (s8)(arg0 >> 0x18);
    D_800CFC24[6] = arg1;
    func_80035208(&D_800CFC24);
}
