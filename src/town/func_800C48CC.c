#include "common.h"

extern u8 D_800C2074[];
extern void func_800C2124(void);
extern void *D_800D4710[];

void func_800C202C(void *arg0) {
    register void **p ASM_REG("$4");   /* MATCH pin: retail delay-slot fill depends on it */

    *(void **)((u8 *)arg0 - 0x10) = (void *)D_800C2074;
    if (D_800D4710[0] != 0) {
        p = D_800D4710;
        do {
            *p = (void *)func_800C2124;
            p += 6;
        } while (*p != 0);
    }
}
