#include "modules/dungeon_resource07_slot0.h"

void dungeonCompleteStagedDestinationMovement(R07_8017284C_S_8017284C_0 *action, EntityRec *motion, Rec_D_80082E80 *sprite, EntityRec *actor)
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
    switch (state) {
    case 0:
        if (sprite->unk_14.at00_u16.v & 0x8000) {
            action->unk_9B = 3;
            action->unk_96.s = 0;
            sprite->unk_14.at00_u16.v |= 0x6000;
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
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
        sprite->unk_2C.as_pv = ((u8 *)D_80174140);
        func_80047784(sprite,
            (*(u8 *)((u8 *)(((u8 *)D_80174140)) + (((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7))),
            0);
        action->unk_96.s = 0;
        action->unk_9B += 1;
        return;

    case 1:
        x_velocity = motion->unk_0C;
        y_velocity = motion->unk_10;
        motion->unk_0C = x_velocity - (x_velocity >> 2);
        motion->unk_10 = y_velocity - (y_velocity >> 2);
        if (sprite->unk_14.at00_u16.v & 0xE000) {
            sprite->unk_2C.as_pv = ((u8 *)D_80174170);
            func_80047784(sprite,
                (*(u8 *)((u8 *)(((u8 *)D_80174170)) + (((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7))),
                0);
            action->unk_96.s = 0x14;
            action->unk_9B += 1;
            return;
        }
        return;

    case 2:
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
            dungeonResolveAttackDamageAndEffects(actor, sprite, actor->facing, 1);
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

    case 3:
        if ((action->unk_96.s <= 0) ||
            (sprite->unk_14.at00_u16.v & 0x8000)) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion, sprite->unk_24, sprite->unk_25);
            dungeonReduceActorFoodMeter(actor, 0x100);
            action->unk_8C = ((void *)func_80170E54);
            dungeonStatus.unk_0C = 0;
            action->unk_98 &= 0xFFF7;
            dungeonAdvanceStatusTimers(actor);
            if (actor->unk_6D == 0) {
                actor->unk_46 &= 0x7FFF;
                return;
            }
            ((void * *)D_800E3DE8)[0] = (u8 *)actor - 0x20;
        }
    }
}
