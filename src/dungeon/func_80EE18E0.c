#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801730E0_0 {
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
} S_801730E0_0;   /* arg0 in func_801730E0 */





extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_80171CE8;
extern u8 D_80174EB8[];
extern u8 D_80174ED0[];
extern u8 D_80174ED8[];

/* Moves the actor to its tile with a hop and completes the timed action. */
void func_801730E0(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 facing_aux;
    s32 phase;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 position_x;
    s32 position_y;
    s16 phase_timer;
    u16 action_timer;
    u8 *anim_table;

    phase = ((S_801730E0_0 *)action)->unk_9B;
    if (phase == 1) {
        goto move_to_tile;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto wait_to_move;
        }
        goto update_countdown;
    }
    if (phase == 2) {
        goto finish_move;
    }
    if (phase == 3) {
        goto restore_animation;
    }
    goto update_countdown;

wait_to_move:
    phase_timer = ((S_801730E0_0 *)action)->unk_9E.s - 1;
    ((S_801730E0_0 *)action)->unk_9E.s = phase_timer;
    if ((phase_timer << 16) != 0) {
        goto update_countdown;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174ED0;
    func_80047784(
        sprite,
        D_80174ED0[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    ((S_801730E0_0 *)action)->unk_98 |= 8;
    (*(u32 *)&actor->flags1C) &= 0xF7FFFFFF;
    ((S_801730E0_0 *)action)->unk_9E.u = 5;
    ((S_801730E0_0 *)action)->unk_A0 = 0;
    ((S_801730E0_0 *)action)->unk_9B++;

move_to_tile:
    move_ticks = ((S_801730E0_0 *)action)->unk_9E.u;
    ((S_801730E0_0 *)action)->unk_90 -= ((S_801730E0_0 *)action)->unk_A0;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        position_x = motion->x.w.i;
        target_x <<= 6;
        position_x -= 0x20;
        motion->unk_0C = ((target_x - position_x) << 16) / move_ticks;

        position_y = motion->y.w.i;
        position_y -= 0x20;
        motion->unk_10 =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - position_y) << 16) /
            ((S_801730E0_0 *)action)->unk_9E.u;
        ((S_801730E0_0 *)action)->unk_A0 =
            (-func_800644B8(((S_801730E0_0 *)action)->unk_9E.u * 0x199)) << 10;
    }

    ((S_801730E0_0 *)action)->unk_90 += ((S_801730E0_0 *)action)->unk_A0;
    phase_timer = ((S_801730E0_0 *)action)->unk_9E.s - 1;
    ((S_801730E0_0 *)action)->unk_9E.s = phase_timer;
    if (phase_timer < 0) {
        ((S_801730E0_0 *)action)->unk_90 = 0;
        ((S_801730E0_0 *)action)->unk_98 &= 0xFFF7;
        (*(u32 *)&actor->flags1C) |= 0x08000000;
        ((S_801730E0_0 *)action)->unk_9B++;
    }

finish_move:
    if (((u32)actor->flags1C) & 0x08000000) {
        ((S_801730E0_0 *)action)->unk_98 &= 0xFFF7;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174ED8;
        func_80047784(
            sprite,
            D_80174ED8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_801730E0_0 *)action)->unk_9B++;
    }
    goto update_countdown;

restore_animation:
    anim_table = D_80174EB8;
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != anim_table) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(
            sprite,
            anim_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }

update_countdown:
    action_timer = ((S_801730E0_0 *)action)->unk_96 - 1;
    ((S_801730E0_0 *)action)->unk_96 = action_timer;
    if ((s16)action_timer > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    if (dungeonStatus.unk_08 != 0) {
        dungeonStatus.unk_08--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
        }
    }

    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_801730E0_0 *)action)->unk_8C = &D_80171CE8;
        func_800A9A04(actor);
    }
}
