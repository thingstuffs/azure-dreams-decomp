#include "common.h"

extern void *D_80016A70[];
extern u8 D_8001B14C[];
extern u8 D_8001C6D0[];
extern u8 D_800227FB[];
extern u8 D_8001C018[];
extern void *func_80016E48(s32);

/* Returns the data pointer selected by the given selector. */
void *func_80018510(s32 unused_0, s32 unused_1, s32 selector)
{
    s32 table_index;
    static void *const keepalive[] = {
        &&case_19, &&case_18, &&case_12, &&case_52_54, &&default_case
    };

    (void)keepalive;
    table_index = selector - 6;
    if ((u32)table_index >= 49) {
        goto default_case;
    }
    goto *D_80016A70[table_index];

case_19:
    return D_8001C6D0;

case_18:
    return D_8001C018;

case_12:
    return D_800227FB;

case_52_54:
    return func_80016E48(selector);

default_case:
    return D_8001B14C;
}
