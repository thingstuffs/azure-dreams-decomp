#include "common.h"

extern void *D_80016000;
void func_80018D14(void *);

void func_80018E34(s32 arg0) {
    void **base;
    void **slot;
    void *object;

    do { base = *(void ***)((u8 *)D_80016000 + 0x38); } while (0);
    slot = (void **)((u8 *)base + 0x29C);
    slot += arg0;
    object = *slot;
    if (*((u8 *)object + 1) == 0x13) {
        func_80018D14(object);
    }
    *(s32 *)*slot = 0;
    *slot = (void *)-1;
}
