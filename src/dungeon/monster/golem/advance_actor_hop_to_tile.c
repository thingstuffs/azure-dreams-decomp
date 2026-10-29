#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "dungeon/item.h"

typedef struct S_80172998_0 {
    u8 pad_00[0x8C];
    ActorActionHandler unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    s16 unk_A4;
} S_80172998_0;   /* arg0 in advance_actor_hop_to_tile */

extern s32 rsin(s32);
extern void on_actor_status_updated(void *);



extern void golem_action_continuation_address();

/* Advance the actor's hop to its tile and finish the motion when its timer expires. */
void advance_actor_hop_to_tile(S_80172998_0 *motion, ObjectPosition *transform, SpriteFrameState *tile, ActorRecord *actor)
{
    u16 coord_result;
    s32 phase;
    u32 actor_flags;

    phase = motion->unk_9B;
    switch (phase) {
    case 0:
        motion->unk_98 |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        motion->unk_A4 = 7;
        motion->unk_A0 = 0;
        motion->unk_9B++;

    case 1:
        motion->unk_90 -= motion->unk_A0;
        if (motion->unk_A4 != 0) {
            {
                s32 target_x = tile->tile_x << 6;
                s32 current_x = transform->x.w.i - 32;

                transform->velocity_x =
                    ((target_x - current_x) << 16) / motion->unk_A4;
            }
            {
                s32 target_y = tile->tile_y << 6;
                s32 current_y = transform->y.w.i - 32;

                transform->velocity_y =
                    ((target_y - current_y) << 16) / motion->unk_A4;
            }
            motion->unk_A0 =
                (-rsin(motion->unk_A4 * 292)) << 9;
        }

        motion->unk_90 += motion->unk_A0;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        motion->unk_A4--;
        if (motion->unk_A4 < 0) {
            motion->unk_90 = 0;
            motion->unk_98 &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            motion->unk_9B++;
        }

    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            motion->unk_98 &= 0xFFF7;
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            set_record_integer_tile_center(transform, tile->tile_x, tile->tile_y);
            motion->unk_9B++;
        }

    default:
        break;
    }

    motion->unk_96--;
    if (motion->unk_96 > 0) {
        return;
    }

    transform->velocity_z = 0;
    transform->velocity_y = 0;
    transform->velocity_x = 0;
    set_record_integer_tile_center(transform, tile->tile_x, tile->tile_y);
    spend_actor_mp(actor, 5);
    advance_status_timers(actor);

    {

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count--;
        }
    }

    actor_flags = ((u32)actor->flags1C);
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else {
        if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    tile->tile_x, tile->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &coord_result);
            }
        }
    }

    if ((check_actor_floor_trap(tile, actor) << 16) > 0) {
        motion->unk_8C = &golem_action_continuation_address;
        on_actor_status_updated(actor);
    }
}
