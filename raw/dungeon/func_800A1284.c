#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

extern void func_800A08A0(s32 arg0);
extern s32 func_800A6DA4(s32 arg0, s32 arg1);

void func_800A69E4(void) {
    s32 count;
    s32 i;
    s32 value;

    count = func_800A6DA4(4, 8) & 0xFFFF;
    i = 0;
    value = 0x20000;
loop1:
    func_800A08A0(value >> 0x10);
    value += 0x10000;
    i += 1;
    if (i < 0x10)
        goto loop1;
    i = 0;
    if (i >= count)
        goto done;
loop2:
        func_800A08A0(1);
        i += 1;
        if (i < count)
            goto loop2;
done:
    ;
}
