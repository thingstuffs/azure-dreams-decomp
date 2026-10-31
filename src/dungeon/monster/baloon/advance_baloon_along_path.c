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
#include "dungeon/item.h"


extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 check_movement_clearance_and_height();
void initialize_angle_indexed_target(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *target, ActorRecord *angleSource);

extern u8 baloon_default_frames[8];

/* Advance the actor along its queued path and update movement timing. */
void advance_baloon_along_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 tile_mask;
    s16 heading;
    s32 x;
    s32 y;

    if ((((s8)actor->movement_queue_state) > 0) &&
        (actor->movement_queue_state > actor->unk_8A)) {
        if (*(u8 **)&sprite->frameTable != baloon_default_frames) {
            (sprite->frameTable) = baloon_default_frames;
            select_sprite_entry(
                sprite,
                baloon_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->unk_9E.s = 0;
        }

        x = sprite->tile_x;
        y = sprite->tile_y;
        tile_mask = (actor->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000;
        update_map_cell_flags_with_item_limit(x, y, tile_mask);

        heading = get_rounded_facing_and_rounding_flag(
            x,
            y,
            ((ActorRecord *)((u8 *)actor + actor->unk_8A))->path_x[0],
            ((ActorRecord *)((u8 *)actor + actor->unk_8A))->path_y[0],
            &body->action_state_flags);
        x = (s16)check_movement_clearance_and_height(heading, sprite, actor, 0x20);

        sprite->tile_x =
            ((ActorRecord *)((u8 *)actor + actor->unk_8A))->path_x[0];
        tile_mask = 0x3000;
        sprite->tile_y =
            ((ActorRecord *)((u8 *)actor + actor->unk_8A))->path_y[0];
        (*(u16 *)&actor->unk_8A)++;

        {
            s32 next_x = sprite->tile_x;
            s32 next_y = sprite->tile_y;

            if (actor->flags1C & ACTOR_PLAYER_SIDE) {
                tile_mask = 0x300;
            }
            cycle_map_cell_flags(next_x, next_y, tile_mask);
        }

        actor->facing = heading;
        if (x == 3 && !(g_dungeon_status.flags & 0x80) && !(sprite->flags & 0x8000)) {
            initialize_angle_indexed_target(body, position, sprite, actor);
            ((Rec_func_801724B0_arg0 *)body)->unk_8C = 0;
        } else {
            body->action_id.s = 0xF;
            ((Rec_func_801724B0_arg0 *)body)->unk_8C = 0;
        }

        (actor->flags1C) |= ACTOR_REFRESH_GROUND;
        if (g_dungeon_status.flags & 0x80) {
            body->action_timer.s = 0;
            return;
        }

        body->action_timer.s = 8;
        x = actor->movement_queue_state;
        if (x > 0) {
            body->action_timer.s = 8 / x;
        }
    }

    return;
}

/* MECHANISM: The four live arguments and two call results naturally produce the retail 0x38 frame and
   saved-register order. Explicit mode initialization plus scoped next-coordinate locals reproduce the
   post-call load/store and branch emission order. */
