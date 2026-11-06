#include "shared/entity.h"
#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"


   /* (u8 *)arg3 + ((S_8017169C_0 *)arg3)->unk_8A.s in advance_actor_path_and_facing */

/* Advance the actor along its path and update its facing and movement timing. */
void advance_actor_path_and_facing(ActorRecord *body, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *actor)
{
    ActorRecord *path_actor = body;
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 tile_mask;

    if (((s8)actor->movement_queue_state) <= 0) {
        return;
    }
    if (actor->movement_queue_state <= actor->unk_8A) {
        return;
    }

    direction_table = *(u8 **)&sprite->frameTable;
    if (direction_table != kewne_direction_frames) {
        (sprite->frameTable) = kewne_direction_frames;
        select_sprite_entry(
            sprite,
            kewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }

    old_x = sprite->tile_x;
    old_y = sprite->tile_y;
    tile_mask = 0x3000;
    if (actor->flags1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

    sprite->tile_x =
        actor->path_x[actor->unk_8A];
    sprite->tile_y =
        actor->path_y[actor->unk_8A];
    actor->unk_8A++;

    new_x = sprite->tile_x;
    new_y = sprite->tile_y;
    tile_mask = 0x3000;
    if (actor->flags1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);

    actor->facing = get_rounded_facing_and_rounding_flag(
        old_x, old_y, sprite->tile_x, sprite->tile_y,
        &path_actor->action_state_flags);
    actor->flags1C |= 0x40000000;
    body->action_id.u = 0xF;
    body->unk_8C.word = 0;

    if (g_dungeon_status.flags & 0x80) {
        body->action_timer.u = 0;
        return;
    }

    body->action_timer.u = 8;
    {
        s32 step_count = actor->movement_queue_state;
        if (step_count > 0) {
            body->action_timer.u = 8 / step_count;
        }
    }
}
