#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

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

typedef struct S_80D65C5C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_80D65C5C_2;   /* sprite in spawn_directional_random_velocity_effect */


typedef struct S_80D65C5C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D65C5C_4;   /* ((S_80D65C5C_0 *)node)->unk_08 in spawn_directional_random_velocity_effect */

   /* ((S_80D65C5C_1 *)arg0)->unk_08 in spawn_directional_random_velocity_effect */

extern s32 rand(void);
extern void register_node(void *, void *);
extern void select_record_entry_and_value(void *, void *, s32);

extern s16 actor_direction_step_pairs[];
extern u8 D_80171384[];

/* Spawns a directional sprite effect near the source with randomized velocity. */
void spawn_directional_random_velocity_effect(S_80D65C5C_1 *source, s32 angle)
{
    ObjectNodeHeader *node;
    S_80D65C5C_2 *sprite;
    s16 *direction_step;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->update_callback = D_80171384;

        ((S_80D65C5C_4 *)(node->position))->unk_02 =
            ((MovingPosition *)(source->unk_08))->x;
        ((S_80D65C5C_4 *)(node->position))->unk_06 =
            ((MovingPosition *)(source->unk_08))->y;
        ((S_80D65C5C_4 *)(node->position))->unk_0A =
            ((MovingPosition *)(source->unk_08))->z - 0x58;

        direction_step = (s16 *)((u8 *)actor_direction_step_pairs + (((u32)angle >> 7) & 0x1C));
        ((S_80D65C5C_4 *)(node->position))->unk_02 += direction_step[0] * 0x12;
        ((S_80D65C5C_4 *)(node->position))->unk_06 += direction_step[1] * 0x12;

        node->sprite->depth_bias = 6;
        ((S_80D65C5C_4 *)(node->position))->unk_0C =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        ((S_80D65C5C_4 *)(node->position))->unk_10 =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        ((S_80D65C5C_4 *)(node->position))->unk_14 =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;

        ((S_80D65C5C_4 *)(node->position))->unk_0C +=
            direction_step[0] * 0x1C0000;
        ((S_80D65C5C_4 *)(node->position))->unk_10 +=
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
