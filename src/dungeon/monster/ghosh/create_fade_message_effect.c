#include "shared/sprite_frame_state.h"
#include "dungeon/monster/ghosh.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "engine/node.h"








/* Allocate and initialize a dungeon object, then increment the object count. */
void create_fade_message_effect(void) {
    ObjectNodeHeader * object;
    ObjectPosition *position;
    SpriteFrameState *primitive;

    object = allocate_flagged_object_node(0x12);
    if (object != 0) {
        (object->update_callback) = fade_scene_for_message;
        register_node(object, draw_linked_sprites);

        position = object->position;
        position->z.w.i = 0;
        position->y.w.i = 0;
        position->x.w.i = 0;

        primitive = object->sprite;
        primitive->scale_y = 0;
        primitive->scale_x = 0;
        primitive->color.c.b = 0;
        primitive->color.c.g = 0;
        primitive->color.c.r = 0;

        (*(GhoshSpriteTemplate *)((u8 *)object + 0x4C)) = ghosh_sprite_payload_template;
        primitive->source = (u8 *)object + 0x4C;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}
