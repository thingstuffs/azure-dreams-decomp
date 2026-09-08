#include "common.h"

#include "common.h"

extern u8 D_80082E6A[];
extern s32 D_80080A6C;

extern s32 func_8003C634(s32 key);
extern void func_8003C6F8(s32 key, s32 index);

/* Returns the key's index, assigning the last index if lookup fails or is bypassed. */
s32 func_8003C758(s32 key)
{
    s32 index;

    if (D_80082E6A[0] == 2 && *(s8 *)0x800DCF4D != -2) {
        index = -1;
    } else {
        index = func_8003C634(key);
    }

    if (index == -1) {
        func_8003C6F8(key, D_80080A6C - 1);
        index = D_80080A6C - 1;
    }

    return index;
}
