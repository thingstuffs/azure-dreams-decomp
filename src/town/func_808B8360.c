#include "common.h"

extern void func_80003BCC(s32 arg0);
extern s32 D_000045F8[];
extern s32 D_00004148[];

/* Call func_80003BCC and return the base value plus its adjustment. */
s32 func_808B8360(void) {
    s32 base_value;
    s32 adjustment;
    s32 result;

    func_80003BCC(0x20C);
    base_value = D_000045F8[0];
    adjustment = D_00004148[0];
    result = base_value + adjustment;
    return result;
}
