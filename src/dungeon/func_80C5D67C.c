/* Relinked copy of dungeon/func_80B43670 (func_80B43670.c); retail differs only at relocation sites. */
#include "modules/dungeon_resource12_slot0.h"

/* r121_nodonor relink of dungeon/func_80B43670: symbols this copy binds at other addresses. */
void func_801533E0(void *controller, void *context, void *entity, void *path_state);
extern u8 D_80156DB4[];
extern u8 D_80156DAC[];
extern u8 D_80156D4C[];
extern u8 D_80156D54[];
void func_80155D94(R12_80173D64_Actor *actor, s32 action, R12_80173D64_Entity *entity, R12_80173D64_MapObject *map_object);
void func_8015652C(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
s32 func_801540C0(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
s32 func_80153DE4(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, EntityRec *actor);
void func_80153FA8(void *action_state, void *action_context, void *sprite, EntityRec *actor);
void func_80153FA8(void *action_state, void *action_context, void *sprite, EntityRec *actor);
extern u8 D_80156D94[];
void func_80153638(void *move_data, void *context, void *position_data, void *actor_data);

void func_80152E7C(void *entity, void *context, void *sprite, void *actor)
{
    u8 *effect_table;
    s32 next_state;
    s16 path_distance;
    s16 target_angle;
    s32 actor_flags;
    s32 action_index;
    s8 tile_id;
    s32 current_state;
    u16 action_flags;
    EntityRec *owner;

    if (dungeonStatus.flags & 0x1000) {
        ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 14;
        func_801533E0(entity, context, sprite, actor);
        return;
    }


    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_25 == 0) {
        dungeonAdvanceActorPendingAction(entity, context, sprite, actor);
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == ((u8 *)D_80156DB4)) {
            return;
        }
        {
            u8 *effects = ((u8 *)D_80156DAC);
            (*(void * *)((u8 *)sprite + (0x2C))) = effects;
            func_80047784(
                sprite,(u8)(effects[((gameWork.view.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                0);
        }
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == ((u8 *)D_80156DB4)) {
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 13;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9B = 1;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_8C = 0;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (dungeonResetActorActionState(entity, context, sprite, ((u8 *)D_80156DAC)) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x100) {
            dungeonBeginPushedActorMove(entity, context, sprite, actor);
            return;
        }

        current_state = ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A;
        next_state = 14;
        if (current_state != next_state) {
            u8 *effect = ((u8 *)D_80156D4C);

            if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C != effect) {
                (*(void * *)((u8 *)sprite + (0x2C))) = effect;
                func_80047784(
                    sprite,(u8)(effect[((gameWork.view.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                    0);
            }
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = next_state;
        }

        ((R12_80170E70_S_80170E70_0 *)entity)->unk_98 &= 0xFFF3;
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_64 != 0) {
            if (dungeonBeginReadyActorDirectionalAction(entity, context, sprite, ((u8 *)D_80156D54)) != 0) {
                return;
            }
        }

        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            func_800AA888(entity, context, sprite, actor);
            func_80155D94(entity, context, sprite, actor);
            return;
        }

        if ((s16)func_800A1C58(actor) != 0) {
            if ((s16)dungeonProcessSelectedActorRecord(entity, context, sprite, actor) != 0) {
                func_8015652C(entity, context, sprite, actor);
            }
        }
    }

    tile_id = ((s8)func_8009FB34((u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v),(u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v)));
    ((R12_80170E70_S_80170E70_2 *)sprite)->unk_26 = tile_id;

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_6D > 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x20) {
            func_800A9A0C(actor);
            return;
        }
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80153638(entity, context, sprite, actor);
            return;
        }

        action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)dungeonCheckEntityRelation(
                        actor, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801540C0(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_80153638(entity, context, sprite, actor);
                return;
            }
        }

        action_index = (((R12_80170E70_S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_80153DE4(entity, context, sprite, actor) != 0) {
                return;
            }
            func_80153FA8(entity, context, sprite, actor);
            return;

        case 4:
        case 5:
        case 6:
            target_angle = ((s16)dungeonGetRoundedFacingAndRoundingFlag(
                ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v, ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &path_distance));
            owner = D_800814A8;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = target_angle;
            if (owner->unk_9A == 0x11) {
                dungeonBeginActorSpellAction(entity, context, sprite, ((u8 *)D_80156D94), ((u8 *)func_80152E7C));
                return;
            }

        case 11:
            func_800A9A0C(actor);
            return;

        case 0:
        case 1:
        case 2:
            dungeonBeginActorSpellAction(entity, context, sprite, ((u8 *)D_80156D94), ((u8 *)func_80152E7C));
            return;

        default:
            func_80153638(entity, context, sprite, actor);
            return;
        }
    }

    actor_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((D_800E2970[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                if ((s16)dungeonCompareMonsterNeighborValues((u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v),(u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v),(u8)(D_80082E80.tileX),(u8)(D_80082E80.tileY)) != 0) {
                    ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = ((s16)dungeonGetRoundedFacingAndRoundingFlag(
                        ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v, ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY, &path_distance));
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    effect_table = ((u8 *)D_80156D4C);
    if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == effect_table) {
        return;
    }
    {
        u8 *effects = effect_table;
        (*(void * *)((u8 *)sprite + (0x2C))) = effects;
        func_80047784(
            sprite,(u8)(effects[((gameWork.view.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
            0);
    }
}
