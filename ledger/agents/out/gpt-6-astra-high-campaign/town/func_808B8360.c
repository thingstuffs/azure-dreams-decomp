#include "common.h"

extern void func_80003BCC(s32 arg0);
extern s32 D_000045F8[];
extern s32 D_00004148[];

/* Call func_80003BCC and return the base value plus its adjustment. */
s32 func_808B8360(void) {
    s32 base_value;
    s32 adjustment;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    func_80003BCC(0x20C);
    base_value = D_000045F8[0];
    adjustment = D_00004148[0];
    result = base_value + adjustment;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return result;
}
