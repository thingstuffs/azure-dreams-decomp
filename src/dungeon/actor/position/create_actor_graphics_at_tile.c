#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

#include "slus/gp_shared_81510.h"

void func_8003DB94();  /* extern */
void *allocate_list_node();            /* extern */
s32 register_node();           /* extern */
void clear_entry_flag_and_link_owner();                      /* extern */
void cycle_map_cell_flags();             /* extern */
s8 find_active_rect_containing_point();                           /* extern */
void set_record_integer_tile_center();              /* extern */
s16 sample_terrain_surface_height();                   /* extern */
void dispatch_actor_actions_and_integrate_gravity(void *object, void *motion, void *entity);
void advance_actor_status_turn_second(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state);
s32 process_actor_state_chain(void *state_base, s32 entry_data, Entry *entry);
extern M2C_UNK D_800DEF08;

typedef struct S_800D2CB4_0 {
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
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_800D2CB4_0;

typedef struct S_800D2CB4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800D2CB4_1;

typedef struct S_800D2CB4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D2CB4_2;

/* Creates a dungeon object at the given tile and initializes its graphics and state. */
void *create_actor_graphics_at_tile(s16 object_kind, u16 tile_x, u16 tile_y, s16 height) {
    s32 tile_flags;
    s16 saved_kind;
    SpriteFrameState *graphics;
    S_800D2CB4_2 *position;
    void *object;
    S_800D2CB4_0 *state;
    u8 saved_x;
    s16 saved_height;
    u8 saved_y;
    s32 kind;
    u8 call_x;
    u8 call_y;

    saved_kind = object_kind;
    state = NULL;
    saved_x = tile_x;
    saved_height = height;
    saved_y = tile_y;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        state = object + 0x20;
        state->unk_13 = 0x34;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
        }
        register_node(object, &process_actor_state_chain);
        position = ((S_800D2CB4_1 *)object)->unk_08;
        position->unk_0A = saved_height;
        graphics = ((S_800D2CB4_1 *)object)->unk_0C;
        graphics->unk_24 = saved_x;
        graphics->unk_25 = saved_y;
        func_8003DB94(graphics, &D_800DEF08, 0);
        graphics->clut = 0x7E02;
        graphics->scale_x = 0x1800;
        graphics->scale_y = 0x2000;
        graphics->flags = (u16) (graphics->flags | 0xC);
        graphics->tpage_abr = (u16) (graphics->tpage_abr | 0x20);
        graphics->flags = (u16) (graphics->flags | 0x100);
        ((S_800D2CB4_1 *)object)->unk_10 = &dispatch_actor_actions_and_integrate_gravity;
        state->unk_8C = &advance_actor_status_turn_second;
        graphics->unk_26 = find_active_rect_containing_point(graphics->unk_24, graphics->unk_25);
        set_record_integer_tile_center(position, graphics->unk_24, graphics->unk_25);
        state->unk_88 = sample_terrain_surface_height(position->unk_02, position->unk_06, position->unk_0A);
        graphics->color.word = 0x808080;
        graphics->flags = (u16) (graphics->flags | 0x8000);
        clear_entry_flag_and_link_owner(object);
        call_x = graphics->unk_24;
        call_y = graphics->unk_25;
        tile_flags = 0x3000;
        if (state->unk_1C & 0x2000) {
            tile_flags = 0x300;
        }
        cycle_map_cell_flags(call_x, call_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_9E = 0;
        state->unk_1C = (s32) (state->unk_1C | 0x40000200);
    }
    return state;
}
