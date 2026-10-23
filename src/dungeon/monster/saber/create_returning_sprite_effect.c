#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80AC55DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80AC55DC_0;   /* node in create_returning_sprite_effect */

typedef struct S_80AC55DC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80AC55DC_1;   /* arg0 in create_returning_sprite_effect */

typedef struct S_80AC55DC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80AC55DC_2;   /* work in create_returning_sprite_effect */

typedef struct S_80AC55DC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80AC55DC_5;   /* ((S_80AC55DC_0 *)node)->unk_08 in create_returning_sprite_effect */

   /* ((S_80AC55DC_1 *)arg0)->unk_08 in create_returning_sprite_effect */

extern void register_node(void *, void *);
extern void select_record_entry_and_value(void *, void *, s32);

extern u8 shared_sprite_entries[];
extern u8 saber_return_effect_update_address[];

/* Creates a sprite effect offset from its origin and initializes its return motion. */
void create_returning_sprite_effect(
    S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    ObjectNodeHeader *node;
    S_80AC55DC_2 *work;
    SpriteFrameState *sprite;
    u16 sprite_flags;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 t;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->update_callback = saber_return_effect_update_address;

        ((S_80AC55DC_5 *)(node->position))->unk_02 =
            ((MovingPosition *)(origin->unk_08))->x + offset_x;
        ((S_80AC55DC_5 *)(node->position))->unk_06 =
            ((MovingPosition *)(origin->unk_08))->y + offset_y;
        ((S_80AC55DC_5 *)(node->position))->unk_0A =
            ((MovingPosition *)(origin->unk_08))->z + offset_z - 0x14;

        work = (S_80AC55DC_2 *)((u8 *)node + 0x20);
        work->unk_36 = ((MovingPosition *)(origin->unk_08))->x;
        work->unk_38 = ((MovingPosition *)(origin->unk_08))->y;
        work->unk_3A = ((MovingPosition *)(origin->unk_08))->z;
        step_x = -(offset_x << 16) / (duration / 8);
        work->unk_40 = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        work->unk_44 = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        t = step_z / 2;
        work->unk_48 = t;
        t = step_x;
        if (t < 0) {
            t += 3;
        }
        work->unk_4C = t >> 2;
        work->unk_50 = step_y / 4;
        work->unk_54 = step_z / 4;

        work->unk_14 = effect_id;
        work->unk_32 = duration;
        work->unk_34 = duration;
        register_node(node, project_sprite_chain);

        sprite = node->sprite;
        sprite_flags = sprite->flags;
        sprite->tpage_abr = 0x20;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->color.c.r = 0;
        sprite->flags = sprite_flags | 0xC;
        ((S_80AC55DC_0 *)node)->unk_20 = effect_value;
        work->unk_08 = effect_value;
        select_record_entry_and_value(sprite, shared_sprite_entries, 0);
    }
}

