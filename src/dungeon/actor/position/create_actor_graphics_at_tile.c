#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/monster_ids.h"
#include "engine/node/allocation.h"
#include "dungeon/level.h"
#include "engine/node.h"
struct Entry;

struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/actor.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "m2c_compat.h"

#include "slus/gp_shared_81510.h"

void select_record_entry_and_value(void *state, void *entries, short index);  /* extern */
void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);                      /* extern */
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);                           /* extern */
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);              /* extern */

void advance_actor_status_turn_second(s32 actor, s32 action_context, s32 sprite, u8 *state);
s32 process_actor_state_chain(void *state_base, void *entry_data, struct Entry *entry);
#include "shared/sprite_source.h"
#include "dungeon/actor/position.h"
extern SpriteSourceEntry D_800DEF08[];

typedef struct S_800D2CB4_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x2];
    void (*unk_8C)(s32,  s32,  s32,  u8 *);
    u8 pad_90[0xA];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x1];
    s16 unk_9E;
} S_800D2CB4_0;

/* Creates a dungeon object at the given tile and initializes its graphics and state. */
void *create_actor_graphics_at_tile(s16 object_kind, u16 tile_x, u16 tile_y, s16 height) {
    s32 tile_flags;
    s16 saved_kind;
    SpriteFrameState *graphics;
    ObjectPosition *position;
    ObjectNodeHeader *object;
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
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        state->unk_13 = MONSTER_WALL_OF_ICE;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | ACTOR_CLASS_ENABLED);
            state->unk_1C = (s32) (state->unk_1C | ACTOR_PLAYER_SIDE);
        }
        register_node(object, &process_actor_state_chain);
        position = object->position;
        position->z.w.i = saved_height;
        graphics = object->sprite;
        graphics->tile_x = saved_x;
        graphics->tile_y = saved_y;
        select_record_entry_and_value(graphics, &D_800DEF08, 0);
        graphics->clut = 0x7E02;
        graphics->scale_x = 0x1800;
        graphics->scale_y = 0x2000;
        graphics->flags = (u16) (graphics->flags | 0xC);
        graphics->tpage_abr = (u16) (graphics->tpage_abr | 0x20);
        graphics->flags = (u16) (graphics->flags | 0x100);
        object->update_callback = &dispatch_actor_actions_and_integrate_gravity;
        state->unk_8C = &advance_actor_status_turn_second;
        graphics->room_index = find_active_rect_containing_point(graphics->tile_x, graphics->tile_y);
        set_record_integer_tile_center(position, graphics->tile_x, graphics->tile_y);
        state->unk_88 = sample_terrain_surface_height(*(u16 *)&position->x.w.i, *(u16 *)&position->y.w.i, position->z.w.i);
        graphics->color.word = 0x808080;
        graphics->flags = (u16) (graphics->flags | 0x8000);
        clear_entry_flag_and_link_owner(object);
        call_x = graphics->tile_x;
        call_y = graphics->tile_y;
        tile_flags = 0x3000;
        if (state->unk_1C & ACTOR_PLAYER_SIDE) {
            tile_flags = 0x300;
        }
        cycle_map_cell_flags(call_x, call_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_9E = 0;
        state->unk_1C = (s32) (state->unk_1C | (ACTOR_REFRESH_GROUND | ACTOR_ASLEEP));
    }
    return state;
}
