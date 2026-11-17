#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/sprite.h"
#include "engine/texture.h"
#include "slus/data.h"

/* Dispatches each occupied slot in mode 1 and clears it. */
void flush_sprite_resource_slots(void)
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
