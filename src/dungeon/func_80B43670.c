#include "modules/dungeon_resource12_slot0.h"

void func_80170E70(void *entity, void *context, void *sprite, void *actor)
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
        func_801713D4(entity, context, sprite, actor);
        return;
    }


    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_25 == 0) {
        func_800AA79C(entity, context, sprite, actor);
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == ((u8 *)D_80175A9C)) {
            return;
        }
        {
            u8 *effects = ((u8 *)D_80175A94);
            (*(void * *)((u8 *)sprite + (0x2C))) = effects;
            func_80047784(
                sprite,(u8)(effects[((gameWork.view.viewAngle + ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A + 0x100) >> 9) & 7]),
                0);
        }
        return;
    }

    if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x200) {
        if (((R12_80170E70_S_80170E70_2 *)sprite)->unk_2C == ((u8 *)D_80175A9C)) {
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A = 13;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_9B = 1;
            ((R12_80170E70_S_80170E70_0 *)entity)->unk_8C = 0;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(entity, context, sprite, ((u8 *)D_80175A94)) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x100) {
            func_800AA258(entity, context, sprite, actor);
            return;
        }

        current_state = ((R12_80170E70_S_80170E70_0 *)entity)->unk_9A;
        next_state = 14;
        if (current_state != next_state) {
            u8 *effect = ((u8 *)D_80175A54);

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
            if (func_800AA6B4(entity, context, sprite, ((u8 *)D_80175A5C)) != 0) {
                return;
            }
        }

        if (((R12_80170E70_S_80170E70_1 *)actor)->unk_1C & 0x80000) {
            func_800AA888(entity, context, sprite, actor);
            func_80173D64(entity, context, sprite, actor);
            return;
        }

        if ((s16)func_800A1C58(actor) != 0) {
            if ((s16)func_800AAB10(entity, context, sprite, actor) != 0) {
                func_8017526C(entity, context, sprite, actor);
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
            func_8017162C(entity, context, sprite, actor);
            return;
        }

        action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(
                        actor, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(entity, context, sprite, 0) == 0) {
                return;
            }
            action_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 | 0x4000;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8017162C(entity, context, sprite, actor);
                return;
            }
        }

        action_index = (((R12_80170E70_S_80170E70_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
            if ((s16)func_80171DD8(entity, context, sprite, actor) != 0) {
                return;
            }
            func_80171F9C(entity, context, sprite, actor);
            return;

        case 4:
        case 5:
        case 6:
            target_angle = ((s16)func_800A0818(
                ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v, ((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &path_distance));
            owner = D_800814A8;
            ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = target_angle;
            if (owner->unk_9A == 0x11) {
                func_800AAF00(entity, context, sprite, ((u8 *)D_80175A8C), ((u8 *)func_80170E70));
                return;
            }

        case 11:
            func_800A9A0C(actor);
            return;

        case 0:
        case 1:
        case 2:
            func_800AAF00(entity, context, sprite, ((u8 *)D_80175A8C), ((u8 *)func_80170E70));
            return;

        default:
            func_8017162C(entity, context, sprite, actor);
            return;
        }
    }

    actor_flags = ((R12_80170E70_S_80170E70_1 *)actor)->unk_1C;
    if ((actor_flags & 0x2000) == 0) {
        if ((tile_id < 0) ||
            ((D_800E2970[tile_id].flags & 2) == 0)) {
            if ((actor_flags & 0x430) == 0) {
                if ((s16)func_8009FD7C((u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at00.v),(u8)(((R12_80170E70_S_80170E70_2 *)sprite)->unk_24.at01.v),(u8)(D_80082E80.tileX),(u8)(D_80082E80.tileY)) != 0) {
                    ((R12_80170E70_S_80170E70_1 *)actor)->unk_2A = ((s16)func_800A0818(
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
    effect_table = ((u8 *)D_80175A54);
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
