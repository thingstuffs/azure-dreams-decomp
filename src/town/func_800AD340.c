#include "common.h"

extern void func_8008F0A4(void *arg0, s32 arg1, void *arg2);
extern void func_8009B218(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);

extern s32 D_800CFD00[];
extern s32 D_800D11D0[];
extern s32 D_800D11EC[];
extern s32 D_800AAB20[];

/* Initialize the object's resources, animation state, and callback table. */
void func_800AAAA0(void *object, s32 transform, s32 anim_state) {
    func_8008F0A4(object, transform, &D_800CFD00);
    func_8009B218(object, transform, anim_state, &D_800D11D0);
    func_800C2E84(object, anim_state, &D_800D11EC);
    *(void **)((s8 *)object - 0x10) = &D_800AAB20;
}
