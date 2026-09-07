#include "common.h"

extern s32 D_80126A10[];
extern u8 D_80126A18[0x70];
extern s32 D_80126A60;
extern s32 D_80126AD0;

void func_801237A4(void *arg0) {
    u8 index = ((u8 *)arg0)[0x16];
    register s32 *table ASM_REG("$5") = (s32 *)0x80120000;   /* MATCH pin: retail register colouring depends on it */
    ASM_KEEP(table);   /* MATCH pin: load-bearing for the whole function shape */
    table += 0x1A84;

    D_80126A60 = table[index];
    D_80126AD0 = table[((u8 *)arg0)[0x16] ^ 1];
}
