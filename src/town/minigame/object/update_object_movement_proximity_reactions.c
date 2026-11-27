#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "slus.h"
#include "sdk/libc.h"
#include "engine/node.h"
#include "town/minigame/effect.h"
#include "town/minigame/object.h"
#include "town/minigame.h"
#include "town/minigame/tako_child_body.h"

extern u8 D_80026748[];
extern u8 D_800F7950[];
extern u8 D_800F795C[];

/* Updates object movement, proximity reactions, and particle effects through each phase. */
void update_object_movement_proximity_reactions(void *state_data, void *position_data, void *sprite_data)
{
    TakoProjectileBody *state = state_data;
    s32 *position = position_data;
    SpriteFrameState *sprite = sprite_data;
    TakoChildBody *object;
    TakoMinigameState *owner;
    s32 remaining;
    s32 next_x;
    s32 particle_x;
    s32 rebound_x;
    s32 burst_x;
    s32 y_distance;
    s32 x_jitter;
    s32 burst_velocity;
    u16 type_index;
    ObjectNodeHeader *effect;
    TakoHitSparkBody *effect_state;
    ObjectPosition *effect_position;
    SpriteFrameState *effect_sprite;
    TileObject *color_state;

    object = state->target;
    object->flags |= 1;
    owner = object->parent;

    if (object->deflect_count == 9 && state->phase == 1 && *position <= 0x4DFFFFF) {
        switch (object->column_index) {
        case 0:
            sprite->color.c.r = 0xFF;
            remaining = 3;
loop_0:
            {
                create_randomized_trail_particle(position);
                remaining--;
            }
            if (remaining >= 0)
                goto loop_0;
            break;
        case 1:
            sprite->flags |= 0xC;
            remaining = 2;
            do {
                create_brief_randomized_particle(position);
                remaining--;
            } while (remaining >= 0);
            break;
        case 2:
            sprite->scale_y += 0x200;
            sprite->scale_x = sprite->scale_y;
            break;
        }
    }

    switch (state->phase) {
    case 0:
        if (state->timer == 0x10) {
            object->flags |= 4;
        } else {
            object->flags &= 0xFFFB;
        }
        state->timer--;
        if (state->timer > 0) {
            break;
        }
        SD_Call(0x518);
        object->parent->field_12++;
        state->phase = 1;
        sprite->flags &= 0xFF7F;
        break;

    case 1:
        state->velocity_x += state->acceleration_x;
        next_x = *position + state->velocity_x;
        *position = next_x;
        if (next_x <= 0x427FFFF) {
            state->timer = 6;
            color_state = &reference_tile_object;
            if (color_state->primitive_color.parts.color_r >= 9) {
                color_state->primitive_color.word = (s32)((s32)(color_state->primitive_color.word) - (0x80808));
            }
            sprite->flags |= 0x80;
            SD_Call(0x506);
            state->phase = 2;
            break;
        }
        y_distance = view_reference_entity.y.v - position[1];
        y_distance = abs(y_distance);
        if (y_distance > 0x200000 || next_x > 0x43FFFFF || (state->flags & 4)) {
            break;
        }
        type_index = owner->counter - 3;
        if ((u32)type_index < 3) {
            SD_Call(0x513);
            state->velocity_x = 0x180000;
            state->phase = 3;
            state->flags |= 4;
            object->deflect_count++;
            object->parent->threshold += 2;
            if (object->deflect_count == 10) {
                object->parent->threshold += 10;
            }
            break;
        }
        if ((u32)type_index >= 7) {
            break;
        }

        SD_Call(0x510);
        remaining = 1;
        state->flags |= 4;
        object->parent->threshold++;
        do {
            effect = allocate_flagged_object_node(0x136);
            if (effect != 0) {
                effect_state = NODE_BODY(effect);
                effect->update_callback = D_80026748;
                register_node(effect, project_sprite_chain);
                effect_position = effect->position;
                effect_sprite = effect->sprite;
                effect_position->x.v = position[0];
                effect_position->y.v = position[1];
                effect_position->z.v = position[2];
                effect_state->drift_x = state->velocity_x;
                effect_state->target = object;
                effect_sprite->scale_y = 0x1000;
                effect_sprite->scale_x = 0x1000;
                if (remaining != 0) {
                    effect_sprite->source = D_800F795C;
                    effect_position->velocity_y = 0x80000;
                } else {
                    effect_sprite->source = D_800F7950;
                    effect_position->velocity_y = 0xFFF80000;
                }
                effect_sprite->unk_04 = 0;
                effect_sprite->frame_ticks = 0;
                effect_sprite->color.word = 0x00808080;
            }
            remaining--;
        } while (remaining >= 0);
        state->phase = 0xFF;
        break;

    case 2:
        remaining = 7;
        do {
            x_jitter = (rand() & 0xFF) - 0x80;
            particle_x = *position + (x_jitter << 14);
            create_tinted_animated_particle(0, particle_x, position[1] + 0x80000,
                ((rand() % 80) << 16) + 0xFFB00000);
            remaining--;
        } while (remaining >= 0);
        goto common_countdown;

    case 3:
        object->flags |= 2;
        rebound_x = *position + state->velocity_x;
        *position = rebound_x;
        if (rebound_x > 0x55FFFFF) {
            state->timer = 5;
            SD_Call(0x50C);
            state->phase = 4;
        }
        break;

    case 4:
        remaining = 7;
        object->flags |= 2;
        do {
            burst_x = (((rand() & 0xFF) - 0x80) << 14) + 0x5600000;
            burst_velocity = ((rand() & 0x3F) << 16) | 0xFFC00000;
            create_tinted_animated_particle(0, burst_x, position[1] + 0x80000, burst_velocity);
            remaining--;
        } while (remaining >= 0);
common_countdown:
        state->timer--;
        if (state->timer <= 0) {
            state->phase = 0xFF;
        }
        break;

    case 0xFF:
        object->flags &= 0xFFFE;
        NODE_HEADER(state)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
