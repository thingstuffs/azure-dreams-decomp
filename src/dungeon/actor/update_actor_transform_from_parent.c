#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/level.h"
#include "dungeon/player.h"

typedef struct EarlyCallData {
    u8 pad0[8];
    s32 value;
} EarlyCallData;

extern s16 lift_jitter_offsets[2];
s32 resolve_record_orientation_or_fallback();
s32 find_flagged_record_by_id(s32, s32);
void set_record_integer_tile_center();
void update_actor_status_and_mp();
void begin_actor_throw_from_attachment();
void cycle_map_cell_flags();
s32 try_move_actor_to_valid_position();
s16 sample_terrain_surface_height();

typedef struct S_800AC82C_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_800AC82C_2_pre;   /* 0x18-byte header immediately before the payload. */

typedef struct S_800AC82C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x18];
    u8 unk_24;
    u8 unk_25;
} S_800AC82C_3;

typedef struct S_800AC82C_6 {
    u8 pad_00[0x2A];
    union { u16 v; s16 n; } unk_2A;   /* accessed as both */
} S_800AC82C_6;

typedef struct S_800AC82C_7_pre {
    EarlyCallData * unk_00;
    u8 pad_04[0x10];
} S_800AC82C_7_pre;   /* the 0x14 bytes before (*(void **)((u8 *)arg3 + 0x60)) in update_actor_transform_from_parent, addressed as (*(void **)((u8 *)arg3 + 0x60))[-1] */

typedef struct S_800AC82C_7 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_800AC82C_7;   /* (*(void **)((u8 *)arg3 + 0x60)) in update_actor_transform_from_parent */

/* Updates the actor's position and facing relative to its parent. */
s32 update_actor_transform_from_parent(Rec_func_800A9E70_arg0 *state, ObjectPosition *position, Rec_D_80082E80 *tile, void *actor) {
    u16 offset[3];
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
    S_800AC82C_3 *parent_data;
    MovingPosition *parent_position;
    void *parent;
    S_800AC82C_6 *parent_rotation;

    ((SpriteFrameState *)tile)->unk_06 = 0;
    phase = state->unk_9B.as_u8;
    if (phase != 0) {
        if (phase != 1) {
            return 0;
        }
    } else {
        parent_data = ((S_800AC82C_7_pre *)((*(void **)((u8 *)actor + 0x60))))[-1].unk_00;
        if (find_flagged_record_by_id(((EarlyCallData *) parent_data)->value, 0) == 0) {
            return 0;
        }
        state->unk_9B.as_u8 = (u8) (state->unk_9B.as_u8 + 1);
    }
    if ((*(s16 *)((u8 *)actor + 0x64)) < 0) {
        clear_player_linked_action_flags();
    }
    if ((*(s8 *)((u8 *)actor + 0x6D)) != 0) {
        update_actor_status_and_mp(actor);
    }
    if ((*(s32 *)((u8 *)actor + 0x1C)) & 0x200000) {
        begin_actor_throw_from_attachment(state, position, tile, actor);
        return 0;
    }
    parent = (*(void **)((u8 *)actor + 0x60));
    parent_data = ((S_800AC82C_2_pre *)parent)[-1].unk_04;
    parent_position = ((S_800AC82C_2_pre *)parent)[-1].unk_00;
    ((SpriteFrameState *)tile)->unk_24 = (u8) parent_data->unk_24;
    ((SpriteFrameState *)tile)->unk_25 = (u8) parent_data->unk_25;
    if (!((*(s32 *)((u8 *)actor + 0x1C)) & 0x80000)) {
        position->velocity_y = 0;
        position->velocity_x = 0;
        state->unk_98 = (u16) (state->unk_98 & 0xFFF7);
        facing = ((S_800AC82C_7 *)((*(void **)((u8 *)actor + 0x60))))->unk_2A;
        (*(u16 *)((u8 *)actor + 0x6A)) = facing;
        ((SpriteFrameState *)tile)->unk_24 = (u8) (parent_data->unk_24 + *(u8 *) &dir_step_x[(facing >> 9) & 7]);
        ((SpriteFrameState *)tile)->unk_25 = (u8) (parent_data->unk_25 + *(u8 *) &dir_step_y[((u16) (*(u16 *)((u8 *)actor + 0x6A)) >> 9) & 7]);
        set_record_integer_tile_center(position, ((SpriteFrameState *)tile)->unk_24, ((SpriteFrameState *)tile)->unk_25);
        ground_height = sample_terrain_surface_height(((u16)position->x.w.i), ((u16)position->y.w.i), (s16) ((*(u16 *)((u8 *)actor
            + 0x88)) - 0x20));
        if (ground_height < 0x200) {
            state->unk_90.at02_s16.v = 0;
            (*(u16 *)((u8 *)actor + 0x88)) = (u16) ground_height;
        }
        if ((find_valid_nearby_position(actor, ((SpriteFrameState *)tile)->unk_24, ((SpriteFrameState *)tile)->unk_25, &dest_x, &dest_y) << 0x10) != 0) {
            ((SpriteFrameState *)tile)->unk_24 = dest_x;
            ((SpriteFrameState *)tile)->unk_25 = dest_y;
            set_record_integer_tile_center(position, ((SpriteFrameState *)tile)->unk_24, ((SpriteFrameState *)tile)->unk_25);
            flags = (*(s32 *)((u8 *)actor + 0x1C)) | 0x40000000;
            (*(s32 *)((u8 *)actor + 0x1C)) = flags;
            tile_x = ((SpriteFrameState *)tile)->unk_24;
            tile_y = ((SpriteFrameState *)tile)->unk_25;
            tile_mask = 0x3000;
            if (flags & 0x2000) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(tile_x, tile_y, tile_mask);
            (*(s8 *)((u8 *)actor + 0x71)) = 0;
            return 1;
        }
        set_record_integer_tile_center(position, ((SpriteFrameState *)tile)->unk_24, ((SpriteFrameState *)tile)->unk_25);
        try_move_actor_to_valid_position(state, position, tile, actor);
        return 0;
    }
    if (resolve_record_orientation_or_fallback(parent_data->unk_08, parent_data, offset, 0) != 0) {
        position->x.w.i = (u16) ((u16) *lift_jitter_offsets + (parent_position->unk_02 + offset[0]));
        position->y.w.i = (u16) ((u16) lift_jitter_offsets[1] + (parent_position->unk_06 + offset[1]));
        parent_height = ((S_800AC82C_7 *)((*(void **)((u8 *)actor + 0x60))))->unk_88;
        (*(u16 *)((u8 *)actor + 0x88)) = parent_height;
        state->unk_90.at02_s16.v = (s16) (((parent_position->unk_0A + offset[2]) - parent_height) + 8);
        ((SpriteFrameState *)tile)->unk_06 = 0x10;
        (*(s32 *)((u8 *)actor + 0x1C)) = (s32) ((*(s32 *)((u8 *)actor + 0x1C)) | 0x40000000);
        parent_rotation = (*(void **)((u8 *)actor + 0x60));
        prev_parent_angle = (*(s16 *)((u8 *)actor + 0x6A));
        parent_angle_raw = parent_rotation->unk_2A.v;
        parent_angle = parent_rotation->unk_2A.n;
        angle = (*(u16 *)((u8 *)actor + 0x2A)) - (prev_parent_angle - parent_angle);
        (*(u16 *)((u8 *)actor + 0x6A)) = parent_angle_raw;
        (*(s16 *)((u8 *)actor + 0x2A)) = angle;
    }
    return 0;
}
