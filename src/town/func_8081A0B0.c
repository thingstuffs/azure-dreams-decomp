#include "common.h"
#include "shared/types3b_types.h"

   /* arg2 in toggle_gym_sprite_by_scene_phase */

/* Update bit 0x80 according to the pointed-to value. */
void toggle_gym_sprite_by_scene_phase(s16 **value_ptr, s32 unused, SpriteFlagsView *object) {
    s16 *value;

    value = *value_ptr;
    if (*value == 4) {
        object->unk_14 = (u16) (object->unk_14 | 0x80);
    }
    if (*value == 0xFF) {
        object->unk_14 = (u16) (object->unk_14 & 0xFF7F);
    }
}
