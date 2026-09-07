#include "common.h"

#include "common.h"

extern s8 D_80082D58[9];
extern u32 D_800814A0_scalar;
extern void func_80033D08(void *arg0);

__asm__(".set D_800814A0_scalar, 0x800814A0");

void func_8003C364(void)
{
    u16 *base = (u16 *)D_80082D58;

    func_80033D08(base);
    base[-1] |= 0x8000;
    D_800814A0_scalar |= 0x8000;
}
