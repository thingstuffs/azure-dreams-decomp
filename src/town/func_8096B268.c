#include "common.h"

extern s32 D_80126A88[];
extern u8 D_80129728[];

void func_80123700(void) {
    s32 i;
    s32 *src;
    void **entry;
    u8 *base;
    s16 fill;

    i = 0;
    fill = 0x800;
    base = D_80129728;
    entry = (void **)(base + 0x38);
    src = D_80126A88;
    do {
        *(s32 *)*entry = *src;
        src += 2;
        i++;
        *((s16 *)*(void **)((u8 *)*entry + 8) + 1) = fill;
        entry++;
    } while (i < 14);
}
