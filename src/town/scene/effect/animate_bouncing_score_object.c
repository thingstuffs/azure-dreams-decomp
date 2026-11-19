#include "common.h"
#include "shared/object_node.h"
#include "town/scene/animation.h"
#include "town/scene/effect.h"
#include "town/scene/score_sprite_data.h"
#include "town/devkit/old_minigame_imports.h"

extern u8 D_8052643C[], score_bounce_update_address[];

/* Create an object, copy its two records, and initialize rendering state. */
void create_bouncing_score_sprite(BouncingScoreBody *source_data, ObjectPosition *initial_data)
{
    ObjectNodeHeader *object;
    ObjectNodeHeader *allocated;
    BouncingScoreBody *payload;
    SpriteFrameState *part;
    u8 *table;

    allocated = func_800373DC(0x136);
    table = D_8052643C;
    object = allocated;
    if (object != 0) {
        payload = NODE_BODY(object);
        *payload = *source_data;
        object->update_callback = animate_bouncing_score_object;
        *object->position = *initial_data;
        func_8003BC18(object, score_sprite_draw_callback_address);
        part = object->sprite;
        part->scale_y = 0x1000;
        part->scale_x = 0x1000;
        part->source = score_object_images[source_data->kind];
        part->unk_04 = 0;
        part->frame_ticks = 0;
        part->color.word = 0x808080;
        part->flags |= 0x80;
        payload->motion_data = table;
        func_8023FA58(payload->work, object->position, score_bounce_update_address);
    }
}
