#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/picket.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "dungeon/actor/status.h"

typedef struct S_80174428_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x1A];
    s16 unk_88;
} S_80174428_0;   /* object in update_movement_destination_selection_recovery_animation */

typedef struct S_80174428_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174428_1;   /* state in update_movement_destination_selection_recovery_animation */

typedef struct S_80174428_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80174428_2;   /* actor in update_movement_destination_selection_recovery_animation */


extern s16 floor_generation_state[3];
extern u8 picket_action_resume_address[];
extern u8 picket_frame_set_2[];
extern u8 picket_frame_set_1[];
extern u8 picket_frame_set_8[];
extern u16 D_80174FC4[];
extern u16 D_80174FD4[];

extern void select_sprite_entry(void *, s32, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern s16 select_dungeon_spawn_tile(u8 *, u8 *);
extern void play_sound_if_enabled(s32);
extern void refresh_actor_proximity_state(u8 *context);
extern void spend_actor_mp(void *, s32);
extern s16 sample_terrain_surface_height(s32, s32, s16);

/* Updates movement, destination selection, and recovery animation for the object. */
/* Animates Picket's dash and retreat, selects a new valid tile when allowed, then restores sprite scale
 * and spends MP. */
void update_movement_destination_selection_recovery_animation(void *state, ObjectPosition *motion, SpriteFrameState *actor, void *object)
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
    raw_direction = ((S_80174428_0 *)object)->unk_2A.s;
    direction_offset = raw_direction >> 8;
    direction_offset &= 0xE;
    state_id = ((S_80174428_1 *)state)->unk_9B;
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
            (((S_80174428_0 *)object)->unk_1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        (*(u8 **)((u8 *)actor + 0x2C)) = picket_frame_set_2;
        select_sprite_entry(actor,
            picket_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        motion->velocity_x = (x_step << 19) + (x_step << 18);
        motion->velocity_y = (y_step << 19) + (y_step << 18);
        ((S_80174428_1 *)state)->unk_96.s = 4;
        play_sound_if_enabled(0x80E);
        ((S_80174428_1 *)state)->unk_9B++;
    case 1:
        if (!(actor->flags & 0x8000)) {
            ((S_80174428_1 *)state)->unk_96.s--;
            if (((S_80174428_1 *)state)->unk_96.u > 0) {
                return;
            }
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        (*(u8 **)((u8 *)actor + 0x2C)) = picket_frame_set_8;
        select_sprite_entry(actor,
            picket_frame_set_8[((*(s16 *)(((u8 *)(&reference_tile_object)) + 0x3A8) +
                ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        ((S_80174428_1 *)state)->unk_96.s = 0;
        motion->velocity_x = (-x_step) << 18;
        motion->velocity_y = (-y_step) << 18;
        ((S_80174428_1 *)state)->unk_9B++;
        return;

    case 2:
        if (!(actor->flags & 0xE000)) {
            return;
        }
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        (*(u8 **)((u8 *)actor + 0x2C)) = picket_frame_set_1;
        select_sprite_entry(actor,
            picket_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174428_0 *)object)->unk_2A.u + 0x100) >> 9) & 7], 0);
        if (((S_80174428_0 *)object)->unk_1C & ACTOR_PLAYER_SIDE) {
            ((S_80174428_1 *)state)->unk_96.s = 7;
            ((S_80174428_1 *)state)->unk_9B = 5;
            return;
        }
        ((S_80174428_0 *)object)->unk_2A.s &= 0xFFF;
        ((S_80174428_1 *)state)->unk_9B++;
        return;

    case 3:
        {
            u16 angle = ((S_80174428_0 *)object)->unk_2A.s;
            if ((((S_80174428_0 *)object)->unk_2A.u == 0x400) ||
                (actor->flags & 0x8000)) {
                select_sprite_entry(actor, 0x37, 0);
                ((S_80174428_1 *)state)->unk_9B++;
                return;
            }
            if ((u32)(angle - 0x401) < 0x800) {
                ((S_80174428_0 *)object)->unk_2A.s = angle - 0x80;
                return;
            }
            ((S_80174428_0 *)object)->unk_2A.s = (angle + 0x80) & 0xFFF;
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
        ((S_80174428_1 *)state)->unk_96.s = 0;
        x_step = actor->tile_x;
        y_step = actor->tile_y;

        for (;;) {
            if (--attempts_left <= 0) {
                actor->tile_x = (u8)x_step;
                actor->tile_y = (u8)y_step;
                ((S_80174428_1 *)state)->unk_9B++;
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
                ((S_80174428_1 *)state)->unk_9B++;
                return;
            }
        }

    case 5:
        {
            actor->scale_x = D_80174FC4[((S_80174428_1 *)state)->unk_96.u];
            actor->scale_y = D_80174FD4[((S_80174428_1 *)state)->unk_96.u];
            if (((S_80174428_1 *)state)->unk_96.u == 4) {
                play_sound_if_enabled(0x705);
            }
            if (!(actor->flags & 0x8000)) {
                ((S_80174428_1 *)state)->unk_96.s++;
                if (((S_80174428_1 *)state)->unk_96.u < 8) {
                    return;
                }
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            refresh_actor_proximity_state(object);
            height = sample_terrain_surface_height((actor->tile_x << 6) | 0x20,
                (actor->tile_y << 6) | 0x20,
                (s16)(((u16) motion->z.w.i) - 0x80));
            ((S_80174428_0 *)object)->unk_88 = height;
            ((S_80174428_2 *)actor)->unk_2C = picket_frame_set_1;
            spend_actor_mp(object, 0x200);
            select_sprite_entry(actor,
                ((u8 *)actor->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174428_0 *)object)->unk_2A.u + 0x100)
                    >> 9) & 7], 0);
            cycle_map_cell_flags(actor->tile_x, actor->tile_y,
                (((S_80174428_0 *)object)->unk_1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
            actor->scale_y = 0x1000;
            actor->scale_x = 0x1000;
            ((S_80174428_1 *)state)->unk_8C = picket_action_resume_address;
            advance_status_timers(object);
            ((S_80174428_0 *)object)->unk_6D = 0;
            ((S_80174428_0 *)object)->unk_46 &= 0x7FFF;
            return;
        }
    }
}
