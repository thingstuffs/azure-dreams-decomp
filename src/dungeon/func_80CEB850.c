#include "modules/dungeon_ovl_7f469800_p07.h"

/* Updates actor state, directional animations, and the shared activity count. */
void dungeonUpdateActorActivityState(void *task, s32 task_id, void *sprite_in, void *actor_in) {
    u8 *next_anim_table;
    u8 *old_anim_table;
    void *starting_task;
    void *actor;
    s32 flags;
    s32 state;
    s32 kind;
    s8 floor;

    actor = actor_in;
    state = ((T_80175050_S_80175050_0 *)task)->unk_9B;
    switch (state) {
    case 0:
        if (!(((T_80175050_S_80175050_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E54;
            func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E54))->unk_00, 0);
            break;
        case 14:
            ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E5C;
            func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E5C))->unk_00, 0);
            break;
        case 15:
            ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E64;
            func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                + 0x100) >> 9) & 7) + (unsigned long)D_80175E64))->unk_00, 0);
            break;
        }
        starting_task = task;
        ((T_80175050_S_80175050_3 *)((u8 *)(&dungeonStatus)))->unk_0A--;
        ((T_80175050_S_80175050_4 *)starting_task)->unk_9B++;
        func_80171BEC_returning(starting_task, task_id, sprite_in);
        return;

    case 1:
        kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
        switch (kind) {
        case 13:
            old_anim_table = ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E54;
            if (old_anim_table != next_anim_table) {
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 14:
            old_anim_table = ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E5C;
            if (old_anim_table != next_anim_table) {
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        case 15:
            old_anim_table = ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C;
            next_anim_table = D_80175E64;
            if (old_anim_table != next_anim_table) {
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = next_anim_table;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)next_anim_table))->unk_00, 0);
            }
            break;
        }

        if ((func_80042900(actor, 1) << 16) == 0) {
            kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C))->unk_00, 0);
                break;
            case 14:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C + 8;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C + 8))->unk_00, 0);
                break;
            case 15:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E7C;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E7C))->unk_00, 0);
                break;
            }
        } else {
            if (dungeonStatus.flags & 0x1000) {
                return;
            }
            if (((T_80175050_S_80175050_2 *)actor)->unk_64 != 0 && dungeonBeginReadyActorDirectionalAction(task, task_id, sprite_in, 0) != 0) {
                return;
            }
            if (((T_80175050_S_80175050_2 *)actor)->unk_25 == 0) {
                if (dungeonStatus.flags & 0x2008) {
                    return;
                }
                dungeonAdvanceActorPendingAction(task, task_id, sprite_in, actor);
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                return;
            }
            flags = ((T_80175050_S_80175050_2 *)actor)->unk_1C;
            if (flags & 0x100) {
                dungeonBeginPushedActorMove(task, task_id, sprite_in, actor);
                return;
            }
            if (flags & 0x80000) {
                func_800AA888(task, task_id, sprite_in, actor);
                dungeonUpdateDirectionalActionDisplay(task, task_id, sprite_in, actor);
                return;
            }
            if (((T_80175050_S_80175050_2 *)actor)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                if ((dungeonCheckEntityRelation(actor, *(u8 **)(((u8 *)D_800814A8) + 0x58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *player;
                player = &D_80082E80;
                floor = ((T_80175050_S_80175050_1 *)sprite_in)->unk_26;
                if ((floor == player->unk_026 && floor >= 0) || dungeonGetTileChebyshevDistance(player, sprite_in) < 2) {
                    if (!(func_800A6D30() & 7)) {
                        func_80042B68(actor, 1);
                    }
                }
            }

            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
            kind = ((T_80175050_S_80175050_2 *)actor)->unk_48;
            switch (kind) {
            case 13:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E6C;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E6C))->unk_00, 0);
                break;
            case 14:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E74;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E74))->unk_00, 0);
                break;
            case 15:
                ((T_80175050_S_80175050_1 *)sprite_in)->unk_2C = D_80175E7C;
                func_80047784(sprite_in, ((T_80175050_S_80175050_3 *)((((gameWork.view.viewAngle + ((T_80175050_S_80175050_2 *)actor)->unk_2A
                    + 0x100) >> 9) & 7) + (unsigned long)D_80175E7C))->unk_00, 0);
                break;
            }
        }

        if (((T_80175050_S_80175050_1 *)sprite_in)->unk_14 & 0x8000) {
            ((T_80175050_S_80175050_0 *)task)->unk_8C = dungeonUpdateActorBehavior;
            return;
        }
        ((T_80175050_S_80175050_3 *)((u8 *)(&dungeonStatus)))->unk_0A++;
        ((T_80175050_S_80175050_0 *)task)->unk_9B++;

        return;

    case 2:
        if (((T_80175050_S_80175050_1 *)sprite_in)->unk_14 & 0xE000) {
            ((T_80175050_S_80175050_3 *)((u8 *)(&dungeonStatus)))->unk_0A--;
            ((T_80175050_S_80175050_0 *)task)->unk_8C = dungeonUpdateActorBehavior;
        }
        return;

    default:
        return;
    }

    return;
}
