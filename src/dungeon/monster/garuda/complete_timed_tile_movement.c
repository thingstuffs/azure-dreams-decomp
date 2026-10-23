#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80173A08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xC];
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_80173A08_0;   /* arg0 in complete_timed_tile_movement */

extern void select_sprite_entry(void *, s32, s32);
extern s32 rsin(s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);

extern u8 garuda_action_resume_address[];
extern u8 D_801748A0[];
extern u8 D_801748A8[];
extern u8 garuda_frame_set_4[];

/* Advance a timed movement animation, snap the entity to its tile, and finish the action. */
void complete_timed_tile_movement(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity)
{
    s32 direction_work[2];
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 world_x;
    s32 arc_base;
    s32 arc_offset;
    s32 world_y;
    s32 height_offset;
    s32 next_move_ticks;
    s32 entity_mask;
    s32 action_ticks;
    s32 entity_flags;
    s32 facing_index;
    DungeonGlobalStatus *global_base;

    state = ((S_80173A08_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        (sprite->frameTable) = D_801748A0;
        facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_801748A0[facing_index & 7], 0);
        ((S_80173A08_0 *)action)->unk_98 |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80173A08_0 *)action)->unk_B0.s = 5;
        ((S_80173A08_0 *)action)->unk_A0 = 0;
        ((S_80173A08_0 *)action)->unk_9B++;
        break;
    case 1:
        ((S_80173A08_0 *)action)->unk_90 += 0xC0000;
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        (sprite->frameTable) = D_801748A8;
        facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_801748A8[facing_index & 7], 0);
        ((S_80173A08_0 *)action)->unk_98 |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80173A08_0 *)action)->unk_B0.s = 5;
        ((S_80173A08_0 *)action)->unk_A0 = 0;
        ((S_80173A08_0 *)action)->unk_90 -= 0x400000;
        ((S_80173A08_0 *)action)->unk_9B++;
                        /* fall through */
    case 2:
        move_ticks = ((S_80173A08_0 *)action)->unk_B0.s;
        ((S_80173A08_0 *)action)->unk_90 -= ((S_80173A08_0 *)action)->unk_A0;
        if (move_ticks != 0) {
            target_x = sprite->tile_x;
            world_x = motion->x.w.i;
            target_x <<= 6;
            world_x -= 0x20;
            motion->velocity_x = ((target_x - world_x) << 16) / move_ticks;

            world_y = motion->y.w.i;
            world_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - world_y) << 16) /
                ((S_80173A08_0 *)action)->unk_B0.s;

            arc_base = (0 - rsin(((S_80173A08_0 *)action)->unk_B0.s * 0x199)) << 10;
            ((S_80173A08_0 *)action)->unk_A0 = arc_base + (arc_base >> 1);
        }

        height_offset = ((S_80173A08_0 *)action)->unk_90;
        arc_offset = ((S_80173A08_0 *)action)->unk_A0;
        next_move_ticks = ((S_80173A08_0 *)action)->unk_B0.u;
        height_offset += arc_offset;
        next_move_ticks -= 1;
        ((S_80173A08_0 *)action)->unk_B0.u = next_move_ticks;
        ((S_80173A08_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) < 0) {

            entity_mask = 0x08000000;
            ((S_80173A08_0 *)action)->unk_90 = 0;
            ((S_80173A08_0 *)action)->unk_98 &= 0xFFF7;
            entity->flags1C |= entity_mask;
            (sprite->frameTable) = garuda_frame_set_4;
            facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
            select_sprite_entry(sprite, garuda_frame_set_4[facing_index & 7], 0);
            ((S_80173A08_0 *)action)->unk_9B++;
        }
                        /* fall through */
    case 3:
        if (!(entity->flags1C & ACTOR_GROUNDED)) {
            break;
        }
        ((S_80173A08_0 *)action)->unk_98 &= 0xFFF7;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        (sprite->frameTable) = garuda_frame_set_4;
        facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(sprite, garuda_frame_set_4[facing_index & 7], 0);
        ((S_80173A08_0 *)action)->unk_9B++;

        break;
    default:
        break;
    }

    action_ticks = ((S_80173A08_0 *)action)->unk_96 - 1;
    ((S_80173A08_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(entity, 4);
    advance_status_timers(entity);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    entity_flags = entity->flags1C;
    if (entity_flags & 0x2000) {
        if (entity->action_flags & ACTOR_ACTION_PENDING) {
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(entity_flags & 0x410)) {
        if (entity_flags & 0x20000) {
            entity->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, direction_work);
        }
    }
    ((S_80173A08_0 *)action)->unk_8C = garuda_action_resume_address;
    on_actor_status_updated(entity);
}
