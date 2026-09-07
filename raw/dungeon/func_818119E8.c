#include "common.h"

extern s32 func_80048EE4(void *arg0, s32 arg1);
extern void func_800491CC(s32 arg0, void *arg1, s32 arg2);

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

extern Vec3 D_8002E5E8;

s32 func_800269E8(void *arg0)
{
    register Vec3 *temp_v1 ASM_REG("$3");
    register s32 temp_v0 ASM_REG("$2");
    s32 var_s1 = 0;

    temp_v0 = func_80048EE4((s8 *)arg0 + 0x74, 4);
    ASM_KEEP(temp_v0);
    *(s32 *)((s8 *)arg0 + 0x70) = temp_v0;
    if (temp_v0 != 0) {
        register s32 call_arg ASM_REG("$4") = temp_v0;

        ASM_KEEP(call_arg);
        temp_v1 = &D_8002E5E8;
        *(s32 *)((s8 *)arg0 + 0x54) = temp_v1->x;
        *(s32 *)((s8 *)arg0 + 0x58) = temp_v1->y;
        *(s32 *)((s8 *)arg0 + 0x5C) = temp_v1->z;
        func_800491CC(call_arg, (s8 *)arg0 + 0x54, 4);
        var_s1 = 1;
    }
    return var_s1;
}
