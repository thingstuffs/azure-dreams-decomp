#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern u8 D_8002609C[];
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
        object->update_callback = &D_8002609C;
        register_node(object, project_sprite_chain);
        sprite = object->sprite;
        *((s32 *) (((s8 *) (object->position)) + 0)) = x;
        *((s32 *) (((s8 *) (object->position)) + 4)) = y;
        *((s32 *) (((s8 *) (object->position)) + 8)) = z;
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
            *((s32 *) (((s8 *) (object->position)) + 0x14)) = 0xFFF00000;
            sprite->flags = (u16) ((sprite->flags) | 0xC);
        }
    }
}
