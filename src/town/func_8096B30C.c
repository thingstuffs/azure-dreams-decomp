#include "common.h"

extern s32 D_80126A10[];
extern u8 D_80126A18[0x70];
extern s32 D_80126A60;
extern s32 D_80126AD0;

/* Load the selected table value and its paired value into global state. */
void func_801237A4(void *selection) {
    u8 index = ((u8 *)selection)[0x16];

    D_80126A60 = D_80126A10[index];
    D_80126AD0 = D_80126A10[((u8 *)selection)[0x16] ^ 1];
}
