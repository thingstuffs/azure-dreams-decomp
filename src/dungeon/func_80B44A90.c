#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


typedef struct S_80172290_0 {
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
} S_80172290_0;   /* arg0 in func_80172290 */


M2C_UNK func_80047784();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
M2C_UNK func_800AD594();
s32 func_800AD9B4();

extern u8 D_80170E70;
extern u8 D_80175A6C[];
extern u8 D_80175A74[];

/* Update a timed jump toward the actor's map tile and handle landing and completion. */
void func_80172290(void *action, void *motion, void *map_actor, void *actor) {
    s32 target_distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172290_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)map_actor + 0x2C)) = D_80175A6C;
        func_80047784(
            map_actor,
            D_80175A6C[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172290_0 *)action)->unk_98 |= 8;
        ((EntityRec *)motion)->flags14 = 0xFFF00000;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((S_80172290_0 *)action)->unk_A0 = 0;
        ((S_80172290_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
        frames_left = ((S_80172290_0 *)action)->unk_96.s;
        ((S_80172290_0 *)action)->unk_90 -= ((S_80172290_0 *)action)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)map_actor)->unk_24 << 6;
                s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

                ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)map_actor)->unk_25 << 6;
                s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

                ((EntityRec *)motion)->unk_10 = ((target_y - current_y) << 16) /
                    ((S_80172290_0 *)action)->unk_96.s;
            }
            ((S_80172290_0 *)action)->unk_A0 += ((EntityRec *)motion)->flags14;
            ((EntityRec *)motion)->flags14 += 0x40000;
        }
        ((S_80172290_0 *)action)->unk_90 += ((S_80172290_0 *)action)->unk_A0;
        if (((S_80172290_0 *)action)->unk_96.s < 0) {
            ((S_80172290_0 *)action)->unk_90 = 0;
            ((S_80172290_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((S_80172290_0 *)action)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((u32)((EntityRec *)actor)->flags1C) & 0x08000000) {
            ((S_80172290_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);
            (*(u8 * *)((u8 *)map_actor + 0x2C)) = D_80175A74;
            func_80047784(
                map_actor,
                D_80175A74[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172290_0 *)action)->unk_9B++;
        }
        break;
    }

    next_timer = ((S_80172290_0 *)action)->unk_96.u - 1;
    ((S_80172290_0 *)action)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        {
            u32 count;
            s32 signed_count;

            signed_count = dungeonStatus.unk_08;
            count = ((u16)dungeonStatus.unk_08);

            if (signed_count != 0) {
                dungeonStatus.unk_08 = count - 1;
            }
        }

        actor_flags = ((u32)((EntityRec *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((EntityRec *)actor)->unk_46 & 0x8000) {
                ((EntityRec *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                ((EntityRec *)actor)->facing = func_800A0818(
                    ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &target_distance);
            }
        }

        if ((func_800AD9B4(map_actor, actor) << 16) > 0) {
            ((S_80172290_0 *)action)->unk_8C = &D_80170E70;
            func_800A9A04(actor);
        }
    }
}
