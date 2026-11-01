#include "shared/object_node.h"
#include "dungeon/monster/ghosh.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef struct S_8016EB14_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016EB14_0;   /* root in spawn_owned_motion_object */


typedef struct S_8016EB14_5 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016EB14_5;   /* source in spawn_owned_motion_object */

typedef struct S_8016EB14_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7E];
    s16 unk_AA;
} S_8016EB14_6;   /* owner in spawn_owned_motion_object */

extern u8 D_800777B8;


/* Spawn an object at the owner's position and initialize its motion and appearance. */
void spawn_owned_motion_object(void)
{
    s32 x;
    s32 source_y;
    s32 direction_y;
    S_8016EB14_0 *owner_object;
    void *owner_data;
    S_8016EB14_5 *source_pos;
    S_8016EB14_6 *owner_state;
    ConditionalSourceEffectBody *object_state;
    ConditionalSourceEffectNode *spawned_object;
    SpriteFrameState *render_part;
    ObjectPosition *spawn_pos;
    u8 *direction_table;
    u8 *direction_entry;

    owner_data = ghosh_actor_node;
    owner_object = owner_data;
    source_pos = owner_object->unk_08;
    owner_state = (u8 *)owner_object + 0x20;
    spawned_object = allocate_flagged_object_node(0x12);
    if (spawned_object != 0) {
        spawned_object->header.update_callback = update_object_motion_and_landing;
        object_state = &spawned_object->body;
        register_node(&spawned_object->header, project_sprite_chain);
        render_part = spawned_object->header.sprite;
        render_part->flags &= 0xFFF3;
        object_state->unk_24 = owner_state;
        spawn_pos = spawned_object->header.position;
        spawn_pos->x.w.i = source_pos->unk_02.s;
        spawn_pos->y.w.i = source_pos->unk_06.s;
        spawn_pos->z.w.i = source_pos->unk_0A - 0x20;
        direction_table = (u8 *)&ghosh_effect_direction_offsets;
        x = *(s16 *)(u8 *)(((owner_state->unk_2A >> 7) & 0x1C) +
                           (u32)direction_table);
        object_state->unk_4C = x << 18;
        direction_y = *(s16 *)((u8 *)(((owner_state->unk_2A >> 7) & 0x1C) +
                                      (u32)direction_table) + 2);
        object_state->unk_54 = 0xFFF80000;
        object_state->unk_60 = 0x14900;
        object_state->unk_50 = direction_y << 18;

        object_state->unk_18 = (owner_state->unk_2A >> 9) & 7;
        render_part = spawned_object->header.sprite;
        render_part->scale_y = 0x1000;
        render_part->scale_x = 0x1000;
        direction_entry = (u8 *)(((owner_state->unk_2A >> 7) & 0x1C) + (u32)direction_table);
        render_part->depth_bias = *(s16 *)(direction_entry + 2) * 6;
        owner_state->unk_AA = 0x4D;

        x = source_pos->unk_02.u;
        object_state->unk_48 = x / 64;
        source_y = source_pos->unk_06.u;
        object_state->unk_49 = source_y / 64;
        render_part->color.c.b = 0x80;
        render_part->color.c.g = 0x80;
        render_part->color.c.r = 0x80;
        render_part->source = &D_800777B8;
        object_state->unk_44 = 0xF;
        object_state->unk_45 = 1;
        object_state->unk_46 = 0;
        object_state->unk_47 = 0;
    }
}
