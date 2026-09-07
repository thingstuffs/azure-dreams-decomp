#include "common.h"

#include "common.h"

extern u8 D_80082E6A[];
extern s32 D_80080A6C;

extern s32 func_8003C634(s32 key);
extern void func_8003C6F8(s32 key, s32 index);

s32 func_8003C758(s32 key)
{
    s32 result;

    if (D_80082E6A[0] == 2 && *(s8 *)0x800DCF4D != -2) {
        result = -1;
    } else {
        result = func_8003C634(key);
    }

    if (result == -1) {
        func_8003C6F8(key, D_80080A6C - 1);
        result = D_80080A6C - 1;
    }

    return result;
}
