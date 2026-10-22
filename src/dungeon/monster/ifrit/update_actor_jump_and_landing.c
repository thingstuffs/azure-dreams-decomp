#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172288_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172288_0;   /* arg0 in update_actor_jump_and_landing */

typedef struct {
    u16 x;
    u16 y;
} PathPoint;

typedef struct {
    PathPoint point[8];
} PathTable;

extern void select_sprite_entry(void *, u8, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_80170838[16];
extern s32 D_80170E84;
#include "dungeon/monster/ifrit.h"

/* Updates an actor's jump motion, landing animation, and completion state. */
void update_actor_jump_and_landing(u8 *motion, ObjectPosition *position, u8 *sprite, ActorRecord *actor)
{
    PathTable frame_path;
    s32 facing_result;
    s32 frames_left;
    s32 current_y;
    s16 timer;
    s32 actor_flags;
    s32 phase;
    u8 phase_value;
    DungeonGlobalStatus *global_counter;

    frame_path = *(PathTable *)D_80170838;
    phase = ((S_80172288_0 *)motion)->unk_9B;

    switch (phase) {
    case 0:
        if (((S_80172288_0 *)motion)->unk_96 < 8) {
            ((S_80172288_0 *)motion)->unk_98 |= 8;
            position->velocity_z = 0xFFEE0000;
            actor->flags1C &= 0xF7FFFFFF;
            phase_value = ((S_80172288_0 *)motion)->unk_9B;
            ((S_80172288_0 *)motion)->unk_A0 = 0;
            ((S_80172288_0 *)motion)->unk_9B = phase_value + 1;
        }
        break;
    case 1:
        frames_left = ((S_80172288_0 *)motion)->unk_96;
        ((S_80172288_0 *)motion)->unk_90 -= ((S_80172288_0 *)motion)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x;
                s32 current_x;

                target_x = sprite[0x24];
                current_x = position->x.w.i;
                target_x <<= 6;
                current_x -= 0x20;
                position->velocity_x =
                    ((target_x - current_x) << 16) / frames_left;
            }
            current_y = position->y.w.i - 0x20;
            position->velocity_y =
                (((sprite[0x25] << 6) - current_y) << 16) /
                ((S_80172288_0 *)motion)->unk_96;
            ((S_80172288_0 *)motion)->unk_A0 += position->velocity_z;
            position->velocity_z += 0x40000;
        }
        ((S_80172288_0 *)motion)->unk_90 += ((S_80172288_0 *)motion)->unk_A0;
        if (((S_80172288_0 *)motion)->unk_96 < 3) {
            ((S_80172288_0 *)motion)->unk_90 = 0;
            ((S_80172288_0 *)motion)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_80172288_0 *)motion)->unk_9B++;
        }
                        /* fall through */
    case 2:
        if (actor->flags1C & 0x08000000) {
            ((S_80172288_0 *)motion)->unk_98 &= 0xFFF7;
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, sprite[0x24], sprite[0x25]);
            ((SpriteFrameState *)sprite)->frameTable = ifrit_direction_frames;
            select_sprite_entry(
                sprite,
                ifrit_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            phase_value = ((S_80172288_0 *)motion)->unk_9B;
            ((S_80172288_0 *)motion)->unk_9B = phase_value + 1;
        }
        break;
    }

    timer = ((S_80172288_0 *)motion)->unk_96 - 1;
    ((S_80172288_0 *)motion)->unk_96 = timer;
    if ((timer << 16) <= 0) {
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, sprite[0x24], sprite[0x25]);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);

        global_counter = &g_dungeon_status;
        if (global_counter->activity_counts.parts.pending_movement_count != 0) {
            (*(u16 *)&global_counter->activity_counts.parts.pending_movement_count)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite[0x24], sprite[0x25], reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &facing_result);
            }
        }

        if ((check_actor_floor_trap(sprite, actor) << 16) <= 0) {
            return;
        }
        ((S_80172288_0 *)motion)->unk_8C = &D_80170E84;
        on_actor_status_updated(actor);
    }
    ((SpriteFrameState *)sprite)->scale_x = frame_path.point[((S_80172288_0 *)motion)->unk_96].x;
    ((SpriteFrameState *)sprite)->scale_y = frame_path.point[((S_80172288_0 *)motion)->unk_96].y;
}
