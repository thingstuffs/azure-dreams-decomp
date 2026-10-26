#include "common.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "engine/sprite.h"

extern SpriteFrameState *sprite_resource_pointer_slots[4];

/* Registers the entry in a nonzero one-based slot and dispatches in mode 2, or mode 3 for slot zero. */
void register_sprite_slot(SpriteFrameState *entry, s32 index) {
    if (index != 0) {
        index = index - 1;
        sprite_resource_pointer_slots[index] = entry;
        process_sprite_scroll_and_texture_uploads(entry->source, entry->animation_resource, 2);
    } else {
        process_sprite_scroll_and_texture_uploads(entry->source, entry->animation_resource, 3);
    }
}
