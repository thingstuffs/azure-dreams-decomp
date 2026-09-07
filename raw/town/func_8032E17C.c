#include "common.h"

extern u8 D_80016000[0x10];
extern s32 D_8001C368[];

void func_8001897C(s32 arg0) {
    register void *temp_v0 ASM_REG("$2");
    register void *temp_a1 ASM_REG("$5");
    s32 val;

    temp_v0 = *(void **)D_80016000;
    temp_a1 = *(void **)((s8 *)temp_v0 + 0x40);
    ASM_KEEP(temp_a1);
    D_8001C368[0] = arg0;
    ASM_KEEP(temp_v0);
    val = *(s32 *)((s8 *)temp_a1 + 0x110);
    val = val + 1;
    val = val + (arg0 * 2);
    *(s32 *)((s8 *)temp_a1 + 0x110) = val;
}
