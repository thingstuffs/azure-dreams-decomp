#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "dungeon/monster/death.h"



extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);

extern u8 death_direction_frames[];

/* Advance the entity along its path and update its movement state. */
void advance_entity_path_state(ActorRecord *motion_state, ObjectPosition *unused, SpriteFrameState *entity, ActorRecord *path_state) {
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 step_count;
    u16 hp;
    u16 energy;
    u16 step_index;

    if (((s8)path_state->movement_queue_state) <= 0) {
        return;
    }
    if ((s32)path_state->movement_queue_state <= path_state->unk_8A) {
        return;
    }

    if (*(u8 **)&entity->frameTable != death_direction_frames) {
        (entity->frameTable) = death_direction_frames;
        select_sprite_entry(entity,
                      death_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + path_state->facing + 0x100) >> 9) & 7],
                      0);
    }

    if (entity->tile_x == path_state->path_x[path_state->unk_8A] &&
        entity->tile_y == path_state->path_y[path_state->unk_8A]) {
        hp = motion_state->unk_90.parts.high.u;
        energy = ((u16)path_state->ground_height);
        motion_state->unk_90.parts.high.u = hp + 0x20;
        step_index = ((u16)path_state->unk_8A);
        path_state->ground_height = energy - 0x20;
        path_state->unk_8A = step_index + 1;
    } else {
        flags = path_state->flags1C;
        old_x = entity->tile_x;
        old_y = entity->tile_y;
        distance = 0x3000;
        if (flags & 0x2000) {
            distance = 0x300;
        }

        update_map_cell_flags_with_item_limit(old_x, old_y, distance);

        entity->tile_x = path_state->path_x[path_state->unk_8A];
        entity->tile_y = path_state->path_y[path_state->unk_8A];
        path_state->unk_8A += 1;

        cycle_map_cell_flags(entity->tile_x, entity->tile_y,
                      (path_state->flags1C & 0x2000) ? 0x300 : 0x3000);

        path_state->facing =
            get_rounded_facing_and_rounding_flag(old_x, old_y, entity->tile_x,
                          entity->tile_y, &motion_state->action_state_flags);
    }

    motion_state->action_id.s = 0xF;
    motion_state->unk_8C.word = 0;
    path_state->flags1C |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        motion_state->action_timer.u = 0;
        return;
    }

    motion_state->action_timer.u = 8;
    step_count = path_state->movement_queue_state;
    if (step_count > 0) {
        motion_state->action_timer.u = 8 / step_count;
    }

    return;
}
