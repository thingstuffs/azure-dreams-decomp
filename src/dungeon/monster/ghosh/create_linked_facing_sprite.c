#include "common.h"
#include "shared/sprite_frame_state.h"
#define F(p,t,o) (*(t)((u8 *)(p)+(o)))
extern s16 D_80083228;
extern s32 D_80045340, D_80083498, D_801714B0, D_80174C5C;
extern void * D_80174CDC[3];
struct ObjectNodeHeader; void * allocate_list_node(s32, struct ObjectNodeHeader * *);
extern void register_node();
#include "engine/graphics/select_sprite_entry_api.h"
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

    object = allocate_list_node(0x112, (struct ObjectNodeHeader * *)(&D_80083498));
    call_object = object;
    if (object != 0) {
        s32 z_offset;

        state = object + 0x20;
        F(state, s8*, 0x13) = 0x15;
        F(object, s32**, 0x10) = &D_801714B0;
        register_node(call_object, &D_80045340);
        call_object = object;
        z_offset = z - 0x18;
        position = F(object, void**, 8);
        F(position, s16*, 0xA) = z_offset;
        sprite = F(object, void**, 0xC);
        ((SpriteFrameState *)sprite)->frameTable = &D_80174C5C;
        ((SpriteFrameState *)sprite)->unk_24 = saved_x;
        ((SpriteFrameState *)sprite)->unk_25 = saved_y;
        ((SpriteFrameState *)sprite)->unk_06 = -4;
        initialize_actor_sprite_and_animation(call_object, position, sprite, 0);
        F(state, s16*, 0x2A) = 0x200;
        select_sprite_entry(sprite, ((u8 *)(*(s32 * *)&((SpriteFrameState *)sprite)->frameTable))[((D_80083228 + 0x300) >> 9) & 7], 0);
        ((SpriteFrameState *)sprite)->scale_y = 0x1800;
        ((SpriteFrameState *)sprite)->scale_x = 0x1800;
        F(position, u16*, 2) -= 0x10;
        F(position, u16*, 6) -= 0x10;
        tile_x = ((SpriteFrameState *)sprite)->unk_24;
        tile_y = ((SpriteFrameState *)sprite)->unk_25;
        tile_mask = 0x3000;
        if (F(state, s32*, 0x1C) & 0x2000)
            tile_mask = 0x300;
        update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
        unlink_entity_node(state);
        D_80174CDC[0] = object;
        F(object, s32**, 0x10) = (s32 *)((s32)F(object, s32**, 0x10) | 0x80000000);
    }
}
