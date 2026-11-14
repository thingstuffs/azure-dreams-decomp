#include "shared/sprite_frame_state.h"
#include "dungeon/monster/ghosh.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "engine/node.h"








/* Allocate a type 0x12 object and initialize its state and default data. */
/* Creates a zero-sized black sprite at the origin with a copied 12-byte entry from D_80077818 and its
 * update callbacks. */
void create_scene_brighten_effect(void)
{
    ObjectNodeHeader * object;
    ObjectPosition *primary_state;
    SpriteFrameState *secondary_state;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->update_callback) = brighten_scene_tint;
        register_node(object, draw_linked_sprites);

        primary_state = object->position;
        primary_state->z.w.i = 0;
        primary_state->y.w.i = 0;
        primary_state->x.w.i = 0;

        secondary_state = object->sprite;
        secondary_state->scale_y = 0;
        secondary_state->scale_x = 0;
        secondary_state->color.c.b = 0;
        secondary_state->color.c.g = 0;
        secondary_state->color.c.r = 0;

        (*(GhoshSpriteTemplate *)((u8 *)object + 0x4C)) = ghosh_sprite_payload_template;
        secondary_state->source = (u8 *)object + 0x4C;
    }
}
