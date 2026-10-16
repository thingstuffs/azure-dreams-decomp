#include "modules/dungeon_resource17_slot0.h"

void updateStagedMovementAndDirection(void *action, void *motion, void *sprite, void *actor)
{
    s32 step_x;
    s32 step_y;
    s32 phase_ticks;
    s32 state;
    s32 dir_offset;
    s32 rise;
    s32 target;
    s32 current;
    void *turn_actor;
    u16 flags;
    u8 *dir_x;
    u8 *dir_y;

    dir_x = ((u8 *)dirStepX);
    dir_offset = (F16(actor, 0x2A) >> 8) & 0xE;
    step_x = *(s16 *)(dir_x + dir_offset);
    dir_y = ((u8 *)dirStepY);
    step_y = *(s16 *)(dir_y + dir_offset);
    state = F8(action, 0x9B);
    F16(action, 0x96)--;

    switch (state) {
    case 0:
        flags = F16(sprite, 0x14);
        turn_actor = actor;
        if (flags & 0x8000) {
            F8(action, 0x9B) = 0xFF;
            F16(sprite, 0x14) |= 0x6000;
            dungeonResolveAttackDamageAndEffects(turn_actor, sprite,(s16)(FS16(turn_actor, 0x2A)),(s16)(1));
            return;
        }
        if (!(flags & 0xE000))
            return;
        FPTR(sprite, 0x2C) = ((u8 *)D_801744B4);
        func_80047784(sprite, ((u8 *)D_801744B4)[((gameWork.view.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F32(motion, 0xC) = (-step_x) << 18;
        F32(motion, 0x10) = (-step_y) << 18;
        F16(action, 0x98) |= 8;
        F32(actor, 0x1C) &= 0xF7FFFFFF;
        F32(actor, 0x1C) &= 0xFFFBFFFF;
        F16(action, 0x96) = 4;
        F32(motion, 0x14) = 0xFFFE8000;
        F8(action, 0x9B)++;
        return;

    case 1:
        rise = F32(motion, 0x14);
        F32(motion, 0x14) = rise + (rise >> 2);
        if (FS16(action, 0x96) > 0)
            return;
        F16(action, 0x96) = 8;
        F8(action, 0x9B)++;
        return;

    case 2:
        F32(motion, 0xC) -= F32(motion, 0xC) >> 3;
        F32(motion, 0x10) -= F32(motion, 0x10) >> 3;
        F32(motion, 0x14) -= F32(motion, 0x14) >> 3;
        phase_ticks = 4;
        if (FS16(action, 0x96) == phase_ticks) {
            F32(motion, 0xC) = 0;
            F32(motion, 0x10) = 0;
            F32(motion, 0x14) = 0;
            FPTR(sprite, 0x2C) = ((u8 *)D_801744BC);
            func_80047784(sprite, ((u8 *)D_801744BC)[((gameWork.view.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        }
        if (FS16(action, 0x96) > 0)
            return;
        if (!(F16(sprite, 0x14) & 0xE000))
            return;
        F16(action, 0x96) = phase_ticks;
        F32(motion, 0xC) = (step_x << 18) + (step_x << 17);
        F32(motion, 0x10) = (step_y << 18) + (step_y << 17);
        FPTR(sprite, 0x2C) = ((u8 *)D_801744C4);
        func_80047784(sprite, ((u8 *)D_801744C4)[((gameWork.view.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F8(action, 0x9B)++;
        return;

    case 3:
        F32(action, 0x90) += 0x80000;
        F32(motion, 0xC) += step_x << 18;
        F32(motion, 0x10) += step_y << 18;
        if (FS16(action, 0x96) == 2) {
            func_800A56E0(0x809);
        }
        turn_actor = actor;
        if (FS16(action, 0x96) > 0)
            return;
        dungeonResolveAttackDamageAndEffects(turn_actor, sprite,(s16)(FS16(turn_actor, 0x2A)),(s16)(1));

        F8(action, 0x9B)++;
        return;

    case 4:
        F32(action, 0x90) += 0x80000;
        if (!(F16(sprite, 0x14) & 0xE000))
            return;
        FPTR(sprite, 0x2C) = ((u8 *)D_801744CC);
        func_80047784(sprite, ((u8 *)D_801744CC)[((gameWork.view.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        F32(motion, 0x14) = 0;
        F32(action, 0x90) = 0;
        F16(action, 0x98) &= 0xFFF7;
        F32(actor, 0x1C) |= 0x08000000;
        F8(action, 0x9B) = 0xFF;
        return;

    case 0xFF:
        target = F8(sprite, 0x24) << 6;
        current = FS16(motion, 2);
        current -= 0x20;
        target -= current;
        target <<= 15;
        target >>= 1;
        F32(motion, 0xC) = target;
        target = F8(sprite, 0x25) << 6;
        current = FS16(motion, 6);
        current -= 0x20;
        target -= current;
        target <<= 15;
        target >>= 1;
        F32(motion, 0x10) = target;
        if (!(F16(sprite, 0x14) & 0xE000))
            return;
        F32(motion, 0x10) = 0;
        F32(motion, 0xC) = 0;
        F32(actor, 0x1C) |= 0x40000;
        dungeonSetRecordIntegerTileCenter(motion, F8(sprite, 0x24), F8(sprite, 0x25));
        dungeonReduceActorFoodMeter(actor, 0x100);
        FPTR(action, 0x8C) = ((u8 *)func_801713A8);
        dungeonStatus.unk_0C = 0;
        dungeonAdvanceStatusTimers(actor);
        FPTR(sprite, 0x2C) = ((u8 *)D_8017449C);
        func_80047784(sprite, ((u8 *)D_8017449C)[((gameWork.view.viewAngle + FS16(actor, 0x2A) + 0x100) >> 9) & 7], 0);
        if (FS8(actor, 0x6D) == 0) {
            F16(actor, 0x46) &= 0x7FFF;
            return;
        }
        (*(void * *)D_800E3DE8) = (u8 *)actor - 0x20;

        return;
    default:
        return;
    }
}
