#include "common.h"
#include "shared/object_index_slots.h"

extern void func_800C2E84(void *state, s32 output, void *entries);
extern s32 D_800C5B48[];
extern u8 D_800D54CC[];

/* Initialize the actor state, clear its entry flag, and start a 16-tick callback countdown. */
void func_800C599C(void *actor, s32 unused, s32 state_context) {
    func_800C2E84(actor, state_context, D_800D54CC);
    ((u8 *)D_80082660)[(*(s32 *)((u8 *)actor + 0x60)) * 8] = 0;
    *(s16 *)((u8 *)actor + 0x6C) = 0x10;
    *(s32 **)((u8 *)actor + 0x54) = D_800C5B48;
}
