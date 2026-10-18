#include "common.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172374_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_80172374_0;   /* arg0 in advance_jump_to_target_tile */


typedef struct S_80172374_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80172374_4;   /* global in advance_jump_to_target_tile */

typedef struct S_80172374_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172374_5;   /* map in advance_jump_to_target_tile */


extern s16 get_rounded_facing_and_rounding_flag();
extern void set_record_integer_tile_center();
extern void advance_status_timers();
extern void func_800A9A04();
extern void reduce_actor_food_meter();
extern s32 check_actor_floor_trap();

extern u8 D_80170E54;

/* Advances a jump toward the target tile and finishes movement when the timer expires. */
void advance_jump_to_target_tile(S_80172374_0 *motion, EntityRec *position, Rec_D_80082E80 *target_tile, EntityRec *entity) {
    s32 direction_aux;
    s32 jump_state;
    s32 frames_left;
    s16 next_frames;
    s32 entity_flags;

    jump_state = motion->unk_9B;
    switch (jump_state) {
    case 0:
        if (motion->unk_96 != 8) {
            break;
        }
        motion->unk_98 |= 8;
        position->flags14 = 0xFFEE0000;
        entity->flags1C &= 0xF7FFFFFF;
        motion->unk_A4 = 0;
        motion->unk_9B++;
                        /* fall through */
    case 1:
        frames_left = motion->unk_96;
        motion->unk_90 -= motion->unk_A4;
        if (frames_left != 0) {
            s32 coord;
            s32 axis_origin;
            s32 coord2;
            s32 axis_origin2;

            coord = target_tile->unk_24 << 6;
            axis_origin = position->x.w.i - 0x20;
            position->unk_0C = ((coord - axis_origin) << 16) / frames_left;
            coord2 = target_tile->unk_25 << 6;
            axis_origin2 = position->y.w.i - 0x20;
            position->unk_10 = ((coord2 - axis_origin2) << 16) / motion->unk_96;
            motion->unk_A4 += position->flags14;
            position->flags14 += 0x40000;
        }
        motion->unk_90 += motion->unk_A4;
        if (motion->unk_96 < 3) {
            motion->unk_90 = 0;
            motion->unk_98 &= 0xFFF7;
            entity->flags1C |= 0x08000000;
            motion->unk_9B++;
        }
                        /* fall through */
    case 2:
        if (entity->flags1C & 0x08000000) {
            motion->unk_98 &= 0xFFF7;
            position->flags14 = 0;
            position->unk_10 = 0;
            position->unk_0C = 0;
            set_record_integer_tile_center(position, target_tile->unk_24, target_tile->unk_25);
            motion->unk_9B++;
        }
        break;
    }

    next_frames = (u16)motion->unk_96 - 1;
    motion->unk_96 = next_frames;
    if ((next_frames << 16) <= 0) {
        position->flags14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        set_record_integer_tile_center(position, target_tile->unk_24, target_tile->unk_25);
        reduce_actor_food_meter(entity, 5);
        advance_status_timers(entity);

        if (g_dungeon_status.unk_08 != 0) {
            g_dungeon_status.unk_08 = (u16)g_dungeon_status.unk_08 - 1;
        }

        entity_flags = entity->flags1C;
        if (entity_flags & 0x2000) {
            if (entity->unk_46 & 0x8000) {
                entity->unk_46 &= 0x7FFF;
            }
        } else if (!(entity_flags & 0x410)) {
            if (entity_flags & 0x20000) {

                entity->facing = get_rounded_facing_and_rounding_flag(
                    target_tile->unk_24, target_tile->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
            }
        }

        if ((check_actor_floor_trap(target_tile, entity) << 16) > 0) {
            motion->unk_8C = &D_80170E54;
            func_800A9A04(entity);
        }
    }
}
