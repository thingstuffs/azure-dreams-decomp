#include "dungeon/monster/u_boat_frames.h"
#include "dungeon/monster/dragon/display_orientation.h"
#include "shared/entity.h"
#include "shared/actor_status_ids.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/barong.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/monster/u_boat.h"
#include "engine/entity.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

extern s32 check_movement_clearance_and_height();
extern s16 get_rounded_facing_and_rounding_flag(); /* Unprototyped: retail call extends the result to this declared width; no shared prototype keeps it */

/* Advance the entity along its path and update its movement state. */
void advance_aura_actor_turn_path(ActorRecord *actor, ObjectPosition *actor_slot, SpriteFrameState *entity_arg, ActorRecord *state_arg) {
    register ActorRecord *state = state_arg;
    register SpriteFrameState *entity= entity_arg;
    s32 tile_flags;
    s16 direction;
    s16 move_result;
    s32 effect_status;
    s16 old_x_early;
    s16 old_x;
    s16 old_y;
    s32 step_count;

    if ((((s8)state->movement_queue_state) > 0) &&
        ((s32)state->movement_queue_state > state->unk_8A)) {
        if ((actor->unk_B4.bytes[1] == 0) &&
            (*(u8 ***)&entity->frameTable != uboat_default_frames)) {
            entity->frameTable = uboat_default_frames;
            select_sprite_entry(entity,
                uboat_default_frames[((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7],
                0);
            if (actor->unk_B0.bytes[0] == 0) {
                create_owner_linked_directional_object(actor, actor_slot, entity);
            }
        }
        old_x_early = entity->tile_x;
        old_y = entity->tile_y;
        effect_status = get_entity_effect_value(state, STATUS_NO_TILE_OCCUPANCY);
        old_x = old_x_early;
        if ((effect_status << 0x10) == 0) {
            s32 tile_x;
            s32 tile_y;
            s32 flags;
            s32 mode;

            tile_x = old_x;
            mode = 0x3000;
            flags = state->flags1C;
            tile_y = old_y;
            if (flags & 0x2000) {
                mode = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, mode);
        }
        direction = get_rounded_facing_and_rounding_flag(old_x, old_y,
            state->path_x[state->unk_8A],
            state->path_y[state->unk_8A],
            (u8 *)actor + 0x98);
        move_result = check_movement_clearance_and_height(direction, entity, state, 0x20);
        entity->tile_x = state->path_x[state->unk_8A];
        entity->tile_y = state->path_y[state->unk_8A];
        state->unk_8A = (u16)state->unk_8A + 1;
        if ((effect_status << 0x10) == 0) {
            s32 new_x;
            s32 new_y;

            tile_flags = 0x3000;
            new_x = entity->tile_x;
            new_y = entity->tile_y;
            if (state->flags1C & ACTOR_PLAYER_SIDE) {
                tile_flags = 0x300;
            }
            cycle_map_cell_flags(new_x, new_y, tile_flags);
        }
        state->facing = direction;
        if (move_result == 3 && (actor->unk_B4.bytes[1] == 0) && !(g_dungeon_status.flags & 0x80) &&
            !(entity->flags & 0x8000)) {
            copy_display_orientation_state(actor, actor_slot, entity, state);
            actor->unk_8C.word = 0;
            state->flags1C |= ACTOR_REFRESH_GROUND;
        } else {
            actor->action_id.s = 0xF;
            actor->unk_8C.word = 0;
            state->flags1C |= ACTOR_REFRESH_GROUND;
        }
        if (g_dungeon_status.flags & 0x80) {
            actor->action_timer.s = 0;
            return;
        }
        actor->action_timer.s = 8;
        step_count = state->movement_queue_state;
        if ((s32)step_count > 0) {
            actor->action_timer.s = 8 / (s32)step_count;
        }
    }
}
