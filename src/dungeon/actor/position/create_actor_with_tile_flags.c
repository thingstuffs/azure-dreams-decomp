
struct ObjectNodeHeader;
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D3F74_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x2];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x6];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_800D3F74_0;   /* result in create_actor_with_tile_flags */

extern void *allocate_list_node();
extern void register_node();
extern void select_record_entry_and_value();
extern s8 find_active_rect_containing_point();
extern void set_record_integer_tile_center();
extern s16 sample_terrain_surface_height();
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);
extern void cycle_map_cell_flags();

extern u8 D_800D4158;
extern u8 D_800D4494;
extern u8 D_800DEEC0;

/* Creates an object at the given tile and height, initializing its sprite and tile flags. */
void *create_actor_with_tile_flags(s16 variant, u16 tile_x, u16 tile_y, s16 spawn_height)
{
    ObjectPosition *position;
    s8 *entity = NULL;
    ObjectNodeHeader *object;
    u8 saved_tile_y = tile_y;
    u8 saved_tile_x = tile_x;
    SpriteFrameState *sprite;
    s16 ground_height;
    s32 tile_flags;
    u8 sprite_tile_x;
    u8 sprite_tile_y;

    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        entity = ((s8 *)object) + 0x20;
        ((S_800D3F74_0 *)entity)->unk_13 = 0x34;
        if (variant == 1) {
            ((S_800D3F74_0 *)entity)->unk_14 |= 0x2000;
            ((S_800D3F74_0 *)entity)->unk_1C |= 0x2000;
        }
        register_node(object, project_sprite_chain);
        position = *(s8 * *)&object->position;
        position->z.w.i = spawn_height;
        sprite = *(s8 * *)&object->sprite;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->unk_24 = saved_tile_x;
        sprite->unk_25 = saved_tile_y;
        sprite->clut = 0x7E40;
        sprite->flags |= 0x100;
        select_record_entry_and_value(sprite, &D_800DEEC0, 0);
        object->unk_10 = &D_800D4158;
        ((S_800D3F74_0 *)entity)->unk_8C = &D_800D4494;
        sprite->unk_26 =
            find_active_rect_containing_point(sprite->unk_24, sprite->unk_25);
        set_record_integer_tile_center(position, sprite->unk_24,
                     sprite->unk_25);
        ground_height = sample_terrain_surface_height(*(u16 *)&position->x.w.i,
                               *(u16 *)&position->y.w.i,
                               position->z.w.i);
        ((S_800D3F74_0 *)entity)->unk_88 = ground_height;
        ((S_800D3F74_0 *)entity)->unk_90.at00.v = 0;
        ((S_800D3F74_0 *)entity)->unk_90.at02.v = spawn_height - ground_height;
        sprite->color.word = 0x2C808080;
        sprite->flags |= 0x8000;
        clear_entry_flag_and_link_owner(object);
        sprite_tile_x = sprite->unk_24;
        sprite_tile_y = sprite->unk_25;
        tile_flags = 0x3000;
        if (((S_800D3F74_0 *)entity)->unk_1C & 0x2000) {
            tile_flags = 0x300;
        }
        cycle_map_cell_flags(sprite_tile_x, sprite_tile_y, tile_flags);
        ((S_800D3F74_0 *)entity)->unk_9A = 0xE;
        ((S_800D3F74_0 *)entity)->unk_9C = -1;
        ((S_800D3F74_0 *)entity)->unk_1C |= 0x40000200;
    }
    return entity;
}

/* MECHANISM: The true-space function uses a 0x30 frame and fixed s1-s5 object/part/argument roles;
   variant and spawn_height remain naturally allocated so their temporary computations stay in v0.
   Naming sprite_tile_x/sprite_tile_y before the tile_flags test hoists both lbu operations and removes the one-word load-delay nop;
   the retail store-slot lineage requires 2.7.2-cdk-G0. */
