#include "common.h"
#include "m2c_compat.h"
struct Dst;
struct Elem;
void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index); /* extern */
struct Rec_D_80082E80; void initialize_optional_object_state(void *, s32, struct Rec_D_80082E80 *, s32); /* extern */
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800D0E04[];

/* Initialize the object's animation data and default behavior. */
void initialize_emote_animation(s32 object, s32 updateContext, s32 animationState) {
    select_record_entry_and_value(animationState, &D_800D0E04, 0);
    initialize_optional_object_state((void *)(object), updateContext, (struct Rec_D_80082E80 *)(animationState), 0);
}
