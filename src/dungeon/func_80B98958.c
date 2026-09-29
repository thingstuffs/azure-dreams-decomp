#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172158_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
} S_80172158_0;   /* arg0 in func_80172158 */





extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80170E9C[];
extern u8 D_80174EE0[];

/* Moves the actor to its tile with a vertical arc and completes the timed action. */
void func_80172158(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 facing_aux;
    s32 move_ticks;
    s32 x_delta;
    s32 axis_pos;
    s32 position;
    s16 next_move_ticks;
    s32 actor_flags;
    u16 action_ticks;
    s32 phase;
    DungeonGlobalStatus *counter_base;

    phase = ((S_80172158_0 *)action)->unk_9B;
    if (phase == 1) {
        goto update_move;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto start_move;
        }
        goto update_timer;
    }
    if (phase == 2) {
        goto finish_move;
    }
    goto update_timer;

start_move:
    if (((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 1) &&
         (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
        (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        ((S_80172158_0 *)action)->unk_98 |= 8;
        (*(u32 *)&actor->flags1C) &= 0xF7FFFFFF;
        ((S_80172158_0 *)action)->unk_9E = 6;
        ((S_80172158_0 *)action)->unk_A0 = 0;
        ((S_80172158_0 *)action)->unk_9B++;
        goto update_move;
    }
    goto update_timer;

update_move:
    move_ticks = ((S_80172158_0 *)action)->unk_9E;
    ((S_80172158_0 *)action)->unk_90 =
        ((S_80172158_0 *)action)->unk_90 - ((S_80172158_0 *)action)->unk_A0;
    if (move_ticks != 0) {
        x_delta = ((Rec_D_80082E80 *)sprite)->unk_24;
        axis_pos = motion->x.w.i;
        x_delta <<= 6;
        axis_pos -= 0x20;
        x_delta -= axis_pos;
        x_delta <<= 16;
        motion->unk_0C = x_delta / move_ticks;
        axis_pos = motion->y.w.i - 0x20;
        motion->unk_10 =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - axis_pos) << 16) /
            (s16)((S_80172158_0 *)action)->unk_9E;
        ((S_80172158_0 *)action)->unk_A0 =
            (-func_800644B8(((S_80172158_0 *)action)->unk_9E * 0x155)) << 9;
    }
    ((S_80172158_0 *)action)->unk_90 += ((S_80172158_0 *)action)->unk_A0;
    next_move_ticks = --((S_80172158_0 *)action)->unk_9E;
    if (next_move_ticks < 0) {
        ((S_80172158_0 *)action)->unk_90 = 0;
        ((S_80172158_0 *)action)->unk_98 &= 0xFFF7;
        (*(u32 *)&actor->flags1C) |= 0x08000000;
        ((S_80172158_0 *)action)->unk_9B++;
    }

finish_move:
    if (((u32)actor->flags1C) & 0x08000000) {
        ((S_80172158_0 *)action)->unk_98 &= 0xFFF7;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174EE0;
        func_80047784(
            sprite,
            D_80174EE0[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172158_0 *)action)->unk_9B++;
    }

update_timer:
    action_ticks = ((S_80172158_0 *)action)->unk_96 - 1;
    ((S_80172158_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        func_800AD594(actor, 3);
        func_800A4ACC(actor);

        counter_base = &dungeonStatus;
        if (counter_base->unk_08 != 0) {
            (*(u16 *)&counter_base->unk_08)--;
        }

        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            if (actor->unk_46 & 0x8000) {
                actor->unk_46 &= 0x7FFF;
            }
            goto check_followup;
        }
        if (actor_flags & 0x410) {
            goto check_followup;
        }
        if (!(actor_flags & 0x20000)) {
            goto check_followup;
        }
        actor->facing = func_800A0818(
            ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
            D_80082E80.tileX, D_80082E80.tileY, &facing_aux);

check_followup:
        if ((func_800AD9B4(sprite, actor) << 16) > 0) {
            ((S_80172158_0 *)action)->unk_8C = D_80170E9C;
            func_800A9A04(actor);
        }
    }
}
