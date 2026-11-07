#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "dungeon/monster/ghosh.h"
#include "dungeon/monster/ghosh_frames.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

extern s32 check_movement_clearance_and_height();
extern void func_8016C698(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation);

/* Advance the entity along its path and update its heading and movement state. */
void advance_entity_along_path(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *path) {
    ActorRecord *path_actor = actor;
    s32 step_index;
    s32 old_tile_flags;
    s16 heading;
    s32 move_result;
    s32 raw_result;
    u8 *step;
    s32 new_tile_flags;
    s32 tile_x;
    s32 tile_y;
    s32 move_state;
    s32 next_x;


    if ((s8)path->movement_queue_state <= 0) {
        return;
    }

    move_state = 15;
    if (actor->action_id != move_state) {
        actor->unk_90.value = 0;
        position->velocity_z = 0;
        actor->unk_9D.u = 0;
    }

    if (path->movement_queue_state <= path->unk_8A) {
        return;
    }

    if (*(u8 **)&sprite->frameTable != ghosh_frame_set_7) {
        (sprite->frameTable) = ghosh_frame_set_7;
        select_sprite_entry(
            sprite,
            ghosh_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + path->facing + 0x100) >> 9) & 7],
            0);
    }

    old_tile_flags = path->flags1C;
    tile_x = sprite->tile_x;
    tile_y = sprite->tile_y;
    old_tile_flags = old_tile_flags & 0x2000;
    update_map_cell_flags_with_item_limit(tile_x, tile_y, old_tile_flags ? 0x300 : 0x3000);

    heading = get_rounded_facing_and_rounding_flag(tile_x, tile_y,
                            path->path_x[path->unk_8A],
                            path->path_y[path->unk_8A],
                            &path_actor->action_state_flags);
    raw_result = check_movement_clearance_and_height(heading, sprite, path, 0x20);

    next_x = path->path_x[path->unk_8A];
    raw_result = raw_result << 16;
    sprite->tile_x = next_x;
    step = path->path_y;
    step += path->unk_8A;
    move_result = raw_result >> 16;
    /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_81324514). */
    do {
        sprite->tile_y = *step;
        step_index = (u16)path->unk_8A;
    } while (0);
    new_tile_flags = path->flags1C;
    step_index = step_index + 1;
    new_tile_flags = new_tile_flags & 0x2000;
    path->unk_8A = step_index;
    cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                  new_tile_flags ? 0x300 : 0x3000);
    path->facing = heading;

    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(sprite->flags & 0x8000)) {
            func_8016C698(actor, position, sprite, path);
        } else {
            actor->action_id = 15;
        }
    } else {
        actor->action_id = move_state;
    }

    actor->unk_8C.word = 0;
    path->flags1C |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        actor->action_timer.s = 0;
        return;
    }

    actor->action_timer.s = 8;
    tile_x = path->movement_queue_state;
    if (tile_x > 0) {
        actor->action_timer.s = 8 / tile_x;
    }
}
