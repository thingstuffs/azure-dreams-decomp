#include "common.h"

extern void townConfigureTheSetModeN2(void *object, s32 transform, void *resource_ptr);
extern void townInitializeOptionalObjectState(void *object, s32 transform, s32 anim_state, void *resource_ptr);
extern void townInitializeObjectEntries(void *object, s32 anim_state, void *resource_ptr);

extern s32 D_800CFD00[];
extern s32 D_800D11D0[];
extern s32 D_800D11EC[];
extern s32 D_800AAB20[];

/* Initialize the object's resources, animation state, and callback table. */
void townInitializePersonResources(void *object, s32 transform, s32 anim_state) {
    townConfigureTheSetModeN2(object, transform, &D_800CFD00);
    townInitializeOptionalObjectState(object, transform, anim_state, &D_800D11D0);
    townInitializeObjectEntries(object, anim_state, &D_800D11EC);
    *(void **)((s8 *)object - 0x10) = &D_800AAB20;
}
