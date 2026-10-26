#include "common.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#define F(p,t,o) (*(t)((u8 *)(p)+(o)))
extern s16 view_facing_angle_alias;
extern s32 scene_object_list_anchor, D_801714B0, ghosh_frame_set;
extern void * D_80174CDC[3];
struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
#include "dungeon/level/unlink_entity_node_api.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"
void initialize_actor_sprite_and_animation(void *, void *, void *, s32);

/* Create and initialize an object at the supplied coordinates and store it globally. */
void create_linked_facing_sprite(u16 x, u16 y, s32 z) {
    u8 saved_x = x;
    u8 saved_y = y;
    void *object, *state, *position, *sprite;
    s32 tile_mask;
    u8 tile_x, tile_y;
    void *call_object;

    object = allocate_list_node(0x112, (struct ObjectNodeHeader * *)(&scene_object_list_anchor));
    call_object = object;
    if (object != 0) {
        s32 z_offset;

        state = object + 0x20;
        F(state, s8*, 0x13) = 0x15;
        F(object, s32**, 0x10) = &D_801714B0;
        register_node(call_object, project_sprite_chain);
        call_object = object;
        z_offset = z - 0x18;
        position = F(object, void**, 8);
        ((ObjectPosition *)position)->z.w.i = z_offset;
        sprite = F(object, void**, 0xC);
        ((SpriteFrameState *)sprite)->frameTable = &ghosh_frame_set;
        ((SpriteFrameState *)sprite)->tile_x = saved_x;
        ((SpriteFrameState *)sprite)->tile_y = saved_y;
        ((SpriteFrameState *)sprite)->depth_bias = -4;
        initialize_actor_sprite_and_animation(call_object, position, sprite, 0);
        F(state, s16*, 0x2A) = 0x200;
        select_sprite_entry(sprite, ((u8 *)(*(s32 * *)&((SpriteFrameState *)sprite)->frameTable))[((view_facing_angle_alias + 0x300) >> 9) & 7], 0);
        ((SpriteFrameState *)sprite)->scale_y = 0x1800;
        ((SpriteFrameState *)sprite)->scale_x = 0x1800;
        *(u16 *)&((ObjectPosition *)position)->x.w.i -= 0x10;
        *(u16 *)&((ObjectPosition *)position)->y.w.i -= 0x10;
        tile_x = ((SpriteFrameState *)sprite)->tile_x;
        tile_y = ((SpriteFrameState *)sprite)->tile_y;
        tile_mask = 0x3000;
        if (F(state, s32*, 0x1C) & 0x2000)
            tile_mask = 0x300;
        update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
        unlink_entity_node(state);
        D_80174CDC[0] = object;
        F(object, s32**, 0x10) = (s32 *)((s32)F(object, s32**, 0x10) | 0x80000000);
    }
}
