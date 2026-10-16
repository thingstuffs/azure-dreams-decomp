#include "modules/dungeon_resource10_slot0.h"

void func_801717F4(void *actor_arg, void *context_arg, void *sprite_arg, EntityRec *entity_arg)
{
    s32 direction_aux;
    s32 tile_record;
    u16 action_state;
    u32 initial_flags = dungeonStatus.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171D7C(actor_arg, context_arg, sprite_arg, entity_arg);
        return;
    }


    if (entity_arg->tileY == 0) {
        u8 *animations;

        dungeonAdvanceActorPendingAction(actor_arg, context_arg, sprite_arg, entity_arg);
        if (((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_2C == ((u8 *)D_801759E8)) {
            return;
        }
        animations = ((u8 *)D_801759E0);
        (*(void * *)((u8 *)sprite_arg + (0x2C))) = animations;
        func_80047784(sprite_arg,
            animations[((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity_arg->flags1C) & 0x200) {
        if (((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_2C == ((u8 *)D_801759E8)) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            entity_arg->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (dungeonResetActorActionState(actor_arg, context_arg, sprite_arg, ((u8 *)D_801759E0)) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity_arg->flags1C) & 0x100) {
            dungeonBeginPushedActorMove(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                u8 *animations = ((u8 *)D_80175988);

                if (((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_2C != animations) {
                    (*(void * *)((u8 *)sprite_arg + (0x2C))) = animations;
                    func_80047784(sprite_arg,
                        animations[((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;

        if (entity_arg->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(actor_arg, context_arg, sprite_arg, ((u8 *)D_80175998)) != 0) {
                return;
            }
        }

        if (((u32)entity_arg->flags1C) & 0x80000) {
            func_800AA888(actor_arg, context_arg, sprite_arg, entity_arg);
            func_80174258(actor_arg, context_arg, sprite_arg, entity_arg);
            (*(void * *)((u8 *)sprite_arg + (0x2C))) = ((u8 *)D_80175988);
            func_80047784(sprite_arg,
                ((u8 *)D_80175988)[((gameWork.view.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((s16)func_800A1C58(entity_arg) != 0) {
            if ((s16)dungeonProcessSelectedActorRecord(actor_arg, context_arg, sprite_arg, entity_arg) != 0) {
                func_801751C0(actor_arg, context_arg, sprite_arg, entity_arg);
            }
        }
    }

    tile_record = func_8009FB34(((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at00.v,
        ((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at01.v);
    ((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_26 = tile_record;

    if (entity_arg->unk_6D > 0) {
        if (((u32)entity_arg->flags1C) & 0x20) {
            func_800A9A0C(entity_arg);
            return;
        }
        if (((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171FE8(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }
        if (!(entity_arg->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(entity_arg,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172A94(actor_arg, context_arg, sprite_arg, 0) == 0) {
                return;
            }
            action_state = entity_arg->unk_46 | 0x4000;
            entity_arg->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                func_80171FE8(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
            }
        }

        switch (entity_arg->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_801727B8(actor_arg, context_arg, sprite_arg, entity_arg) != 0) {
                return;
            }
            func_8017297C(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        case 9:
            func_80174798(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s16 direction;

                direction = dungeonGetRoundedFacingAndRoundingFlag((s16)(((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at00.v),(s16)(((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                    &direction_aux);
                player = D_800814A8;
                entity_arg->facing = direction;
                if (player->unk_9A == 0x11) {
                    dungeonBeginActorSpellAction(actor_arg, context_arg, sprite_arg, ((u8 *)D_801759D0), ((void *)func_801717F4));
                    return;
                }
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(entity_arg);
            return;
        case 1:
        case 2:
        case 3:
            dungeonBeginActorSpellAction(actor_arg, context_arg, sprite_arg, ((u8 *)D_801759D0), ((void *)func_801717F4));
            return;
        default:
            func_80171FE8(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }
    }

    if (!(((u32)entity_arg->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) ||
            !(D_800E2970[record_index].flags & 2)) {
            if (!(((u32)entity_arg->flags1C) & 0x430)) {

                if ((s16)dungeonCompareMonsterNeighborValues(
                        ((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at00.v, ((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    entity_arg->facing = dungeonGetRoundedFacingAndRoundingFlag((s16)(((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at00.v),(s16)(((R10_801717F4_S_801717F4_2 *)sprite_arg)->unk_24.at01.v),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                        &direction_aux);
                }
            }
        }
    }
}
