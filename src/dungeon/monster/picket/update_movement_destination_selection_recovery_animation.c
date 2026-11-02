#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/picket.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor/state.h"





extern s16 floor_generation_state[3];
extern u8 picket_action_resume_address[];
extern u8 picket_frame_set_2[];
extern u8 picket_frame_set_1[];
extern u8 picket_frame_set_8[];
extern u16 D_80174FC4[];
extern u16 D_80174FD4[];


extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 select_dungeon_spawn_tile(u8 *, u8 *); /* Unprototyped: retail call extends the result to this declared width; no shared prototype keeps it */

extern s16 sample_terrain_surface_height(s32, s32, s16);

/* Updates movement, destination selection, and recovery animation for the object. */
/* Animates Picket's dash and retreat, selects a new valid tile when allowed, then restores sprite scale
 * and spends MP. */
void update_movement_destination_selection_recovery_animation(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *actor, void *object)
{
    s32 y_step;
    s32 x_step;
    s16 *x_step_ptr;
    s32 direction_offset;
    register u32 raw_direction;
    s16 height;
    s32 attempts_left;
    TileObject *world;
    s16 *level;
    u32 state_id;
    x_step_ptr = (s16 *)((u8 *)dir_step_x);
    raw_direction = ((u16)((ActorRecord *)object)->facing);
    direction_offset = raw_direction >> 8;
    direction_offset &= 0xE;
    state_id = state->action_phase.u;
    x_step_ptr = (s16 *)((u8 *)x_step_ptr + direction_offset);
    direction_offset += (u32)((u8 *)dir_step_y);
    raw_direction = state_id < 6;
    x_step = *x_step_ptr;
    y_step = *(s16 *)direction_offset;
    if (!raw_direction) {
        return;
    }
    switch (state_id) {
    case 0:
        update_map_cell_flags_with_item_limit(actor->tile_x, actor->tile_y,
            (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        actor->frameTable = picket_frame_set_2;
        select_sprite_entry(actor,
            picket_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)object)->facing + 0x100) >> 9) & 7], 0);
        motion->velocity_x = (x_step << 19) + (x_step << 18);
        motion->velocity_y = (y_step << 19) + (y_step << 18);
        state->action_timer.u = 4;
        play_sound_if_enabled(0x80E);
        state->action_phase.u++;
    case 1:
        if (!(actor->flags & 0x8000)) {
            state->action_timer.u--;
            if (state->action_timer.s > 0) {
                return;
            }
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        (*(u8 **)((u8 *)actor + 0x2C)) = picket_frame_set_8;
        select_sprite_entry(actor,
            picket_frame_set_8[((*(s16 *)(((u8 *)(&reference_tile_object)) + 0x3A8) +
                ((ActorRecord *)object)->facing + 0x100) >> 9) & 7], 0);
        state->action_timer.u = 0;
        motion->velocity_x = (-x_step) << 18;
        motion->velocity_y = (-y_step) << 18;
        state->action_phase.u++;
        return;

    case 2:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        actor->frameTable = picket_frame_set_1;
        select_sprite_entry(actor,
            picket_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)object)->facing + 0x100) >> 9) & 7], 0);
        if (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) {
            state->action_timer.u = 7;
            state->action_phase.u = 5;
            return;
        }
        ((ActorRecord *)object)->facing &= 0xFFF;
        state->action_phase.u++;
        return;

    case 3:
        {
            u16 angle = ((u16)((ActorRecord *)object)->facing);
            if ((((ActorRecord *)object)->facing == 0x400) ||
                (actor->flags & 0x8000)) {
                select_sprite_entry(actor, 0x37, 0);
                state->action_phase.u++;
                return;
            }
            if ((u32)(angle - 0x401) < 0x800) {
                ((ActorRecord *)object)->facing = angle - 0x80;
                return;
            }
            ((ActorRecord *)object)->facing = (angle + 0x80) & 0xFFF;
            return;
        }

    case 4:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        select_sprite_entry(actor, 0x38, 0);
        attempts_left = 0x40;
        world = &reference_tile_object;
        level = floor_generation_state;
        state->action_timer.u = 0;
        x_step = actor->tile_x;
        y_step = actor->tile_y;

        for (;;) {
            if (--attempts_left <= 0) {
                actor->tile_x = (u8)x_step;
                actor->tile_y = (u8)y_step;
                state->action_phase.u++;
                return;
            }
            direction_offset = select_dungeon_spawn_tile(&actor->tile_x, &actor->tile_y);
            if (direction_offset < 0) {
                continue;
            }
            if (direction_offset == (s8)((u8)world->room_index) &&
                *(s16 *)((u8 *)level + 6) >= 2) {
                continue;
            }
            direction_offset = sample_terrain_surface_height((actor->tile_x << 6) | 0x20,
                (actor->tile_y << 6) | 0x20,
                (s16)(((u16) motion->z.w.i) - 0x80));
            raw_direction = direction_offset < 0x201;
            if (raw_direction) {
                state->action_phase.u++;
                return;
            }
        }

    case 5:
        {
            actor->scale_x = D_80174FC4[state->action_timer.s];
            actor->scale_y = D_80174FD4[state->action_timer.s];
            if (state->action_timer.s == 4) {
                play_sound_if_enabled(0x705);
            }
            if (!(actor->flags & 0x8000)) {
                state->action_timer.u++;
                if (state->action_timer.s < 8) {
                    return;
                }
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            refresh_actor_proximity_state(object);
            height = sample_terrain_surface_height((actor->tile_x << 6) | 0x20,
                (actor->tile_y << 6) | 0x20,
                (s16)(((u16) motion->z.w.i) - 0x80));
            ((ActorRecord *)object)->ground_height = height;
            actor->frameTable = picket_frame_set_1;
            spend_actor_mp(object, 0x200);
            select_sprite_entry(actor,
                ((u8 *)actor->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)object)->facing + 0x100)
                    >> 9) & 7], 0);
            cycle_map_cell_flags(actor->tile_x, actor->tile_y,
                (((ActorRecord *)object)->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
            actor->scale_y = 0x1000;
            actor->scale_x = 0x1000;
            state->unk_8C.byte_ptr = picket_action_resume_address;
            advance_status_timers(object);
            ((ActorRecord *)object)->pending_turn_updates = 0;
            ((ActorRecord *)object)->action_flags &= 0x7FFF;
            return;
        }
    }
}
