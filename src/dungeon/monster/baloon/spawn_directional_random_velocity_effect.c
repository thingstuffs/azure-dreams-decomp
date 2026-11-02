#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "dungeon/monster/baloon.h"

typedef s32 M2C_UNK;

typedef struct S_80D65C5C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D65C5C_0;   /* node in spawn_directional_random_velocity_effect */

typedef struct S_80D65C5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80D65C5C_1;   /* arg0 in spawn_directional_random_velocity_effect */




   /* ((S_80D65C5C_1 *)arg0)->unk_08 in spawn_directional_random_velocity_effect */

extern s32 rand(void);
extern void select_record_entry_and_value(void *state, void *entries, short index);

extern s16 actor_direction_step_pairs[];
extern u8 D_80171384[];

/* Spawns a directional sprite effect near the source with randomized velocity. */
void spawn_directional_random_velocity_effect(S_80D65C5C_1 *source, s32 angle)
{
    ObjectNodeHeader *node;
    DirectionalRandomVelocityEffectBody *sprite;
    s16 *direction_step;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->update_callback = D_80171384;

        node->position->x.unsigned_parts.integer =
            ((MovingPosition *)(source->unk_08))->x;
        node->position->y.unsigned_parts.integer =
            ((MovingPosition *)(source->unk_08))->y;
        node->position->z.w.i =
            ((MovingPosition *)(source->unk_08))->z - 0x58;

        direction_step = (s16 *)((u8 *)actor_direction_step_pairs + (((u32)angle >> 7) & 0x1C));
        node->position->x.unsigned_parts.integer += direction_step[0] * 0x12;
        node->position->y.unsigned_parts.integer += direction_step[1] * 0x12;

        node->sprite->depth_bias = 6;
        node->position->velocity_x =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        node->position->velocity_y =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        node->position->velocity_z =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;

        node->position->velocity_x +=
            direction_step[0] * 0x1C0000;
        node->position->velocity_y +=
            direction_step[1] * 0x1C0000;

        sprite = (u8 *)node + 0x20;
        sprite->unk_0A = angle;
        sprite->unk_0C = 0xC;
        sprite->unk_0E = 0xC;
        register_node(node, project_sprite_chain);

        {
            SpriteFrameState *part = node->sprite;

            part->flags |= 0xC;
            part->tpage_abr = 0x60;
            part->flags |= 2;
            part->scale_x = 0x800;
            part->scale_y = 0x800;
            part->color.c.b = 0x80;
            part->color.c.g = 0x80;
            part->color.c.r = 0x80;
            part->flags |= 0x100;
            part->clut = 0x7DCF;
            select_record_entry_and_value(part, effect_sprite_sources, 0);
        }
    }
}
