#include "common.h"
#include "shared/object_flags.h"

extern s32 classify_object_against_bounds(void *, void *);
extern void unlink_node_if_registered(void *object);
extern void advance_sprite_animation_and_textures(void *fallback_data);

/* Clear object status and set flags on a successful check, or run the fallback. */
void finalize_checked_object_or_fallback(void *object, void *check_data, void *fallback_data)
{
    u8 *status_byte;

    if (classify_object_against_bounds(object, check_data) != 0) {
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    } else {
        advance_sprite_animation_and_textures(fallback_data);
    }
}
