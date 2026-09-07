#include "common.h"

extern u8 D_800E3648[];
extern void func_80095530(s32);

s32 func_800954E0(void *arg0) {
    s32 cursor;
    s32 result;
    u8 *base;
    u8 flags;

    cursor = *(s16 *)((u8 *)arg0 + 0x100);
    result = 1;
    if (cursor >= 0) {
        base = D_800E3648;
        
        cursor = (s32)(base + cursor * 4);
        
        flags = *((u8 *)cursor + 3);
        if (!(flags & 0x80)) {
            func_80095530(flags);
            return 1;
        }
        if (flags & 0x40) {
            result = 0;
            goto done;
        }
        *((u8 *)cursor + 3) = flags & 0x7F;
        result = 0;
    }
done:
    
    return result;
}

/* MECHANISM: Frameless leaf; an s32 cursor held in $v1 changes role from signed index
   to record address, with the named base created before scaling to fix emission order.
   A path-local $v0 zero edge and SHAPE-C constant return reproduce both tail slots. */
