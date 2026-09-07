#include "common.h"

extern s32 func_8009EEA4();
extern s16 D_80083350[5];
extern u8 D_800E50A8[];

s32 func_8009EE4C(s16 arg0, s16 arg1) {
    u32 index;
    u8 *ptr;
    u8 value;
    s32 flag;
    s32 shift;
#ifndef NON_MATCHING
    s16 *shiftPage;
#endif

#ifndef NON_MATCHING
    shiftPage = (s16 *)0x80080000;
    __asm__ volatile("" : "=r"(shiftPage) : "0"(shiftPage));
    shift = shiftPage[0x19A8];
#else
    shift = D_80083350[0];
#endif
    index = (arg1 << shift) + arg0;
    ptr = ((s32)((index + (index >> 31)) << 15) >> 16) + D_800E50A8;
    value = *ptr;
    flag = arg0 & 1;
    if (flag == 0) {
#ifndef NON_MATCHING
        __asm__ volatile("" : "=r"(value) : "0"(value));
#endif
        return value & 0xF;
    }
    return func_8009EEA4(flag, ptr) & 0xF0;
}
