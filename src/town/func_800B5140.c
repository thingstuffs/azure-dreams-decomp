#include "common.h"

extern u8 D_800133E6;
extern u8 D_80089260[];

s32 func_800B28A0(void) {
    u8 list[6];
    u8 *cursor;
    s32 index;
    s32 first;
    s32 wanted;

    memcpy(list, D_80089260, sizeof(list));
    first = list[0];
    
    wanted = (s32)0x80010000;
    
    wanted = *(u8 *)(wanted + 0x33E6);
    index = 0;
    if (first != 0) {
        cursor = list;
        do {
            if (*cursor == wanted) {
                return index;
            }
            cursor++;
            index++;
        } while (*cursor != 0);
    }
    return index;
}

/* MECHANISM: A six-byte array copy forces the 8-byte leaf frame and exact
   lwl/lwr plus byte-tail copy; the pointer/count do-loop fixes the scan CFG.
   At CDK, guarded $v0 first-byte and reused $a1 page/value live ranges close
   the final load-order/register residue. */
