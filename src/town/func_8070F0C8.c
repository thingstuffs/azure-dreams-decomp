#include "common.h"

extern void *D_80016860[43];
extern u8 D_800227FB[];
extern u8 D_8001B14C[];
extern u8 D_8001C018[];

extern u8 *func_80016E48(u32);
extern u8 *func_80017C08(s32);

u8 *func_800180C8(s32 arg0, s32 arg1, s32 arg2)
{
    s32 index;
    void *target;
    void **entry;
    register s32 selector ASM_REG("$6") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void **table;
    static void *const keepalive[] = {
        &&case_12,
        &&case_19,
        &&case_18,
        &&case_52_54,
        &&default_case
    };

    (void)keepalive;
    index = selector - 12;
    if ((u32)index >= 43) {
        goto default_case;
    }
    table = D_80016860;
    entry = (void **)((u32)(index << 2) + (u32)table);
    target = *entry;
    goto *target;

case_12:
    return func_80017C08(arg0);

case_19:
    return D_8001C018;

case_18:
    return D_800227FB;

case_52_54:
    return func_80016E48(selector);

default_case:
    return D_8001B14C;
}
