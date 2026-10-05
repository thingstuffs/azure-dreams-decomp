#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F00_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 p; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172F00_0;   /* arg0 in func_80172F00 */


extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174ADC[];

/* Updates staged directional motion, then restores the entity to its tile and animation. */
void func_80172F00(void *action, EntityRec *motion, void *sprite, EntityRec *entity)
{
    s16 timer_signed;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_vx;
    s32 rounded_vy;
    s32 tracked_entity;
    s32 state;
    u16 timer;
    s32 timer_wide;

    state = ((S_80172F00_0 *)action)->unk_9B;
    direction = (entity->unk_6A >> 9) & 7;

    switch (state) {
    case 0:
        func_800AD4D0(entity);
        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            motion->flags14 = 0xFFFD0000;
            func_800AAA54(action, motion, sprite, D_80174ADC);
            return;
        }

        {
            u32 mask_bit_27 = 0xF7FFFFFF;
            u32 mask_bit_18 = 0xFFFBFFFF;
            u32 entity_flags;
            u16 action_flags;

            motion->unk_0C =
                ((s16 *)((s8 *)dirStepX))[direction] << 18;
            motion->unk_10 =
                ((s16 *)((s8 *)dirStepY))[direction] << 18;
            motion->flags14 = 0x20000;

            action_flags = ((S_80172F00_0 *)action)->unk_98;
            action_flags |= 8;
            ((S_80172F00_0 *)action)->unk_98 = action_flags;
            entity_flags = ((u32)entity->flags1C);
            entity_flags &= mask_bit_27;
            entity_flags &= mask_bit_18;
            entity->flags1C = entity_flags;
        }

        ((S_80172F00_0 *)action)->unk_9B = ((S_80172F00_0 *)action)->unk_9B + 1;
        timer_signed = -1;
        if (((u32)entity->flags1C) & 0x228) {
            timer_signed = 8;
        }
        ((S_80172F00_0 *)action)->unk_96.s = timer_signed;

        velocity_x = motion->unk_0C;
        rounded_vx = velocity_x;
        if (velocity_x < 0) {
            rounded_vx = velocity_x + 3;
        }
        velocity_y = motion->unk_10;
        motion->unk_0C = velocity_x - (rounded_vx >> 2);
        rounded_vy = velocity_y;
        motion->unk_10 = velocity_y - (rounded_vy / 4);
        return;
    case 1:
        motion->unk_0C -=
            ((s16 *)((s8 *)dirStepX))[direction] << 15;
        motion->unk_10 -= ((s16 *)((s8 *)dirStepY))[direction] << 15;

        timer_signed = ((S_80172F00_0 *)action)->unk_96.s;
        timer_wide = ((S_80172F00_0 *)action)->unk_96.p;
        if (timer_signed > 0) {
            ((S_80172F00_0 *)action)->unk_96.p = timer_wide - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80172F00_0 *)action)->unk_96.p = 0;
        }

        if (((S_80172F00_0 *)action)->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            ((S_80172F00_0 *)action)->unk_9B = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            motion->flags14 = 0xFFFD0000;
            func_800AAA54(action, motion, sprite, D_80174ADC);
        } else {
            ((S_80172F00_0 *)action)->unk_96.s = 5;
            ((S_80172F00_0 *)action)->unk_9B = ((S_80172F00_0 *)action)->unk_9B + 1;
        }
        return;
    case 2:
        motion->flags14 = 0xFFFD0000;
        if (((S_80172F00_0 *)action)->unk_96.s != 0) {
            s32 tile_coord;
            s32 position_offset;

            tile_coord = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            position_offset = motion->x.w.i;
            position_offset -= 0x20;
            motion->unk_0C = (tile_coord - position_offset) << 15;
            tile_coord = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            position_offset = motion->y.w.i;
            position_offset -= 0x20;
            motion->unk_10 = (tile_coord - position_offset) << 15;
        }

        timer = ((S_80172F00_0 *)action)->unk_96.p - 1;
        ((S_80172F00_0 *)action)->unk_96.p = timer;
        if ((timer << 16) > 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        ((S_80172F00_0 *)action)->unk_98 &= 0xFFF7;
        entity->flags1C |= 0x08000000;
        entity->flags1C |= 0x00040000;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174AD4;
        func_80047784(
            sprite,
            D_80174AD4[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        ((S_80172F00_0 *)action)->unk_8C = D_80171138;
        break;
    default:
        return;
    }
}
