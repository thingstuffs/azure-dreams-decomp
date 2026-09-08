#include "common.h"

#include "common.h"

extern s8 D_80082D58[9];
extern u32 D_800814A0_scalar;
extern void func_80033D08(void *arg0);

__asm__(".set D_800814A0_scalar, 0x800814A0");

/* Processes the runtime data and sets both 0x8000 flags. */
void func_8003C364(void)
{
    u16 *runtime_data = (u16 *)D_80082D58;

    func_80033D08(runtime_data);
    runtime_data[-1] |= 0x8000;
    D_800814A0_scalar |= 0x8000;
}
