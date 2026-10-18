#include "common.h"
#include "m2c_compat.h"

typedef struct S_800240B0_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800240B0_0;   /* arg2 in toggle_gym_sprite_by_scene_phase */

/* Update bit 0x80 according to the pointed-to value. */
void toggle_gym_sprite_by_scene_phase(s16 **value_ptr, M2C_UNK unused, S_800240B0_0 *object) {
    s16 *value;

    value = *value_ptr;
    if (*value == 4) {
        object->unk_14 = (u16) (object->unk_14 | 0x80);
    }
    if (*value == 0xFF) {
        object->unk_14 = (u16) (object->unk_14 & 0xFF7F);
    }
}
