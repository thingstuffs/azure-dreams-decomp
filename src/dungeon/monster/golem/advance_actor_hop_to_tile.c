#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172998_0 {
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
    s16 unk_A4;
} S_80172998_0;   /* arg0 in advance_actor_hop_to_tile */

extern s32 func_800644B8(s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void reduce_actor_food_meter(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern M2C_UNK D_80170E94;

/* Advance the actor's hop to its tile and finish the motion when its timer expires. */
void advance_actor_hop_to_tile(S_80172998_0 *motion, EntityRec *transform, SpriteFrameState *tile, EntityRec *actor)
{
    s32 coord_result;
    s32 phase;
    u32 actor_flags;

    phase = motion->unk_9B;
    switch (phase) {
    case 0:
        motion->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        motion->unk_A4 = 7;
        motion->unk_A0 = 0;
        motion->unk_9B++;

    case 1:
        motion->unk_90 -= motion->unk_A0;
        if (motion->unk_A4 != 0) {
            {
                s32 target_x = tile->unk_24 << 6;
                s32 current_x = transform->x.w.i - 32;

                transform->unk_0C =
                    ((target_x - current_x) << 16) / motion->unk_A4;
            }
            {
                s32 target_y = tile->unk_25 << 6;
                s32 current_y = transform->y.w.i - 32;

                transform->unk_10 =
                    ((target_y - current_y) << 16) / motion->unk_A4;
            }
            motion->unk_A0 =
                (-func_800644B8(motion->unk_A4 * 292)) << 9;
        }

        motion->unk_90 += motion->unk_A0;
        actor->flags1C &= 0xF7FFFFFF;
        motion->unk_A4--;
        if (motion->unk_A4 < 0) {
            motion->unk_90 = 0;
            motion->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            motion->unk_9B++;
        }

    case 2:
        if (((u32)actor->flags1C) & 0x08000000) {
            motion->unk_98 &= 0xFFF7;
            transform->flags14 = 0;
            transform->unk_10 = 0;
            transform->unk_0C = 0;
            set_record_integer_tile_center(transform, tile->unk_24, tile->unk_25);
            motion->unk_9B++;
        }

    default:
        break;
    }

    motion->unk_96--;
    if (motion->unk_96 > 0) {
        return;
    }

    transform->flags14 = 0;
    transform->unk_10 = 0;
    transform->unk_0C = 0;
    set_record_integer_tile_center(transform, tile->unk_24, tile->unk_25);
    reduce_actor_food_meter(actor, 5);
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
    } else {
        if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    tile->unk_24, tile->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &coord_result);
            }
        }
    }

    if ((check_actor_floor_trap(tile, actor) << 16) > 0) {
        motion->unk_8C = &D_80170E94;
        on_actor_status_updated(actor);
    }
}
