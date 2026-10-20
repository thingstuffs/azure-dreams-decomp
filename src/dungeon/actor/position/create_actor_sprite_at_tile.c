#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_800D24A8_0 {
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
} S_800D24A8_0;

typedef struct S_800D24A8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800D24A8_1;

typedef struct S_800D24A8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D24A8_2;

void *allocate_list_node();            /* extern */
s32 register_node();           /* extern */
void clear_entry_flag_and_link_owner();                      /* extern */
void cycle_map_cell_flags();             /* extern */
s8 find_active_rect_containing_point();                           /* extern */
void set_record_integer_tile_center();              /* extern */
s16 sample_terrain_surface_height();                   /* extern */
extern void update_actor_gravity(void *object, void *motion, void *entity);
extern void advance_actor_status_turn(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state);
extern M2C_UNK D_800E221C;

/* Create a dungeon object at the given tile and initialize its sprite and tile flags. */
void *create_actor_sprite_at_tile(s16 object_kind, u16 tile_x, u16 tile_y, s16 height) {
    s32 tile_flags;
    s16 saved_kind;
    SpriteFrameState *sprite;
    S_800D24A8_2 *position;
    void *object;
    S_800D24A8_0 *state;
    u8 saved_tile_x;
    s16 saved_height;
    u8 saved_tile_y;
    s32 kind;
    u8 flag_tile_x;
    u8 flag_tile_y;

    saved_kind = object_kind;
    state = NULL;
    saved_tile_x = tile_x;
    saved_height = height;
    saved_tile_y = tile_y;
    object = allocate_list_node(0x112, ((s32 *)&D_80083498.next));
    if (object != NULL) {
        state = object + 0x20;
        state->unk_13 = 0x34;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
        }
        register_node(object, project_sprite_chain);
        position = ((S_800D24A8_1 *)object)->unk_08;
        position->unk_0A = saved_height;
        sprite = ((S_800D24A8_1 *)object)->unk_0C;
        sprite->source = &D_800E221C;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1400;
        sprite->scale_x = 0x1400;
        sprite->unk_24 = saved_tile_x;
        sprite->unk_25 = saved_tile_y;
        ((S_800D24A8_1 *)object)->unk_10 = &update_actor_gravity;
        state->unk_8C = &advance_actor_status_turn;
        sprite->unk_26 = find_active_rect_containing_point(sprite->unk_24, sprite->unk_25);
        set_record_integer_tile_center(position, sprite->unk_24, sprite->unk_25);
        state->unk_88 = sample_terrain_surface_height(position->unk_02, position->unk_06, position->unk_0A);
        sprite->color.word = 0x2C808080;
        sprite->flags = (u16) (sprite->flags | 0x8000);
        clear_entry_flag_and_link_owner(object);
        flag_tile_x = sprite->unk_24;
        flag_tile_y = sprite->unk_25;
        tile_flags = 0x3000;
        if (state->unk_1C & 0x2000) {
            tile_flags = 0x300;
        }
        cycle_map_cell_flags(flag_tile_x, flag_tile_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_1C = (s32) (state->unk_1C | 0x40000200);
    }
    return state;
}
/* MECHANISM: The exact 0x30 frame comes from one named live range for each
   retail s0/s2/s6/s4/s5/s3/s1 role, with s0 reused for the later object base.
   Preloading call bytes removes the displacement cascade; u8 color fields and
   the 2.7.2-cdk-G0 scheduler produce the final literal and load-slot ordering. */
