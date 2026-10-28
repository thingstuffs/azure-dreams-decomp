#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_801724B0_arg0.h"
#include "engine/graphics.h"
#include "dungeon/level.h"

typedef struct S_801724B0_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801724B0_3;   /* (u8 *)arg3 + ((S_801724B0_0 *)arg3)->unk_8A.s in advance_baloon_along_path */

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 check_movement_clearance_and_height();
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
void initialize_angle_indexed_target(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *target, ActorRecord *angleSource);

extern u8 baloon_default_frames[8];

/* Advance the actor along its queued path and update movement timing. */
void advance_baloon_along_path(ActorRecord *motion, ObjectPosition *actor_index, SpriteFrameState *actor, ActorRecord *move_data) {
    s32 tile_mask;
    s16 heading;
    s32 x;
    s32 y;

    if ((((s8)move_data->movement_queue_state) > 0) &&
        (move_data->movement_queue_state > move_data->unk_8A)) {
        if (*(u8 **)&actor->frameTable != baloon_default_frames) {
            (actor->frameTable) = baloon_default_frames;
            select_sprite_entry(
                actor,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + move_data->facing + 0x100) >> 9) & 7],
                0);
            motion->unk_9E.s = 0;
        }

        x = actor->tile_x;
        y = actor->tile_y;
        tile_mask = (move_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000;
        update_map_cell_flags_with_item_limit(x, y, tile_mask);

        heading = get_rounded_facing_and_rounding_flag(
            x,
            y,
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_74,
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_7C,
            &motion->action_state_flags);
        x = (s16)check_movement_clearance_and_height(heading, actor, move_data, 0x20);

        actor->tile_x =
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_74;
        tile_mask = 0x3000;
        actor->tile_y =
            ((S_801724B0_3 *)((u8 *)move_data + move_data->unk_8A))->unk_7C;
        (*(u16 *)&move_data->unk_8A)++;

        {
            s32 next_x = actor->tile_x;
            s32 next_y = actor->tile_y;

            if (move_data->flags1C & ACTOR_PLAYER_SIDE) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(next_x, next_y, tile_mask);
        }

        move_data->facing = heading;
        if (x == 3 && !(g_dungeon_status.flags & 0x80) && !(actor->flags & 0x8000)) {
            initialize_angle_indexed_target(motion, actor_index, actor, move_data);
            ((Rec_func_801724B0_arg0 *)motion)->unk_8C = 0;
        } else {
            motion->action_id.s = 0xF;
            ((Rec_func_801724B0_arg0 *)motion)->unk_8C = 0;
        }

        (move_data->flags1C) |= ACTOR_REFRESH_GROUND;
        if (g_dungeon_status.flags & 0x80) {
            motion->action_timer.s = 0;
            return;
        }

        motion->action_timer.s = 8;
        x = move_data->movement_queue_state;
        if (x > 0) {
            motion->action_timer.s = 8 / x;
        }
    }

    return;
}

/* MECHANISM: The four live arguments and two call results naturally produce the retail 0x38 frame and
   saved-register order. Explicit mode initialization plus scoped next-coordinate locals reproduce the
   post-call load/store and branch emission order. */
