#include "common.h"

extern s8 D_80089268[];
extern s32 func_800B2834();

u8 func_800B2918(void) {
    volatile s8 values[3];
#ifdef NON_MATCHING
    s8 *global = D_80089268;
#else
    register s8 *page ASM_REG("$2") = (s8 *) 0x80090000;   /* MATCH pin: load-bearing for the whole function shape */
    s8 *global;
#endif
    register s32 first ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 second;
    s32 third;

#ifndef NON_MATCHING
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    global = page - 0x6D98;
    ASM_KEEP(global);   /* MATCH pin: keeps a statement from moving across a call/branch */
#endif
    first = global[0];
    second = global[1];
    third = global[2];
    values[0] = first;
    values[1] = second;
    values[2] = third;
    return (u8) values[func_800B2834(second, third, global)];
}
