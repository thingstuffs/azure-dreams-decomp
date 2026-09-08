#include "common.h"

extern void *D_80016700[];
extern u8 D_8001B14C[];
extern u8 D_8001C018[];
extern u8 D_8001C6D0[];
extern u8 D_800227FB[];
extern void *func_80016E48(s32);

/* Selects a data pointer by ID, using default data for unhandled IDs. */
void *func_80017E6C(s32 unused_0, s32 unused_1, s32 data_id)
{
    s32 dispatch_index;
    static void *const keepalive[] = {
        &&case_19, &&case_18, &&case_12, &&case_52_54, &&default_case
    };

    (void)keepalive;
    dispatch_index = data_id - 12;
    if ((u32)dispatch_index >= 43) {
        goto default_case;
    }
    goto *D_80016700[dispatch_index];

case_19:
    return D_8001C018;

case_18:
    return D_800227FB;

case_12:
    return D_8001C6D0;

case_52_54:
    return func_80016E48(data_id);

default_case:
    return D_8001B14C;
}
