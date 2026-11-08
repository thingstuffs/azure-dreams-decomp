#include "shared/actor_status_flags.h"
/* Relinked copy of dungeon/func_80B1AA58 (func_80B1AA58.c); this jump variant keeps its counter at +0xA0 (twin +0xA8) and uses launch speed 0xFFE80000 / gravity 0x60000 (twin 0xFFEE0000 / 0x40000); otherwise retail differs only at relocation sites. */
#include "common.h"
#include "dungeon/actor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/graphics.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/status.h"
#include "dungeon/item.h"




void spend_actor_mp(ActorRecord *entity, s32 base_reduction);


extern u8 tyrant_slot_f_action_callback;
extern u8 D_8016DFD8[];
extern u8 D_8016DFE0[];

/* Updates a jump toward the destination tile and completes movement when its timer expires. */
void jump_tyrant_to_tile(ActorRecord *jump, ObjectPosition *motion, SpriteFrameState *sprite, void *actor) {
    u16 facing_aux;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = jump->action_phase;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_8016DFD8;
        select_sprite_entry(
            sprite,
            D_8016DFD8[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        jump->action_state_flags |= 8;
        motion->velocity_z = 0xFFE80000;
        ((EntityRec *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        jump->unk_A0.value = 0;
        jump->action_phase++;

    case 1:
        frames_left = ((s16)jump->action_timer);
        jump->unk_90.value -= jump->unk_A0.value;
        if (frames_left != 0) {
            {
                s32 target_x = sprite->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = sprite->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16) /
                    ((s16)jump->action_timer);
            }
            jump->unk_A0.value += motion->velocity_z;
            motion->velocity_z += 0x60000;
        }
        jump->unk_90.value += jump->unk_A0.value;
        if (((s16)jump->action_timer) < 2) {
            jump->unk_90.value = 0;
            jump->action_state_flags &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= ACTOR_GROUNDED;
            jump->action_phase++;
        }

    case 2:
        if (((u32)((EntityRec *)actor)->flags1C) & ACTOR_GROUNDED) {
            jump->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_8016DFE0;
            select_sprite_entry(
                sprite,
                D_8016DFE0[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
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
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {

            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count--;
            }
        }

        actor_flags = ((u32)((EntityRec *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((EntityRec *)actor)->unk_46 & 0x8000) {
                ((EntityRec *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                ((EntityRec *)actor)->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
            }
        }

finish:
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            jump->unk_8C.byte_ptr = &tyrant_slot_f_action_callback;
            on_actor_status_updated(actor);
        }
    }
}
