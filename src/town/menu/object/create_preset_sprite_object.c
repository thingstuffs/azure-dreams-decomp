#include "common.h"

extern void create_positioned_sprite_object(s32 position, void *state_value, void *graphic_id);
extern u8 D_800A74D8[];
extern u8 emote_sprite_entries[];

/* Creates an object at the given position with preset state and sprite data. */
void create_preset_sprite_object(s32 position) {
    create_positioned_sprite_object(position, D_800A74D8, emote_sprite_entries);
}
