#include "common.h"

extern s8 D_80089268[];
extern s32 func_800B2834();

u8 func_800B2918(void) {
    volatile s8 values[3];
#ifdef NON_MATCHING
    s8 *global = D_80089268;
#else
    register s8 *page ASM_REG("$2") = (s8 *) 0x80090000;
    s8 *global;
#endif
    register s32 first ASM_REG("$3");
    s32 second;
    s32 third;

#ifndef NON_MATCHING
    ASM_KEEP(page);
    global = page - 0x6D98;
    ASM_KEEP(global);
#endif
    first = global[0];
    ASM_KEEP(first);
    second = global[1];
    third = global[2];
    values[0] = first;
    values[1] = second;
    values[2] = third;
    return (u8) values[func_800B2834(second, third, global)];
}
