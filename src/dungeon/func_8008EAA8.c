#include "common.h"

extern void func_80094260(void);
extern void func_80099844(s32, void *);
extern s32 D_80012090[];
extern u8 D_800E0600[];
extern s32 D_800E3D7C;

s32 func_80094208(s32 arg0) {
    s32 value;

    {
        s32 *base = &D_800E3D7C;

        value = *(s32 *)((s8 *)(((s32)(arg0 << 0x10) >> 0xE) + *base) + 0xAC);
    }
    if (value != 0) {
        s32 one = 1;

        ASM_KEEP(one);   /* MATCH pin: retail basic-block layout depends on it */
        if (D_80012090[0] == one) {
            func_80099844(value, D_800E0600);
            func_80094260();
            return 1;
        }
    }
    return 0;
}
