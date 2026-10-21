#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
typedef struct S_800D1C70_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x2];
    s32 * unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_800D1C70_0;

typedef struct S_800D1C70_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800D1C70_1;

typedef struct S_800D1C70_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D1C70_2;

void select_record_entry_and_value(void *, void *, s32);
void *allocate_list_node(s32, void *);
void register_node(void *, void *);
void clear_entry_flag_and_link_owner(void *);
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
s8 find_active_rect_containing_point(u8, u8);
void set_record_integer_tile_center(void *, u8, u8);
s16 sample_terrain_surface_height(u16, u16, s16);
void update_actor_floor_contact(void *object_arg, void *motion_arg, void *entity_arg);
void process_actor_status_transitions(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state);
extern s32 D_800E2178;

/* Creates a dungeon object at the given tile and height, initializing its sprite and tile flags. */
void *create_actor_at_tile(s16 spawn_kind, u16 tile_x, u16 tile_y, s16 height) {
    s32 tile_flags;
    s16 saved_kind;
    SpriteFrameState *sprite;
    S_800D1C70_2 *position;
    void *object;
    S_800D1C70_0 *state;
    u8 saved_x;
    s16 saved_height;
    u8 saved_y;
    s32 kind;
    u8 call_x;
    u8 call_y;

    saved_kind = spawn_kind;
    state = 0;
    saved_x = tile_x;
    saved_height = height;
    saved_y = tile_y;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        state = object + 0x20;
        state->unk_13 = 0x34;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
        }
        register_node(object, project_sprite_chain);
        position = ((S_800D1C70_1 *)object)->unk_08;
        position->unk_0A = saved_height;
        sprite = ((S_800D1C70_1 *)object)->unk_0C;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->unk_24 = saved_x;
        sprite->unk_25 = saved_y;
        sprite->scale_y = 0x1800;
        sprite->scale_x = 0x1800;
        select_record_entry_and_value(sprite, &D_800E2178, 0);
        ((S_800D1C70_1 *)object)->unk_10 = &update_actor_floor_contact;
        state->unk_8C = &process_actor_status_transitions;
        sprite->unk_26 = find_active_rect_containing_point(sprite->unk_24, sprite->unk_25);
        set_record_integer_tile_center(position, sprite->unk_24, sprite->unk_25);
        state->unk_88 = sample_terrain_surface_height(position->unk_02, position->unk_06, position->unk_0A);
        sprite->color.word = 0x2C808080;
        sprite->flags = (u16) (sprite->flags | 0x8000);
        clear_entry_flag_and_link_owner(object);
        call_x = sprite->unk_24;
        call_y = sprite->unk_25;
        tile_flags = 0x3000;
        if (state->unk_1C & 0x2000) {
            tile_flags = 0x300;
        }
        cycle_map_cell_flags(call_x, call_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_1C = (s32) (state->unk_1C | 0x40000200);
    }
    return state;
}

/* MECHANISM: The 0x30 frame is the exact s0/s2/s6/s4/s5/s3/s1 hold set:
   s2 owns the returned +0x20 base, while s0 is reused after arg0 dies.
   Narrow call-byte locals and the full-width color store preserve the retail
   call ABI, one-word base materialization, and 113-word function length. */
