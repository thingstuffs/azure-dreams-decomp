#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/sprite.h"
#include "engine/texture.h"

/* Sprite parts registered by register_sprite_slot (one-based slot index). */
extern SpriteFrameState *sprite_resource_pointer_slots[4];

/* Dispatches each occupied slot in mode 1 and clears it. */
void dispatch_and_clear_four_pointer_slots(void)
{
    SpriteFrameState **slot = sprite_resource_pointer_slots;
    s32 slots_left;

    for (slots_left = 4; slots_left > 0; slots_left--, slot++) {
        SpriteFrameState *object = *slot;
        if (object != 0) {
            process_sprite_scroll_and_texture_uploads(object->source, object->animation_resource, 1);
            *slot = 0;
        }
    }
}
