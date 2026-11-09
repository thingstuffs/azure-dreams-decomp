#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/graphics.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/status.h"
#include "dungeon/item.h"
#include "dungeon/data.h"

typedef struct S_80172258_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s32 unk_A8;
} S_80172258_0;   /* arg0 in complete_actor_jump_to_destination */

void spend_actor_mp(ActorRecord *entity, s32 base_reduction);


extern u8 ashra_action_continuation_address;

/* Updates a jump toward the destination tile and completes movement when its timer expires. */
void complete_actor_jump_to_destination(ActorRecord *jump, ObjectPosition *motion, void *sprite, void *actor) {
    u16 facing_aux;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = jump->action_phase;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = ashra_frame_set_1;
        select_sprite_entry(
            sprite,
            ashra_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
            0);
        jump->action_state_flags |= 8;
        motion->velocity_z = 0xFFEE0000;
        ((ActorRecord *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80172258_0 *)jump)->unk_A8 = 0;
        jump->action_phase++;

    case 1:
        frames_left = (s16)jump->action_timer;
        jump->unk_90.value -= ((S_80172258_0 *)jump)->unk_A8;
        if (frames_left != 0) {
            {
                s32 target_x = ((SpriteFrameState *)sprite)->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((SpriteFrameState *)sprite)->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16) /
                    (s16)jump->action_timer;
            }
            ((S_80172258_0 *)jump)->unk_A8 += motion->velocity_z;
            motion->velocity_z += 0x40000;
        }
        jump->unk_90.value += ((S_80172258_0 *)jump)->unk_A8;
        if ((s16)jump->action_timer < 2) {
            jump->unk_90.value = 0;
            jump->action_state_flags &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= ACTOR_GROUNDED;
            jump->action_phase++;
        }

    case 2:
        if (((u32)((ActorRecord *)actor)->flags1C) & ACTOR_GROUNDED) {
            jump->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
            ((SpriteFrameState *)sprite)->frameTable = ashra_frame_set_2;
            select_sprite_entry(
                sprite,
                ashra_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            jump->action_phase++;
        }
    default:
        break;
    }

    next_timer = jump->action_timer - 1;
    jump->action_timer = next_timer;
    if ((next_timer << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {

            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count--;
            }
        }

        actor_flags = ((u32)((ActorRecord *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((ActorRecord *)actor)->action_flags & ACTOR_ACTION_PENDING) {
                ((ActorRecord *)actor)->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                ((ActorRecord *)actor)->facing = get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
            }
        }

finish:
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            jump->unk_8C.byte_ptr = &ashra_action_continuation_address;
            on_actor_status_updated(actor);
        }
    }
}
