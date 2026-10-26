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

s16 get_rounded_facing_and_rounding_flag();
void on_actor_status_updated(void *actor);
void spend_actor_mp();


extern u8 ashra_action_continuation_address;
extern u8 ashra_frame_set_1[];
extern u8 ashra_frame_set_2[];

/* Updates a jump toward the destination tile and completes movement when its timer expires. */
void complete_actor_jump_to_destination(void *jump, void *motion, void *sprite, void *actor) {
    s32 facing_aux;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172258_0 *)jump)->unk_9B;
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
        ((S_80172258_0 *)jump)->unk_98 |= 8;
        ((EntityRec *)motion)->flags14 = 0xFFEE0000;
        ((ActorRecord *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80172258_0 *)jump)->unk_A8 = 0;
        ((S_80172258_0 *)jump)->unk_9B++;

    case 1:
        frames_left = ((S_80172258_0 *)jump)->unk_96.s;
        ((S_80172258_0 *)jump)->unk_90 -= ((S_80172258_0 *)jump)->unk_A8;
        if (frames_left != 0) {
            {
                s32 target_x = ((SpriteFrameState *)sprite)->tile_x << 6;
                s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

                ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((SpriteFrameState *)sprite)->tile_y << 6;
                s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

                ((EntityRec *)motion)->unk_10 = ((target_y - current_y) << 16) /
                    ((S_80172258_0 *)jump)->unk_96.s;
            }
            ((S_80172258_0 *)jump)->unk_A8 += ((EntityRec *)motion)->flags14;
            ((EntityRec *)motion)->flags14 += 0x40000;
        }
        ((S_80172258_0 *)jump)->unk_90 += ((S_80172258_0 *)jump)->unk_A8;
        if (((S_80172258_0 *)jump)->unk_96.s < 2) {
            ((S_80172258_0 *)jump)->unk_90 = 0;
            ((S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((ActorRecord *)actor)->flags1C |= ACTOR_GROUNDED;
            ((S_80172258_0 *)jump)->unk_9B++;
        }

    case 2:
        if (((u32)((ActorRecord *)actor)->flags1C) & ACTOR_GROUNDED) {
            ((S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
            ((SpriteFrameState *)sprite)->frameTable = ashra_frame_set_2;
            select_sprite_entry(
                sprite,
                ashra_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172258_0 *)jump)->unk_9B++;
        }
    default:
        break;
    }

    next_timer = ((S_80172258_0 *)jump)->unk_96.u - 1;
    ((S_80172258_0 *)jump)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
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
            ((S_80172258_0 *)jump)->unk_8C = &ashra_action_continuation_address;
            on_actor_status_updated(actor);
        }
    }
}
