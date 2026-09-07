#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_8014CF20[];
extern u8 D_8014FB98[];
extern u8 D_801522C8[];
extern u8 D_80152300[];
extern u8 D_80152328[];
extern u8 D_80152360[];

/* Updates the state table or selects a directional animation for the actor. */
void func_8014F720(void *state_arg, void *context, void *visual_arg, void *actor_arg) {
    void *state = state_arg;
    void *visual = visual_arg;
    register void *actor ASM_REG("$18") = actor_arg;   /* MATCH pin: load-bearing for the whole function shape */
    void *current_table;
    register u8 *anim_table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    u8 *anim_entry;
    void *anim_target;
    s32 direction;

    if (func_800AC82C(state_arg, context, visual_arg, actor_arg) != 0) {
        if ((func_800AD9B4(visual, actor) << 0x10) > 0) {
            if (*(u8 *)((u8 *)state + 0xA7) != 0) {
                *(void **)((u8 *)state + 0x8C) = D_8014FB98;
            } else {
                *(void **)((u8 *)state + 0x8C) = D_8014CF20;
            }
        }
        return;
    }

    current_table = *(void **)((u8 *)visual + 0x2C);
    if (current_table == D_80152300) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        anim_table = D_801522C8;
    } else if (current_table == D_80152360) {
        if (*(s32 *)((u8 *)actor + 0x1C) & 0x208) {
            return;
        }
        anim_table = D_80152328;
    } else {
        return;
    }

    *(void **)((u8 *)visual + 0x2C) = anim_table;
    direction = (D_80083228 + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9;
    anim_target = visual;
    anim_entry = (u8 *)((u32)(direction & 7) + (u32)anim_table);
    func_80047784(anim_target, *anim_entry, 0);
}

/* MECHANISM: The 0x20 frame and s1/s0/s2 held arguments preserve the proven CFG.
   Pinned a0 call-object and v0 anim_entry lifetimes fill the lh delay slot without length drift.
   Integer direction-first address addition defeats pointer-first canonicalization at word 57. */
