#include "engine/scene.h"
#include "shared/sprite_frame_state.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/level.h"
#include "dungeon/player.h"
#include "dungeon/globals.h"

#include "engine/graphics.h"
#include "dungeon/actor.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/state.h"


typedef struct S_800AC82C_6 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800AC82C_6;



/* Updates the actor's position and facing relative to its parent. */
s32 update_actor_transform_from_parent(Rec_func_800A9E70_arg0 *state, ObjectPosition *position, Rec_D_80082E80 *tile, void *actor) {

    GteShortVector offset;
    u16 dest_x;
    u16 dest_y;
    s32 tile_mask;
    s16 ground_height;
    s32 flags;
    u16 parent_height;
    u16 parent_angle_raw;
    s32 parent_angle;
    s32 prev_parent_angle;
    u16 facing;
    s32 angle;
    u8 phase;
    u8 tile_x;
    u8 tile_y;
    SpriteFrameState *parent_data;
    ObjectPosition *parent_position;
    void *parent_body;
    S_800AC82C_6 *parent_rotation;

    tile->unk_06.as_s16 = 0;
    phase = state->unk_9B.as_u8;
    if (phase != 0) {
        if (phase != 1) {
            return 0;
        }
    } else {
        parent_data = NODE_HEADER(((ActorRecord *)actor)->target)->sprite;
        if (find_flagged_record_by_id(parent_data->source, 0) == 0) {
            return 0;
        }
        state->unk_9B.as_u8 = (u8) (state->unk_9B.as_u8 + 1);
    }
    if (((ActorRecord *)actor)->hp_delta < 0) {
        clear_player_linked_action_flags();
    }
    if (((ActorRecord *)actor)->pending_turn_updates != 0) {
        update_actor_status_and_mp(actor);
    }
    if (((ActorRecord *)actor)->flags1C & 0x200000) {
        begin_actor_throw_from_attachment(state, position, tile, actor);
        return 0;
    }
    parent_body = ((ActorRecord *)actor)->target;
    parent_data = NODE_HEADER(parent_body)->sprite;
    parent_position = NODE_HEADER(parent_body)->position;
    tile->unk_24 = (u8) parent_data->tile_x;
    tile->unk_25 = (u8) parent_data->tile_y;
    if (!(((ActorRecord *)actor)->flags1C & ACTOR_LIFTED)) {
        position->velocity_y = 0;
        position->velocity_x = 0;
        state->unk_98 = (u16) (state->unk_98 & 0xFFF7);
        facing = ((ActorRecord *)((ActorRecord *)actor)->target)->facing;
        ((ActorRecord *)actor)->movement_facing = facing;
        tile->unk_24 = (u8) (parent_data->tile_x + *(u8 *) &dir_step_x[(facing >> 9) & 7]);
        tile->unk_25 = (u8) (parent_data->tile_y + *(u8 *) &dir_step_y[(((ActorRecord *)actor)->movement_facing >> 9) & 7]);
        set_record_integer_tile_center(position, tile->unk_24, tile->unk_25);
        ground_height = sample_terrain_surface_height(((u16)position->x.w.i), ((u16)position->y.w.i), (s16) ((*(u16 *)((u8 *)actor
            + 0x88)) - 0x20));
        if (ground_height < 0x200) {
            state->unk_90.at02_s16.v = 0;
            ((ActorRecord *)actor)->ground_height = ground_height;
        }
        if ((find_valid_nearby_position(actor, tile->unk_24, tile->unk_25, &dest_x, &dest_y) << 0x10) != 0) {
            tile->unk_24 = dest_x;
            tile->unk_25 = dest_y;
            set_record_integer_tile_center(position, tile->unk_24, tile->unk_25);
            flags = ((ActorRecord *)actor)->flags1C | ACTOR_REFRESH_GROUND;
            ((ActorRecord *)actor)->flags1C = flags;
            tile_x = tile->unk_24;
            tile_y = tile->unk_25;
            tile_mask = 0x3000;
            if (flags & ACTOR_PLAYER_SIDE) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(tile_x, tile_y, tile_mask);
            ((ActorRecord *)actor)->movement_queue_state = 0;
            return 1;
        }
        set_record_integer_tile_center(position, tile->unk_24, tile->unk_25);
        try_move_actor_to_valid_position(state, position, tile, actor);
        return 0;
    }
    if (resolve_record_orientation_or_fallback(parent_data->source, parent_data, &offset, 0) != 0) {
        position->x.w.i = (u16) ((u16) *lift_jitter_offsets + (parent_position->x.unsigned_parts.integer + ((u16)offset.vx)));
        position->y.w.i = (u16) ((u16) lift_jitter_offsets[1] + (parent_position->y.unsigned_parts.integer + ((u16)offset.vy)));
        parent_height = ((ActorRecord *)((ActorRecord *)actor)->target)->ground_height;
        ((ActorRecord *)actor)->ground_height = parent_height;
        state->unk_90.at02_s16.v = (s16) (((parent_position->z.unsigned_parts.integer + ((u16)offset.vz)) - parent_height) + 8);
        tile->unk_06.as_s16 = 0x10;
        ((ActorRecord *)actor)->flags1C = (s32) (((ActorRecord *)actor)->flags1C | ACTOR_REFRESH_GROUND);
        parent_rotation = ((ActorRecord *)actor)->target;
        prev_parent_angle = (*(s16 *)((u8 *)actor + 0x6A));
        parent_angle_raw = ((u16)parent_rotation->unk_2A);
        parent_angle = parent_rotation->unk_2A;
        angle = (*(u16 *)((u8 *)actor + 0x2A)) - (prev_parent_angle - parent_angle);
        ((ActorRecord *)actor)->movement_facing = parent_angle_raw;
        ((ActorRecord *)actor)->facing = angle;
    }
    return 0;
}
