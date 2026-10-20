#include "common.h"
#include "m2c_compat.h"
struct Dst;
struct Elem;
void func_8003DB94(struct Dst *state, struct Elem *entries, short index); /* extern */
struct Rec_D_80082E80; void initialize_optional_object_state(void *, s32, struct Rec_D_80082E80 *, s32); /* extern */
extern M2C_UNK D_800D0E04;

/* Initialize the object's animation data and default behavior. */
void initialize_emote_animation(s32 object, s32 updateContext, s32 animationState) {
    func_8003DB94(animationState, &D_800D0E04, 0);
    initialize_optional_object_state((void *)(object), updateContext, (struct Rec_D_80082E80 *)(animationState), 0);
}
