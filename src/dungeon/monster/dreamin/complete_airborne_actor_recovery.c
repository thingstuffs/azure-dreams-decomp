#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

extern u8 dreamin_action_continuation_address[];
extern u8 D_80173884[];
extern u8 D_8017388C[];

/* Updates airborne movement, landing animation, and actor recovery when the timer expires. */
void complete_airborne_actor_recovery(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 direction_aux;
    s32 move_ticks;
    s32 origin_x;
    s32 origin_y;
    s32 height_offset;
    s32 height;
    s32 arc_ticks;
    s32 target_x;
    s16 next_tick;
    s32 actor_flags;
    u16 remaining_ticks;
    s32 phase;
    DungeonGlobalStatus *counter_base;

    phase = body->action_phase.u;
    switch (phase) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_80173884;
        select_sprite_entry(
            sprite,
            D_80173884[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        body->action_state_flags |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        motion->velocity_z = 0xFFF00000;
        body->unk_A0.value = 0;
        body->action_phase.u++;
    case 1:
        move_ticks = body->unk_A4.halves.low.s;
        body->unk_90.value =
            body->unk_90.value - body->unk_A0.value;
        if (move_ticks != 0) {
            target_x = sprite->tile_x << 6;
            origin_x = motion->x.w.i - 0x20;
            origin_y = motion->y.w.i - 0x20;
            motion->velocity_x =
                ((target_x - origin_x) << 16) /
                move_ticks;
            motion->velocity_y =
                (((sprite->tile_y << 6) - origin_y) << 16) /
                (s16)body->unk_A4.halves.low.s;
            arc_ticks = body->unk_A4.halves.low.s;
            motion->velocity_z += (arc_ticks << 15) + (arc_ticks << 13);
            body->unk_A0.value += motion->velocity_z;
        }
        height = body->unk_90.value;
        height_offset = body->unk_A0.value;
        next_tick = body->unk_A4.halves.low.u - 1;
        height += height_offset;
        body->unk_A4.halves.low.s = next_tick;
        body->unk_90.value = height;
        if (next_tick < 0) {
            body->unk_90.value = 0;
            body->action_state_flags &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            body->action_phase.u++;
        }
    case 2:
        if (actor->flags1C & 0x08000000) {
            body->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_8017388C;
            select_sprite_entry(
                sprite,
                D_8017388C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
        }
    }

    remaining_ticks = body->action_timer.u - 1;
    body->action_timer.u = remaining_ticks;
    if ((remaining_ticks << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);

        counter_base = &g_dungeon_status;
        if (counter_base->activity_counts.parts.pending_movement_count != 0) {
            (*(u16 *)&counter_base->activity_counts.parts.pending_movement_count)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->action_flags & 0x8000) {
                actor->action_flags &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            }
        }

        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            body->unk_8C.byte_ptr = dreamin_action_continuation_address;
            on_actor_status_updated(actor);
        }
    }
}

/* MECHANISM: Four held arguments naturally give the 0x38 frame and s0/s1/s3/s2 save order. Named
   coordinate/delta and position/offset locals close both load-order residues. */
