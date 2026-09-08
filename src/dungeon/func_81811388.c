#include "common.h"

extern s32 func_80049DE8(s32 a0, s32 a1, s32 a2);
extern u8 D_800294F8[];

void func_80026388(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 value ASM_REG("$2") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    volatile u8 *table = D_800294F8;

    func_80049DE8(arg1, value, table[arg2]);
}
