#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;


typedef struct S_80172834_0 {
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
} S_80172834_0;   /* arg0 in update_jump_motion_2 */


extern void select_sprite_entry(S_80047784 *object, s16 table_index, s16 entry_index);
s16 get_rounded_facing_and_rounding_flag();
void set_record_integer_tile_center();
s32 advance_status_timers();
extern void on_actor_status_updated(void *actor);
void reduce_actor_food_meter();
s32 check_actor_floor_trap();

extern u8 D_80170F6C;
extern u8 D_80175278[];
extern u8 D_80175280[];

/* Updates jump motion and animation, then completes the landing. */
void update_jump_motion_2(void *action, EntityRec *motion, void *unit, EntityRec *actor) {
    s32 distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172834_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)unit)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)unit + 0x2C)) = D_80175278;
        select_sprite_entry(
            unit,
            D_80175278[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172834_0 *)action)->unk_98 |= 8;
        motion->flags14 = 0xFFEE0000;
        actor->flags1C &= 0xF7FFFFFF;
        ((S_80172834_0 *)action)->unk_A0 = 0;
        ((S_80172834_0 *)action)->unk_9B++;

    case 1:
        frames_left = ((S_80172834_0 *)action)->unk_96.s;
        ((S_80172834_0 *)action)->unk_90 -= ((S_80172834_0 *)action)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)unit)->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)unit)->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->unk_10 = ((target_y - current_y) << 16) /
                    ((S_80172834_0 *)action)->unk_96.s;
            }
            ((S_80172834_0 *)action)->unk_A0 += motion->flags14;
            motion->flags14 += 0x40000;
        }
        ((S_80172834_0 *)action)->unk_90 += ((S_80172834_0 *)action)->unk_A0;
        if (((S_80172834_0 *)action)->unk_96.s < 2) {
            ((S_80172834_0 *)action)->unk_90 = 0;
            ((S_80172834_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((S_80172834_0 *)action)->unk_9B++;
        }

    case 2:
        if (((u32)actor->flags1C) & 0x08000000) {
            ((S_80172834_0 *)action)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)unit)->unk_24, ((Rec_D_80082E80 *)unit)->unk_25);
            (*(u8 * *)((u8 *)unit + 0x2C)) = D_80175280;
            select_sprite_entry(
                unit,
                D_80175280[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172834_0 *)action)->unk_9B++;
        }
    default:
        break;
    }

    next_timer = ((S_80172834_0 *)action)->unk_96.u - 1;
    ((S_80172834_0 *)action)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)unit)->unk_24, ((Rec_D_80082E80 *)unit)->unk_25);
        reduce_actor_food_meter(actor, 4);
        advance_status_timers(actor);
        {

            if (g_dungeon_status.unk_08 != 0) {
                g_dungeon_status.unk_08--;
            }
        }

        actor_flags = ((u32)actor->flags1C);
        if (actor_flags & 0x2000) {
            if (actor->unk_46 & 0x8000) {
                actor->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                actor->facing = get_rounded_facing_and_rounding_flag(
                    ((Rec_D_80082E80 *)unit)->unk_24, ((Rec_D_80082E80 *)unit)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &distance);
            }
        }

        if ((check_actor_floor_trap(unit, actor) << 16) > 0) {
            ((S_80172834_0 *)action)->unk_8C = &D_80170F6C;
            on_actor_status_updated(actor);
        }
    }
}
