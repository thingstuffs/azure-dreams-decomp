#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

extern s32 func_8008B2E4(s32 arg0);

extern u8 D_800CF828[15];
extern s32 D_800CF838[16];

s32 func_8008B328(void) {
    s32 i;
    u8 *base;
    s32 *table;
    s32 ret;

    i = 0;
    base = D_800CF828;
    table = D_800CF838;
loop_1:
    {
        s32 found = func_8008B2E4(table[*(u8 *)((u32)i + (u32)base)]);

        ASM_KEEP(found);
        i += 1;
        if (found != 0) {
            ret = 1;
            goto epilogue;
        }
    }
    if (i < 0xF) {
        goto loop_1;
    }
    ret = 0;
epilogue:
    return ret;
}
