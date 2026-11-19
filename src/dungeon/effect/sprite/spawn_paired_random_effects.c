#include "dungeon/effect/screen/transform_shade_and_queue_model_quads.h"
#include "shared/game_work.h"
#include "dungeon/effect/screen.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libc.h"
#include "dungeon/data.h"

extern u8 D_8002822C[12];

/* Spawn two pairs of effects at random offsets around the source. */
void spawn_paired_random_effects(ObjectNodeHeader *source, s16 effect_param, s32 render_param)
{
    s32 remaining;
    ObjectNodeHeader *effect;
    MotionRecord *effect_data;
    SpriteFrameState *render_data;
    remaining = 2;
    do {
        effect = allocate_list_node(0x212, &source->next);
        if (effect != 0) {
            effect->update_callback = paired_random_effect_callback;
            register_node(effect, project_sprite_chain);
            effect_data = NODE_BODY(effect);
            effect->position->x.w.i =
                (source->position->x.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->y.w.i =
                (source->position->y.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->z.w.i =
                (source->position->z.w.i + (rand() & 0x3F)) - 0x20;
            render_data = effect->sprite;
            render_data->source = D_8002822C;
            render_data->scale_y = 0x1000;
            render_data->scale_x = 0x1000;
            render_data->color.word = render_param;
            render_data->depth_bias = 8;
            effect_data->direction = effect_param;
            effect_data->speed = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
    remaining = 2;
    do {
        effect = allocate_list_node(0x212, &source->next);
        if (effect != 0) {
            effect->update_callback = paired_random_effect_callback;
            register_node(effect, queue_linked_visible_rectangle_copies);
            effect_data = NODE_BODY(effect);
            effect->position->x.w.i =
                (source->position->x.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->y.w.i =
                (source->position->y.w.i + (rand() & 0x3F)) - 0x20;
            effect->position->z.w.i =
                (source->position->z.w.i + (rand() & 0x3F)) - 0x20;
            effect_data->copy.width = 0x20;
            effect_data->copy.height = 0x20;
            effect_data->copy.delta_x = 1;
            effect_data->copy.delta_y = 0;
            effect_data->direction = effect_param;
            effect_data->speed = (rand() & 0xFF) | 0x80;
        }
        remaining--;
    }
    while (remaining > 0);
}
