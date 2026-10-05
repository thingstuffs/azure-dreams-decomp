#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80173354_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173354_1;   /* arg0 in func_80173354 */


extern void func_80047784(void *, u8, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants);
extern void func_800AD4D0(void *);

extern u8 D_80171400[];
extern u8 D_80175148[];
extern u8 D_80175158[];

/* Updates directional hop motion and returns the actor to its tile on landing. */
void func_80173354(void *action, void *motion, void *sprite, void *actor)
{
    s16 flight_timer;
    s32 direction;
    s32 velocity_x;
    s32 velocity_y;
    s32 rounded_velocity_x;
    s32 rounded_velocity_y;

    direction = (((EntityRec *)actor)->unk_6A >> 9) & 7;

    switch (((S_80173354_1 *)action)->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800AAA54(action, motion, sprite, D_80175158);
            return;
        }

        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80173354_1 *)action)->unk_96.s = 0;
            ((S_80173354_1 *)action)->unk_9B = 2;
            return;
        }

        ((EntityRec *)motion)->unk_0C = ((s16 *)((s8 *)dirStepX))[direction] << 18;
        ((EntityRec *)motion)->unk_10 = ((s16 *)((s8 *)dirStepY))[direction] << 18;
        ((EntityRec *)motion)->flags14 = 0x40000;
        ((S_80173354_1 *)action)->unk_98 |= 8;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((EntityRec *)actor)->flags1C &= 0xFFFBFFFF;
        ((S_80173354_1 *)action)->unk_9B++;

        flight_timer = -1;
        if (((u32)((EntityRec *)actor)->flags1C) & 0x228) {
            flight_timer = 8;
        }
        ((S_80173354_1 *)action)->unk_96.s = flight_timer;

        velocity_x = ((EntityRec *)motion)->unk_0C;
        rounded_velocity_x = velocity_x;
        if (velocity_x < 0) {
            rounded_velocity_x = velocity_x + 3;
        }
        velocity_y = ((EntityRec *)motion)->unk_10;
        ((EntityRec *)motion)->unk_0C = velocity_x - (rounded_velocity_x >> 2);
        rounded_velocity_y = velocity_y;
        if (velocity_y < 0) {
            rounded_velocity_y = velocity_y + 3;
        }
        ((EntityRec *)motion)->unk_10 = velocity_y - (rounded_velocity_y >> 2);
        return;

    case 1:
        ((EntityRec *)motion)->unk_0C -= ((s16 *)((s8 *)dirStepX))[direction] << 14;
        ((EntityRec *)motion)->unk_10 -= ((s16 *)((s8 *)dirStepY))[direction] << 14;

        if (((S_80173354_1 *)action)->unk_96.s > 0) {
            ((S_80173354_1 *)action)->unk_96.u--;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80173354_1 *)action)->unk_96.s = 0;
        }
        if (((S_80173354_1 *)action)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            ((S_80173354_1 *)action)->unk_9B = 0;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800AAA54(action, motion, sprite, D_80175158);
            return;
        }
        ((S_80173354_1 *)action)->unk_96.s = 8;
        ((S_80173354_1 *)action)->unk_9B++;
        return;

    case 2:
        ((EntityRec *)motion)->flags14 = 0xFFFE0000;
        if (((S_80173354_1 *)action)->unk_96.s != 0) {
            s32 tile_delta;
            s32 position;

            tile_delta = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            position = ((EntityRec *)motion)->x.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            ((EntityRec *)motion)->unk_0C = tile_delta >> 1;
            tile_delta = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            position = ((EntityRec *)motion)->y.w.i;
            position -= 0x20;
            tile_delta -= position;
            tile_delta <<= 15;
            ((EntityRec *)motion)->unk_10 = tile_delta >> 1;
            ((EntityRec *)motion)->unk_0C += ((EntityRec *)motion)->unk_0C >> 1;
            ((EntityRec *)motion)->unk_10 += ((EntityRec *)motion)->unk_10 >> 1;
        }

        {
            s16 landing_timer = (u16)((S_80173354_1 *)action)->unk_96.s - 1;

            ((S_80173354_1 *)action)->unk_96.s = landing_timer;
            if (landing_timer > 0) {
                return;
            }
        }

        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        ((S_80173354_1 *)action)->unk_90 = 0;
        ((S_80173354_1 *)action)->unk_98 &= 0xFFF7;
        ((EntityRec *)actor)->flags1C |= 0x08000000;
        ((EntityRec *)actor)->flags1C |= 0x00040000;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80175148;
        func_80047784(sprite,
            D_80175148[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);

        {
            DungeonGlobalStatus *global_state = &dungeonStatus;

            if (((s32)global_state->unk_10) == (u8 *)actor - 0x20) {
                (*(u32 *)&global_state->unk_10) &= 0x7FFFFFFF;
            }
        }
        ((S_80173354_1 *)action)->unk_8C = D_80171400;
        return;

    default:
        return;
    }
}
