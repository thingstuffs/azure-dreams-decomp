#include "common.h"

extern s32 func_80049DE8(s32 a0, s32 a1, s32 a2);
extern u8 D_800294F8[];

/* Call func_80049DE8 with the target, input value, and indexed table byte. */
void func_80026388(s32 input_value, s32 target, s32 lookup_index)
{
    register s32 value ASM_REG("$2") = input_value;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    volatile u8 *table = D_800294F8;

    func_80049DE8(target, value, table[lookup_index]);
}
