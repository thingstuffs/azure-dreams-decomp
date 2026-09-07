#include "common.h"

extern s32 D_80175D48;

#ifndef NON_MATCHING
extern u8 D_04816000;
__asm__(".set D_04816000, 0x04816000");
#define INITIAL_VALUE ((s32)&D_04816000)
#else
#define INITIAL_VALUE 0x04816000
#endif

void func_8016F834(s32 arg0) {
    s32 value;
    s32 *ptr;

    do {
        D_80175D48 = INITIAL_VALUE;
    } while (0);
    value = D_80175D48;
    
    ptr = &D_80175D48;
    
    value = (arg0 * 9) + 0x30B2;
    ptr[1] = value;
}
