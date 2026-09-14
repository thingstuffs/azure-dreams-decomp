#include "common.h"

extern u8 D_800C2074[];
extern void func_800C2124(void);
extern void *D_800D4710[];

/* Set the preceding handler pointer and replace each active table callback. */
void func_800C202C(void *entry_data) {
    void **p;

    *(void **)((u8 *)entry_data - 0x10) = (void *)D_800C2074;
    p = D_800D4710;
    if (*p != 0) {
        do {
            *p = (void *)func_800C2124;
            p += 6;
        } while (*p != 0);
    }
}
