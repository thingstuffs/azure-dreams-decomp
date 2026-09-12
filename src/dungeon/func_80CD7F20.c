#include "common.h"

extern s32 func_800AC82C(void *, void *, void *, void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);

extern s16 D_80083228;
extern u8 D_80158F20[];
extern u8 D_8015BB98[];
extern u8 D_8015E2C8[];
extern u8 D_8015E300[];
extern u8 D_8015E328[];
extern u8 D_8015E360[];

/* Update the owner state or select an animation frame from the facing direction. */
void func_8015B720(void *owner_arg, void *context, void *anim_obj_arg, void *state_arg) {
    void *owner = owner_arg;
    void *anim_obj = anim_obj_arg;
    void *state = state_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *current_table;

    if (func_800AC82C(owner_arg, context, anim_obj_arg, state_arg) != 0) {
        if ((func_800AD9B4(anim_obj, state) << 0x10) > 0) {
            if (*(u8 *)((u8 *)owner + 0xA7) != 0) {
                *(void **)((u8 *)owner + 0x8C) = D_8015BB98;
            } else {
                *(void **)((u8 *)owner + 0x8C) = D_80158F20;
            }
        }
        return;
    }

    current_table = *(void **)((u8 *)anim_obj + 0x2C);
    if (current_table == D_8015E300) {
        if (*(s32 *)((u8 *)state + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)anim_obj + 0x2C) = D_8015E2C8;
        func_80047784(anim_obj, D_8015E2C8[((D_80083228 + *(s16 *)((u8 *)state + 0x2A) + 0x100) >> 9) & 7], 0);
    } else if (current_table == D_8015E360) {
        if (*(s32 *)((u8 *)state + 0x1C) & 0x208) {
            return;
        }
        *(void **)((u8 *)anim_obj + 0x2C) = D_8015E328;
        func_80047784(anim_obj, D_8015E328[((D_80083228 + *(s16 *)((u8 *)state + 0x2A) + 0x100) >> 9) & 7], 0);
    } else {
        return;
    }

}
