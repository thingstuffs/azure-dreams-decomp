/* Relink of matched town/func_800CE888; every changed retail word is a paired relocation. */
#define D_800D6AA8 D_800D6EE8
#include "common.h"

extern void func_800C2E84(void *state, s32 output, void *entries);
extern u8 D_800D6EE8;

/* Initialize the object and advance its state. */
void func_800CCD24(void *object, s32 unused, s32 context) {
    func_800C2E84(object, context, &D_800D6EE8);
    *(u16 *)((u8 *)object + 0x68) += 1;
}
