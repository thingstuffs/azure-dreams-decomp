#include "common.h"

extern void func_80003BCC(s32 arg0);
extern s32 D_000045F8[];
extern s32 D_00004148[];

s32 func_808B8360(void) {
    s32 first_value;
    s32 second_value;
    register s32 result ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

    func_80003BCC(0x20C);
    first_value = D_000045F8[0];
    second_value = D_00004148[0];
    result = first_value + second_value;
    ASM_KEEP(result);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return result;
}
