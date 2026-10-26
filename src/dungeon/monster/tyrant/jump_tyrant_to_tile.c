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


typedef struct S_80172258_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172258_0;   /* arg0 in jump_tyrant_to_tile */




s16 get_rounded_facing_and_rounding_flag();
s32 on_actor_status_updated();
void spend_actor_mp();


extern u8 tyrant_slot_f_action_callback;
extern u8 D_8016DFD8[];
extern u8 D_8016DFE0[];

/* Updates a jump toward the destination tile and completes movement when its timer expires. */
void jump_tyrant_to_tile(void *jump, void *motion, void *sprite, void *actor) {
    s32 facing_aux;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172258_0 *)jump)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016DFD8;
        select_sprite_entry(
            sprite,
            D_8016DFD8[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172258_0 *)jump)->unk_98 |= 8;
        ((EntityRec *)motion)->flags14 = 0xFFE80000;
        ((EntityRec *)actor)->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80172258_0 *)jump)->unk_A0 = 0;
        ((S_80172258_0 *)jump)->unk_9B++;

    case 1:
        frames_left = ((S_80172258_0 *)jump)->unk_96.s;
        ((S_80172258_0 *)jump)->unk_90 -= ((S_80172258_0 *)jump)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

                ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

                ((EntityRec *)motion)->unk_10 = ((target_y - current_y) << 16) /
                    ((S_80172258_0 *)jump)->unk_96.s;
            }
            ((S_80172258_0 *)jump)->unk_A0 += ((EntityRec *)motion)->flags14;
            ((EntityRec *)motion)->flags14 += 0x60000;
        }
        ((S_80172258_0 *)jump)->unk_90 += ((S_80172258_0 *)jump)->unk_A0;
        if (((S_80172258_0 *)jump)->unk_96.s < 2) {
            ((S_80172258_0 *)jump)->unk_90 = 0;
            ((S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= ACTOR_GROUNDED;
            ((S_80172258_0 *)jump)->unk_9B++;
        }

    case 2:
        if (((u32)((EntityRec *)actor)->flags1C) & ACTOR_GROUNDED) {
            ((S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8016DFE0;
            select_sprite_entry(
                sprite,
                D_8016DFE0[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
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
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
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
                    ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
            }
        }

finish:
        if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
            ((S_80172258_0 *)jump)->unk_8C = &tyrant_slot_f_action_callback;
            on_actor_status_updated(actor);
        }
    }
}
