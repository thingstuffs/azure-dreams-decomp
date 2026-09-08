#include "common.h"

extern u8 D_80016000[0x10];

/* Copy three signed 16-bit components into the current 32-bit component array. */
void func_80019B70(s16 *components) {
    {
        s32 *output_components = *(s32 **)((u8 *)*(s32 **)D_80016000 + 0x1C);
        output_components[0] = components[0];
    }
    {
        s32 *context = *(s32 **)D_80016000;
        ((s32 *)*(s32 **)((u8 *)context + 0x1C))[1] = components[1];
        ((s32 *)*(s32 **)((u8 *)context + 0x1C))[2] = components[2];
    }
}
