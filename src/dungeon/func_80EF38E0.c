#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801610E0_0 {
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
} S_801610E0_0;   /* arg0 in func_801610E0 */

typedef struct S_801610E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801610E0_1;   /* arg3 in func_801610E0 */





extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_8015FCE8;
extern u8 D_80162EB8[];
extern u8 D_80162ED0[];
extern u8 D_80162ED8[];

/* Moves an actor to its tile with a timed hop, updates animation, and completes the action. */
void func_801610E0(void *action, void *motion, void *sprite, void *actor)
{
    s32 direction_aux;
    s32 state;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 pos_x;
    s32 pos_y;
    s16 phase_ticks;
    u16 action_ticks;
    u8 *anim_table;

    state = ((S_801610E0_0 *)action)->unk_9B;
    if (state == 1) {
        goto move_to_tile;
    }
    if (state < 2) {
        if (state == 0) {
            goto wait_to_move;
        }
        goto update_countdown;
    }
    if (state == 2) {
        goto finish_move;
    }
    if (state == 3) {
        goto restore_animation;
    }
    goto update_countdown;

wait_to_move:
    phase_ticks = ((S_801610E0_0 *)action)->unk_9E.s - 1;
    ((S_801610E0_0 *)action)->unk_9E.s = phase_ticks;
    if ((phase_ticks << 16) != 0) {
        goto update_countdown;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80162ED0;
    func_80047784(
        sprite,
        D_80162ED0[((gameWork.view.viewAngle + ((S_801610E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801610E0_0 *)action)->unk_98 |= 8;
    ((S_801610E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
    ((S_801610E0_0 *)action)->unk_9E.u = 5;
    ((S_801610E0_0 *)action)->unk_A0 = 0;
    ((S_801610E0_0 *)action)->unk_9B++;

move_to_tile:
    move_ticks = ((S_801610E0_0 *)action)->unk_9E.u;
    ((S_801610E0_0 *)action)->unk_90 -= ((S_801610E0_0 *)action)->unk_A0;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        pos_x = ((EntityRec *)motion)->x.w.i;
        target_x <<= 6;
        pos_x -= 0x20;
        ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

        pos_y = ((EntityRec *)motion)->y.w.i;
        pos_y -= 0x20;
        ((EntityRec *)motion)->unk_10 =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
            ((S_801610E0_0 *)action)->unk_9E.u;
        ((S_801610E0_0 *)action)->unk_A0 =
            (-func_800644B8(((S_801610E0_0 *)action)->unk_9E.u * 0x199)) << 10;
    }

    ((S_801610E0_0 *)action)->unk_90 += ((S_801610E0_0 *)action)->unk_A0;
    phase_ticks = ((S_801610E0_0 *)action)->unk_9E.s - 1;
    ((S_801610E0_0 *)action)->unk_9E.s = phase_ticks;
    if (phase_ticks < 0) {
        ((S_801610E0_0 *)action)->unk_90 = 0;
        ((S_801610E0_0 *)action)->unk_98 &= 0xFFF7;
        ((S_801610E0_1 *)actor)->unk_1C.s |= 0x08000000;
        ((S_801610E0_0 *)action)->unk_9B++;
    }

finish_move:
    if (((S_801610E0_1 *)actor)->unk_1C.s & 0x08000000) {
        ((S_801610E0_0 *)action)->unk_98 &= 0xFFF7;
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80162ED8;
        func_80047784(
            sprite,
            D_80162ED8[((gameWork.view.viewAngle + ((S_801610E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801610E0_0 *)action)->unk_9B++;
    }
    goto update_countdown;

restore_animation:
    anim_table = D_80162EB8;
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != anim_table) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(
            sprite,
            anim_table[((gameWork.view.viewAngle + ((S_801610E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

update_countdown:
    action_ticks = ((S_801610E0_0 *)action)->unk_96 - 1;
    ((S_801610E0_0 *)action)->unk_96 = action_ticks;
    if ((s16)action_ticks > 0) {
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

    actor_flags = ((S_801610E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_801610E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_801610E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_801610E0_1 *)actor)->unk_2A = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
        }
    }

    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_801610E0_0 *)action)->unk_8C = &D_8015FCE8;
        func_800A9A04(actor);
    }
}
