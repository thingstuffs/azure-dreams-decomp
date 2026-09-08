#include "common.h"

extern void *D_80016000;
void func_80018D14(void *);

// Clears the indexed object and marks its slot unused, with cleanup for type 0x13.
void func_80018E34(s32 slotIndex) {
    void **objectTableBase;
    void **objectSlot;
    void *object;

    do { objectTableBase = *(void ***)((u8 *)D_80016000 + 0x38); } while (0);
    objectSlot = (void **)((u8 *)objectTableBase + 0x29C);
    objectSlot += slotIndex;
    object = *objectSlot;
    if (*((u8 *)object + 1) == 0x13) {
        func_80018D14(object);
    }
    *(s32 *)*objectSlot = 0;
    *objectSlot = (void *)-1;
}
