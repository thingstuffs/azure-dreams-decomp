#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80035208();
extern s8 D_800CFC24[12];


/* Packs a value and command byte into the global buffer and submits it. */
void func_8008B5D8(s32 value, s32 command) {
    D_800CFC24[3] = (s8)(value >> 8);
    D_800CFC24[2] = value;
    D_800CFC24[4] = (s8)(value >> 0x10);
    D_800CFC24[5] = (s8)(value >> 0x18);
    D_800CFC24[6] = command;
    func_80035208(&D_800CFC24);
}
