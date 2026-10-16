#include "modules/dungeon_resource03_slot0.h"

void func_80170E54(void *controller, void *context, void *entity, EntityRec *actor_state)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        dungeonAdvanceStoredEntityPath(controller, context, entity, actor_state);
        return;
    }

    if (actor_state->tileY == 0) {
        dungeonAdvanceActorPendingAction(controller, context, entity, actor_state);
        if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C != ((u8 *)D_80173CDC)) {
            u8 *early_table = ((u8 *)D_80173CD4);
            void *record = entity;
            entity = (u8 *)entity + 0x2C;
            *(void **)entity = early_table;
            func_80047784(record,
                early_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor_state->flags1C) & 0x200) {
        if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C == ((u8 *)D_80173CDC)) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor_state->flags1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(controller, context, entity, ((u8 *)D_80173CD4))) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)actor_state->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(controller, context, entity, actor_state);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 != 0xE) {
            u8 control_state = 0xE;

            anim_table = ((u8 *)D_80173C7C);
            if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C != anim_table) {
                (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
                func_80047784(entity,
                    anim_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = control_state;
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor_state->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(controller, context, entity, ((u8 *)D_80173C84))) {
                return;
            }
        }

        if (((u32)actor_state->flags1C) & 0x80000) {
            func_800AA888(controller, context, entity, actor_state);
            func_80173A30(controller, context, entity, actor_state);
            return;
        }

        if ((s16)func_800A1C58(actor_state) != 0) {
            dungeonProcessSelectedActorRecord(controller, context, entity, actor_state);
        }
    }

    room_id = func_8009FB34(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v, ((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v);
    ((R03_80170E54_S_80170E54_2 *)entity)->unk_26 = room_id;

    if (actor_state->unk_6D > 0) {
        if (((u32)actor_state->flags1C) & 0x20) {
            func_800A9A0C(actor_state);
            return;
        }
        if (((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            advanceActorPathWithItemSearch(controller, context, entity, actor_state);
            return;
        }
        if (!(actor_state->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(actor_state,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8017207C(controller, context, entity, 0) == 0) {
                return;
            }
            actor_state->unk_46 |= 0x4000;
            if (!(actor_state->unk_46 & 0x8000)) {
                advanceActorPathWithItemSearch(controller, context, entity, actor_state);
                return;
            }
        }

        switch (actor_state->unk_46 & 0x3FFF) {
        case 8:
        case 9:
            if ((s16)dungeonCheckActorTransitionAndStartEffect(controller, context, entity, actor_state) == 0) {
                dungeonStartDirectionalActorEffect(controller, context, entity, actor_state);
                return;
            }
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player_controller;
                s32 direction;

                direction = dungeonGetRoundedFacingAndRoundingFlag((s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v),(s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                    &direction_flags);
                player_controller = D_800814A8;
                actor_state->facing = direction;
                if (player_controller->unk_9A != 0x11) {
                    func_800A9A0C(actor_state);
                    return;
                }
                dungeonBeginActorSpellAction(controller, context, entity, ((u8 *)D_80173CCC), ((void *)func_80170E54));
                return;
            }
        case 12:
            func_800A9A0C(actor_state);
            return;
        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(controller, context, entity, ((u8 *)D_80173CCC), ((void *)func_80170E54));
            return;
        default:
            break;
        }

        advanceActorPathWithItemSearch(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)actor_state->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor_state->flags1C) & 0x430)) {

                if ((s16)dungeonCompareMonsterNeighborValues(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v,
                    ((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v, D_80082E80.tileX,
                    D_80082E80.tileY) != 0) {
                    actor_state->facing = dungeonGetRoundedFacingAndRoundingFlag((s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at00.v),(s16)(((R03_80170E54_S_80170E54_2 *)entity)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                        &direction_flags);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((R03_80170E54_S_80170E54_2 *)entity)->unk_14 & 0x40) {
        return;
    }
    anim_table = ((u8 *)D_80173C7C);
    if (((R03_80170E54_S_80170E54_2 *)entity)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)entity + (0x2C))) = anim_table;
    func_80047784(entity,
        *(u8 *)((u32)(((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
