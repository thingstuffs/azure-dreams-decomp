#include "common.h"

extern void townInitializeObjectEntries(void *state, s32 output, void *entries);
extern u8 D_800D6AA8;

/* Initialize the object and advance its state. */
void townInitializeObjectAndAdvance(void *object, s32 unused, s32 context) {
    townInitializeObjectEntries(object, context, &D_800D6AA8);
    *(u16 *)((u8 *)object + 0x68) += 1;
}
