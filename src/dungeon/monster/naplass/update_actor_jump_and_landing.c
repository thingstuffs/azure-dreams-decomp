#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;


typedef struct S_80172288_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_80172288_0;   /* arg0 in update_actor_jump_and_landing */


void select_sprite_entry(S_80047784 *object, s16 table_index, s16 entry_index);
s16 get_rounded_facing_and_rounding_flag();
void set_record_integer_tile_center();
s32 advance_status_timers();
void on_actor_status_updated(void *actor);
void spend_actor_mp();
s32 check_actor_floor_trap();

extern u8 D_80170E68;
extern u8 D_801741B4[];
extern u8 D_801741BC[];

/* Updates an actor's jump toward its target tile and completes the landing. */
void update_actor_jump_and_landing(void *jump, ObjectPosition *motion, void *map_entity, ActorRecord *actor) {
    s32 facing_aux;
    s32 jump_ticks;
    s16 ticks_left;
    s32 actor_flags;

    switch (((S_80172288_0 *)jump)->unk_9B) {
    case 0:
        if (!(((Rec_D_80082E80 *)map_entity)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)map_entity + 0x2C)) = D_801741B4;
        select_sprite_entry(
            map_entity,
            D_801741B4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172288_0 *)jump)->unk_98 |= 8;
        motion->velocity_z = 0xFFEE0000;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_80172288_0 *)jump)->unk_A4 = 0;
        ((S_80172288_0 *)jump)->unk_9B++;

    case 1:
        jump_ticks = ((S_80172288_0 *)jump)->unk_96.s;
        ((S_80172288_0 *)jump)->unk_90 -= ((S_80172288_0 *)jump)->unk_A4;
        if (jump_ticks != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)map_entity)->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / jump_ticks;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)map_entity)->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16) /
                    ((S_80172288_0 *)jump)->unk_96.s;
            }
            ((S_80172288_0 *)jump)->unk_A4 += motion->velocity_z;
            motion->velocity_z += 0x40000;
        }
        ((S_80172288_0 *)jump)->unk_90 += ((S_80172288_0 *)jump)->unk_A4;
        if (((S_80172288_0 *)jump)->unk_96.s < 2) {
            ((S_80172288_0 *)jump)->unk_90 = 0;
            ((S_80172288_0 *)jump)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_80172288_0 *)jump)->unk_9B++;
        }

    case 2:
        if (((u32)actor->flags1C) & 0x08000000) {
            ((S_80172288_0 *)jump)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25);
            (*(u8 * *)((u8 *)map_entity + 0x2C)) = D_801741BC;
            select_sprite_entry(
                map_entity,
                D_801741BC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172288_0 *)jump)->unk_9B++;
        }

    default:
        break;
    }

    ticks_left = ((S_80172288_0 *)jump)->unk_96.u - 1;
    ((S_80172288_0 *)jump)->unk_96.s = ticks_left;
    if ((ticks_left << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {

            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count--;
            }
        }

        actor_flags = ((u32)actor->flags1C);
        if (actor_flags & 0x2000) {
            if (actor->action_flags & 0x8000) {
                actor->action_flags &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                actor->facing = get_rounded_facing_and_rounding_flag(
                    ((Rec_D_80082E80 *)map_entity)->unk_24, ((Rec_D_80082E80 *)map_entity)->unk_25,
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, &facing_aux);
            }
        }

        if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
            ((S_80172288_0 *)jump)->unk_8C = &D_80170E68;
            on_actor_status_updated(actor);
        }
    }
}
