#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801550E0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801550E0_0;   /* arg0 in func_801550E0 */

typedef struct S_801550E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801550E0_1;   /* arg3 in func_801550E0 */


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_80153CE8;
extern u8 D_80156EB8[];
extern u8 D_80156ED0[];
extern u8 D_80156ED8[];

/* Updates a timed hop to the actor's tile and handles action completion. */
void func_801550E0(void *action, void *motion, void *sprite, void *actor)
{
    s32 facing_aux;
    s32 state;
    s32 hop_frames;
    s32 actor_flags;
    s32 target_x;
    s32 x_offset;
    s32 y_offset;
    s16 next_frame;
    u16 action_timer;
    u8 *anim_table;

    state = ((S_801550E0_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        next_frame = ((S_801550E0_0 *)action)->unk_9E.s - 1;
        ((S_801550E0_0 *)action)->unk_9E.s = next_frame;
        if ((next_frame << 16) != 0) {
            break;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80156ED0;
        func_80047784(
            sprite,
            D_80156ED0[((gameWork.view.viewAngle + ((S_801550E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801550E0_0 *)action)->unk_98 |= 8;
        ((S_801550E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801550E0_0 *)action)->unk_9E.u = 5;
        ((S_801550E0_0 *)action)->unk_A0 = 0;
        ((S_801550E0_0 *)action)->unk_9B++;

    case 1:
        hop_frames = ((S_801550E0_0 *)action)->unk_9E.u;
        ((S_801550E0_0 *)action)->unk_90 -= ((S_801550E0_0 *)action)->unk_A0;
        if (hop_frames != 0) {
            target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
            x_offset = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            x_offset -= 0x20;
            ((EntityRec *)motion)->unk_0C = ((target_x - x_offset) << 16) / hop_frames;

            y_offset = ((EntityRec *)motion)->y.w.i;
            y_offset -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - y_offset) << 16) /
                ((S_801550E0_0 *)action)->unk_9E.u;
            ((S_801550E0_0 *)action)->unk_A0 =
                (-func_800644B8(((S_801550E0_0 *)action)->unk_9E.u * 0x199)) << 10;
        }

        ((S_801550E0_0 *)action)->unk_90 += ((S_801550E0_0 *)action)->unk_A0;
        next_frame = ((S_801550E0_0 *)action)->unk_9E.s - 1;
        ((S_801550E0_0 *)action)->unk_9E.s = next_frame;
        if (next_frame < 0) {
            ((S_801550E0_0 *)action)->unk_90 = 0;
            ((S_801550E0_0 *)action)->unk_98 &= 0xFFF7;
            ((S_801550E0_1 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801550E0_0 *)action)->unk_9B++;
        }

    case 2:
        if (((S_801550E0_1 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801550E0_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80156ED8;
            func_80047784(
                sprite,
                D_80156ED8[((gameWork.view.viewAngle + ((S_801550E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801550E0_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        anim_table = D_80156EB8;
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != anim_table) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
            func_80047784(
                sprite,
                anim_table[((gameWork.view.viewAngle + ((S_801550E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_timer = ((S_801550E0_0 *)action)->unk_96 - 1;
    ((S_801550E0_0 *)action)->unk_96 = action_timer;
    if ((s16)action_timer > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    if (dungeonStatus.unk_08 != 0) {
        dungeonStatus.unk_08--;
    }

    actor_flags = ((S_801550E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_801550E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_801550E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_801550E0_1 *)actor)->unk_2A = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
        }
    }

    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_801550E0_0 *)action)->unk_8C = &D_80153CE8;
        func_800A9A04(actor);
    }
}
