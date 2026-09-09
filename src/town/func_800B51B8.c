#include "common.h"

extern s8 D_80089268[];
extern s32 get_player_homerank();

/* Return the selected value from the three global entries. */
u8 func_800B2918(void) {
    volatile s8 values[3];
#ifdef NON_MATCHING
    s8 *global = D_80089268;
#else
    register s8 *page ASM_REG("$2") = (s8 *) 0x80090000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 *global;
#endif
    register s32 first ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 second;
    s32 third;

#ifndef NON_MATCHING
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    global = page - 0x6D98;
    ASM_KEEP(global);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
#endif
    first = global[0];
    second = global[1];
    third = global[2];
    values[0] = first;
    values[1] = second;
    values[2] = third;
    return (u8) values[get_player_homerank(second, third, global)];
}
