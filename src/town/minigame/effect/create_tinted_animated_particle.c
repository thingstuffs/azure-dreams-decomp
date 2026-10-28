#include "shared/object_node.h"
#include "town/minigame.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"




extern u8 map_animation_sprite_entries[];
/* Creates a sprite at the given position and applies color-specific settings. */
void create_tinted_animated_particle(s32 color, s32 x, s32 y, s32 z)
{
    s32 resource_word;
    SpriteFrameState *sprite;
    SpriteFrameState *sprite_alias;
    ObjectNodeHeader *object;
    object = allocate_flagged_object_node(0x136);
    if (object != 0) {
        object->update_callback = advance_fading_particle_until_animation_boundary;
        register_node(object, project_sprite_chain);
        sprite = object->sprite;
        (object->position)->x.v = x;
        (object->position)->y.v = y;
        (object->position)->z.v = z;
        *((s16 *) (((s8 *) sprite) + 0x1E)) = 0x1000;
        *((s16 *) (((s8 *) sprite) + 0x1C)) = 0x1000;
        *((s32 **) (((s8 *) sprite) + 0)) = &map_animation_sprite_entries;
        resource_word = *((s32 *) (((s8 *) (&map_animation_sprite_entries)) + 4));
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->color.word = color;
        sprite_alias = sprite;
        sprite_alias->source = (s32) resource_word;
        if (color == 0x808080) {
            sprite->flags = (u16) ((sprite->flags) | 0xC);
        } else if (color == 0xF0F0F0) {
            sprite->tpage_abr = 0x60;
            (object->position)->velocity_z = 0xFFF00000;
            sprite->flags = (u16) ((sprite->flags) | 0xC);
        }
    }
}
