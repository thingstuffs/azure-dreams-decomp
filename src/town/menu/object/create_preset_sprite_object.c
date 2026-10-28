#include "common.h"

#include "town/menu/object/create_positioned_sprite_object_g01142.h"
extern u8 D_800A74D8[];
extern SpriteSourceEntry emote_sprite_entries[];

/* Creates an object at the given position with preset state and sprite data. */
ObjectNodeHeader *create_preset_sprite_object(IntVector3 *position) {
    return create_positioned_sprite_object(position, D_800A74D8, emote_sprite_entries);
}
