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

extern s32 register_node();
extern u8 D_8002609C[];
extern u8 D_800F15AC[];
/* Creates a sprite at the given position and applies color-specific settings. */
void create_tinted_animated_particle(s32 color, s32 x, s32 y, s32 z)
{
    s32 resource_word;
    void *sprite;
    SpriteFrameState *sprite_alias;
    void *object;
    object = func_8003FC64(0x136);
    if (object != 0) {
        *((s32 **) (((s8 *) object) + 0x10)) = &D_8002609C;
        register_node(object, project_sprite_chain);
        sprite = *((void **) (((s8 *) object) + 0xC));
        *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 0)) = x;
        *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 4)) = y;
        *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 8)) = z;
        *((s16 *) (((s8 *) sprite) + 0x1E)) = 0x1000;
        *((s16 *) (((s8 *) sprite) + 0x1C)) = 0x1000;
        *((s32 **) (((s8 *) sprite) + 0)) = &D_800F15AC;
        resource_word = *((s32 *) (((s8 *) (&D_800F15AC)) + 4));
        *((s8 *) (((s8 *) sprite) + 4)) = 0;
        *((s8 *) (((s8 *) sprite) + 5)) = 0;
        *((s32 *) (((s8 *) sprite) + 0xC)) = color;
        sprite_alias = sprite;
        sprite_alias->source = (s32) resource_word;
        if (color == 0x808080) {
            *((u16 *) (((s8 *) sprite) + 0x14)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x14))) | 0xC);
        } else if (color == 0xF0F0F0) {
            *((s16 *) (((s8 *) sprite) + 0x10)) = 0x60;
            *((s32 *) (((s8 *) (*((void **) (((s8 *) object) + 8)))) + 0x14)) = 0xFFF00000;
            *((u16 *) (((s8 *) sprite) + 0x14)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x14))) | 0xC);
        }
    }
}
