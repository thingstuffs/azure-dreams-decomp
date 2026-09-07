#include "common.h"

extern void *D_80016A70[];
extern u8 D_8001B14C[];
extern u8 D_8001C6D0[];
extern u8 D_800227FB[];
extern u8 D_8001C018[];
extern void *func_80016E48(s32);

void *func_80018510(s32 arg0, s32 arg1, s32 arg2)
{
    s32 index;
    static void *const keepalive[] = {
        &&case_19, &&case_18, &&case_12, &&case_52_54, &&default_case
    };

    (void)keepalive;
    index = arg2 - 6;
    if ((u32)index >= 49) {
        goto default_case;
    }
    goto *D_80016A70[index];

case_19:
    return D_8001C6D0;

case_18:
    return D_8001C018;

case_12:
    return D_800227FB;

case_52_54:
    return func_80016E48(arg2);

default_case:
    return D_8001B14C;
}

/* MECHANISM: Preserve the seed's 0x18 frame, ra-only save, extern jump-table dispatch,
   and shared return epilogue. The sole residue was word 2's switch bias:
   index = arg2 - 6 emits retail's addiu v1,a0,-6 and closes all 33 words. */
