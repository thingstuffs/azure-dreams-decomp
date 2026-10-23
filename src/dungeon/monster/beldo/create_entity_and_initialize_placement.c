#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/monster/beldo.h"

void *allocate_list_node();
s32 register_node();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
s32 func_80173C30(void);
void update_actor_movement_and_height(void *entity_arg, void *motion_arg, SpriteFrameState *monster_arg);
void update_object_animation(void *obj, void *motion, SpriteFrameState *part, void *state);
extern M2C_UNK beldo_frame_set_1;
extern void *beldo_active_entity;

typedef struct S_80170F84_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x6C];
    s32 * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_80170F84_1;

typedef struct S_80170F84_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80170F84_2;

/* Create a dungeon entity and initialize its state and placement. */
/* Creates Beldo and two attached sprites above the player's height, restores sprite scale, and starts its
 * effect. */
void *create_entity_and_initialize_placement(s16 entity_id, s32 tile_x, s16 tile_y, u16 initial_height) {
    S_80170F84_1 *entity_state = NULL;
    s16 saved_tile_x;
    s16 saved_height;
    s16 saved_tile_y;
    u16 saved_tile_1c;
    u16 saved_tile_1e;
    SpriteFrameState *tile_state;
    S_80170F84_2 *world_state;
    ObjectNodeHeader *entity;

    saved_tile_x = tile_x;
    saved_height = initial_height;
    saved_tile_y = tile_y;
    entity = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (entity != NULL) {
        entity_state = ((void *)entity) + 0x20;
        beldo_active_entity = entity;
        entity->unk_10 = &update_actor_movement_and_height;
        entity_state->unk_13 = MONSTER_BELDO;
        register_node(entity, project_sprite_chain);
        world_state = entity->position;
        world_state->unk_0A = saved_height;
        tile_state = entity->sprite;
        tile_state->unk_24 = saved_tile_x;
        tile_state->unk_25 = saved_tile_y;
        tile_state->frameTable = &beldo_frame_set_1;
        entity_state->unk_9E = 0;
        initialize_actor_sprite_and_animation(entity, world_state, tile_state, entity_id);
        entity_state->unk_9A = 0xFF;
        entity_state->unk_9C = -1;
        entity_state->unk_8C = &update_object_animation;
        entity_state->unk_1C = (s32) (entity_state->unk_1C | 0x40000);
        tile_state->tpage_abr = 0x20;
        tile_state->flags = (u16) (tile_state->flags | 0xC);
        try_move_actor_to_valid_position(entity_state, world_state, tile_state, entity_state);
        world_state->unk_0A = (u16) ((u16)view_reference_entity.z.w.i);
        world_state->unk_16 = (s16) (world_state->unk_0A - 0x20);
        world_state->unk_0A = (u16) (world_state->unk_0A - 0x190);
        saved_tile_1c = tile_state->scale_x;
        saved_tile_1e = tile_state->scale_y;
        tile_state->scale_x = 0U;
        tile_state->scale_y = 0U;
        tile_state->flags = (u16) (tile_state->flags | 0x80);
        create_attached_sprite_with_offset(entity_state, world_state, tile_state, 1);
        create_attached_sprite_with_offset(entity_state, world_state, tile_state, 2);
        tile_state->scale_x = saved_tile_1c;
        tile_state->scale_y = saved_tile_1e;
        func_80173C30();
    }
    return entity_state;
}
