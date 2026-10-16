/* Relink of matched town/func_800CE888; every changed retail word is a paired relocation. */
#define D_800D6AA8 D_800D6F24
#include "common.h"

extern void townInitializeObjectEntries(void *state, s32 output, void *entries);
extern u8 D_800D6F24;

/* Initialize the object and advance its state. */
void func_800CCCE0(void *object, s32 unused, s32 context) {
    townInitializeObjectEntries(object, context, &D_800D6F24);
    *(u16 *)((u8 *)object + 0x68) += 1;
}
