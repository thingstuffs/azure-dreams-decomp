#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80172C54_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80172C54_0;   /* arg0 in func_80172C54 */






extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_801717F4;
extern u8 D_80175988[];
extern u8 D_801759A8[];
extern u8 D_801759B8[];

/* Updates movement toward a tile, its animation, and completion handling. */
void func_80172C54(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 height_step;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *global_base;

    state = ((S_80172C54_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801759A8;
    func_80047784(
        sprite,
        D_801759A8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
    ((S_80172C54_0 *)action)->unk_98 |= 8;
    actor->flags1C &= 0xF7FFFFFF;
    ((S_80172C54_0 *)action)->unk_9E.s = 5;
    ((S_80172C54_0 *)action)->unk_A4 = 0;
    ((S_80172C54_0 *)action)->unk_9B++;

state_one:
    move_ticks = ((S_80172C54_0 *)action)->unk_9E.s;
    ((S_80172C54_0 *)action)->unk_90 -= ((S_80172C54_0 *)action)->unk_A4;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        pos_x = motion->x.w.i;
        target_x <<= 6;
        pos_x -= 0x20;

        motion->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

        pos_y = motion->y.w.i;
        pos_y -= 0x20;
        motion->unk_10 =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
            ((S_80172C54_0 *)action)->unk_9E.s;

        ((S_80172C54_0 *)action)->unk_A4 =
            (-func_800644B8(((S_80172C54_0 *)action)->unk_9E.s * 0x199)) << 10;
    }

    height_offset = ((S_80172C54_0 *)action)->unk_90;
    height_step = ((S_80172C54_0 *)action)->unk_A4;
    next_move_ticks = ((S_80172C54_0 *)action)->unk_9E.u;
    height_offset += height_step;
    next_move_ticks -= 1;
    ((S_80172C54_0 *)action)->unk_9E.u = next_move_ticks;
    ((S_80172C54_0 *)action)->unk_90 = height_offset;
    if ((next_move_ticks << 16) >= 0) {
        goto state_two;
    }

    ((S_80172C54_0 *)action)->unk_90 = 0;
    ((S_80172C54_0 *)action)->unk_98 &= 0xFFF7;
    actor->flags1C |= 0x08000000;
    ((S_80172C54_0 *)action)->unk_9B++;

state_two:
    if (actor->flags1C & 0x08000000) {
        ((S_80172C54_0 *)action)->unk_98 &= 0xFFF7;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801759B8;
        func_80047784(
            sprite,
            D_801759B8[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172C54_0 *)action)->unk_9B++;
    }
    goto decrement_timer;

state_three:
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_80175988) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80175988;
    func_80047784(
        sprite,
        D_80175988[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);

decrement_timer:
    action_ticks = ((S_80172C54_0 *)action)->unk_96 - 1;
    ((S_80172C54_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    global_base = &dungeonStatus;
    if (global_base->unk_08 != 0) {
        (*(u16 *)&global_base->unk_08)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
        goto collision_check;
    }
    if (actor_flags & 0x410) {
        goto collision_check;
    }
    if (!(actor_flags & 0x20000)) {
        goto collision_check;
    }
    actor->facing = func_800A0818(
        ((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25,
        D_80082E80.tileX,
        D_80082E80.tileY,
        &facing_aux);

collision_check:
    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_80172C54_0 *)action)->unk_8C = &D_801717F4;
        func_800A9A04(actor);
    }
}
