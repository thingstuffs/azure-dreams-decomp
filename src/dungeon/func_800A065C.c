#include "common.h"

extern void *func_8003FC64(s32);
extern s32 D_80083460;
extern s32 D_800A5D5C;


/* Set the object data pointer and increment the global state counter. */
void func_800A5DBC(void) {
    void *base;

    ((s32 **)func_8003FC64(0))[4] = &D_800A5D5C;
    base = &D_80083460;
    ASM_KEEP(base);
    *(u16 *)((u8 *)base + 0xA) += 1;
}
