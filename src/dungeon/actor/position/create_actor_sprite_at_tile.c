#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/monster_ids.h"

struct ObjectNodeHeader;
#include "common.h"
#include "dungeon/actor.h"
#include "shared/entity.h"
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

void *allocate_list_node();            /* extern */
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *entry);                      /* extern */
void cycle_map_cell_flags(s16 x, s16 y, u16 flags);             /* extern */
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);                           /* extern */
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y);              /* extern */
s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);                   /* extern */

extern void advance_actor_status_turn(s32 actor, s32 action_context, s32 sprite, u8 *state);
extern M2C_UNK D_800E221C;

/* Create a dungeon object at the given tile and initialize its sprite and tile flags. */
void *create_actor_sprite_at_tile(s16 object_kind, u16 tile_x, u16 tile_y, s16 height) {
    s32 tile_flags;
    s16 saved_kind;
    SpriteFrameState *sprite;
    ObjectPosition *position;
    ObjectNodeHeader *object;
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
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        state->unk_13 = MONSTER_WALL_OF_ICE;
        kind = (s16) saved_kind;
        if (kind == 1) {
            state->unk_14 = (s32) (state->unk_14 | ACTOR_CLASS_ENABLED);
            state->unk_1C = (s32) (state->unk_1C | ACTOR_PLAYER_SIDE);
        }
        register_node(object, project_sprite_chain);
        position = object->position;
        position->z.w.i = saved_height;
        sprite = object->sprite;
        sprite->source = &D_800E221C;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->scale_y = 0x1400;
        sprite->scale_x = 0x1400;
        sprite->tile_x = saved_tile_x;
        sprite->tile_y = saved_tile_y;
        object->update_callback = &update_actor_gravity;
        state->unk_8C = &advance_actor_status_turn;
        sprite->room_index = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
        set_record_integer_tile_center(position, sprite->tile_x, sprite->tile_y);
        state->unk_88 = sample_terrain_surface_height(*(u16 *)&position->x.w.i, *(u16 *)&position->y.w.i, position->z.w.i);
        sprite->color.word = 0x2C808080;
        sprite->flags = (u16) (sprite->flags | 0x8000);
        clear_entry_flag_and_link_owner(object);
        flag_tile_x = sprite->tile_x;
        flag_tile_y = sprite->tile_y;
        tile_flags = 0x3000;
        if (state->unk_1C & ACTOR_PLAYER_SIDE) {
            tile_flags = 0x300;
        }
        cycle_map_cell_flags(flag_tile_x, flag_tile_y, tile_flags);
        state->unk_9A = 0xE;
        state->unk_9C = -1;
        state->unk_1C = (s32) (state->unk_1C | (ACTOR_REFRESH_GROUND | ACTOR_ASLEEP));
    }
    return state;
}
/* MECHANISM: The exact 0x30 frame comes from one named live range for each
   retail s0/s2/s6/s4/s5/s3/s1 role, with s0 reused for the later object base.
   Preloading call bytes removes the displacement cascade; u8 color fields and
   the 2.7.2-cdk-G0 scheduler produce the final literal and load-slot ordering. */
