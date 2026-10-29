#include "common.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "town/scene/list_setup.h"
#include "town/player/object_setup.h"
#include "town/menu.h"
#include "town/player/object.h"

typedef struct S_800A6DA0_0 {
    void (*unk_00)(void *, void *, void *);
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A6DA0_0;   /* arg0 in initialize_scaled_effect_object; pointer addresses record offset 0x10 */

extern M2C_UNK D_800D0DA8;

/* Initializes the object and sets its transform scale to 0xC00 on all axes. */
void initialize_scaled_effect_object(void *object, void *position, struct SpriteFrameState *transform) {
    ((S_800A6DA0_0 *)((u8 *)object - 0x10))->unk_00 = &retire_object_on_check_or_callback;
    ((S_800A6DA0_0 *)((u8 *)object - 0x10))->unk_60 = 0;
    initialize_object_transform_and_state((s32)(object), transform, 0x48);
    configure_the_set_mode_n_3(object, position, &D_800D0DA8);
    transform->offset_x = 0xC00;
    transform->scale_y = 0xC00;
    transform->scale_x = 0xC00;
}
