#include "modules/dungeon_resource17_slot0.h"

void func_801713A8(void *actor, void *context, void *sprite, EntityRec *status)
{
    s32 distance;
    u32 flags;
    s32 action_index;
    s8 tile_index;
    u16 action_flags;
    void *resume_handler;

    if (dungeonStatus.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        advanceEntityAlongPath(actor, context, sprite, status);
        return;
    }

    if (status->tileY == 0) {
        dungeonAdvanceActorPendingAction(actor, context, sprite, status);
        if (((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C == ((u8 *)D_801744FC)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801744EC);
        func_80047784(
            sprite,(u8)(((u8 *)D_801744EC)[((gameWork.view.viewAngle + status->facing + 0x100) >> 9) & 7]),
            0);
        return;
    }

    if (((u32)status->flags1C) & 0x200) {
        if (((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C == ((u8 *)D_801744FC)) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 13;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 2;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            status->flags1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(actor, context, sprite, ((u8 *)D_801744EC)) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((u32)status->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(actor, context, sprite, status);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 14) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 14;
        }

        if ((((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C != ((u8 *)D_80174494)) &&
            (((R17_801713A8_S_801713A8_2 *)sprite)->unk_2C != ((u8 *)D_8017449C))) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_8017449C);
            func_80047784(
                sprite,(u8)(((u8 *)D_8017449C)[((gameWork.view.viewAngle + status->facing + 0x100) >> 9) & 7]),
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A8);
        }

        status->flags1C |= 0x40000;
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF7;

        if (status->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor, context, sprite, ((u8 *)D_801744A4)) != 0) {
                return;
            }
        }

        if (((u32)status->flags1C) & 0x80000) {
            func_800AA888(actor, context, sprite, status);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A8 = 0;
            func_80174250(actor, context, sprite, status);
            return;
        }

        if ((s16)func_800A1C58(status) != 0) {
            dungeonProcessSelectedActorRecord(actor, context, sprite, status);
        }
    }

    tile_index = ((s8)func_8009FB34((u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v)));
    ((R17_801713A8_S_801713A8_2 *)sprite)->unk_26 = tile_index;

    if (status->unk_6D > 0) {
        if (((u32)status->flags1C) & 0x20) {
            func_800A9A0C(status);
            return;
        }
        if (((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171A98(actor, context, sprite, status);
            return;
        }
        action_flags = status->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(
                        status, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801724C4(actor, context, sprite, 0) == 0) {
                return;
            }
            action_flags = status->unk_46 | 0x4000;
            status->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_80171A98(actor, context, sprite, status);
                return;
            }
        }

        action_index = (status->unk_46 & 0x3FFF) - 1;
        switch (action_index) {

        case 7:
        case 8:
            if ((s16)func_801721E0(actor, context, sprite, status) != 0) {
                return;
            }
            func_801723A4(actor, context, sprite, status);
            return;

        case 4:
        case 5:
        case 6:
        {
            s16 target_angle;
            EntityRec *active_actor;

            target_angle = ((s16)dungeonGetRoundedFacingAndRoundingFlag((s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY), &distance));
            active_actor = D_800814A8;
            status->facing = target_angle;
            if (active_actor->unk_9A != 0x11) {
                func_800A9A0C(status);
                return;
            }
        }
            resume_handler = (void *)func_801713A8;
            dungeonBeginActorSpellAction(actor, context, sprite, ((u8 *)D_801744D4), resume_handler);
            return;

        case 11:
            func_800A9A0C(status);
            return;

        case 0:
        case 1:
        case 2:
            resume_handler = (void *)func_801713A8;

            dungeonBeginActorSpellAction(actor, context, sprite, ((u8 *)D_801744D4), resume_handler);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_80171A98(actor, context, sprite, status);
            return;
        }
    }

    flags = ((u32)status->flags1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    if ((s16)dungeonCompareMonsterNeighborValues((u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(u8)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v),(u8)(D_80082E80.tileX),(u8)(D_80082E80.tileY)) == 0) {
        return;
    }
    status->facing = ((s16)dungeonGetRoundedFacingAndRoundingFlag((s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at00.v),(s16)(((R17_801713A8_S_801713A8_2 *)sprite)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY), &distance));
}
