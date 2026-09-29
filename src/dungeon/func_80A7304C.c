#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"


extern void func_80047784();
extern void func_8009C12C();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern void func_800AD594();

extern void *D_800E3DE8[];
extern u8 D_80170E54;
extern u8 D_80174140;
extern u8 D_80174170;


typedef struct S_8017284C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_8017284C_0;   /* arg0 in func_8017284C */




/* Updates staged movement and animation, then places the actor on its destination tile. */
void func_8017284C(S_8017284C_0 *action, EntityRec *motion, Rec_D_80082E80 *sprite, EntityRec *actor)
{
    s16 timer;
    s32 direction_y;
    s32 direction;
    s32 wrap_base;
    s32 x_velocity;
    s32 y_velocity;
    s32 z_velocity;
    s32 speed_component;
    s32 facing;
    s32 state;

    state = action->unk_9B;
    if (state == 1) {
        goto state1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state0;
        }
        return;
    }
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    return;

state0:
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        action->unk_9B = 3;
        action->unk_96.s = 0;
        sprite->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(actor, sprite, actor->facing, 1);
        return;
    }

    facing = ((u16)actor->facing >> 9) & 7;
    direction = facing + 4;
    wrap_base = direction;
    if (direction < 0) {
        wrap_base = facing + 11;
    }
    direction -= wrap_base & 0x18;
    motion->unk_0C =
        (*(s16 *)((u8 *)(((s8 *)dirStepX)) + (direction * 2))) * 0x60000;
    direction_y = (*(s16 *)((u8 *)(((s8 *)dirStepY)) + (direction * 2)));
    motion->flags14 = 0;
    motion->unk_10 = direction_y * 0x60000;
    sprite->unk_2C.as_pv = &D_80174140;
    func_80047784(sprite,
        (*(u8 *)((u8 *)(&D_80174140) + (((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7))),
        0);
    action->unk_96.s = 0;
    action->unk_9B += 1;
    return;

state1:
    x_velocity = motion->unk_0C;
    y_velocity = motion->unk_10;
    motion->unk_0C = x_velocity - (x_velocity >> 2);
    motion->unk_10 = y_velocity - (y_velocity >> 2);
    if (sprite->unk_14.at00_u16.v & 0xE000) {
        sprite->unk_2C.as_pv = &D_80174170;
        func_80047784(sprite,
            (*(u8 *)((u8 *)(&D_80174170) + (((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7))),
            0);
        action->unk_96.s = 0x14;
        action->unk_9B += 1;
        return;
    }
    return;

state2:
    timer = action->unk_96.u - 1;
    z_velocity = motion->flags14;
    action->unk_96.s = timer;
    if (timer < 12) {
        z_velocity += 0x1400;
    } else {
        z_velocity += 0x20000;
    }
    motion->flags14 = z_velocity;
    action->unk_90 += z_velocity;

    if (action->unk_96.s == 0x11) {
        func_800A56E0(0x808);
        direction = ((u16)actor->facing >> 9) & 7;
        speed_component = (*(s16 *)((u8 *)(((s8 *)dirStepX)) + (direction * 2))) * 0x30000;
        motion->unk_0C = speed_component + (speed_component >> 2);
        speed_component = (*(s16 *)((u8 *)(((s8 *)dirStepY)) + (direction * 2))) * 0x30000;
        motion->unk_10 = speed_component + (speed_component >> 2);
    }

    if (((sprite->unk_04.as_s8 == 3) &&
         (sprite->unk_14.at00_u16.v & 0x1000)) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, actor->facing, 1);
    }

    if (((sprite->unk_04.as_s8 == 5) &&
         (sprite->unk_14.at00_u16.v & 0x1000)) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        motion->unk_0C =
            ((((sprite->unk_24 << 6) + 0x20) << 16) -
             motion->x.v) / action->unk_96.s;
        motion->unk_10 =
            ((((sprite->unk_25 << 6) + 0x20) << 16) -
             motion->y.v) / action->unk_96.s;
    }

    if ((action->unk_96.s <= 0) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        action->unk_9B += 1;
        return;
    }
    return;

state3:
    if ((action->unk_96.s <= 0) ||
        (sprite->unk_14.at00_u16.v & 0x8000)) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        func_800AD594(actor, 0x100);
        action->unk_8C = &D_80170E54;
        dungeonStatus.unk_0C = 0;
        action->unk_98 &= 0xFFF7;
        func_800A4ACC(actor);
        if (actor->unk_6D == 0) {
            actor->unk_46 &= 0x7FFF;
            return;
        }
        D_800E3DE8[0] = (u8 *)actor - 0x20;
    }
    return;

    return;
}
